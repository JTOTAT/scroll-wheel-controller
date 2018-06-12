
// One switch ECU
// LCD Display of choice
// Long pulse over 1 sec. will change the choice
// Short pulse will send X10 of salient choice
// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>
#include <X10Firecracker.h>
#include "Adafruit_Soundboard.h"

#define SFX_TX 5
#define SFX_RX 6
#define SFX_RST 7
//SoftwareSerial portOne(10,11);

SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(2,8); // RX/TX pin 3 = TX, pin 6 = RX (unused)

Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
//char myChar = 'PFAN12345OGG\n';


unsigned long interval=1000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
int timecop = 5; // how many times through 1 sec loop

int val; // new mouse
int encoder0PinA = 11;
int encoder0PinB = 12;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

int buttonApin = 9; // was 10
int X10ALT = 0;
int X10ALT2 = 0;
int var = 0 ;
int var2 = 0;
int cop = 0;
int mcop = 0;
int voicecop = 0;
long Time = 0;  // the last time the output pin was toggled
char* myStrings[12] = {"Call for help","YES","NO","X1 Module","X2 Module","Science Friday"," Tell a Joke","Power TV","CHAN UP","Alexa Music","Alexa News","Call for help"};
void setup(){
 pinMode (encoder0PinA, INPUT); // new m
 pinMode (encoder0PinB, INPUT); //new m
  
   
  ss.begin(9600);
  
  //if (!sfx.reset()) {
 //   Serial.println("Not found");
   // while (1);
  //}
  //Serial.println("SFX board found");


{
  X10.init( 2, 4, 1);
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  pinMode(buttonApin, INPUT_PULLUP); // don't need external resistor
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  mySerial.write("                "); // clear display
  mySerial.write("                ");
   
}}

void loop()
{
 unsigned long currentMillis = millis(); // grab current time
  
 n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
      mcop = 2;
      timecop = 4;
    } else {
      encoder0Pos++;
      mcop = 2;
      timecop = 4;
    }
if (encoder0Pos < 0)
{
  encoder0Pos = 0;
  }
if (encoder0Pos > 11)
{
  encoder0Pos = 11;
  }
  }
  encoder0PinALast = n;

 cop = 0; // cop is to set long or short pulse
 if (mcop == 2) // some thing new has happened
 {

  voicecop = 0;
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  mySerial.write("                "); // clear display
  
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  // mySerial.print(encoder0Pos);
  mySerial.print(myStrings [encoder0Pos]);
 

 mcop = 1; // sets value to pass around above
  }

if (timecop < 2 && voicecop == 0) // play once after interval 
{ 
  // Serial.println(" Do something here ");
 //sfx.playTrack(encoder0Pos); // play salient neumber of audio
 // add output to case below, Alexa or X10
 
 switch (encoder0Pos) {
    case 0: //1
      sfx.playTrack (encoder0Pos);   // play salient neumber of audio        //Help     can't do 0
      // any number can be added to var
      break;
    case 1: //2 Yes
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 2://3 No
      sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 3://4 X1
      sfx.playTrack(encoder0Pos);   // play salient neumber of audio
if (X10ALT == 0) //if OFF turn on
  {
  X10.sendCmd( hcB, (1), cmdOn ); //send X10 command
  X10ALT = 1; 
  goto Breakout;
  }
 if (X10ALT == 1) // if ON turn off
 {
  // sfx.playTrack(var); 
   X10.sendCmd( hcB, (1), cmdOff );
   X10ALT = 0;
 }
      
      break;
    case 4://5 X2 
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio

if (X10ALT2 == 0) //if OFF turn on
  {
  X10.sendCmd( hcB, (2), cmdOn ); //send X10 command
  X10ALT2 = 1; 
  goto Breakout;
  }
 if (X10ALT2 == 1) // if ON turn off
 {
  // sfx.playTrack(var); 
   X10.sendCmd( hcB, (2), cmdOff );
   X10ALT2 = 0;
 }

    
      break;
    case 5://6 Sci Friday
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 6://7 Joke 
      sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 7: //Alexa TV power
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 8: // Alexa Channel UP
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 9:// Music
      sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 10:// news
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 11: //Help

    encoder0Pos = 0;
       sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
 
 /*   case 14:
      // sfx.playTrack(encoder0Pos);   // play salient neumber of audio
      break;
    case 15: // X10 example

  if (X10ALT2 == 0) //if OFF turn on
  {
  X10.sendCmd( hcB, (2), cmdOn ); //send X10 command
  X10ALT2 = 1; 
  goto Breakout;
  }
 if (X10ALT2 == 1) // if ON turn off
 {
  // sfx.playTrack(var); 
   X10.sendCmd( hcB, (2), cmdOff );
   X10ALT2 = 0;
 }
 */
 Breakout:; 
      //sfx.playTrack(4);   // play salient neumber of audio  // can also just assign a number
      //sfx.playTrack(encoder0Pos);   // play salient neumber of audio depending on VAR
      break;      
  }

   delay (1200); // 
  voicecop = 3; // set anti play again
  timecop = 4; //reset countdown
}

  if ((unsigned long)(currentMillis - previousMillis) >= interval) {    // check if "interval" time has passed (1000 milliseconds)
  timecop = timecop -1;   // countdown
  
  mySerial.write(254); // move cursor to beginning of first line // clear 2nd line
  mySerial.write(192);
  mySerial.write("                ");
  mySerial.write(254); // move cursor to beginning of 2nd line
  mySerial.write(192);

  mySerial.print(" Action in ");
  mySerial.print(timecop);
  
   previousMillis = millis();  // save the "current" time
 }
if (timecop < 0)
{timecop = 0;

}


  // all below down not matter -------------------------------------
  //var2 = var + 1;
  //mySerial.print(myStrings [var2]); // show what is next in line

   if (digitalRead(buttonApin) == LOW)
   {cop = 2; // short pulse
   sfx.playTrack(var); // play salient neumber of audio
   delay (1200); // see if long pulse or short
   if (digitalRead(buttonApin) == LOW)  // if still low then long pulse cop = 2 or long pulse
   {
   cop = 1; // long pulse
   var = var + 1; 
   if (var > 15)
   var = 0;
    
    }}
 
{ 
  if (cop == 2)// action for short pulse
  {
   //sfx.playTrack(var); // play salient neumber of audio
   var = var + 1;
   mySerial.write(254); // move cursor to beginning of first line
   mySerial.write(133);
   mySerial.write(" ACTION"); 
   mySerial.write(254); // move cursor to beginning of first line
   mySerial.write(199);
   mySerial.print(var,DEC);
   
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(202);
  if (X10ALT == 0)
  { mySerial.print("ON");}
  if (X10ALT == 1)
  { mySerial.print("OFF");}
  
  /* if (X10ALT == 0)
  {
  
   //sfx.playTrack(var);  
    X10.sendCmd( hcB, (var), cmdOn );
  X10ALT = 1;
  goto Breakout;
  }
 if (X10ALT == 1) 
 {
  // sfx.playTrack(var); 
   X10.sendCmd( hcB, (var), cmdOff );
   X10ALT = 0;
    
 }
 Breakout:; 
 */ 
  var = var - 1; 
 //delay (3000);
    
  }
  }
  } 
  




























