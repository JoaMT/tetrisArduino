#include "LedControl.h"
#include "Keypad.h"
#include "pitches.h"

const byte ROWS = 3; //four rows
const byte COLS = 2; //four columns
//define the cymbols on the buttons of the keypads
const char hexaKeys[ROWS][COLS] = {
  {'2','U'},
  {'B','L'},
  {'1','R'}
};
const byte rowPins[ROWS] = {9, 11, 12}; //connect to the row pinouts of the keypad
const byte colPins[COLS] = {8, 10}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


const int numDevices = 2;      // number of MAX7219s used in this case 2
const long scrollDelay = 50;   // adjust scrolling speed
unsigned long bufferLong [14] = {0};  
const unsigned char scrollTextMenu[] PROGMEM = {" SELECCIONA UN JUEGO  "};
const unsigned char scrollTextMasBrillo[] PROGMEM = {" MAS BRILLO  "};
const unsigned char scrollTextMenosBrillo[] PROGMEM = {" MENOS BRILLO  "};
const unsigned char scrollTextSonidoOff[] PROGMEM = {" SONIDO OFF  "};
const unsigned char scrollTextSonidoOn[] PROGMEM = {" SONIDO ON  "};
const unsigned char scrollTextTetris[] PROGMEM = {" TETRIS  "};
const unsigned char scrollTextSerpiente[] PROGMEM = {" SERPIENTE  "};
const unsigned char scrollTextPong[] PROGMEM = {" PONG  "};
const unsigned char scrollTextFloppy[] PROGMEM = {" LOPPY POINT  "};
const unsigned char scrollTextHasPerdido[] PROGMEM = {" HAS PERDIDO           "};
const unsigned char scrollTextPuntuacion[] PROGMEM = {" PUNTUACION:           "};
//pins for led matrix dataPin clkPin csPin
LedControl lc=LedControl(6,3,7,numDevices);
LedControl lc2=LedControl(2,5,4,numDevices);

//pin for active buzzer
const int buzzer = 13;

const int melodyScaleC[] PROGMEM = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};

const unsigned char font5x7 [] PROGMEM = {      //Numeric Font Matrix (Arranged as 7x font data + 1x kerning data)
    B00000000,  //Space (Char 0x20)
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    3,//cambias el tamaño del espacio entre letras
 
    B01000000,  //!
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B00000000,
    B01000000,
    2,
 
    B10100000,  //"
    B10100000,
    B10100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    4,
 
    B01010000,  //#
    B01010000,
    B11111000,
    B01010000,
    B11111000,
    B01010000,
    B01010000,
    6,
 
    B00100000,  //$
    B01111000,
    B10100000,
    B01110000,
    B00101000,
    B11110000,
    B00100000,
    6,
 
    B11000000,  //%
    B11001000,
    B00010000,
    B00100000,
    B01000000,
    B10011000,
    B00011000,
    6,
 
    B01100000,  //&
    B10010000,
    B10100000,
    B01000000,
    B10101000,
    B10010000,
    B01101000,
    6,
 
    B11000000,  //'
    B01000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    3,
 
    B00100000,  //(
    B01000000,
    B10000000,
    B10000000,
    B10000000,
    B01000000,
    B00100000,
    4,
 
    B10000000,  //)
    B01000000,
    B00100000,
    B00100000,
    B00100000,
    B01000000,
    B10000000,
    4,
 
    B00000000,  //*
    B00100000,
    B10101000,
    B01110000,
    B10101000,
    B00100000,
    B00000000,
    6,
 
    B00000000,  //+
    B00100000,
    B00100000,
    B11111000,
    B00100000,
    B00100000,
    B00000000,
    6,
 
    B00000000,  //,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    3,
 
    B00000000,  //-
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    6,
 
    B00000000,  //.
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    3,
 
    B00000000,  ///
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B00000000,
    6,
 
    B01110000,  //0
    B10001000,
    B10011000,
    B10101000,
    B11001000,
    B10001000,
    B01110000,
    6,
 
    B01000000,  //1
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B01110000,  //2
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    6,
 
    B11111000,  //3
    B00010000,
    B00100000,
    B00010000,
    B00001000,
    B10001000,
    B01110000,
    6,
 
    B00010000,  //4
    B00110000,
    B01010000,
    B10010000,
    B11111000,
    B00010000,
    B00010000,
    6,
 
    B11111000,  //5
    B10000000,
    B11110000,
    B00001000,
    B00001000,
    B10001000,
    B01110000,
    6,
 
    B00110000,  //6
    B01000000,
    B10000000,
    B11110000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B11111000,  //7
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000,
    6,
 
    B01110000,  //8
    B10001000,
    B10001000,
    B01110000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B01110000,  //9
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B00010000,
    B01100000,
    6,
 
    B00000000,  //:
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000,
    3,
 
    B00000000,  //;
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    3,
 
    B00010000,  //<
    B00100000,
    B01000000,
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    5,
 
    B00000000,  //=
    B00000000,
    B11111000,
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    6,
 
    B10000000,  //>
    B01000000,
    B00100000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    5,
 
    B01110000,  //?
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00000000,
    B00100000,
    6,
 
    B01110000,  //@
    B10001000,
    B00001000,
    B01101000,
    B10101000,
    B10101000,
    B01110000,
    6,
 
    B01100000,  //A
    B10010000,
    B10010000,
    B10010000,
    B11110000,
    B10010000,
    B10010000,
    5,
 
    B11100000,  //B
    B10010000,
    B10010000,
    B11100000,
    B10010000,
    B10010000,
    B11100000,
    5,
 
    B01100000,  //C
    B10010000,
    B10000000,
    B10000000,
    B10000000,
    B10010000,
    B01100000,
    5,
 
    B11000000,  //D
    B10100000,
    B10010000,
    B10010000,
    B10010000,
    B10100000,
    B11000000,
    5,
 
    B11110000,  //E
    B10000000,
    B10000000,
    B11100000,
    B10000000,
    B10000000,
    B11110000,
    5,
 
    B11110000,  //F
    B10000000,
    B10000000,
    B11100000,
    B10000000,
    B10000000,
    B10000000,
    5,
 
    B01100000,  //G
    B10010000,
    B10000000,
    B11110000,
    B10010000,
    B10010000,
    B01110000,
    5,
 
    B10010000,  //H
    B10010000,
    B10010000,
    B11110000,
    B10010000,
    B10010000,
    B10010000,
    5,
 
    B11100000,  //I
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B01110000,  //J
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B10100000,
    B01000000,
    5,
 
    B10010000,  //K
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    B10010000,
    5,
 
    B10000000,  //L
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11110000,
    5,
 
    B10001000,  //M
    B11011000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B10001000,  //N
    B10001000,
    B11001000,
    B10101000,
    B10011000,
    B10001000,
    B10001000,
    6,
 
    B01100000,  //O
    B10010000,
    B10010000,
    B10010000,
    B10010000,
    B10010000,
    B01100000,
    5,
 
    B11100000,  //P
    B10010000,
    B10010000,
    B11100000,
    B10000000,
    B10000000,
    B10000000,
    5,
 
    B01110000,  //Q
    B10001000,
    B10001000,
    B10001000,
    B10101000,
    B10010000,
    B01101000,
    6,
 
    B11110000,  //R
    B10001000,
    B10001000,
    B11110000,
    B10100000,
    B10010000,
    B10001000,
    6,
 
    B01110000,  //S
    B10000000,
    B10000000,
    B01100000,
    B00010000,
    B00010000,
    B11100000,
    5,
 
    B11110000,  //T
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    5,
 
    B10010000,  //U
    B10010000,
    B10010000,
    B10010000,
    B10010000,
    B10010000,
    B01100000,
    5,
 
    B10001000,  //V
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    6,
 
    B10001000,  //W
    B10001000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    6,
 
    B10001000,  //X
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    B10001000,
    6,
 
    B10001000,  //Y
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    B00100000,
    B00100000,
    6,
 
    B11111000,  //Z
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B11111000,
    6,
 
    B11100000,  //[
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11100000,
    4,
 
    B00000000,  //(Backward Slash)
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000000,
    6,
 
    B11100000,  //]
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B11100000,
    4,
 
    B00100000,  //^
    B01010000,
    B10001000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    6,
 
    B00000000,  //_
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111000,
    6,
 
    B10000000,  //`
    B01000000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    4,
 
    B00000000,  //a
    B00000000,
    B01110000,
    B00001000,
    B01111000,
    B10001000,
    B01111000,
    6,
 
    B10000000,  //b
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B11110000,
    6,
 
    B00000000,  //c
    B00000000,
    B01110000,
    B10001000,
    B10000000,
    B10001000,
    B01110000,
    6,
 
    B00001000,  //d
    B00001000,
    B01101000,
    B10011000,
    B10001000,
    B10001000,
    B01111000,
    6,
 
    B00000000,  //e
    B00000000,
    B01110000,
    B10001000,
    B11111000,
    B10000000,
    B01110000,
    6,
 
    B00110000,  //f
    B01001000,
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01000000,
    6,
 
    B00000000,  //g
    B01111000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    6,
 
    B10000000,  //h
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B01000000,  //i
    B00000000,
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B00010000,  //j
    B00000000,
    B00110000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    5,
 
    B10000000,  //k
    B10000000,
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    5,
 
    B11000000,  //l
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B00000000,  //m
    B00000000,
    B11010000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    6,
 
    B00000000,  //n
    B00000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B00000000,  //o
    B00000000,
    B01110000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B00000000,  //p
    B00000000,
    B11110000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    6,
 
    B00000000,  //q
    B00000000,
    B01101000,
    B10011000,
    B01111000,
    B00001000,
    B00001000,
    6,
 
    B00000000,  //r
    B00000000,
    B10110000,
    B11001000,
    B10000000,
    B10000000,
    B10000000,
    6,
 
    B00000000,  //s
    B00000000,
    B01110000,
    B10000000,
    B01110000,
    B00001000,
    B11110000,
    6,
 
    B01000000,  //t
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01001000,
    B00110000,
    6,
 
    B00000000,  //u
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B10011000,
    B01101000,
    6,
 
    B00000000,  //v
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    6,
 
    B00000000,  //w
    B00000000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    6,
 
    B00000000,  //x
    B00000000,
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    6,
 
    B00000000,  //y
    B00000000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    6,
 
    B00000000,  //z
    B00000000,
    B11111000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    6,
 
    B00100000,  //{
    B01000000,
    B01000000,
    B10000000,
    B01000000,
    B01000000,
    B00100000,
    4,
 
    B10000000,  //|
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    2,
 
    B10000000,  //}
    B01000000,
    B01000000,
    B00100000,
    B01000000,
    B01000000,
    B10000000,
    4,
 
    B00000000,  //~
    B00000000,
    B00000000,
    B01101000,
    B10010000,
    B00000000,
    B00000000,
    6,
 
    B01100000,  // (Char 0x7F)
    B10010000,
    B10010000,
    B01100000,
    B00000000,
    B00000000,
    B00000000,
    5,
    
    B00000000,  // smiley
    B01100000,
    B01100110,
    B00000000,
    B10000001,
    B01100110,
    B00011000,
    5
};

