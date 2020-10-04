#include <ThinkLabBLDC.h>

#define M1_BRAKE 4
#define M1_DIRECTION 5
#define M1_PWM 8

#define M2_BRAKE 6
#define M2_DIRECTION 7
#define M2_PWM 9

#define MAX_POWER 50 //0 to 100
#define DELAY_TIME 100

ThinkLabBLDC motor1 = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);
ThinkLabBLDC motor2 = ThinkLabBLDC(M2_PWM, M2_DIRECTION, M2_BRAKE);

void setup()
{
    Serial.begin(115200);

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
    for (int i = 0; i <= MAX_POWER; i++)
    {
        motor1.setPWM(i);
        motor2.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    for (int i = MAX_POWER; i >= 0; i--)
    {
        motor1.setPWM(i);
        motor2.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }

    motor1.stop();
    motor2.stop();
    delay(2000);

    //spin counterclockwise
    motor1.setDirection(CCW);
    motor2.setDirection(CCW);
    for (int i = 0; i <= MAX_POWER; i++)
    {
        motor1.setPWM(i);
        motor2.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    for (int i = MAX_POWER; i >= 0; i--)
    {
        motor1.setPWM(i);
        motor2.setPWM(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    motor1.stop();
    motor2.stop();
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