#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>
#include "hidjoystickrptparser.h"
//servo
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
// USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

//motor controller
#define BRAKEVCC 0
#define CW 1
#define CCW 2
#define BRAKEGND 3
#define CS_THRESHOLD 100
#define RSTPIN  2

#define BOTFLAG 1
#define MTRSPEED 1023
#define SPDLEFTRIGHT 500 //stable at 60

#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)
#define SERVOLEVER1 5
#define SERVOLEVER2 6
#define SERVOCLTR1  7
#define SERVOCLTR2  8
#define DELAYSERVO  1000

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs 
 xxx[1] controls '2' outputs */
int inApin[2] = {7, 4}; // INA: Clockwise input
int inBpin[2] = {8, 3}; // INB: Counter-clockwise input  9=3,pinalitan lang,default:9
int pwmpin[2] = {5, 6}; // PWM input

int mtrShotA[2] = {14, 15};   // [7,4] - motor shield (shooter motor A clockwise)
int mtrShotB[2] = {16, 17};   // [8,9] - motor shield (shooter motor B counter-clockwise)
int pwmShot[2] = {18,19};     // [5,6] - motor shield (pwm input shooter)

int cspin[2] = {2, 3};  // CS: Current sense ANALOG input
int enpin[2] = {0, 1};  // EN: Status of switches output (Analog pin)

int statpin = 13;

bool resetFlag = true;

void setup()
{
  pinMode(statpin, OUTPUT);
  pinMode(RSTPIN, OUTPUT);

  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(10);

  // while(resetFlag == true)
  // {
  //   digitalWrite(RSTPIN, LOW);
  //   delay(500);
  //   digitalWrite(RSTPIN, HIGH);
  //   resetFlag = false;
  // }

  // Initialize digital pins as outputs
  for (int i = 0; i < 2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
    //shooter variables
    pinMode(mtrShotA[i], OUTPUT);
    pinMode(mtrShotB[i], OUTPUT);
    pinMode(pwmShot[i], OUTPUT);
  }
  // Initialize braked
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
    //shooter variables
    digitalWrite(mtrShotA[i], LOW);
    digitalWrite(mtrShotB[i], LOW);
  }

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay(200);

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);

    digitalWrite(statpin, HIGH);
}

void loop()
{
  // pwm.setPWM(SERVOCLTR1, 0, 600);
  // getAtcommand();
  
  Usb.Task();

    if (JoyEvents.valueRead == 0)
    {
      Serial.println("Forward!");
      forward_up();
    }
    else if (JoyEvents.valueRead == 4)
    {
      Serial.println("Reverse!");
      reverse_down();
    }
    else if (JoyEvents.valueRead == 6)
    {
      Serial.println("Left!");
      left_LEFT();
    }
    else if (JoyEvents.valueRead == 2)
    {
      Serial.println("Right!");
      right_RIGHT();
    }
    else if (JoyEvents.mtrshoot == 2)
    {
      Serial.println("Start shooting!");
      launcher_up();
    }
    else if (JoyEvents.mtrshoot == 3)
    {
      Serial.println("Stop motor shoot!");
      shooterMotorOff(18);
      shooterMotorOff(19);
    }
    else if (JoyEvents.mtrshoot == 1)
    {
      Serial.println("X button is pressed!");
    }
    else if (JoyEvents.mtrshoot == 4)
    {
      Serial.println("Y button is pressed!");
    }
    else if (JoyEvents.mtrshoot == 7)
    {
      Serial.println("collecting ball!");
      pwm.setPWM(SERVOLEVER1, 0, angleToPulse(50));
      pwm.setPWM(SERVOLEVER2, 0, angleToPulse(270-50));   //servo 2 reverse direction

      // pwm.setPWM(SERVOLEVER1, 0, 110);    //minimum 110
    }
    else if (JoyEvents.mtrshoot == 5)
    {
      Serial.println("feeding ball to shoot!");
      // pwm.setPWM(SERVOLEVER1, 0, 580);    //maximum 580 @270 degrees
      pwm.setPWM(SERVOLEVER1, 0, angleToPulse(120));
      pwm.setPWM(SERVOLEVER2, 0, angleToPulse(270-120));    //servo 2 reverse direction
      delay(DELAYSERVO);
      pwm.setPWM(SERVOLEVER1, 0, angleToPulse(0));
      pwm.setPWM(SERVOLEVER2, 0, angleToPulse(270-0));      //servo 2 reverse direction
    }
    else if (JoyEvents.mtrshoot == 8)
    {
      Serial.println("collecting ball to lever!");
      pwm.setPWM(SERVOCLTR1, 0, angleToPulse(0));
      pwm.setPWM(SERVOCLTR2, 0, angleToPulse(270-0));
    }
    else if (JoyEvents.mtrshoot == 6)
    {
      Serial.println("back to original position!");
      pwm.setPWM(SERVOCLTR1, 0, angleToPulse(90));
      pwm.setPWM(SERVOCLTR2, 0, angleToPulse(270-90));
    }
    else
    {
      break_bot();
    }
    
}

