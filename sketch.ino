int speed = 200;

void setup() {
  Serial.begin(9600);
  DDRD |= 0b11110000; // Configure Pins 4, 5, 6, 7 as OUTPUT
}

void loop() {
  int scannerPins[] = {4, 5, 6, 7, 6, 5};
  int totalSteps = 6;

  for (int i = 0; i < totalSteps; i++) {
    PORTD = (PORTD & 0x0F) | (1 << scannerPins[i]);

    unsigned long startTime = millis();
    while (millis() - startTime < (unsigned long)speed) {
      checkSerialInput();
    }
  }
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read();

    if (inputChar == 'f' || inputChar == 'F') {
      speed -= 50;
      if (speed < 30) speed = 30;
      
      Serial.print("New Speed: ");
      Serial.print(speed);
      Serial.println(" ms");
    } 
    else if (inputChar == 's' || inputChar == 'S') {
      speed += 50;
      if (speed > 1000) speed = 1000;
      
      Serial.print("New Speed: ");
      Serial.print(speed);
      Serial.println(" ms");
    }
  }
}