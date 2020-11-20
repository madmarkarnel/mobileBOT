#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver(0x40);

#define PIN_PWM_SERVO1 1

#define DELAY_TIME 3000

void setup()
{
    Serial.begin(115200);

    pwmServoDriver.begin();
    pwmServoDriver.setPWMFreq(50); // 50 Hz
}

void loop()
{

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 0);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 30);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 60);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 90);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 120);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 150);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 180);
    delay(DELAY_TIME);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 45);
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
