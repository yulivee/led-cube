#include <Arduino.h>
#include <pattern.h>
#include <move.h>
#include "main.h"

int HC595_clockPin=0;   // SH_CP of 74HC595 
int HC595_latchPin=1;   // ST_CP of 74HC595 
int HC595_dataPin=3;    // DS of 74HC595 
int HC595_enablePin=2;  // Not OE of 74HC595
int LED_Pin16= 4;
int LED_Pin17= 5;
int LED_Pin18= 6;
int LED_Pin19= 7;
int LED_Plane[] = {LED_Pin16, LED_Pin17, LED_Pin18, LED_Pin19};
int patternNumber=0;
int numPatterns=sizeof(pattern)/8;
int tickCount=0;
int tickCountMax=50;      // How many times to loop before changing the pattern
unsigned int currentPattern[4];


void setup() {
  // put your setup code here, to run once:
  pinMode( HC595_latchPin,  OUTPUT );
  pinMode( HC595_clockPin,  OUTPUT );
  pinMode( HC595_dataPin,   OUTPUT );
  pinMode( HC595_enablePin, OUTPUT );
  
  pinMode( LED_Pin16, OUTPUT );
  pinMode( LED_Pin17, OUTPUT );
  pinMode( LED_Pin18, OUTPUT );
  pinMode( LED_Pin19, OUTPUT );
  
  digitalWrite(LED_Pin16,HIGH);
  digitalWrite(LED_Pin17,HIGH);
  digitalWrite(LED_Pin18,HIGH);
  digitalWrite(LED_Pin19,HIGH);
//  digitalWrite(HC595_enablePin, LOW);  // Enable Not OE (negative logic)

  patternNumber=0;
  tickCount = tickCountMax;
}

/*
  Protocol for sending the data to the hc595 is as follows:
   (see: http://www.arduino.cc/en/Tutorial/ShiftOut)
   
   "when the clock pin goes from low to high, the shift register
    reads the state of the data pin ... when the latch pin goes
    from low to high the sent data gets moved from the shift
    registers ... to the output pins"
   
   As we have two HC595s chained together, we use a 16 bit input value
*/
void write_74HC595 (unsigned int hc595value) { 
   digitalWrite(HC595_latchPin, LOW);   // ensures LEDs don't light whilst changing values
//   digitalWrite(HC595_enablePin, HIGH); // OE is negative logic
   
   // Shift each 8 bit value in sequence - the two chained HC595s automatically grab
   // the right bits - the first 8 to the first chip, second 8 to the second chip
   shiftOut(HC595_dataPin, HC595_clockPin, LSBFIRST, hc595value);  
   shiftOut(HC595_dataPin, HC595_clockPin, LSBFIRST, (hc595value >> 8));
   
   digitalWrite(HC595_latchPin, HIGH);  // data transferred from shift register to outputs when latch goes LOW->HIGH
//   digitalWrite(HC595_enablePin, LOW);  // re-enable (negative logic again)
}

/*
  Inputs: Array of 4 integers - one for each plane
*/
void display (unsigned int *pPattern)
{
  int i;
  for (i=0; i<4; i++)
  {
    int j;
    for (j=0; j<1500; j++)
    {
      // Slow this down so that there is time for the LEDS to light
      // Experimentation shows that 200+ gives brighter LEDs
      // NB: Do it this way so an empty loop isn't optimised out
      if (j==0)
      {
        digitalWrite(LED_Plane[0], HIGH);
        digitalWrite(LED_Plane[1], HIGH);
        digitalWrite(LED_Plane[2], HIGH);
        digitalWrite(LED_Plane[3], HIGH);
        write_74HC595 (pPattern[i]);
        digitalWrite(LED_Plane[i], LOW);
      }
    }
  }
}

void displayPattern ()
{
  int i;
  // only update it every tick otherwise just display as is
  tickCount--;
  if (tickCount <= 0)
  {
    tickCount = tickCountMax;
    for (i=0; i<4; i++)
    {
      currentPattern[i] = pattern[i*2 + patternNumber*8] * 256 + pattern[i*2 + 1 + patternNumber*8];
    }
    patternNumber++;
    if (patternNumber >= numPatterns)
    {
      patternNumber = 0;
    }
  }
  display(&currentPattern[0]);
}

void loop() {
  // put your main code here, to run repeatedly:
  displayPattern();
}
