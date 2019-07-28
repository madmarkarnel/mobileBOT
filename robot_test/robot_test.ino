/*  MonsterMoto Shield Example Sketch
  date: 5/24/11
  code by: Jim Lindblom
  hardware by: Nate Bernstein
  SparkFun Electronics
 
 License: CC-SA 3.0, feel free to use this code however you'd like.
 Please improve upon it! Let me know how you've made it better.
 
 This is really simple example code to get you some basic
 functionality with the MonsterMoto Shield. The MonsterMote uses
 two VNH2SP30 high-current full-bridge motor drivers.
 
 Use the motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) 
 function to get motors going in either CW, CCW, BRAKEVCC, or 
 BRAKEGND. Use motorOff(int motor) to turn a specific motor off.
 
 The motor variable in each function should be either a 0 or a 1.
 pwm in the motorGo function should be a value between 0 and 255.
 */
#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

#define BOTFLAG 1
#define MTRSPEED 1023
#define SPDLEFTRIGHT  60    //stable at 60

#include <PS2X_lib.h>  //for v1.6
PS2X ps2x; // create PS2 Controller Class
//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */
int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

int statpin = 13;

void setup()
{
  Serial.begin(57600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
  pinMode(statpin, OUTPUT);

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
}

void loop()
{
  robotControls();
}

void left_LEFT()
{
  for(int i=0; i<=SPDLEFTRIGHT; i++){
    motorGo(0, 1, i);
    motorGo(1, 1, i);
    Serial.println("Going left!");
  }
}

void right_RIGHT()
{
  for(int i=0; i <= SPDLEFTRIGHT; i++){
    motorGo(1, 2, i);
    motorGo(0, 2, i);  
    Serial.println("Going right!");
    delay(2);
  }
}

void launcher_up()
{
  // for(int i=0; i<=MTRSPEED; i++){
    motorGo(0, 1, MTRSPEED);
    motorGo(1, 2, MTRSPEED);  
    Serial.println("Forward!");  
    delay(2);
  // }
}

void launcher_down()
{
  // for(int i=0; i <= MTRSPEED; i++){
    motorGo(0, 2, MTRSPEED);
    motorGo(1, 1, MTRSPEED);  
    Serial.println("Reverse!"); 
    delay(2);
  // } 
}

void forward_up()
{
  for(int i=0; i<=MTRSPEED; i++){
    motorGo(0, 1, i);
    motorGo(1, 2, i);  
    Serial.println("Forward!");  
    delay(2);
  }
}

void reverse_down()
{
  for(int i=0; i <= MTRSPEED; i++){
    motorGo(0, 2, i);
    motorGo(1, 1, i);  
    Serial.println("Reverse!"); 
    delay(2);
  } 
}

void break_bot()
{
  motorOff(5);
  motorOff(6);   
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++){
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
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
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

void robotControls()
{
  ps2x.read_gamepad();

  while (BOTFLAG == 1){
    ps2x.read_gamepad();

    // added functions for robot controls (MAD)
    if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      forward_up();
      // break;
    }
    else if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      right_RIGHT();
      // break;
    }
    else if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      left_LEFT();
      // break;
    }
    else if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      reverse_down();
      // break;
    }
    else if(ps2x.ButtonPressed(PSB_RED)){
      //circle
      launcher_up();
    }
    else if(ps2x.ButtonReleased(PSB_PINK)){
      //square
      launcher_down();
    }
    
    else{
      Serial.println("Triagle pressed!");
      break_bot();
    }
    delay(50);
  }

  if(ps2x.Button(PSB_GREEN)){
  Serial.println("Triagle pressed!");
  break_bot();
  }

  break_bot();
  delay(50);
}


/*
  if(ps2x.Button(PSB_GREEN))
        Serial.println("Triangle pressed");  

  if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
        Serial.println("Circle just pressed");
        
  if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
        Serial.println("Square just released");     
  
  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
        Serial.println("X just changed");  
  
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRU
  */