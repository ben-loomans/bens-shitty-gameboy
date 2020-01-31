#include "draw.h"
#include "buttons.h"

extern char buttonState;
extern char frame_buffer[SCREEN_HEIGHT/8][SCREEN_WIDTH];

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

short unsigned int head;
short unsigned int snake_len; 

short unsigned int snake[256][2];
enum Direction snake_dir;

void init_snake() {
  head = 0;
  snake_len = 1;

  snake[0][0] = 128 / 2;
  snake[0][1] = 64 / 2;

  snake_dir = LEFT;
}

void draw_snake() {
  for (int segment = head; segment > head - snake_len; segment--) {
    Serial.print("Drawing bit ");
    Serial.println(segment);
    draw_bit(snake[segment][0], snake[segment][1]);
  }
  
}

void move_snake() {
  switch(snake_dir) {
    case LEFT:
    snake[head + 1][0] = snake[head][0] - 1;
    snake[head + 1][1] = snake[head][1];
    break;
    case RIGHT:
    snake[head + 1][0] = snake[head][0] + 1;
    snake[head + 1][1] = snake[head][1];
    break;
    case UP:
    snake[head + 1][0] = snake[head][0];
    snake[head + 1][1] = snake[head][1] - 1;
    break;
    case DOWN:
    snake[head + 1][0] = snake[head][0];
    snake[head + 1][1] = snake[head][1] + 1;
    break;
  }

  head++;
}

char cherry[2];

void init_cherry() {
  cherry[0] = random(0, 127);
  cherry[1] = random(0, 63);
}

void draw_cherry() {
  draw_bit(cherry[0], cherry[1]);
}

void run_snake() {
  if (update_buttons()) {
    if (buttonState & (1 << LEFT)) {
      snake_dir = Direction.LEFT;
    }
  }
}

void setup() {
  Serial.begin(9600);
  init_buttons();
  init_pins();
  init_lcd();
  //clear_screen();

  randomSeed(analogRead(21));
  init_cherry();
  init_snake();
}

void loop() {
  clear_buffer();
  run_snake();
  update_screen(frame_buffer);
  delay(200);
}
