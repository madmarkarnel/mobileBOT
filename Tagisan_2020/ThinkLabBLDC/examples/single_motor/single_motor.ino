#include <ThinkLabBLDC.h>

#define M1_BRAKE 7
#define M1_DIRECTION 6
#define M1_PWM 9

#define DELAY_TIME 100
#define DELAY_INTERVAL 3000

ThinkLabBLDC motor1 = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);

void setup()
{
    Serial.begin(115200);

    motor1.setMaxPower(80);
    motor1.setDirection(CW);
    motor1.stop();
    Serial.println("Done Initializing!");
}

void loop()
{
    //spin clockwise
    Serial.println("CLockwise!");
    motor1.setDirection(CW);
    for (int i = 0; i <= 100; i++)
    {
        motor1.setSpeed(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    motor1.stop();
    delay(DELAY_INTERVAL);

    //spin counterclockwise
    Serial.println("counterclockwise!");
    motor1.setDirection(CCW);
    for (int i = 0; i <= 100; i++)
    {
        motor1.setSpeed(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    motor1.stop();
    delay(DELAY_INTERVAL);
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