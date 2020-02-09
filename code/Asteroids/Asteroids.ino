#include "asteroid_functions.h"
 
void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(21));

  //init_buttons();
  init_lcd();
  asteroidb.set_speed(-2, 1);
  ship.set_speed(0, -4);
}

void loop() {
  clear_buffer();
  asteroidb.draw();
  ship.draw();
  //asteroidb.draw();
  asteroidb.update();
  ship.update();
  update_screen(frame_buffer);
  delay(200);
}
