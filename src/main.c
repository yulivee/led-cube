#include <Arduino.h>
#include <pattern.h>
#include <move.h>
#include "main.h"

Snake snake;

void setup() {

   randomSeed(analogRead(A0));

   snake_init( snake, 1, 1, 1, 0, FORTH );

}

void displayPattern ()
{
   //snake_chdir(snake, random(4,9));
   snake_chdir(snake);
}

void loop() {
  // put your main code here, to run repeatedly:
  displayPattern();
}
