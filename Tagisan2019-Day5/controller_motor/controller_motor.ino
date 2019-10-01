#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>
#include "hidjoystickrptparser.h"

#include <MonsterMotor.h>

#define DELAY_TIME 300
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

  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("Controller did not start.");

  delay(200);

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);


  motor1.setMaxPower(MOTOR_POWER);
  motor1.enable();
  motor2.setMaxPower(MOTOR_POWER);
  motor2.enable();
}

void loop()
{
  Usb.Task();

  if (JoyEvents.valueRead == 0)
  {
    Serial.println("Up button is pressed");
    turnForward();
  }
  else if (JoyEvents.valueRead == 4)
  {
    Serial.println("Down button is pressed");
    turnReverse();
  }
  else if (JoyEvents.valueRead == 6)
  {
    Serial.println("Left button is pressed");
    turnLeft();
  }
  else if (JoyEvents.valueRead == 2)
  {
    Serial.println("Right button is pressed");
    turnRight();
  }
  else if (JoyEvents.buttonPress == 2)
  {
    Serial.println("A button is pressed");
  }
  else if (JoyEvents.buttonPress == 3)
  {
    Serial.println("B button is pressed");
    motorSample();
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
  }
  else if (JoyEvents.buttonPress == 5)
  {
    Serial.println("LB button is pressed!");
  }
  else if (JoyEvents.buttonPress == 8)
  {
    Serial.println("RT button is pressed!");
  }
  else if (JoyEvents.buttonPress == 6)
  {
    Serial.println("RB button is pressed!");
  }
  else
  {
    motor1.stop();
    motor2.stop();
  }
}

void turnRight()
{
  motor1.setDirection(CCW);
  motor2.setDirection(CCW);
  for (int i = 0; i <= 100; i++)
  {
    // Serial.println(i);
    motor1.setSpeed(i);
    motor2.setSpeed(i);

  }
}

void turnLeft()
{
  motor1.setDirection(CW);
  motor2.setDirection(CW);
  for (int i = 0; i <= 100; i++)
  {
    // Serial.println(i);
    motor1.setSpeed(i);
    motor2.setSpeed(i);
//    delay(2);
  }
}

void turnReverse()
{
  motor1.setDirection(CW);
  motor2.setDirection(CCW);
  for (int i = 0; i <= 100; i++)
  {
    // Serial.println(i);
    motor1.setSpeed(i);
    motor2.setSpeed(i);

  }
}

void turnForward()
{
  motor1.setDirection(CCW);
  motor2.setDirection(CW);
  for (int i = 0; i <= 100; i++)
  {
    // Serial.println(i);
    motor1.setSpeed(i);
    motor2.setSpeed(i);

  }
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
