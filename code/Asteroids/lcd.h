  #include "lcd_commands.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

//uint8_t screen_buffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
 

#define LCD_H
#define CS_PIN    10
#define SI_PIN    11
#define A0_PIN    12
#define SCL_PIN   13
#define RESET_PIN 21


#define SCL_LOW digitalWrite(13, 0)
#define SCL_HIGH digitalWrite(13, 1)

#define A0_COMM digitalWrite(12, 0)
#define A0_DATA digitalWrite(12, 1)

#define SI_LOW digitalWrite(11, 0)
#define SI_HIGH digitalWrite(11, 1)

#define CS_LOW digitalWrite(10, 0)
#define CS_HIGH digitalWrite(10, 1)

#define RESET_LOW digitalWrite(21, 0)
#define RESET_HIGH digitalWrite(21, 1)

#define DELAY delayMicroseconds(1)


void init_pins() {
  
  pinMode(CS_PIN, OUTPUT);
  pinMode(SI_PIN, OUTPUT);
  pinMode(A0_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  
}

void out(uint8_t data) {
  for (int i = 0; i < 8; i++) {

    SCL_LOW;
    DELAY;
    
    if ((data & (0x80 >> i))) {
      SI_HIGH;
      //Serial.print("1");
    } else {
      SI_LOW;
      //Serial.print("0");
    }
    DELAY;
    
    SCL_HIGH;
    DELAY;
    
  }
}

void send_command(uint8_t data) {
  CS_LOW;
  A0_COMM;
  DELAY;
  
  out(data);
  
  CS_HIGH;
  DELAY;
}

void send_data(uint8_t data) {
  CS_LOW;
  A0_DATA;
  DELAY;
  
  out(data);
  
  CS_HIGH;
  //Serial.println(data, HEX);
  DELAY;
}

void init_lcd() {
  init_pins();
  
  CS_LOW;
  RESET_HIGH;
  RESET_LOW;
  delay(100);
  RESET_HIGH;
  delay(100);

  send_command(INTERNAL_RESET);
  delay(10);
  send_command(LCD_BIAS_NINTH);
  delay(10);
  send_command(COM_OUTPUT_REV);
  delay(10);
  send_command(SET_STARTLINE | 0);
  delay(10);
  send_command(RESISTOR_RATIO | 5);
  delay(10);
  send_command(ELEC_VOL_MODE);
  delay(10);
  send_command(ELEC_VOL_SET | 16);
  delay(10);
  send_command(POWER_MODE_SET | 7);
  delay(10);
  send_command(DISPLAY_ON);
  delay(10);
  send_command(DISPLAY_ALL_ON);
  delay(1000);
  send_command(DISPLAY_ALL_OFF);
}

void update_screen(uint8_t frame_buffer[][SCREEN_WIDTH]) {
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