const byte tetris[7][4][4]={
   {  // cuadrdado                    
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000}, 
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000}
  },

  {   // palo                   
    {B00000000,   
     B11110000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B01000000,    
     B01000000,    
     B01000000}, 
    {B00000000,   
     B11110000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B01000000,    
     B01000000,    
     B01000000}
  },   

  {   // L                   
    {B10000000,   
     B10000000,    
     B11000000,    
     B00000000},
    {B11100000,   
     B10000000,    
     B00000000,    
     B00000000}, 
    {B11000000,   
     B01000000,    
     B01000000,    
     B00000000},
    {B00100000,   
     B11100000,    
     B00000000,    
     B00000000}
  },   

  {  //L invertida                    
    {B01000000,   
     B01000000,    
     B11000000,    
     B00000000},
    {B10000000,   
     B11100000,    
     B00000000,    
     B00000000}, 
    {B11000000,   
     B10000000,    
     B10000000,    
     B00000000},
    {B11100000,   
     B00100000,    
     B00000000,    
     B00000000}
  },   

  { // T                     
    {B01000000,   
     B11100000,    
     B00000000,    
     B00000000},
    {B10000000,   
     B11000000,    
     B10000000,    
     B00000000}, 
    {B11100000,   
     B01000000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B11000000,    
     B01000000,    
     B00000000}
  },   

  { // Z                      
    {B11000000,   
     B01100000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B11000000,    
     B10000000,    
     B00000000}, 
    {B11000000,   
     B01100000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B11000000,    
     B10000000,    
     B00000000}
  },   

  { // Z invertida                     
    {B01100000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B10000000,   
     B11000000,    
     B01000000,    
     B00000000}, 
    {B01100000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B10000000,   
     B11000000,    
     B01000000,    
     B00000000}  
  }
};

bool sound=true;
int luz=0;
int option=0;
unsigned long delaytime1=100;
unsigned long delaytime2=30;
int patallaTetris[17];
int scroll=0;
int juego=0;
int cont=70;
int bCont=100;
byte px[80]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte py[80]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int  pox=4;
int  poy=4;
int  vy=0;
int  vx=1;
int  bx=0;
int  by=0;
int  longitud=3;
int  dif=1;
int  ficha=0;
int  fichaSiguiente=0;
int  rotacion=0;
int  gameSpeed=1;
int  puntuacion=0;
int  level=1; 
bool teclaArriba=false;
bool teclaAbajo=false;
bool teclaIzq=false;
bool teclaDer=false;
    
void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0,false); lc.shutdown(1,false);
  lc2.shutdown(0,false); lc2.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,luz); lc.setIntensity(1,luz);
  lc2.setIntensity(0,luz); lc2.setIntensity(1,luz);
  /* and clear the display */
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0);lc2.clearDisplay(1);

  checkBatt(true);

   musicaFeliz();

   randomSeed(analogRead(0));
}

