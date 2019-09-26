#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#include <SPI.h>
#include "hidjoystickrptparser.h"

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
}

void loop()
{
  Usb.Task();
/*
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
  }
*/

  //analog values
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

}
