/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
const int num = 7;
int buttons[] = {14, 15, 16, 17, 18, 19, 20};
String names[] = {"A", "B", "RIGHT", "DOWN", "UP", "LEFT", "LIGHT"};
char buttonState, prevButtonState;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  for (int i = 0; i < num; i++) {
    pinMode(buttons[i], INPUT);
  }

  buttonState = prevButtonState = 0;
}

void printUpdate(char state) {

  String pressed = "";
  
  if (state == 0) {
    pressed = "NONE";
  } else {
  
    for (int i = 0; i < num; i++) {
      
      if ((state & (1 << i)) != 0) {
        pressed += (names[i] + " ");
      }
    }
  }

  Serial.println(pressed);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  prevButtonState = buttonState;
  buttonState = 0;
  for (int i = 0; i < num; i++) {
    
    buttonState |= (digitalRead(buttons[i]) << i);
    
  }

  if (prevButtonState != buttonState) {

    printUpdate(buttonState);
    
  }

  //Serial.println((float)analogRead(20) / 1024);
  
  delay(1);        // delay in between reads for stability
}
