#define PIN_DIR 2
#define PIN_STEP 3

#define STEPS_PER_REVOLUTION 200

#define DELAY_TIME_SLOW 2000
#define DELAY_TIME_FAST 1000

void setup() {
	pinMode(PIN_STEP, OUTPUT);
	pinMode(PIN_DIR, OUTPUT);
}

void loop() {
	digitalWrite(PIN_DIR, HIGH);    // Clockwise

	// Spin motor slowly
	for(int i = 0; i < STEPS_PER_REVOLUTION; i++) {
		digitalWrite(PIN_STEP, HIGH);
		delayMicroseconds(DELAY_TIME_SLOW);
		digitalWrite(PIN_STEP, LOW);
		delayMicroseconds(DELAY_TIME_SLOW);
	}
	delay(1000);
	
	digitalWrite(PIN_DIR, LOW);     // Counterclockwise

	// Spin motor quickly
	for(int i = 0; i < STEPS_PER_REVOLUTION; i++) {
		digitalWrite(PIN_STEP, HIGH);
		delayMicroseconds(DELAY_TIME_FAST);
		digitalWrite(PIN_STEP, LOW);
		delayMicroseconds(DELAY_TIME_FAST);
	}
	delay(1000);
}