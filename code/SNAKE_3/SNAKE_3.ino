#include "snake_functions.h"

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(21));

  init_buttons();
  init_lcd();
}

void loop() {
  game();
}
