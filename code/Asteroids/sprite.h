#include "screen_buffer.h"

int mod(int a, int n) {
  int mod = a % n;
  if (a < 0) {
    mod += n;
  }
  return mod;
}

class Sprite {
    int width, height;
    float x, y, v_x, v_y;
    uint8_t *bitmap;
  public:
    Sprite (float s_x, float s_y, int s_width, int s_height, uint8_t* s_bitmap) {
      x = s_x;
      y = s_y;
      width = s_width;
      height = s_height;
      bitmap = s_bitmap;
    };

    void set_bitmap(int s_width, int s_height, uint8_t* s_bitmap) {
       width = s_width;
       height = s_height;
       bitmap = s_bitmap;
    }

    void draw() {
      int a, b;
      for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
          a = mod((int)x + i, SCREEN_WIDTH);
          b = mod((int)y + j, SCREEN_HEIGHT);
          draw_bit(a, b, bitmap[j] & ((1 << width -1) >> i));
          
//          Serial.print(a);
//          Serial.print(" ");
//          Serial.println(b);
//
//          delay(100);
        }
      }
    };

    void set_speed(float vel_x, float vel_y) {
      v_x = vel_x;
      v_y = vel_y;
    }

    void update() {
      x += v_x;
      y += v_y;
      
      if (x < 0) {
        x += SCREEN_WIDTH;
      }

      if (y < 0) {
        y += SCREEN_HEIGHT;
      }

      if (x >= SCREEN_WIDTH) {
        x -= SCREEN_WIDTH;
      }

      if (y >= SCREEN_HEIGHT) {
        y -= SCREEN_HEIGHT;
      }
    }
};
