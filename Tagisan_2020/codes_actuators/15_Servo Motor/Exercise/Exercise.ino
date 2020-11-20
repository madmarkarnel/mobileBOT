/**
 *  DO NOT RUN THIS PROGRAM USING A WEAK VOLTAGE SUPPLY FOR SERVO MOTORS 
 */

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver(0x40);

#define PIN_PWM_SERVO1 0
#define PIN_PWM_SERVO2 2
#define PIN_PWM_SERVO3 4
#define PIN_PWM_SERVO4 6
#define PIN_PWM_SERVO5 8

#define DELAY_TIME 15

void setup()
{
    Serial.begin(115200);

    pwmServoDriver.begin();
    pwmServoDriver.setPWMFreq(50);

    Serial.println("Done Intializing");
    Serial.println("Enter angle of servo: ");
}

void loop()
{
    while (!Serial.available())
        ; // Wait for input from Serial

    String str_angle = Serial.readString();
    int servoAngle = str_angle.toInt();

    Serial.println(servoAngle);

    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, servoAngle);
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO2, servoAngle);
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO3, servoAngle);
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO4, servoAngle);
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO5, servoAngle);

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
