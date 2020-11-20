#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver(0x40);

#define PIN_PWM_SERVO1 1
#define PIN_PWM_SERVO2 2

#define PIN_POT A0

#define DELAY_TIME 50

void setup()
{
  Serial.begin(115200);

  pwmServoDriver.begin();
  pwmServoDriver.setPWMFreq(50); // 50 Hz
}

void loop()
{
  int analogValue = analogRead(PIN_POT);
  int angle = map(analogValue, 0, 1023, 0, 180);

  setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, angle);
  setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO2, angle);
  delay(DELAY_TIME);
}

void setPwmSevoDriveServoAngle(Adafruit_PWMServoDriver _pwmServoDriver, int _pinServo, float _angle)
{

  const int COUNTER_WIDTH_MIN = 150; // 0 angle
  const int COUNTER_WIDTH_MAX = 470; // 180 angle

  if (_angle < 0)
    _angle = 0;
  else if (_angle > 180)
    _angle = 180;

  int pulseWidth = map(_angle, 0, 180, COUNTER_WIDTH_MIN, COUNTER_WIDTH_MAX);

  Serial.println(pulseWidth);

  _pwmServoDriver.setPWM(_pinServo, 0, pulseWidth);
}
