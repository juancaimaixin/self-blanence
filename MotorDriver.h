#pragma once
#include <Arduino.h>

class MotorDriver {
    private:
    int in1_, in2_, in3_, in4_;
    int LeftOffset_, RightOffset_;
    int lastLeft_  = 0;
    int lastRight_ = 0;

    public:
    MotorDriver(int in1, int in2, int in3, int in4, int leftOffset, int rightOffset);

    void begin();
    void Conductmotor(float leftEN, float rightEN);
    void combinedcontrol(int vertical_pwm, int turn_pwm);

    float lastLeft();
    float lastRight();
};

