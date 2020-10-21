#include <ThinkLabBLDC.h>

#define M1_BRAKE 7
#define M1_DIRECTION 6
#define M1_PWM 9

#define M2_BRAKE 2
#define M2_DIRECTION 3
#define M2_PWM 8

#define DELAY_TIME 100

ThinkLabBLDC motor1 = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);
ThinkLabBLDC motor2 = ThinkLabBLDC(M2_PWM, M2_DIRECTION, M2_BRAKE);

void setup()
{
    Serial.begin(115200);

    motor1.setMaxPower(12);
    motor2.setMaxPower(12);

    motor1.setDirection(CW);
    motor2.setDirection(CW);

    motor1.stop();
    motor2.stop();
    Serial.println("Done Initializing!");
}

void loop()
{
    //spin clockwise
    motor1.setDirection(CW);
    motor2.setDirection(CW);
    for (int i = 0; i <= 100; i++)
    {
        motor1.setSpeed(i);
        motor2.setSpeed(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    motor1.stop();
    motor2.stop();
    delay(4000);

    //spin counterclockwise
    motor1.setDirection(CCW);
    motor2.setDirection(CCW);
    for (int i = 0; i <= 100; i++)
    {
        motor1.setSpeed(i);
        motor2.setSpeed(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    motor1.stop();
    motor2.stop();
    delay(4000);
}

void printMotorValues()
{
    Serial.print("getDirection: ");
    Serial.println(motor1.getDirection());

    Serial.print("getSpeed: ");
    Serial.println(motor1.getSpeed());

    Serial.print("getPwmValue: ");
    Serial.println(motor1.getPwmValue());

    Serial.println();
}