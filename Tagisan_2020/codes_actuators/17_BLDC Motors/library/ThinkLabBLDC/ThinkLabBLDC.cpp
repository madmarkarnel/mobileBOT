#include "ThinkLabBLDC.h"

ThinkLabBLDC::ThinkLabBLDC(int _pinPwm, int _pinDir, int _pinBrake)
{
    pinPwm = _pinPwm;
    pinDir = _pinDir;
    pinBrk = _pinBrake;

    pinMode(pinPwm, OUTPUT);
    pinMode(pinDir, OUTPUT);
    pinMode(pinBrk, OUTPUT);

    setSpeed(0.0);
    // disableMotor();
}

void ThinkLabBLDC::setMaxPower(float _maxPowerPercent)
{
    maxPowerPercent = _maxPowerPercent;
    if (maxPowerPercent > 100)
        maxPowerPercent = 100;
    else if (maxPowerPercent < 0)
        maxPowerPercent = 0;
    
    setSpeed(speedPercent);
}

float ThinkLabBLDC::getMaxPower()
{
    return maxPowerPercent;
}

void ThinkLabBLDC::setSpeed(float _speedPercent)
{
    speedPercent = _speedPercent;
    if (speedPercent > 100) speedPercent = 100;
    else if (speedPercent <= 0) speedPercent = 0;

    float dutyCycle = maxPowerPercent * speedPercent / 100;

    setPWM(dutyCycle);
}

float ThinkLabBLDC::getSpeed()
{
    return speedPercent;
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
