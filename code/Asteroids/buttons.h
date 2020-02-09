//only logic pertaining to the interpretation of button inputs
//should go here

#define NUM_BUTTONS 7

unsigned int button_pins[NUM_BUTTONS] = {14, 15, 16, 17, 18, 19, 20};
uint8_t button_state, prev_button_state;

enum Buttons {
  BUTTON_A = 0,
  BUTTON_B,
  BUTTON_RIGHT,
  BUTTON_DOWN,
  BUTTON_UP,
  BUTTON_LEFT,
  BUTTON_LIGHT
};

enum Type {
  BUTTON_LOW = 0,
  BUTTON_HIGH,
  BUTTON_PRESS,
  BUTTON_RELEASE,
  BUTTON_CHANGE
};

void init_buttons() {
  for (int button = 0; button < NUM_BUTTONS; button++) {
    
    pinMode(button_pins[button], INPUT);
    
  }
}

void poll_buttons() {
  prev_button_state = button_state;
  button_state = 0;
  
  for (int button = 0; button < NUM_BUTTONS; button++) {
    
    button_state |= (digitalRead(button_pins[button]) << button);
    
  }
}

const int STACK_SIZE = 10;

int button_stack_ptr = 0;
void (*button_stack[STACK_SIZE])();

void pop_button_function() {

  *button_stack[button_stack_ptr];
  if (button_stack_ptr > 0) {
    button_stack_ptr--;
  }
  
}

void push_button_function(void (*button_function)(), enum Buttons button, enum Type type) {

  switch (type) {
    case BUTTON_LOW:
      if (!button_state & (1 << button)) {
        
        button_stack[button_stack_ptr] = button_function;
        button_stack_ptr++;
        
      }
      break;
      
    case BUTTON_HIGH:
      if (button_state & (1 << button)) {

        button_stack[button_stack_ptr] = button_function;
        button_stack_ptr++;
        
      }
      break;
      
    case BUTTON_PRESS:
      if ((button_state ^ prev_button_state) & button_state & (1 << button)) {

        button_stack[button_stack_ptr] = button_function;
        button_stack_ptr++;
       
      }
      break;

    case BUTTON_RELEASE:
      if ((button_state ^ prev_button_state) & prev_button_state & (1 << button)) {

        button_stack[button_stack_ptr] = button_function;
        button_stack_ptr++;
       
      }
      break;

    case BUTTON_CHANGE:
      if ((button_state ^ prev_button_state) & (1 << button)) {

        button_stack[button_stack_ptr] = button_function;
        button_stack_ptr++;
       
      }
      break;
  }
}
