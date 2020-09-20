#define SERVO_FEEDER_L 0
#define SERVO_FEEDER_R 2
#define SERVOMIN 110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 580 // this is the 'maximum' pulse length count (out of 4096)

void ball_feeder_up()
{
    // setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_L, 270 - 80);
    // setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_R, 80);
    pwmServoDriver.setPWM(SERVO_FEEDER_R, 0, angleToPulse(125));
    pwmServoDriver.setPWM(SERVO_FEEDER_L, 0, angleToPulse(270 - 125)); //servo 2 reverse direction

}

void ball_feeder_down()
{
    // setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_L, 0);
    // setPwmSevoDriveServoAngle(pwmServoDriver, SERVO_FEEDER_R, 270 - 0);
    pwmServoDriver.setPWM(SERVO_FEEDER_R, 0, angleToPulse(0));
    pwmServoDriver.setPWM(SERVO_FEEDER_L, 0, angleToPulse(270 - 0)); //servo 2 reverse direction
}

int angleToPulse(int angle)
{
    int pulse = map(angle, 0, 270, SERVOMIN, SERVOMAX);
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" Pulse: ");
    Serial.println(pulse);
    return pulse;
}

void setPwmSevoDriveServoAngle(Adafruit_PWMServoDriver _pwmServoDriver, int _pinServo, int _angle)
{
    /**MG996R calibrated rotation
    * di kaya ng MG996R ang load ng ball feader
    const int COUNTER_WIDTH_MIN = 150; // 0 angle
    const int COUNTER_WIDTH_MAX = 470; // 180 angle
    */

    /**DSS-M15S calibrated rotation
    * di kaya ng MG996R ang load ng ball feader
    */
    const int COUNTER_WIDTH_MIN = 110; // 0 angle
    const int COUNTER_WIDTH_MAX = 580; // 270 angle

    if (_angle < 0)
        _angle = 0;
    else if (_angle > 270)
        _angle = 270;

    int pulseWidth = map(_angle, 0, 270, COUNTER_WIDTH_MIN, COUNTER_WIDTH_MAX);

    Serial.println(pulseWidth);

    _pwmServoDriver.setPWM(_pinServo, 0, pulseWidth);
}