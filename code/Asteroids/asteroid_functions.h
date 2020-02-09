#include "buttons.h"
#include "lcd.h"
#include "sprite.h"

uint8_t ship_up_bitmap[] = {
  0b0110,
  0b1111,
  0b1111,
  0b1001
};

uint8_t ship_down_bitmap[] = {
  0b1111,
  0b1111,
  0b1111,
  0b0110
};

uint8_t ship_left_bitmap[] = {
  0b0111,
  0b1110,
  0b1110,
  0b0111
};

uint8_t ship_right_bitmap[] = {
  0b1110,
  0b0111,
  0b0111,
  0b1110
};

uint8_t big_asteroid_bitmap[] = {
  0b011000,
  0b111100,
  0b111111,
  0b011111,
  0b111110,
  0b011100,
};

uint8_t med_asteroid_bitmap[] = {
  0b0110,
  0b1111,
  0b1111,
  0b0110
};

uint8_t small_asteroid_bitmap[] = {
  0b11,
  0b11
};

Sprite asteroid(15, 15, 4, 4, med_asteroid_bitmap);
Sprite asteroidb(26, 26, 6, 6, big_asteroid_bitmap);
Sprite ship(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 4, 4, ship_up_bitmap);

void game() {

  clear_buffer();
  //asteroid.draw();
  update_screen(frame_buffer);
  delay(1000);
}
