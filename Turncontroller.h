#pragma once
#include <Arduino.h>

class Turncontroller {
    private:
    float output_ = 0;

    public:
    float turn_Kp = 0;
    float turn_speed = 0;

    float computeTurnPWM(float gyro_z);
};