//only logic pertaining to the interpretation of button inputs
//should go here

#define NUM_BUTTONS 7

uint8_t button_state, prev_button_state;

unsigned int button_pins[NUM_BUTTONS] = {14, 15, 16, 17, 18, 19, 20};

enum Buttons {
  A_BUTTON = 0,
  B_BUTTON,
  RIGHT_BUTTON,
  DOWN_BUTTON,
  UP_BUTTON,
  LEFT_BUTTON,
  LIGHT_BUTTON
};

void init_buttons() {
  button_state = prev_button_state = 0;
  
  for (int button = 0; button < NUM_BUTTONS; button++) {
    
    pinMode(button_pins[button], INPUT);
    
  }
}

uint8_t get_button_state() {
  prev_button_state = button_state;
  button_state = 0;
  for (int button = 0; button < NUM_BUTTONS; button++) {
    
    button_state |= (digitalRead(button_pins[button]) << button);
    
  }
  
  return button_state;
}

bool get_button_press(enum Buttons button) {

  return (button_state ^ prev_button_state) & button_state & (1 << button);
}

bool get_button_release(enum Buttons button) {
  
  return (button_state ^ prev_button_state) & prev_button_state & (1 << button);
  
}
