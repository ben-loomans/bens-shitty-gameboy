#define NUM_BUTTONS 7

int buttons[] = {14, 15, 16, 17, 18, 19, 20};
String names[] = {"A", "B", "RIGHT", "DOWN", "UP", "LEFT", "LIGHT"};
enum ButtonFlags {
  A = 0,
  B,
  RIGHT,
  DOWN,
  UP,
  LEFT,
  LIGHT
};

char buttonState, prevButtonState;

void init_buttons() {
  for (int button = 0; button < NUM_BUTTONS; button++) {
    pinMode(buttons[button], INPUT);
  }

  buttonState = prevButtonState = 0;
}

bool update_buttons() {
  prevButtonState = buttonState;
  buttonState = 0;
  for (int i = 0; i < NUM_BUTTONS; i++) {
    
    buttonState |= (digitalRead(buttons[i]) << i);
    
  }

  if (prevButtonState != buttonState) {
    return true;
  } else {
    return false;
  }
}
