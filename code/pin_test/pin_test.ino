void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(21, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH); //CLOCK
  delay(1000);
  digitalWrite(13, LOW);
  
  digitalWrite(12, HIGH); //A0
  delay(1000);
  digitalWrite(12, LOW);
  
  digitalWrite(11, HIGH); //SERIAL INPUT
  delay(1000);
  digitalWrite(11, LOW);
  
  digitalWrite(10, HIGH); //CHIP SELECT
  delay(1000);
  digitalWrite(10, LOW);
  
  digitalWrite(21, HIGH); //RESET
  delay(1000);
  digitalWrite(21, LOW);
}