int angleToPulse(int angle)
{
  int pulse = map(angle, 0, 270, SERVOMIN, SERVOMAX);
  Serial.print("Angle: ");  Serial.print(angle);
  Serial.print(" Pulse: "); Serial.println(pulse);
  return pulse;
}

void left_LEFT()
{
    motorGo(0, 1, MTRSPEED);
    motorGo(1, 1, MTRSPEED);
    Serial.println("Going left!");
}

void right_RIGHT()
{
    motorGo(0, 2, MTRSPEED);
    motorGo(1, 2, MTRSPEED);
    Serial.println("Going right!");
}

void launcher_up()
{
  shootMotorGo(0, 1, MTRSPEED);
  shootMotorGo(1, 2, MTRSPEED);
  Serial.println("Shooter forward!");
}

void launcher_down()
{
  shootMotorGo(0, 2, MTRSPEED);
  shootMotorGo(1, 1, MTRSPEED);
  Serial.println("Shooter reverse!");
}

void forward_up()
{
    motorGo(0, 1, MTRSPEED);    //left motor
    motorGo(1, 2, MTRSPEED);    //right motor
    Serial.println("Forward!");
}

void reverse_down()
{
    motorGo(0, 2, MTRSPEED);    //left motor
    motorGo(1, 1, MTRSPEED);    //right motor
    Serial.println("Reverse!");
}

void break_bot()
{
  motorOff(5);
  motorOff(6);
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

void shooterMotorOff(int motor)
{
  // Initialize braked shooter motor
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(mtrShotA[i], LOW);
    digitalWrite(mtrShotB[i], LOW);
  }
  analogWrite(pwmShot[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <= 4)
    {
      // Set inA[motor]
      if (direct <= 1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct == 0) || (direct == 2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

void shootMotorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <= 4)
    {
      // Set inA[motor]
      if (direct <= 1)
        digitalWrite(mtrShotA[motor], HIGH);
      else
        digitalWrite(mtrShotA[motor], LOW);

      // Set inB[motor]
      if ((direct == 0) || (direct == 2))
        digitalWrite(mtrShotB[motor], HIGH);
      else
        digitalWrite(mtrShotB[motor], LOW);

      analogWrite(pwmShot[motor], pwm);
    }
  }
}


#define ATCMD     "AT"
#define ATECMDTRUE  "ATE"
#define ATECMDFALSE "ATE0"
#define OKSTR     "OK"
#define ERRORSTR  "ERROR"

bool ate = false;

void getAtcommand(){

  String serial_line, command;
  int i_equals = 0;
    
  do{
     serial_line = Serial.readStringUntil('\r\n');
    }while(serial_line == "");
    serial_line.toUpperCase();
    serial_line.replace("\r","");

    // echo command if ate is set, default true
    if (ate) Serial.println(serial_line);

    // get characters before '='
    i_equals = serial_line.indexOf('=');
    if (i_equals == -1) command = serial_line;
    else command = serial_line.substring(0,i_equals);

    // Serial.println(command);
    
    if (command == ATCMD)
      Serial.println(OKSTR);
    else if (command == ATECMDTRUE){
      ate = true;
      Serial.println(OKSTR);
    }
    else if (command == ATECMDFALSE){
      ate = false;
      Serial.println(OKSTR);
    }
    else if (command == "W"){
      forward_up();
    }
    else if (command == "S"){
      reverse_down();
    }
    else if (command == "A"){
      left_LEFT();
    }
    else if (command == "D"){
      right_RIGHT();
    }    
    else{
      Serial.println(ERRORSTR);
    }
}