#define PIN_POT A0

#define PIN_DIR 2
#define PIN_STEP 3

#define STEPS_PER_REVOLUTION 200

#define DELAY_TIME_SLOW 2000
#define DELAY_TIME_FAST 1000

void setup() {
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);

  digitalWrite(PIN_DIR, HIGH);    // Clockwise
}

void loop() {
  
  int analogValue = analogRead(PIN_POT);

  int delay_time = map(analogValue, 0, 1023, 400, 1600);
  
  digitalWrite(PIN_STEP, HIGH);
  delayMicroseconds(delay_time);
  digitalWrite(PIN_STEP, LOW);
  delayMicroseconds(delay_time);
}
