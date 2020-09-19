#define M1_BRAKE 32
#define M1_DIRECTION 22
#define M1_PWM 8

#define M2_BRAKE 34
#define M2_DIRECTION 24
#define M2_PWM 10

#define POWER 80 //0-255 max pwm
#define INCREMENT 5
#define DECREMENT 15
#define START_OFFSET 10
#define PWM_DELAY 20

#define POT A0
#define LED_OUT 13

bool forward_flag = false;
bool reverse_flag = false;
bool move_left_flag = false;
bool move_right_flag = false;

bool cw_direction = false;
bool ccw_direction = false;
bool turn_motor = true;

uint8_t in_power = 20; // 0-100 ;default = 20%

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
  Serial.println("BLDC Motor Controller Test!");
}

void loop()
{
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
    reverse();
  }
  else if (serial_input == "UP")
  {
    Serial.println(serial_input);
    forward();
  }
  else if (serial_input == "LEFT")
  {
    Serial.println(serial_input);
    turn_left();
  }
  else if (serial_input == "RIGHT")
  {
    Serial.println(serial_input);
    turn_right();
  }
  else if (serial_input == "D1")
  {
    Serial.println(serial_input);
    in_power = 40;
  }
  else if (serial_input == "D2")
  {
    Serial.println(serial_input);
    in_power = 60;
  }
  else if (serial_input == "D3")
  {
    Serial.println(serial_input);
    in_power = 80;
  }
  else if (serial_input == "D4")
  {
    Serial.println(serial_input);
    in_power = 100;
  }
  else if (serial_input == "LEFTZ-2")
  {
    Serial.println(serial_input);
    brake_motors();
  }
  else if (serial_input == "LEFTZ-1")
  {
    Serial.println(serial_input);
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
    brake_motors();
  }
}

float mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

int setPWM(int power) //0 to 100
{
  int _power = mapFloat(power, 0, 100, 0, 255);
  if (_power > 255)
  {
    _power = 255;
  }
  else if (_power < 0)
  {
    _power = 0;
  }
  return _power;
}

/**
 * Move Reverse
 * Motor 2 is delayed
*/
void reverse()
{
  reverse_flag = true;
  Serial.println("Moving Reverse!");
  digitalWrite(M1_BRAKE, HIGH);
  digitalWrite(M2_BRAKE, HIGH);

  digitalWrite(M1_DIRECTION, LOW);
  digitalWrite(M2_DIRECTION, HIGH);
  delay(50);

  analogWrite(M2_PWM, setPWM(in_power));
  delay(50);
  analogWrite(M1_PWM, setPWM(in_power));
}

/**
 * Move Forward
 * Motor 1 is delayed
*/
void forward()
{
  forward_flag = true;
  Serial.println("Moving Forward!");
  digitalWrite(M1_BRAKE, HIGH);
  digitalWrite(M2_BRAKE, HIGH);

  digitalWrite(M2_DIRECTION, LOW);
  digitalWrite(M1_DIRECTION, HIGH);
  delay(50);

  analogWrite(M1_PWM, setPWM(in_power));
  delay(50);
  analogWrite(M2_PWM, setPWM(in_power));
}

/**
 * Move Left
 * motor 2 delayed
*/
void turn_right()
{
  move_right_flag = true;
  Serial.println("Moving to the right!");
  digitalWrite(M1_BRAKE, HIGH);
  digitalWrite(M2_BRAKE, HIGH);

  digitalWrite(M1_DIRECTION, HIGH);
  digitalWrite(M2_DIRECTION, HIGH);
  delay(50);

  analogWrite(M1_PWM, setPWM(in_power));
  delay(50);
  analogWrite(M2_PWM, setPWM(in_power));
}

/**
 * Move Left
 * motor 1 delayed
*/
void turn_left()
{
  move_left_flag = true;
  Serial.println("Moving to the left!");
  digitalWrite(M1_BRAKE, HIGH);
  digitalWrite(M2_BRAKE, HIGH);

  digitalWrite(M1_DIRECTION, LOW);
  digitalWrite(M2_DIRECTION, LOW);
  delay(50);
  
  analogWrite(M2_PWM, setPWM(in_power));
  delay(50);
  analogWrite(M1_PWM, setPWM(in_power));
}

/**
 * Break Motor 1 and Motor 2
*/
void brake_motors()
{
  Serial.println("Breaking . . .");
  if(forward_flag || move_left_flag)
  {
    digitalWrite(M2_BRAKE, LOW);
    digitalWrite(M1_BRAKE, LOW);
    forward_flag = false;
    move_left_flag = false;
  }
  if (reverse_flag || move_right_flag)
  {
    digitalWrite(M1_BRAKE, LOW);
    digitalWrite(M2_BRAKE, LOW);
    reverse_flag = false;
    move_right_flag = false;
  }
}

/**
 * Rotate motor clockwise
*/
void rotate_CW(int motorToTurn, int _direction, int _brake)
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

/**
 * Rotate motor counterclockwise
*/
void rotate_CCW(int motorToTurn, int _direction, int _brake)
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
    }
    ccw_direction = false;
  }
  Serial.print("Braking: ");
  Serial.println(_brake);
  digitalWrite(_brake, LOW);
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
  String inData;
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