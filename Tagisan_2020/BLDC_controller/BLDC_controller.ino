#define M1_BRAKE 32
#define M2_BRAKE 34
#define M1_DIRECTION 22
#define M2_DIRECTION 24
#define M1_PWM 8
#define M2_PWM 10
#define POWER 230 //0-255 max pwm
#define POT A0
#define INCREMENT 5
#define DECREMENT 15
#define MIN_BRAKE_STOP 30
#define LED_OUT 13

bool cw_direction = false;
bool ccw_direction = false;
bool turn_motor = true;

String inData;

void setup()
{
  Serial.begin(115200);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M1_DIRECTION, OUTPUT);
  pinMode(M2_DIRECTION, OUTPUT);
  pinMode(M1_BRAKE, OUTPUT);
  pinMode(M2_BRAKE, OUTPUT);

  pinMode(LED_OUT, OUTPUT);
  /**Motor Break
   * HIGH - break is NOT enabled
   * LOW - break IS ENABLED
  */
  digitalWrite(M1_BRAKE, LOW);
  digitalWrite(M2_BRAKE, LOW);
  /**Motor DIRECTION
   * HIGH - clockwise rotation (default)
   * LOW - counterclockwise
  */
  digitalWrite(M1_DIRECTION, HIGH);
  digitalWrite(M2_DIRECTION, HIGH);
  Serial.println("BLDC Motor Controller Sample!");
}

void loop()
{
  // read_controller();
  read_serial();
}

void read_serial()
{
  String serial_input;
  do
  {
    serial_input = Serial.readStringUntil('\r\n');
  } while (serial_input == "");
  serial_input.replace("\r", "");

  if (serial_input == "DOWN")
  {
    Serial.println(serial_input);
    rotate_CW(M1_PWM, M1_DIRECTION, M1_BRAKE);
    rotate_CCW(M2_PWM, M2_DIRECTION, M2_BRAKE);
  }
  else if (serial_input == "UP")
  {
    Serial.println(serial_input);
    rotate_CCW(M1_PWM, M1_DIRECTION, M1_BRAKE);
    rotate_CW(M2_PWM, M2_DIRECTION, M2_BRAKE);
  }  
  else if (serial_input == "LEFT")
  {
    Serial.println(serial_input);
    rotate_CW(M1_PWM, M1_DIRECTION, M1_BRAKE);
    rotate_CW(M2_PWM, M2_DIRECTION, M2_BRAKE);
  }  
  else if (serial_input == "RIGHT")
  {
    Serial.println(serial_input);
    rotate_CCW(M1_PWM, M1_DIRECTION, M1_BRAKE);
    rotate_CCW(M2_PWM, M2_DIRECTION, M2_BRAKE);
  }
  else if (serial_input == "LEFTZ-2")
  {
    Serial.println(serial_input);
    break_motor(M1_PWM, M1_DIRECTION, M1_BRAKE);
    break_motor(M2_PWM, M2_DIRECTION, M2_BRAKE);
  }
  else if (serial_input == "LEFTZ-1")
  {
    Serial.println(serial_input);
    hard_break(M1_BRAKE);
    hard_break(M2_BRAKE);
    // break_motor(M1_BRAKE);
  }
  /*
  else if (serial_input >= "530")
  {
    Serial.println("analog UP");
    Serial.println(serial_input);
    // Serial.println(serial_input.toInt()); //convert to integer
    int x = serial_input.toInt(); //convert to integer
    x = map(x, 530, 1023, 0, 255);
    Serial.println(x);
  }
  else if (serial_input <= "500")
  {
    Serial.println("analog DOWN");
    Serial.println(serial_input);
  }
  */
  else
  {
    Serial.println(serial_input);
  }
}

/**
 * Rotate motor clockwise
*/
void rotate_CW(int motorToTurn, int _direction, int _brake)
{
  if (turn_motor)
  {
    digitalWrite(_brake, HIGH);
    // digitalWrite(LED_OUT, HIGH);
    cw_direction = true;
    Serial.println("Clockwise rotation");
    digitalWrite(_direction, HIGH);
    for (int PWM_VALUE = 0; PWM_VALUE <= POWER; PWM_VALUE += INCREMENT)
    {
      analogWrite(motorToTurn, PWM_VALUE);
      delay(50);
    }
  }
}

