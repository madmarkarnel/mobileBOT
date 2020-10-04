#include <ThinkLabBLDC.h>

#define M1_BRAKE 49
#define M1_DIRECTION 47
#define M1_PWM 45

#define MAX_POWER 50 //0 to 100
#define DELAY_TIME 100

ThinkLabBLDC motor1 = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);

void setup()
{
    Serial.begin(115200);
    motor1.setDirection(CW);
    motor1.stop();
    Serial.println("Done Initializing!");
}

void loop()
{
    //spin clockwise
    motor1.setDirection(CW);
    for (int i = 0; i <= MAX_POWER; i++)
    {
        motor1.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    for (int i = MAX_POWER; i >= 0; i--)
    {
        motor1.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }

    motor1.stop();
    delay(2000);

    //spin counterclockwise
    motor1.setDirection(CCW);
    for (int i = 0; i <= MAX_POWER; i++)
    {
        motor1.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    for (int i = MAX_POWER; i >= 0; i--)
    {
        motor1.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    motor1.stop();
    delay(2000);
}

void printMotorValues()
{
    Serial.print("getDirection: ");
    Serial.println(motor1.getDirection());

    Serial.print("getPwmValue: ");
    Serial.println(motor1.getPwmValue());

    Serial.println();
}