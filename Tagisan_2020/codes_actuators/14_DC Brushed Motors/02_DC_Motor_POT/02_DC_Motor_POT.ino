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
    Serial.begin(9600);
    //set control pins to outputs
    pinMode(ENABLE_A, OUTPUT);
    pinMode(ENABLE_B, OUTPUT);
    pinMode(INPUT_1, OUTPUT);
    pinMode(INPUT_2, OUTPUT);
    pinMode(INPUT_3, OUTPUT);
    pinMode(INPUT_4, OUTPUT);
    
    //Initial state - clockwise
    digitalWrite(INPUT_1, LOW);
    digitalWrite(INPUT_2, HIGH);
    digitalWrite(INPUT_3, LOW);
    digitalWrite(INPUT_4, HIGH);
    
    Serial.println("Done Initializing!");
}

void loop()
{
    int potValue = analogRead(A0);

    int pwmVal = map(potValue, 0, 1023, 0, 255);

    analogWrite(ENABLE_A, pwmVal);
    analogWrite(ENABLE_B, pwmVal);
}