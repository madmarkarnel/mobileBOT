#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>
#include "hidjoystickrptparser.h"

#include <Adafruit_PWMServoDriver.h>
#include <MonsterMotor.h>

Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver();

#define PIN_PWM_SERVO1 1
#define DELAY_TIME 1000
#define MOTOR_SPEED 50
#define MOTOR_POWER 50

#define MOTOR1_PIN_ENABLE A0
#define MOTOR1_DIR1 7
#define MOTOR1_DIR2 8
#define MOTOR1_PWM 5

MonsterMotor motor1 = MonsterMotor(MOTOR1_PIN_ENABLE, MOTOR1_DIR1, MOTOR1_DIR2, MOTOR1_PWM);

#define MOTOR2_PIN_ENABLE A1
#define MOTOR2_DIR1 4
#define MOTOR2_DIR2 3
#define MOTOR2_PWM 6

MonsterMotor motor2 = MonsterMotor(MOTOR2_PIN_ENABLE, MOTOR2_DIR1, MOTOR2_DIR2, MOTOR2_PWM);

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

void setup()
{
  Serial.begin(115200);

  pwmServoDriver.begin();
  pwmServoDriver.setPWMFreq(50); // 50 Hz

  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("Controller did not start.");

  delay(200);

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);

}

void loop()
{
  Usb.Task();

  if (JoyEvents.valueRead == 0)
  {
    Serial.println("Up button is pressed");
  }
  else if (JoyEvents.valueRead == 4)
  {
    Serial.println("Down button is pressed");
  }
  else if (JoyEvents.valueRead == 6)
  {
    Serial.println("Left button is pressed");
  }
  else if (JoyEvents.valueRead == 2)
  {
    Serial.println("Right button is pressed");
  }
  else if (JoyEvents.buttonPress == 2)
  {
    Serial.println("A button is pressed");
  }
  else if (JoyEvents.buttonPress == 3)
  {
    Serial.println("B button is pressed");
  }
  else if (JoyEvents.buttonPress == 1)
  {
    Serial.println("X button is pressed!");
  }
  else if (JoyEvents.buttonPress == 4)
  {
    Serial.println("Y button is pressed!");
  }
  else if (JoyEvents.buttonPress == 7)
  {
    Serial.println("LT button is pressed!");
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 90);
    delay(DELAY_TIME);
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 180);
    delay(DELAY_TIME);
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 0);
    motorSample();
  }
  else if (JoyEvents.buttonPress == 5)
  {
    Serial.println("LB button is pressed!");
  }
  else if (JoyEvents.buttonPress == 8)
  {
    Serial.println("RT button is pressed!");
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 180);
  }
  else if (JoyEvents.buttonPress == 6)
  {
    Serial.println("RB button is pressed!");
    setPwmSevoDriveServoAngle(pwmServoDriver, PIN_PWM_SERVO1, 0);
  }
  else
  {
  }

  /*
  //analog read values
  Serial.print("X: ");
  Serial.print(JoyEvents.X);
  Serial.print(" Y: ");
  Serial.print(JoyEvents.Y);
  Serial.print(" Z1: ");
  Serial.print(JoyEvents.Z1);
  Serial.print(" Z2: ");
  Serial.print(JoyEvents.Z2);
  Serial.print(" Rz: ");
  Serial.print(JoyEvents.Rz);
  Serial.println("");
*/
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

  // Serial.println(pulseWidth);

  _pwmServoDriver.setPWM(_pinServo, 0, pulseWidth);
}

void motorSample()
{
  Serial.println("motor ON");
  motor1.setDirection(CW);
  motor2.setDirection(CCW);
  for (int i = 0; i <= 100; i++)
  {
    Serial.println(i);

    motor1.setSpeed(i);
    motor2.setSpeed(i);

    delay(DELAY_TIME);
  }
  for (int i = 100; i >= 0; i--)
  {
    Serial.println(i);

    motor1.setSpeed(i);
    motor2.setSpeed(i);

    delay(DELAY_TIME);
  }
}