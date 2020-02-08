#include "asteroid_functions.h"

Sprite asteroid(15, 15, 4, 4, med_asteroid_bitmap);
Sprite asteroidb(26, 26, 6, 6, big_asteroid_bitmap);
Sprite ship(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 4, 4, ship_up_bitmap);
 
void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(21));

  init_buttons();
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
