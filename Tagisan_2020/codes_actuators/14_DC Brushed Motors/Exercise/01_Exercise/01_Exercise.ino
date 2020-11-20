//Motor A connections
#define ENABLE_A 9
#define INPUT_1 8
#define INPUT_2 7
//Motor B connections
#define ENABLE_B 3
#define INPUT_3 5
#define INPUT_4 4

int pwmValue;

void setup()
{
    Serial.begin(9600);
    //set control pins to outputs
    pinMode(ENABLE_A, OUTPUT);
    pinMode(ENABLE_B, OUTPUT);
    pinMode(INPUT_1, OUTPUT);
    pinMode(INPUT_2, OUTPUT);
    pinMode(INPUT_3, OUTPUT);
    pinMode(INPUT_4, OUTPUT);

    //Initial state - stop
    digitalWrite(INPUT_1, LOW);
    digitalWrite(INPUT_2, LOW);
    digitalWrite(INPUT_3, LOW);
    digitalWrite(INPUT_4, LOW);

    Serial.println("Done Initializing!");
}

void loop()
{
    int potValue = analogRead(A0);
    Serial.println(potValue);

    if (potValue < 500)
    {
        //clockwise direction
        digitalWrite(INPUT_1, LOW);
        digitalWrite(INPUT_2, HIGH);
        digitalWrite(INPUT_3, LOW);
        digitalWrite(INPUT_4, HIGH);

        analogWrite(ENABLE_A, 255);
        analogWrite(ENABLE_B, 255);
    }
    else if (potValue > 550)
    {
        //counterclockwise direction
        digitalWrite(INPUT_1, HIGH);
        digitalWrite(INPUT_2, LOW);
        digitalWrite(INPUT_3, HIGH);
        digitalWrite(INPUT_4, LOW);

        analogWrite(ENABLE_A, 255);
        analogWrite(ENABLE_B, 255);
    }
    else
    {
        //stop the motors
        digitalWrite(INPUT_1, LOW);
        digitalWrite(INPUT_2, LOW);
        digitalWrite(INPUT_3, LOW);
        digitalWrite(INPUT_4, LOW);
    }
}