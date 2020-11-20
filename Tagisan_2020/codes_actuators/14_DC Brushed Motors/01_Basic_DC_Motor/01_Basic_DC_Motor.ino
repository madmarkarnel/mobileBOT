//Motor A connections
#define ENABLE_A 9
#define INPUT_1 8
#define INPUT_2 7

//Motor B connections
#define ENABLE_B 3
#define INPUT_3 5
#define INPUT_4 4

void setup()
{
    //set control pins to outputs
    pinMode(ENABLE_A, OUTPUT);
    pinMode(ENABLE_B, OUTPUT);
    pinMode(INPUT_1, OUTPUT);
    pinMode(INPUT_2, OUTPUT);
    pinMode(INPUT_3, OUTPUT);
    pinMode(INPUT_4, OUTPUT);
    
    //Initial state - turn off motor
    digitalWrite(INPUT_1, LOW);
    digitalWrite(INPUT_2, LOW);
    digitalWrite(INPUT_3, LOW);
    digitalWrite(INPUT_4, LOW);
}

void loop()
{
    //turn ON the motors - clockwise rotation
    digitalWrite(INPUT_1, HIGH);
    digitalWrite(INPUT_2, LOW);
    digitalWrite(INPUT_3, HIGH);
    digitalWrite(INPUT_4, LOW);

    //accelerate from zero to maximum speed
    for (int i = 0; i <= 255; i++)
    {
        analogWrite(ENABLE_A, i);
        analogWrite(ENABLE_B, i);
        delay(50);
    }
    //decelerate from maximum to zero
    for (int i = 255; i >= 0; --i)
    {
        analogWrite(ENABLE_A, i);
        analogWrite(ENABLE_B, i);
        delay(50);
    }
    delay(2000);

    //turn ON the motors - counterclockwise rotation
    digitalWrite(INPUT_1, HIGH);
    digitalWrite(INPUT_2, LOW);
    digitalWrite(INPUT_3, HIGH);
    digitalWrite(INPUT_4, LOW);

    //accelerate from zero to maximum speed
    for (int i = 0; i <= 255; i++)
    {
        analogWrite(ENABLE_A, i);
        analogWrite(ENABLE_B, i);
        delay(50);
    }
    //decelerate from maximum to zero
    for (int i = 255; i >= 0; --i)
    {
        analogWrite(ENABLE_A, i);
        analogWrite(ENABLE_B, i);
        delay(50);
    }
    delay(2000);
}