#include "buttons.h"
#include "lcd.h"
#include "screen_buffer.h"

#define SNAKE_BUF 256

enum SnakeDirection {
  SNAKE_LEFT,
  SNAKE_UP,
  SNAKE_RIGHT,
  SNAKE_DOWN
};

void printlnout(String s) {
  Serial.println(s);
  delay(1);
}

int mod(int value) {
  int mod = value % SNAKE_BUF;
  if (value < 0) {
    mod += SNAKE_BUF;
  }
  return mod;
}

short unsigned int head;
short unsigned int snake_len; 

uint8_t snake[SNAKE_BUF][2];

enum SnakeDirection snake_dir;

void init_snake() {
  printlnout("init snake");
  head = 2;
  snake_len = 3;

  for (int len = 0; len < snake_len; len++) {
    snake[len][0] = (SCREEN_WIDTH >> 2);
    snake[len][1] = (SCREEN_HEIGHT >> 2);
  }

  snake_dir = SNAKE_LEFT;
}

uint8_t cherry[2];

void init_cherry() {
  printlnout("init cherry");
  cherry[0] = random(0, (SCREEN_WIDTH >> 1) - 1);
  cherry[1] = random(0, (SCREEN_HEIGHT >> 1) - 1);
}

void draw_cherry() {
  printlnout("draw cherry");
  draw_square(cherry[0], cherry[1]);
  
}

void set_direction(enum SnakeDirection set_snake_dir) {
  if ((set_snake_dir + snake_dir) % 2 != 0) {

    snake_dir = set_snake_dir;
    
  }
}

void draw_snake() {
  printlnout("draw snake");
  for (int segment = head; segment > (head - snake_len); segment--) {
    
    draw_square(snake[mod(segment)][0], snake[mod(segment)][1]);
    
  }
}

void move_snake() {
  printlnout("move snake");
  switch(snake_dir) {
    case SNAKE_LEFT:
    snake[mod(head + 1)][0] = snake[head][0] - 1;
    snake[mod(head + 1)][1] = snake[head][1];
    break;
    case SNAKE_RIGHT:
    snake[mod(head + 1)][0] = snake[head][0] + 1;
    snake[mod(head + 1)][1] = snake[head][1];
    break;
    case SNAKE_UP:
    snake[mod(head + 1)][0] = snake[head][0];
    snake[mod(head + 1)][1] = snake[head][1] - 1;
    break;
    case SNAKE_DOWN:
    snake[mod(head + 1)][0] = snake[head][0];
    snake[mod(head + 1)][1] = snake[head][1] + 1;
    break;
  }

  head = mod(head + 1);
}

void grow_snake() {
  printlnout("grow snake");
  snake_len += 3;
  return;
}

void eat_cherry() {
  printlnout("eat cherry");
  if (snake[head][0] == cherry[0] && snake[head][1] == cherry[1]) {
    grow_snake();
    init_cherry();
  }
}

bool in_bounds() {
  printlnout("in bounds");
  uint8_t x, y;
  x = snake[head][0];
  y = snake[head][1];
  return ((0 <= x) && (x < (SCREEN_WIDTH >> 1)) && (0 <= y) && (y < (SCREEN_HEIGHT >> 1)));
}

void process_button_input() {
  printlnout("process button input");
  if (get_button_press(LEFT_BUTTON)) {
    set_direction(SNAKE_LEFT);
  }

  if (get_button_press(RIGHT_BUTTON)) {
    set_direction(SNAKE_RIGHT);
  }

  if (get_button_press(UP_BUTTON)) {
    set_direction(SNAKE_UP);
  }

  if (get_button_press(DOWN_BUTTON)) {
    set_direction(SNAKE_DOWN);
  }

  if (get_button_press(A_BUTTON)) {
    grow_snake();
  }
}

void game_begin() {
  printlnout("game begin");
  clear_buffer();

  init_snake();
  init_cherry();
  
  draw_snake();
  draw_cherry();

  update_screen(frame_buffer);
  
  while (!get_button_release(B_BUTTON)) {
    get_button_state();
    delay(100);
  }

  Serial.println("Game Started!");
}

void game_loop() {
  Serial.println("game loop");
  
  clear_buffer();
  draw_snake();
  draw_cherry();
  update_screen(frame_buffer);

  get_button_state();
  process_button_input();

  move_snake();
  eat_cherry();
  
  delay(100);
}

void game_over() {
  Serial.println("game over");
  while (!get_button_press(B_BUTTON)) {
    get_button_state();
    delay(100);
  }
}

void game() {
  printlnout("game");
  game_begin();
  
  while (in_bounds()) {
    game_loop();
  }
  
  game_over();
}
