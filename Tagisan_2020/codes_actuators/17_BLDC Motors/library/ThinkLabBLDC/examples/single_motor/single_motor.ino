#include <ThinkLabBLDC.h>

#define M1_BRAKE 48
#define M1_DIRECTION 46
#define M1_PWM 44

#define DELAY_TIME 60

ThinkLabBLDC motor1 = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);

void setup()
{
    Serial.begin(115200);

    motor1.setMaxPower(30);
    motor1.setDirection(CW);
    motor1.stop();
    Serial.println("Done Initializing!");
}

void loop()
{
    //spin clockwise
    motor1.setDirection(CW);
    for (int i = 0; i <= 100; i++)
    {
        motor1.setSpeed(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    // for (int i = 100; i >= 0; i--)
    // {
    //     motor1.setSpeed(i);
    //     delay(DELAY_TIME);
    //     printMotorValues();
    //     if (i <= )
    //     {            
    //         Serial.println("BREAK!");
    //         motor1.stop();
    //         break;
    //     }
    // }

    motor1.stop();
    delay(2000);

    //spin counterclockwise
    motor1.setDirection(CCW);
    for (int i = 0; i <= 100; i++)
    {
        motor1.setSpeed(i);
        delay(DELAY_TIME);
        printMotorValues();
    }
    // for (int i = 100; i >= 0; i--)
    // {
    //     motor1.setSpeed(i);
    //     delay(DELAY_TIME);
    //     printMotorValues();
    // }
    motor1.stop();
    delay(2000);
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