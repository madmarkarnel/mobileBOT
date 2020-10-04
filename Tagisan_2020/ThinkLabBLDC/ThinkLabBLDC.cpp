#include "ThinkLabBLDC.h"

ThinkLabBLDC::ThinkLabBLDC(int _pinPwm, int _pinDir, int _pinBrake)
{
    pinPwm = _pinPwm;
    pinDir = _pinDir;
    pinBrk = _pinBrake;

    pinMode(pinPwm, OUTPUT);
    pinMode(pinDir, OUTPUT);
    pinMode(pinBrk, OUTPUT);

    // setSpeed(0.0);
    // disableMotor();
}

void ThinkLabBLDC::setDirection(bool _direction)
{
    direction = _direction;

    if (direction)
    {
        digitalWrite(pinBrk, HIGH);
        digitalWrite(pinDir, HIGH);
    }
    else
    {
        digitalWrite(pinBrk, HIGH);
        digitalWrite(pinDir, LOW);
    }
}

bool ThinkLabBLDC::getDirection()
{
    return direction;
}

void ThinkLabBLDC::stop()
{
    digitalWrite(pinBrk, LOW);
}

int ThinkLabBLDC::getPwmValue()
{
    return pwmValue;
}

float ThinkLabBLDC::mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void ThinkLabBLDC::setPWM(float _dutyCycle)
{

    int pwmVal = mapFloat(_dutyCycle, 0, 100, 0, 255);

    if (pwmVal > 255)
        pwmVal = 255;
    else if (pwmVal < 0)
        pwmVal = 0;

    analogWrite(pinPwm, pwmVal);

    pwmValue = pwmVal;
}
