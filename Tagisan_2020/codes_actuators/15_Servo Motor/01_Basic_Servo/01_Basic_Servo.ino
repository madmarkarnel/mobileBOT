#include <Servo.h>

#define DELAY_TIME 3000

Servo myservo;

void setup()
{
    myservo.attach(9);
}

void loop()
{
    myservo.write(0);
    delay(DELAY_TIME);

    myservo.write(30);
    delay(DELAY_TIME);

    myservo.write(90);
    delay(DELAY_TIME);

    myservo.write(180);
    delay(DELAY_TIME);

    myservo.write(45);
    delay(DELAY_TIME);
}