void checkBatt(boolean infoAllStates) {
  int battRead = analogRead(4);
  //Serial.print(battRead);
  if (infoAllStates and battRead>799) {
      displayLed(5,5,true); displayLed(6,5,true); displayLed(12,5,true); displayLed(11,10,true); displayLed(13,7,true);
      displayLed(5,10,true); displayLed(7,5,true); displayLed(6,10,true); displayLed(12,10,true); displayLed(13,8,true);
      displayLed(4,5,true); displayLed(8,5,true); displayLed(7,10,true); displayLed(12,9,true); displayLed(3,6,true);
      displayLed(4,10,true); displayLed(9,5,true); displayLed(8,10,true); displayLed(12,8,true); displayLed(3,7,true);
      displayLed(3,5,true); displayLed(10,5,true); displayLed(9,10,true); displayLed(12,7,true); displayLed(3,8,true);
      displayLed(3,10,true); displayLed(11,5,true); displayLed(10,10,true); displayLed(12,6,true); displayLed(3,9,true);
      for (int col = 4;col<12;col++) {
        for (int row = 6;row<10;row++) {
          displayLed(col,row,true);
        }
      }
      delay(3000);
  } else if (infoAllStates and battRead>749 and battRead<800) {
      displayLed(5,5,true); displayLed(6,5,true); displayLed(12,5,true); displayLed(11,10,true); displayLed(13,7,true);
      displayLed(5,10,true); displayLed(7,5,true); displayLed(6,10,true); displayLed(12,10,true); displayLed(13,8,true);
      displayLed(4,5,true); displayLed(8,5,true); displayLed(7,10,true); displayLed(12,9,true); displayLed(3,6,true);
      displayLed(4,10,true); displayLed(9,5,true); displayLed(8,10,true); displayLed(12,8,true); displayLed(3,7,true);
      displayLed(3,5,true); displayLed(10,5,true); displayLed(9,10,true); displayLed(12,7,true); displayLed(3,8,true);
      displayLed(3,10,true); displayLed(11,5,true); displayLed(10,10,true); displayLed(12,6,true); displayLed(3,9,true);
      for (int col = 4;col<8;col++) {
        for (int row = 6;row<10;row++) {
          displayLed(col,row,true);
        }
      }
      delay(3000);
  } else if (infoAllStates and battRead>699 and battRead<750) {
      displayLed(5,5,true); displayLed(6,5,true); displayLed(12,5,true); displayLed(11,10,true); displayLed(13,7,true);
      displayLed(5,10,true); displayLed(7,5,true); displayLed(6,10,true); displayLed(12,10,true); displayLed(13,8,true);
      displayLed(4,5,true); displayLed(8,5,true); displayLed(7,10,true); displayLed(12,9,true); displayLed(3,6,true);
      displayLed(4,10,true); displayLed(9,5,true); displayLed(8,10,true); displayLed(12,8,true); displayLed(3,7,true);
      displayLed(3,5,true); displayLed(10,5,true); displayLed(9,10,true); displayLed(12,7,true); displayLed(3,8,true);
      displayLed(3,10,true); displayLed(11,5,true); displayLed(10,10,true); displayLed(12,6,true); displayLed(3,9,true);
      for (int col = 4;col<6;col++) {
        for (int row = 6;row<10;row++) {
          displayLed(col,row,true);
        }
      }
      delay(3000);
  } else if (battRead<700) {
      displayLed(5,5,true); displayLed(6,5,true); displayLed(12,5,true); displayLed(11,10,true); displayLed(13,7,true);
      displayLed(5,10,true); displayLed(7,5,true); displayLed(6,10,true); displayLed(12,10,true); displayLed(13,8,true);
      displayLed(4,5,true); displayLed(8,5,true); displayLed(7,10,true); displayLed(12,9,true); displayLed(3,6,true);
      displayLed(4,10,true); displayLed(9,5,true); displayLed(8,10,true); displayLed(12,8,true); displayLed(3,7,true);
      displayLed(3,5,true); displayLed(10,5,true); displayLed(9,10,true); displayLed(12,7,true); displayLed(3,8,true);
      displayLed(3,10,true); displayLed(11,5,true); displayLed(10,10,true); displayLed(12,6,true); displayLed(3,9,true);
      delay(30000);
      lc.shutdown(0,true); lc.shutdown(1,true);
      lc2.shutdown(0,true); lc2.shutdown(1,true);
      while (battRead < 780){
        battRead = analogRead(4);
        delay(5000);
      }
      lc.shutdown(0,false); lc.shutdown(1,false);
      lc2.shutdown(0,false); lc2.shutdown(1,false);
  }
}

void scrollFont() {
    for (int counter=0x20;counter<0x80;counter++){
        loadBufferLong(counter);
        delay(500);
    }
}

