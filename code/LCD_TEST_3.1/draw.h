#include "lcd.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

char frame_buffer[SCREEN_HEIGHT/8][SCREEN_WIDTH];

void draw_bit(int x, int y) {
  frame_buffer[y / 8][x] |= (1 << (y % 8));
  
  return;
}

void erase_bit(int x, int y) {
  frame_buffer[y / 8][x] &= ~(1 << (y % 8));
  
  return;
}

void draw_byte(int column, int page, char data) {
  frame_buffer[page][column] = data;
}

void draw_page(int page, char* data) {
  for (int column = 0; column < SCREEN_WIDTH; column++) {
    draw_byte(column, page, data[column]);
  }
}

void draw_frame(char data[][SCREEN_WIDTH]) {
  for (int page = 0; page < SCREEN_HEIGHT / 8; page++) {
    draw_page(page, data[page]);
  }
}

void clear_buffer() {
  for (int page = 0; page < SCREEN_HEIGHT / 8; page++) {
    for (int column = 0; column < SCREEN_WIDTH; column++) {
    draw_byte(column, page, 0x00);
  }
  }
}

void update_screen(char frame_buffer[][SCREEN_WIDTH]) {
  //send_command(DISPLAY_OFF);
  for (int page = 0; page < SCREEN_HEIGHT/8; page++) {
    send_command(SET_PAGE_ADDR | page);
    send_command(UPPER_COL_ADDR | 0);
    send_command(LOWER_COL_ADDR | 0);
    for (int column = 0; column < SCREEN_WIDTH; column++) {
      send_data(frame_buffer[page][column]);
    }
  }
  //send_command(DISPLAY_ON);
}

void clear_screen() {
  send_command(DISPLAY_OFF);
  for (int page = 0; page < SCREEN_HEIGHT/8; page++) {
    send_command(SET_PAGE_ADDR | page);
    send_command(UPPER_COL_ADDR | 0);
    send_command(LOWER_COL_ADDR | 0);
    for (int column = 0; column < SCREEN_WIDTH; column++) {
      send_data(0x0);
    }
  }
  send_command(DISPLAY_ON);
}
