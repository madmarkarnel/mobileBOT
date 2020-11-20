#include <ThinkLabBLDC.h>

//motor 1
#define M1_BRAKE 7
#define M1_DIRECTION 6
#define M1_PWM 9

//motor 2
#define M2_BRAKE 2
#define M2_DIRECTION 3
#define M2_PWM 8

#define MAX_SPEED 100   //0 to 100

ThinkLabBLDC motor1 = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);
ThinkLabBLDC motor2 = ThinkLabBLDC(M2_PWM, M2_DIRECTION, M2_BRAKE);

String serial_input;

void setup()
{
    Serial.begin(115200);

    motor1.setMaxPower(20);
    motor1.setDirection(CW);
    motor1.stop();

    motor2.setMaxPower(20);
    motor2.setDirection(CW);
    motor2.stop();

    Serial.println("Done Initializing!");
    Serial.println("Input commands in serial");
}

void loop()
{
    /*wait for \r\n Input*/
    do
    {
        serial_input = Serial.readStringUntil('\r\n');
    } while (serial_input == "");
    serial_input.replace("\r", "");

    if (serial_input == "w")
    {
        Serial.println(serial_input);
        Serial.println("Clockwise!");
        motor1.setDirection(CW);
        motor2.setDirection(CW);

        motor1.setSpeed(MAX_SPEED);
        motor2.setSpeed(MAX_SPEED);
    }
    else if (serial_input == "s")
    {
        Serial.println(serial_input);
        Serial.println("Counterclockwise!");
        motor1.setDirection(CCW);
        motor2.setDirection(CCW);

        motor1.setSpeed(MAX_SPEED);
        motor2.setSpeed(MAX_SPEED);
    }
    else
    {
        Serial.println(serial_input);
        Serial.println("invalid command!");
        motor1.stop();
        motor2.stop();
    }
}