void cuadrado() {
  switch(option){
    case 1:
      displayLed(0,0,true); displayLed(7,0,true); displayLed(1,7,true); displayLed(1,0,true);
      displayLed(0,1,true); displayLed(7,1,true); displayLed(2,7,true); displayLed(2,0,true);
      displayLed(0,2,true); displayLed(7,2,true); displayLed(3,7,true); displayLed(3,0,true);
      displayLed(0,3,true); displayLed(7,3,true); displayLed(4,7,true); displayLed(4,0,true);
      displayLed(0,4,true); displayLed(7,4,true); displayLed(5,7,true); displayLed(5,0,true);
      displayLed(0,5,true); displayLed(7,5,true); displayLed(6,7,true); displayLed(6,0,true);
      displayLed(0,6,true); displayLed(7,6,true); displayLed(7,7,true);
      displayLed(0,7,true);

      displayLed(8,0,false); displayLed(15,0,false); displayLed(9,7,false); displayLed(9,0,false);
      displayLed(8,1,false); displayLed(15,1,false); displayLed(10,7,false); displayLed(10,0,false);
      displayLed(8,2,false); displayLed(15,2,false); displayLed(11,7,false); displayLed(11,0,false);
      displayLed(8,3,false); displayLed(15,3,false); displayLed(12,7,false); displayLed(12,0,false);
      displayLed(8,4,false); displayLed(15,4,false); displayLed(13,7,false); displayLed(13,0,false);
      displayLed(8,5,false); displayLed(15,5,false); displayLed(14,7,false); displayLed(14,0,false);
      displayLed(8,6,false); displayLed(15,6,false); displayLed(15,7,false);
      displayLed(8,7,false);

      displayLed(0,8,false); displayLed(7,8,false); displayLed(1,15,false); displayLed(1,8,false);
      displayLed(0,9,false); displayLed(7,9,false); displayLed(2,15,false); displayLed(2,8,false);
      displayLed(0,10,false); displayLed(7,10,false); displayLed(3,15,false); displayLed(3,8,false);
      displayLed(0,11,false); displayLed(7,11,false); displayLed(4,15,false); displayLed(4,8,false);
      displayLed(0,12,false); displayLed(7,12,false); displayLed(5,15,false); displayLed(5,8,false);
      displayLed(0,13,false); displayLed(7,13,false); displayLed(6,15,false); displayLed(6,8,false);
      displayLed(0,14,false); displayLed(7,14,false); displayLed(7,15,false);
      displayLed(0,15,false);

      displayLed(8,8,false); displayLed(15,8,false); displayLed(9,15,false); displayLed(9,8,false);
      displayLed(8,9,false); displayLed(15,9,false); displayLed(10,15,false); displayLed(10,8,false);
      displayLed(8,10,false); displayLed(15,10,false); displayLed(11,15,false); displayLed(11,8,false);
      displayLed(8,11,false); displayLed(15,11,false); displayLed(12,15,false); displayLed(12,8,false);
      displayLed(8,12,false); displayLed(15,12,false); displayLed(13,15,false); displayLed(13,8,false);
      displayLed(8,13,false); displayLed(15,13,false); displayLed(14,15,false); displayLed(14,8,false);
      displayLed(8,14,false); displayLed(15,14,false); displayLed(15,15,false);
      displayLed(8,15,false);
    break;
    case 3:
      displayLed(0,0,false); displayLed(7,0,false); displayLed(1,7,false); displayLed(1,0,false);
      displayLed(0,1,false); displayLed(7,1,false); displayLed(2,7,false); displayLed(2,0,false);
      displayLed(0,2,false); displayLed(7,2,false); displayLed(3,7,false); displayLed(3,0,false);
      displayLed(0,3,false); displayLed(7,3,false); displayLed(4,7,false); displayLed(4,0,false);
      displayLed(0,4,false); displayLed(7,4,false); displayLed(5,7,false); displayLed(5,0,false);
      displayLed(0,5,false); displayLed(7,5,false); displayLed(6,7,false); displayLed(6,0,false);
      displayLed(0,6,false); displayLed(7,6,false); displayLed(7,7,false);
      displayLed(0,7,false);

      displayLed(8,0,true); displayLed(15,0,true); displayLed(9,7,true); displayLed(9,0,true);
      displayLed(8,1,true); displayLed(15,1,true); displayLed(10,7,true); displayLed(10,0,true);
      displayLed(8,2,true); displayLed(15,2,true); displayLed(11,7,true); displayLed(11,0,true);
      displayLed(8,3,true); displayLed(15,3,true); displayLed(12,7,true); displayLed(12,0,true);
      displayLed(8,4,true); displayLed(15,4,true); displayLed(13,7,true); displayLed(13,0,true);
      displayLed(8,5,true); displayLed(15,5,true); displayLed(14,7,true); displayLed(14,0,true);
      displayLed(8,6,true); displayLed(15,6,true); displayLed(15,7,true);
      displayLed(8,7,true);

      displayLed(0,8,false); displayLed(7,8,false); displayLed(1,15,false); displayLed(1,8,false);
      displayLed(0,9,false); displayLed(7,9,false); displayLed(2,15,false); displayLed(2,8,false);
      displayLed(0,10,false); displayLed(7,10,false); displayLed(3,15,false); displayLed(3,8,false);
      displayLed(0,11,false); displayLed(7,11,false); displayLed(4,15,false); displayLed(4,8,false);
      displayLed(0,12,false); displayLed(7,12,false); displayLed(5,15,false); displayLed(5,8,false);
      displayLed(0,13,false); displayLed(7,13,false); displayLed(6,15,false); displayLed(6,8,false);
      displayLed(0,14,false); displayLed(7,14,false); displayLed(7,15,false);
      displayLed(0,15,false);

      displayLed(8,8,false); displayLed(15,8,false); displayLed(9,15,false); displayLed(9,8,false);
      displayLed(8,9,false); displayLed(15,9,false); displayLed(10,15,false); displayLed(10,8,false);
      displayLed(8,10,false); displayLed(15,10,false); displayLed(11,15,false); displayLed(11,8,false);
      displayLed(8,11,false); displayLed(15,11,false); displayLed(12,15,false); displayLed(12,8,false);
      displayLed(8,12,false); displayLed(15,12,false); displayLed(13,15,false); displayLed(13,8,false);
      displayLed(8,13,false); displayLed(15,13,false); displayLed(14,15,false); displayLed(14,8,false);
      displayLed(8,14,false); displayLed(15,14,false); displayLed(15,15,false);
      displayLed(8,15,false);
    break;
    case 6:
      displayLed(0,0,false); displayLed(7,0,false); displayLed(1,7,false); displayLed(1,0,false);
      displayLed(0,1,false); displayLed(7,1,false); displayLed(2,7,false); displayLed(2,0,false);
      displayLed(0,2,false); displayLed(7,2,false); displayLed(3,7,false); displayLed(3,0,false);
      displayLed(0,3,false); displayLed(7,3,false); displayLed(4,7,false); displayLed(4,0,false);
      displayLed(0,4,false); displayLed(7,4,false); displayLed(5,7,false); displayLed(5,0,false);
      displayLed(0,5,false); displayLed(7,5,false); displayLed(6,7,false); displayLed(6,0,false);
      displayLed(0,6,false); displayLed(7,6,false); displayLed(7,7,false);
      displayLed(0,7,false);

      displayLed(8,0,false); displayLed(15,0,false); displayLed(9,7,false); displayLed(9,0,false);
      displayLed(8,1,false); displayLed(15,1,false); displayLed(10,7,false); displayLed(10,0,false);
      displayLed(8,2,false); displayLed(15,2,false); displayLed(11,7,false); displayLed(11,0,false);
      displayLed(8,3,false); displayLed(15,3,false); displayLed(12,7,false); displayLed(12,0,false);
      displayLed(8,4,false); displayLed(15,4,false); displayLed(13,7,false); displayLed(13,0,false);
      displayLed(8,5,false); displayLed(15,5,false); displayLed(14,7,false); displayLed(14,0,false);
      displayLed(8,6,false); displayLed(15,6,false); displayLed(15,7,false);
      displayLed(8,7,false);

      displayLed(0,8,true); displayLed(7,8,true); displayLed(1,15,true); displayLed(1,8,true);
      displayLed(0,9,true); displayLed(7,9,true); displayLed(2,15,true); displayLed(2,8,true);
      displayLed(0,10,true); displayLed(7,10,true); displayLed(3,15,true); displayLed(3,8,true);
      displayLed(0,11,true); displayLed(7,11,true); displayLed(4,15,true); displayLed(4,8,true);
      displayLed(0,12,true); displayLed(7,12,true); displayLed(5,15,true); displayLed(5,8,true);
      displayLed(0,13,true); displayLed(7,13,true); displayLed(6,15,true); displayLed(6,8,true);
      displayLed(0,14,true); displayLed(7,14,true); displayLed(7,15,true);
      displayLed(0,15,true);

      displayLed(8,8,false); displayLed(15,8,false); displayLed(9,15,false); displayLed(9,8,false);
      displayLed(8,9,false); displayLed(15,9,false); displayLed(10,15,false); displayLed(10,8,false);
      displayLed(8,10,false); displayLed(15,10,false); displayLed(11,15,false); displayLed(11,8,false);
      displayLed(8,11,false); displayLed(15,11,false); displayLed(12,15,false); displayLed(12,8,false);
      displayLed(8,12,false); displayLed(15,12,false); displayLed(13,15,false); displayLed(13,8,false);
      displayLed(8,13,false); displayLed(15,13,false); displayLed(14,15,false); displayLed(14,8,false);
      displayLed(8,14,false); displayLed(15,14,false); displayLed(15,15,false);
      displayLed(8,15,false);
    break;
    case 9:
      displayLed(0,0,false); displayLed(7,0,false); displayLed(1,7,false); displayLed(1,0,false);
      displayLed(0,1,false); displayLed(7,1,false); displayLed(2,7,false); displayLed(2,0,false);
      displayLed(0,2,false); displayLed(7,2,false); displayLed(3,7,false); displayLed(3,0,false);
      displayLed(0,3,false); displayLed(7,3,false); displayLed(4,7,false); displayLed(4,0,false);
      displayLed(0,4,false); displayLed(7,4,false); displayLed(5,7,false); displayLed(5,0,false);
      displayLed(0,5,false); displayLed(7,5,false); displayLed(6,7,false); displayLed(6,0,false);
      displayLed(0,6,false); displayLed(7,6,false); displayLed(7,7,false);
      displayLed(0,7,false);

      displayLed(8,0,false); displayLed(15,0,false); displayLed(9,7,false); displayLed(9,0,false);
      displayLed(8,1,false); displayLed(15,1,false); displayLed(10,7,false); displayLed(10,0,false);
      displayLed(8,2,false); displayLed(15,2,false); displayLed(11,7,false); displayLed(11,0,false);
      displayLed(8,3,false); displayLed(15,3,false); displayLed(12,7,false); displayLed(12,0,false);
      displayLed(8,4,false); displayLed(15,4,false); displayLed(13,7,false); displayLed(13,0,false);
      displayLed(8,5,false); displayLed(15,5,false); displayLed(14,7,false); displayLed(14,0,false);
      displayLed(8,6,false); displayLed(15,6,false); displayLed(15,7,false);
      displayLed(8,7,false);

      displayLed(0,8,false); displayLed(7,8,false); displayLed(1,15,false); displayLed(1,8,false);
      displayLed(0,9,false); displayLed(7,9,false); displayLed(2,15,false); displayLed(2,8,false);
      displayLed(0,10,false); displayLed(7,10,false); displayLed(3,15,false); displayLed(3,8,false);
      displayLed(0,11,false); displayLed(7,11,false); displayLed(4,15,false); displayLed(4,8,false);
      displayLed(0,12,false); displayLed(7,12,false); displayLed(5,15,false); displayLed(5,8,false);
      displayLed(0,13,false); displayLed(7,13,false); displayLed(6,15,false); displayLed(6,8,false);
      displayLed(0,14,false); displayLed(7,14,false); displayLed(7,15,false);
      displayLed(0,15,false);

      displayLed(8,8,true); displayLed(15,8,true); displayLed(9,15,true); displayLed(9,8,true);
      displayLed(8,9,true); displayLed(15,9,true); displayLed(10,15,true); displayLed(10,8,true);
      displayLed(8,10,true); displayLed(15,10,true); displayLed(11,15,true); displayLed(11,8,true);
      displayLed(8,11,true); displayLed(15,11,true); displayLed(12,15,true); displayLed(12,8,true);
      displayLed(8,12,true); displayLed(15,12,true); displayLed(13,15,true); displayLed(13,8,true);
      displayLed(8,13,true); displayLed(15,13,true); displayLed(14,15,true); displayLed(14,8,true);
      displayLed(8,14,true); displayLed(15,14,true); displayLed(15,15,true);
      displayLed(8,15,true);
    break;
  }
}
 
