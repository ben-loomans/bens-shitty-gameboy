//logic pertaining to writing to the frame buffer

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

uint8_t frame_buffer[SCREEN_HEIGHT/8][SCREEN_WIDTH];

void draw_bit(int x, int y, boolean data) {
  if (data) {
    
    frame_buffer[y / 8][x] |= (1 << (y % 8));
    
  } else {
    
    frame_buffer[y / 8][x] &= ~(1 << (y % 8));
    
  }
  
  return;
}

void draw_square(int x, int y) {
  draw_bit((x << 1), (y << 1), 1);
  draw_bit((x << 1) + 1, (y << 1), 1);
  draw_bit((x << 1), (y << 1) + 1, 1);
  draw_bit((x << 1) + 1, (y << 1) + 1, 1);
}

void draw_byte(int column, int page, uint8_t data, bool transparent) {

  if (transparent) {
    
    frame_buffer[page][column] |= data;
    
  } else {

    frame_buffer[page][column] = data;
    
  }

  return;
}

void draw_page(int page, uint8_t* data, bool transparent) {
  
  for (int column = 0; column < SCREEN_WIDTH; column++) {
    
    draw_byte(column, page, data[column], transparent);
    
  }

  return;
}

void draw_frame(uint8_t data[][SCREEN_WIDTH], bool transparent) {
  
  for (int page = 0; page < SCREEN_HEIGHT / 8; page++) {
    
    draw_page(page, data[page], transparent);
    
  }

  return;
}

void clear_buffer() {
  
  for (int page = 0; page < SCREEN_HEIGHT / 8; page++) {
    
    for (int column = 0; column < SCREEN_WIDTH; column++) {
      
      draw_byte(column, page, 0x00, false);
    
    }
  }
}
