#ifndef ThinkLabBLDC_h
#define ThinkLabBLDC_h

#include "Arduino.h"

#define CW  true
#define CCW false

class ThinkLabBLDC
{
    public:
        ThinkLabBLDC(int _pinPwm, int _pinDir, int _pinBrake);

        void setMaxPower(float _maxPowerPercent);
        float getMaxPower();

        void setDirection(bool _direction);
        bool getDirection();

        void setSpeed(float _speedPercent);
        float getSpeed();

        void stop();

        int getPwmValue();

    private:
        int pinPwm;
        int pinDir;
        int pinBrk;

        int pwmValue;
        
        bool direction = CW;

        float maxPowerPercent = 20;
        float speedPercent = 0;
        
        void setPWM(float _dutycycle);

        float mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh);
};

#endif