void menu() {
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0);lc2.clearDisplay(1);
  displayLed(1,1,true); displayLed(1,2,true); displayLed(1,3,true); displayLed(2,3,true);
  displayLed(3,1,true); displayLed(4,1,true); displayLed(5,1,true); displayLed(6,1,true);
  displayLed(4,4,true); displayLed(5,4,true); displayLed(5,3,true); displayLed(6,3,true);
  displayLed(1,5,true); displayLed(2,5,true); displayLed(1,6,true); displayLed(2,6,true);
  displayLed(4,6,true); displayLed(5,6,true); displayLed(6,6,true); displayLed(6,5,true);

  displayLed(9,1,true); displayLed(10,1,true); displayLed(11,1,true); displayLed(12,1,true); displayLed(13,1,true); displayLed(14,1,true);
  displayLed(14,2,true); displayLed(14,3,true); displayLed(14,4,true); displayLed(14,5,true); displayLed(14,6,true); displayLed(13,6,true);
  displayLed(12,6,true); displayLed(12,5,true); displayLed(12,4,true); displayLed(12,3,true); displayLed(11,3,true); displayLed(10,3,true);
  displayLed(10,4,true); displayLed(10,6,true);

  displayLed(1,11,true); displayLed(1,12,true); displayLed(1,13,true);
  displayLed(6,9,true); displayLed(6,10,true); displayLed(6,11,true); displayLed(4,12,true); 
  
  displayLed(10,14,true); displayLed(11,14,true); displayLed(12,14,true); displayLed(11,13,true);
  displayLed(9,9,true); displayLed(11,9,true); displayLed(13,9,true);
  displayLed(9,11,true); displayLed(11,11,true); displayLed(13,11,true);
  
  while(juego==0){
    char customKey = customKeypad.getKey();
    switch(customKey){
    case 'U':
        option=1; cuadrado();
        tono(buzzer, NOTE_G5, 50);
        break;
    case 'R': 
        option=3; cuadrado();
        tono(buzzer, NOTE_G5, 50);
        break;
    case 'B':
        option=6; cuadrado();
        tono(buzzer, NOTE_G5, 50);
        break;
    case 'L':
        option=9; cuadrado();
        tono(buzzer, NOTE_G5, 50);
        break;
    case '1':
        juego=option;
        tono(buzzer, NOTE_C6, 50);
        break;
    case 'X':
        if (luz<5) { luz++; }
        tono(buzzer, NOTE_C5, 50);
        lc.setIntensity(0,luz); lc.setIntensity(1,luz);
        lc2.setIntensity(0,luz); lc2.setIntensity(1,luz);
        break;
    case 'Y':
        if (luz>0) { luz--; }
        tono(buzzer, NOTE_C5, 50);
        lc.setIntensity(0,luz); lc.setIntensity(1,luz);
        lc2.setIntensity(0,luz); lc2.setIntensity(1,luz);
        break;
    case '2':
        if (sound) {
          sound=false;

        } else {
          sound=true;
          if (sound){
            tono(buzzer, NOTE_C5, 50);} delay(100); tono(buzzer, NOTE_C5, 50);
        }
        lc.setIntensity(0,luz);
        break;
    }
    delay(scrollDelay);
  }
}

// Scroll Message
void scrollMessage(const unsigned char * messageString) {
    int counter = 0;
    int myChar=0; char customKey = customKeypad.getKey();
    do {
        // read back a char 
        myChar =  pgm_read_byte_near(messageString + counter); 
        if (myChar != 0){
            loadBufferLong(myChar);
        }
        counter++;
    } 
    while (myChar != 0);
}

// Load character into scroll buffer
void loadBufferLong(int ascii){
    if (ascii >= 0x20 && ascii <=0x7f){
        for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font
            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);     // Index into character table to get row data
            unsigned long x = bufferLong [a*2];     // Load current scroll buffer
            x = x | c;                              // OR the new character onto end of current
            bufferLong [a*2] = x;                   // Store in buffer
        }
        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);     // Index into character table for kerning data
        for (byte x=0; x<count;x++){
            rotateBufferLong();
            printBufferLong();
            delay(scrollDelay);
        }
    }
}

// Rotate the buffer
void rotateBufferLong(){
    for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font
        unsigned long x = bufferLong [a*2];     // Get low buffer entry
        byte b = bitRead(x,31);                 // Copy high order bit that gets lost in rotation
        x = x<<1;                               // Rotate left one bit
        bufferLong [a*2] = x;                   // Store new low buffer
        x = bufferLong [a*2+1];                 // Get high buffer entry
        x = x<<1;                               // Rotate left one bit
        bitWrite(x,0,b);                        // Store saved bit
        bufferLong [a*2+1] = x;                 // Store new high buffer
    }
}  
// Display Buffer on LED matrix
void printBufferLong(){
  for (int a=0;a<7;a++){                    // Loop 7 times for a 5x7 font
    unsigned long x = bufferLong [a*2+1];   // Get high buffer entry
    byte y = x;                             // Mask off first character
    lc.setRow(3,a,y);                       // Send row to relevent MAX7219 chip
    x = bufferLong [a*2];                   // Get low buffer entry
    y = (x>>24);                            // Mask off second character
    lc.setRow(2,a,y);                       // Send row to relevent MAX7219 chip
    y = (x>>16);                            // Mask off third character
    lc.setRow(1,a,y);                       // Send row to relevent MAX7219 chip
    y = (x>>8);                             // Mask off forth character
    lc.setRow(0,a,y);                       // Send row to relevent MAX7219 chip
  }
}

