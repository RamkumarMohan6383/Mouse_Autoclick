const int sensorPin = A3;
bool lastState = LOW;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool currentState = digitalRead(sensorPin);

  // Rising edge detection
  if (currentState == HIGH && lastState == LOW) {
    Serial.println("CLICK");
    delay(50);   // debounce
  }

  lastState = currentState;
}
