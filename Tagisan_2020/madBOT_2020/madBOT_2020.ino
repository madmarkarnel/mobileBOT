#include <ThinkLabBLDC.h>
#include <Adafruit_PWMServoDriver.h>

//left drive motor
#define M1_BRAKE 32
#define M1_DIRECTION 22
#define M1_PWM 8

//right drive motor
#define M2_BRAKE 34
#define M2_DIRECTION 24
#define M2_PWM 9

//left shooter
#define M3_BRAKE 48
#define M3_DIRECTION 46
#define M3_PWM 44

//right shooter
#define M4_BRAKE 49
#define M4_DIRECTION 47
#define M4_PWM 45

#define INCREMENT 5
#define MAX_PWM 80

//servo related
#define SERVO_FEEDER_L 2
#define SERVO_FEEDER_R 3
#define SERVO_CLAW_L 4
#define SERVO_CLAW_R 5

ThinkLabBLDC driveRight = ThinkLabBLDC(M1_PWM, M1_DIRECTION, M1_BRAKE);
ThinkLabBLDC driveLeft = ThinkLabBLDC(M2_PWM, M2_DIRECTION, M2_BRAKE);
ThinkLabBLDC shooterRight = ThinkLabBLDC(M3_PWM, M3_DIRECTION, M3_BRAKE);
ThinkLabBLDC shooterLeft = ThinkLabBLDC(M4_PWM, M4_DIRECTION, M4_BRAKE);

Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver(0x40);

String serial_input;

int in_power = 5;
int shooter_power = 10;

void setup()
{
    Serial.begin(115200);
    pwmServoDriver.begin();
    pwmServoDriver.setPWMFreq(50); // 50 Hz

    driveRight.setDirection(CW);
    driveLeft.setDirection(CCW);

    shooterRight.setDirection(CW);
    shooterLeft.setDirection(CCW);

    driveRight.stop();
    driveLeft.stop();

    shooterRight.stop();
    shooterLeft.stop();

    Serial.println("Done intializing madBOT_2020!");
}

void loop()
{
    //run code forever
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
        in_power += 5;
        if (in_power >= 80)
        {
            in_power = 80;
        }

        Serial.println(in_power);
    }
    else if (serial_input == "D2")
    {
        Serial.println(serial_input);
        in_power -= 5;
        if (in_power <= 5)
        {
            in_power = 5;
        }
        Serial.println(in_power);
    }
    else if (serial_input == "D3")
    {
        Serial.println(serial_input);
        shooter_power -= INCREMENT;
        if (shooter_power <= 5)
        {
            shooter_power = 5;
        }
    }
    else if (serial_input == "D4")
    {
        Serial.println(serial_input);
        shooter_power += INCREMENT;
        if (shooter_power >= MAX_PWM)
        {
            shooter_power = MAX_PWM;
        }
    }
    else if (serial_input == "LEFTZ-2")
    {
        Serial.println(serial_input);
        claw_out();
    }
    else if (serial_input == "LEFTZ-1")
    {
        Serial.println(serial_input);
        claw_in();
    }
    else if (serial_input == "RIGHTZ-2")
    {
        Serial.println(serial_input);
        ball_feeder_down();
    }
    else if (serial_input == "RIGHTZ-1")
    {
        Serial.println(serial_input);
        ball_feeder_up();
    }
    else if (serial_input == "RIGHTJ")
    {
        Serial.println(serial_input);
        stop_shooter();
    }
    else if (serial_input == "LEFTJ")
    {
        Serial.println(serial_input);
        spin_shooter();
    }
    else
    {
        Serial.println(serial_input);
        driveRight.stop();
        driveLeft.stop();
    }
}

void forward()
{
    driveRight.setDirection(CCW);
    driveLeft.setDirection(CW);

    driveRight.setPWM(in_power);
    driveLeft.setPWM(in_power);
}

void reverse()
{
    driveRight.setDirection(CW);
    driveLeft.setDirection(CCW);

    driveRight.setPWM(in_power);
    driveLeft.setPWM(in_power);
}

void turn_left()
{
    //turn_left
    driveLeft.setDirection(CW);
    driveLeft.setPWM(in_power);
}

void turn_right()
{
    //turn_right
    driveRight.setDirection(CCW);
    driveRight.setPWM(in_power);
}

void spin_shooter()
{
    //spin_shooter
    shooterRight.setDirection(CCW);
    shooterLeft.setDirection(CW);

    shooterRight.setPWM(shooter_power);
    shooterLeft.setPWM(shooter_power);
}

void stop_shooter()
{
    shooterRight.stop();
    shooterLeft.stop();
}

void setPwmSevoDriveServoAngle(Adafruit_PWMServoDriver _pwmServoDriver, int _pinServo, int _angle)
{
    /**MG996R calibrated rotation
    * di kaya ng MG996R ang load ng ball feader
    */
    const int COUNTER_WIDTH_MIN = 150; // 0 angle
    const int COUNTER_WIDTH_MAX = 470; // 180 angle

    if (_angle < 0)
        _angle = 0;
    else if (_angle > 180)
        _angle = 180;

    int pulseWidth = map(_angle, 0, 180, COUNTER_WIDTH_MIN, COUNTER_WIDTH_MAX);

    Serial.println(pulseWidth);

    _pwmServoDriver.setPWM(_pinServo, 0, pulseWidth);
}

void ball_feeder_up()
{
    //half UP
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_R, 180 - 70);
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_L, 70);
}

void ball_feeder_down()
{
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_R, 180 - 130);
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_L, 130);
    delay(1000);
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_R, 180 - 0);
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_L, 0);
}

void claw_out()
{
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_CLAW_L, 180 - 60);
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_CLAW_R, 60);
}

void claw_in()
{
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_CLAW_L, 0);
    setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_CLAW_R, 180 - 0);
}