void displayLed(int lx2,int ly2, bool state) {
  int lx=ly2; int ly=lx2;
  if (lx>7 && ly<8) {
    lc2.setLed(1,lx-8,ly,state);
  } else
  if (lx<8 && ly>7) {
    lc.setLed(0,lx,ly-8,state);
  } else
  if (lx>7 && ly>7) {
    lc2.setLed(0,lx-8,ly-8,state);
  } else {
    lc.setLed(1,lx,ly,state);
  }
}

void llenaPantalla(byte row){
  lc.setRow(1,0,row); lc.setRow(0,0,row);
  lc.setRow(1,1,row); lc.setRow(0,1,row);
  lc.setRow(1,2,row); lc.setRow(0,2,row);
  lc.setRow(1,3,row); lc.setRow(0,3,row);
  lc.setRow(1,4,row); lc.setRow(0,4,row);
  lc.setRow(1,5,row); lc.setRow(0,5,row);
  lc.setRow(1,6,row); lc.setRow(0,6,row);
  lc.setRow(1,7,row); lc.setRow(0,7,row);
  lc2.setRow(1,0,row); lc2.setRow(0,0,row);
  lc2.setRow(1,1,row); lc2.setRow(0,1,row);
  lc2.setRow(1,2,row); lc2.setRow(0,2,row);
  lc2.setRow(1,3,row); lc2.setRow(0,3,row);
  lc2.setRow(1,4,row); lc2.setRow(0,4,row);
  lc2.setRow(1,5,row); lc2.setRow(0,5,row);
  lc2.setRow(1,6,row); lc2.setRow(0,6,row);
  lc2.setRow(1,7,row); lc2.setRow(0,7,row);
}

void tono(int bp, int nota, int dur){
  if (sound) { tone(bp, nota, dur); }
}

void musicaFeliz() {
  
  llenaPantalla(B11111111);
  tono(buzzer, NOTE_G5, 250); delay(200);
  lc.setColumn(0,0,B00000000); lc.setColumn(1,7,B00000000);
  lc2.setColumn(0,0,B00000000); lc2.setColumn(1,7,B00000000);
  delay(50); 
  tono(buzzer, NOTE_A5, 150); delay(150);
  lc.setColumn(0,1,B00000000); lc.setColumn(1,6,B00000000);
  lc2.setColumn(0,1,B00000000); lc2.setColumn(1,6,B00000000);
  tono(buzzer, NOTE_G5, 200); delay(200);
  lc.setColumn(0,2,B00000000); lc.setColumn(1,5,B00000000);
  lc2.setColumn(0,2,B00000000); lc2.setColumn(1,5,B00000000);
  tono(buzzer, NOTE_F5, 200); delay(200);
  lc.setColumn(0,3,B00000000); lc.setColumn(1,4,B00000000);
  lc2.setColumn(0,3,B00000000); lc2.setColumn(1,4,B00000000);
  tono(buzzer, NOTE_E5, 200); delay(200);
  lc.setColumn(0,4,B00000000); lc.setColumn(1,3,B00000000);
  lc2.setColumn(0,4,B00000000); lc2.setColumn(1,3,B00000000);
  tono(buzzer, NOTE_F5, 200); delay(200);
  lc.setColumn(0,5,B00000000); lc.setColumn(1,2,B00000000);
  lc2.setColumn(0,5,B00000000); lc2.setColumn(1,2,B00000000);
  tono(buzzer, NOTE_E5, 200); delay(200);
  lc.setColumn(0,6,B00000000); lc.setColumn(1,1,B00000000);
  lc2.setColumn(0,6,B00000000); lc2.setColumn(1,1,B00000000);
  tono(buzzer, NOTE_D5, 200); delay(200);
  lc.setColumn(0,7,B00000000); lc.setColumn(1,0,B00000000);
  lc2.setColumn(0,7,B00000000); lc2.setColumn(1,0,B00000000);
  tono(buzzer, NOTE_C5, 400); delay(400);
  tono(buzzer, NOTE_G4, 400); delay(400);
}

void musicaTriste() {
  tono(buzzer, NOTE_A5, 250); delay(200);
  lc.setColumn(1,0,B11111111); lc.setColumn(0,7,B11111111);
  lc2.setColumn(1,0,B11111111); lc2.setColumn(0,7,B11111111);
  delay(50); 
  tono(buzzer, NOTE_AS5, 150); delay(150);
  lc.setColumn(1,1,B11111111); lc.setColumn(0,6,B11111111);
  lc2.setColumn(1,1,B11111111); lc2.setColumn(0,6,B11111111);
  tono(buzzer, NOTE_A5, 200); delay(200);
  lc.setColumn(1,2,B11111111); lc.setColumn(0,5,B11111111);
  lc2.setColumn(1,2,B11111111); lc2.setColumn(0,5,B11111111);
  tono(buzzer, NOTE_G5, 200); delay(200);
  lc.setColumn(1,3,B11111111); lc.setColumn(0,4,B11111111);
  lc2.setColumn(1,3,B11111111); lc2.setColumn(0,4,B11111111);
  tono(buzzer, NOTE_F5, 200); delay(200);
  lc.setColumn(1,4,B11111111); lc.setColumn(0,3,B11111111);
  lc2.setColumn(1,4,B11111111); lc2.setColumn(0,3,B11111111);
  tono(buzzer, NOTE_G5, 200); delay(200);
  lc.setColumn(1,5,B11111111); lc.setColumn(0,2,B11111111);
  lc2.setColumn(1,5,B11111111); lc2.setColumn(0,2,B11111111);
  tono(buzzer, NOTE_F5, 200); delay(200);
  lc.setColumn(1,6,B11111111); lc.setColumn(0,1,B11111111);
  lc2.setColumn(1,6,B11111111); lc2.setColumn(0,1,B11111111);
  tono(buzzer, NOTE_E5, 200); delay(200);
  lc.setColumn(1,7,B11111111); lc.setColumn(0,0,B11111111);
  lc2.setColumn(1,7,B11111111); lc2.setColumn(0,0,B11111111);
  tono(buzzer, NOTE_D5, 400); delay(400);
  tono(buzzer, NOTE_A4, 400); delay(400);
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0); lc2.clearDisplay(1);
}

/*
 * 
 * 
 * TETRIS
 * 
 */

void juegoTetrisStart() {
  bx=5; by=0; rotacion=0; puntuacion=0;
  delaytime2=30; gameSpeed=1; level=1;
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0); lc2.clearDisplay(1);
  juego=2; cont=0; ficha=random(6);
  fichaSiguiente=random(6);
  for(int row=0;row<17;row++) {
   patallaTetris[row]=0;   
  }
  for(int col=0;col<12;col++) {
    bitWrite(patallaTetris[16],15-col,true); 
  }
  for(int row=0;row<17;row++) {
    bitWrite(patallaTetris[row],15-0,true); 
    bitWrite(patallaTetris[row],15-11,true);
  }
  tetrisDebug();
  llenaPantalla(B00000000);
  lc.setColumn(0,2,B11111111); lc2.setColumn(0,2,B11111111);
  pintaSiguienteFicha(true);
}

void tetrisDebug() {
  for(int row=0;row<17;row++) {
    for(int col=0;col<12;col++) {
      if (bitRead(patallaTetris[row],15-col)) {
        Serial.print(F("0"));
      } else {
        Serial.print(F("_"));
      }
    }
    Serial.println(F(";"));
  }
  Serial.println(F(" "));
}