/**
 * Rotate motor counterclockwise
*/
void rotate_CCW(int motorToTurn, int _direction, int _brake)
{
  if (turn_motor)
  {
    digitalWrite(_brake, HIGH);
    // digitalWrite(LED_OUT, HIGH);
    ccw_direction = true;
    Serial.println("counterClockwise rotation");
    digitalWrite(_direction, LOW);
    for (int PWM_VALUE = 0; PWM_VALUE <= POWER; PWM_VALUE += INCREMENT)
    {
      analogWrite(motorToTurn, PWM_VALUE);
      delay(50);
    }
  }
}

/**
 * How to interrupt the motors while rotating?
*/
void break_motor(int motor_pin, int _direction, int _brake)
{
  if (cw_direction)
  {
    Serial.println("CW:  ");
    for (int PWM_VALUE = POWER; PWM_VALUE >= 0; PWM_VALUE -= DECREMENT)
    {
      analogWrite(motor_pin, PWM_VALUE);
      delay(10);
      /*
      if (PWM_VALUE <= MIN_BRAKE_STOP)
      {
        // digitalWrite(motor_pin, LOW);
        Serial.println(PWM_VALUE);
        // delay(100);
        break;
      }
      */
    }
    cw_direction = false;
  }
  if (ccw_direction)
  {
    Serial.println("CCW:  ");
    digitalWrite(_direction, LOW);
    for (int PWM_VALUE = POWER; PWM_VALUE >= 0; PWM_VALUE -= DECREMENT)
    {
      analogWrite(motor_pin, PWM_VALUE);
      delay(10);
      /*
      if (PWM_VALUE <= MIN_BRAKE_STOP)
      {
        // digitalWrite(motor_pin, LOW);
        Serial.println(PWM_VALUE);
        // delay(100);
        break;
      }
      */
    }
    ccw_direction = false;
  }
  Serial.print("Braking: ");
  Serial.println(_brake);
  digitalWrite(_brake, LOW);
  // digitalWrite(LED_OUT, LOW);
  // delay(500);
  // digitalWrite(motor_pin, HIGH);
}

void hard_break(int _brakePin)
{
  Serial.print("HARD Braking: ");
  Serial.println(_brakePin);
  digitalWrite(_brakePin, LOW);
}

/**Left Joystick
 * Down - 510 to 0
 * Up - 511 to 1023
 * Left - 511 to 1023
 * Right - 510 to 0
*/
void read_controller()
{
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    inData += input;

    if (input == '\n')
    {
      Serial.println(inData);

      if (inData == "UP")
      {
        Serial.println("UP - is pressed!");
      }
      else if (inData == "DOWN")
      {
        Serial.println("DOWN - is pressed!");
      }

      inData = "";
    }
  }
}

void read_pot()
{
  int potVal = analogRead(A0);

  int pwmVal = map(potVal, 0, 1023, 0, 255);

  analogWrite(M1_PWM, pwmVal);

  Serial.print("Analog: ");
  Serial.print(potVal);
  Serial.print(", PWM Value: ");
  Serial.println(pwmVal);
  delay(100);
}

void ramp_up_down()
{
  //counterclockwise - CCW
  for (int PWM_VALUE = 0; PWM_VALUE <= 255; PWM_VALUE += 1)
  {
    analogWrite(M1_PWM, PWM_VALUE);
    delay(50);
  }
  delay(2000);
  for (int PWM_VALUE = 255; PWM_VALUE >= 0; PWM_VALUE -= 1)
  {
    analogWrite(M1_PWM, PWM_VALUE);
    delay(50);
  }
  delay(2000);
}

void rotate_cw_ccw()
{
  //clockwise
  digitalWrite(M1_DIRECTION, HIGH);
  for (int PWM_VALUE = 0; PWM_VALUE <= 255; PWM_VALUE += 5)
  {
    analogWrite(M1_PWM, PWM_VALUE);
    delay(30);
  }
  delay(2000);
  for (int PWM_VALUE = 255; PWM_VALUE >= 0; PWM_VALUE -= 5)
  {
    analogWrite(M1_PWM, PWM_VALUE);
    delay(30);
  }
  // delay(500);
  //break motor_1
  // break_motor(M1_BRAKE);

  //counterclockwise
  digitalWrite(M1_DIRECTION, LOW);
  for (int PWM_VALUE = 0; PWM_VALUE <= 255; PWM_VALUE += 5)
  {
    analogWrite(M1_PWM, PWM_VALUE);
    delay(30);
  }
  delay(2000);
  for (int PWM_VALUE = 255; PWM_VALUE >= 0; PWM_VALUE -= 5)
  {
    analogWrite(M1_PWM, PWM_VALUE);
    delay(30);
  }
  // delay(500);
  // break_motor(M1_BRAKE);
}