void tecladoTetris() {
  char customKey = customKeypad.getKey();
  switch(customKey){
    case 'U':
      teclaArriba=true; teclaIzq=false; teclaDer=false; teclaAbajo=false;
    break;
    case '1':
      teclaArriba=true; teclaIzq=false; teclaDer=false; teclaAbajo=false;
    break;
    case 'L':
      teclaIzq=true; teclaArriba=false; teclaDer=false; teclaAbajo=false;
    break;
    case 'R':
      teclaDer=true; teclaIzq=false; teclaArriba=false; teclaAbajo=false;
    break;
    case 'B':
      teclaAbajo=true; teclaIzq=false; teclaDer=false; teclaArriba=false;
    break;
    /*case '2':
      tetrisDebug();
      Serial.println(bx);
      Serial.println(by);
      Serial.println(F(" "));*/
    break;
    case '2':
      juego=0; option=0;
      tono(buzzer, NOTE_A4, 50);
    break;
  }
}

void tetrisLineaEffect(int linea){

  for (int col=0;col<10;col++){
    displayLed(col, linea, false);
    tono(buzzer, pgm_read_byte(&melodyScaleC[col]), 50);
    delay(25);
  }
}

void tetrisLinea() {
  
  int clinea=0;
  for(int linea=15;linea>=0;linea--) {
    clinea=0;
    for(int col=1;col<11;col++) {
      if (bitRead(patallaTetris[linea],15-col)) {
         clinea++;
      }
    }
    if (clinea==10) {
      tetrisLineaEffect(linea);
      for(int col=1;col<11;col++) {
        bitWrite(patallaTetris[linea],15-col,false);
      }
      for(int row=linea-1;row>=0;row--) {
        patallaTetris[row+1]=patallaTetris[row];
      } linea++;
      lc.clearDisplay(1); lc.setColumn(0,0,B00000000); lc.setColumn(0,1,B00000000);
      lc2.clearDisplay(1); lc2.setColumn(0,0,B00000000); lc2.setColumn(0,1,B00000000);
      puntuacion++; if (puntuacion%10==0){level++; gameSpeed=level; } pintaPuncuation();
      for(int row=1;row<16;row++) {
        for(int col=1;col<11;col++) {
          if (bitRead(patallaTetris[row],15-col)){
            displayLed(col-1,row,true);
          }
        }
      }
    }
  }
}

void pintaSiguienteFicha(boolean colorea) {
  for(int row=0;row<4;row++) {
    for(int col=0;col<4;col++) {
      if (bitRead(tetris[fichaSiguiente][0][row],7-col)) {
        displayLed(row+13,col+12,colorea);
      }
    }
  }
}

void pintaPuncuation() {
  int cont = 0;
  for (int row = 0; row<16; row++){
    for (int col = 11; col<16; col++){
      cont++;
      if (cont==puntuacion) {
        displayLed(col,row,true);
      }
    }
  }
}

void tetrisFicha(int estado,bool rmv, bool save) {

  for(int row=0;row<4;row++) {
    for(int col=0;col<4;col++) {
      if (bitRead(tetris[ficha][estado][row],7-col)) {
        if (save) { bitWrite(patallaTetris[col+by+1],15-row-bx-1,rmv); }
        displayLed(row+bx,col+by+1,rmv);
      }
    }
  }
}

bool tetrisFichaChoca(int estado, int cx, int cy) {
  bool choca=false;
  for(int row=0;row<4;row++) {
    for(int col=0;col<4;col++) {
      if (bitRead(tetris[ficha][estado][row],7-col)) {
        if (bitRead(patallaTetris[col+cy+1],15-row-cx-1)) { choca=true; }
      }
    }
  }//bitRead(letra[col],row)
  return(choca);
}

void tetrisGame() {

  if(teclaIzq && !tetrisFichaChoca(rotacion,bx-1,by)){
    tetrisFicha(rotacion,false,false); bx--; teclaIzq=false; tetrisFicha(rotacion,true,false);
  }
  if(teclaDer && !tetrisFichaChoca(rotacion,bx+1,by)){
    tetrisFicha(rotacion,false,false); bx++; teclaDer=false; tetrisFicha(rotacion,true,false);
  }
  if(teclaArriba && !tetrisFichaChoca(rotacion+1,bx,by)){
    tono(buzzer, NOTE_C5, 20);
    tetrisFicha(rotacion,false,false);
    if (rotacion<3){ rotacion++; } else { rotacion=0; } teclaArriba=false;
    tetrisFicha(rotacion,true,false);
  }
  if(teclaAbajo){
    tono(buzzer, NOTE_C6, 20);
    if (gameSpeed<12) { gameSpeed=12; } else { gameSpeed=level;} teclaAbajo=false;
  }

  if (++cont>30) {
    cont=0; by++;
    if (tetrisFichaChoca(rotacion,bx,by)) {
      tono(buzzer, NOTE_C5, 50); delay(50); tono(buzzer, NOTE_E5, 50);
      if (by==-2) {
        musicaTriste();
        juego=0; scroll=0; cont=70;
        scrollMessage(scrollTextHasPerdido);
      }
      by--; tetrisFicha(rotacion,true,true); tetrisLinea();
      by=-3; bx=5; rotacion=0; ficha=fichaSiguiente;
      pintaSiguienteFicha(false); fichaSiguiente=random(6);
      pintaSiguienteFicha(true); checkBatt(false);
      gameSpeed=level; tetrisFicha(rotacion,true,false);
    } else {
      by--; tetrisFicha(rotacion,false,false);
      by++; tetrisFicha(rotacion,true,false);
    }
  }
  
  delay(delaytime2/(gameSpeed));
  tecladoTetris();
}

/*
 * 
 * 
 * SNAKE
 * 
 */

void snakeStart() {
  pox=2; vx=1;
  poy=8; vy=0;
  bx=random(16); by=random(16);
  longitud=3; dif=3;
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0); lc2.clearDisplay(1);
  juego=4;
  for(int del=0;del<16;del++) {
    px[del]=0;
    py[del]=0;
  }
}

void snakeGame() {
  if (--bCont < 1 ) { checkBatt(false); bCont=100; }
  
  tecladoSnake();

  if(teclaArriba && vy!=1){ vy=-1; vx=0; teclaArriba=false; }
  if(teclaIzq && vx!=1){ vx=-1; vy=0; teclaIzq=false; }
  if(teclaDer && vx!=-1){ vx=1; vy=0; teclaDer=false; }
  if(teclaAbajo && vy!=-1){ vy=1; vx=0; teclaAbajo=false; }
 
  poy=poy+vy;
  pox=pox+vx;
  if (pox>15 || pox<0 || poy>15 || poy<0){
    musicaTriste();
    juego=0; scroll=0; cont=70;
    scrollMessage(scrollTextHasPerdido);
  }

  px[0]=pox; py[0]=poy;
  for(int del=longitud;del>0;del--) {
    if ((del!=longitud) && px[del]==pox && py[del]==poy) {
      musicaTriste();
      juego=0; scroll=0; cont=70;
      scrollMessage(scrollTextHasPerdido);
    } else {
      px[del]=px[del-1];
      py[del]=py[del-1];
    }
  }

 if (pox==bx && poy==by && longitud<80) {
    buscaPosBolaSnake();
    tono(buzzer, NOTE_G5, 20);
    longitud++; if (longitud==10) { dif=4; }
    if (longitud==20) { dif=5; }
    if (longitud==40) { dif=6; }
  }
  displayLed(px[longitud],py[longitud],false);
  displayLed(px[longitud],py[longitud],false);
  displayLed(px[0],py[0],true);
  displayLed(bx,by,true);
  delay(delaytime1/dif);
  tecladoSnake();
  delay(delaytime1/dif);
  displayLed(bx,by,false);
  tecladoSnake();
  delay(delaytime1/dif);
  tecladoSnake();
  delay(delaytime1/dif);
  displayLed(bx,by,true);
  tecladoSnake();
  delay(delaytime1/dif);
}

void buscaPosBolaSnake() {
  bx=random(15); by=random(15);
  for(int l=0;l<longitud;l++) {
    if (bx==px[l] && by==py[l]) {
      bx=px[longitud]; by=px[longitud]; break;
    } 
  }
}

void tecladoSnake() {
  char customKey = customKeypad.getKey();
  switch(customKey){
    case 'U':
      teclaArriba=true; teclaIzq=false; teclaDer=false; teclaAbajo=false;
    break;
    case 'L':
      teclaIzq=true; teclaArriba=false; teclaDer=false; teclaAbajo=false;
    break;
    case 'R':
      teclaDer=true; teclaIzq=false; teclaArriba=false; teclaAbajo=false;
    break;
    case 'B':
      teclaAbajo=true; teclaIzq=false; teclaDer=false; teclaArriba=false;
    break;
    case '2':
      juego=0; option=0;
      tono(buzzer, NOTE_A4, 50);
    break;
  }
}

/*
 * 
 * 
 * PONG
 * 
 */

void pongStart() {
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0); lc2.clearDisplay(1);
  pox=4; vx=1;
  poy=4; vy=1;
  bx=8; by=8;
  longitud=3; dif=4;
  lc.clearDisplay(0);
  juego=7;
  for(int del=0;del<16;del++) {
    px[del]=0;
    py[del]=0;
  }
}

void pongGame() {
  if (--bCont < 1 ) { checkBatt(false); bCont=100; }
  
  displayLed(bx,by,false);

  if (teclaArriba) { displayLed(0,poy+2,false); poy--; teclaArriba=false; }
  if (teclaAbajo) { displayLed(0,poy-3,false); poy++; teclaAbajo=false; }
  if (poy>13){ poy=13; } if (poy<3){ poy=3; }

  if (bx<1){
    tono(buzzer, NOTE_C6, 20);
    if (by==poy+2 || by==poy+1 ){
      vx=1; vy=1; 
    }
    if (by==poy || by==poy-1){
      vx=1; vy=0;
    }
    if (by==poy-3 || by==poy-2){
      vx=1; vy=-1;
    }
   }
  
  if (bx>14){
    tono(buzzer, NOTE_C5, 20);
    vx=-1; vy=2-random(4);
  }
  if (by>14){ vy=-abs(vy); } if (by<1){ vy=abs(vy); }
  if (bx<0){
    musicaTriste();
    juego=0; scroll=0; cont=70;
    scrollMessage(scrollTextHasPerdido);
  }
  bx=bx+vx;
  by=by+vy;

  if (by>-1 && by<15){
    if (abs(vy)==2) {
      displayLed(15,by-2,false); displayLed(15,by+2,false);
      displayLed(15,by-3,false); displayLed(15,by+3,false);
    } else { 
      displayLed(15,by-2,false); displayLed(15,by+2,false);
    }
    displayLed(15,by,true); displayLed(15,by+1,true); displayLed(15,by-1,true);
  }
  displayLed(0,poy,true); displayLed(0,poy+1,true); displayLed(0,poy-1,true);
  displayLed(0,poy+2,true); displayLed(0,poy-2,true);  displayLed(0,poy-3,true);
  displayLed(bx,by,true);  if (abs(vy)==2) { displayLed(bx+1,by-(vy/2),true); }
  delay(delaytime1/dif);
  tecladoPong(); if (abs(vy)==2) { displayLed(bx+1,by-(vy/2),false); }
  delay(delaytime1/dif);
  tecladoPong(); if (abs(vy)==2) { displayLed(bx+1,by-(vy/2),true); }
  delay(delaytime1/dif);
  tecladoPong(); if (abs(vy)==2) { displayLed(bx+1,by-(vy/2),false); }
  delay(delaytime1/dif);
  tecladoPong(); if (abs(vy)==2) { displayLed(bx+1,by-(vy/2),true); }
  delay(delaytime1/dif);
  tecladoPong(); if (abs(vy)==2) { displayLed(bx+1,by-(vy/2),false); }
}

void tecladoPong() {
  char customKey = customKeypad.getKey();
  switch(customKey){
    case 'U':
      teclaArriba=true; teclaAbajo=false;
    break;
    case 'B':
      teclaAbajo=true; teclaArriba=false;
    break;
    case '2':
      juego=0; option=0;
      tono(buzzer, NOTE_A4, 50);
    break;
  }
}

/*
 * 
 * 
 * SPACE INVADERS
 * 
 */

void juegoSpace() {
  if (--bCont < 1 ) { checkBatt(false); bCont=100; }
  
  tecladoSpace();

  if (pox!=bx) {
    displayLed(pox,14,false);
    displayLed(pox-1,15,false);
    displayLed(pox,15,false);
    displayLed(pox+1,15,false);
    pox=bx;
    displayLed(bx,14,true);
    displayLed(bx-1,15,true);
    displayLed(bx,15,true);
    displayLed(bx+1,15,true);
  }
  
  delay(delaytime1/2);
  tecladoSpace();
  delay(delaytime1/2);
  tecladoSpace(); 
  delay(delaytime1/2);
  tecladoSpace(); 
}

void tecladoSpace() {
  char customKey = customKeypad.getKey();
  switch(customKey){
    case 'R':
      if (bx<14) { bx++; }
    break;
    case 'L':
      if (bx>1) { bx--; }
    break;
    case '2':
      juego=0; option=0;
      tono(buzzer, NOTE_A4, 50);
    break;
  }
}

void juegoSpaceStart() {
  lc.clearDisplay(0); lc.clearDisplay(1);
  lc2.clearDisplay(0); lc2.clearDisplay(1);

  displayLed(3,11,true); displayLed(8,11,true); displayLed(13,11,true); 
  displayLed(2,13,true); displayLed(7,13,true); displayLed(12,13,true); 
  displayLed(3,13,true); displayLed(8,13,true); displayLed(13,13,true); 
  displayLed(4,13,true); displayLed(9,13,true); displayLed(14,13,true); 
  displayLed(2,12,true); displayLed(7,12,true); displayLed(12,12,true); 
  displayLed(3,12,true); displayLed(8,12,true); displayLed(13,12,true);
  displayLed(4,12,true); displayLed(9,12,true); displayLed(14,12,true);
  
  juego=10; bx=7;
}

/*
 * 
 * 
 * LOOP
 * 
 */

void loop() { 
  switch(juego){
    case 0:
        menu();
      break;
    case 1:
        juegoTetrisStart();
      break;
    case 2:
        tetrisGame();
       break;
    case 3:
        snakeStart();
      break;
    case 4:
        snakeGame();
      break;
    case 6:
        pongStart();
      break;
    case 7:
        pongGame();
      break;
   case 9:
        juegoSpaceStart();
      break;
    case 10:
        juegoSpace();
      break;
  }
}
