#include "MotorDriver.h"

MotorDriver::MotorDriver(int in1, int in2, int in3, int in4, int leftOffset, int rightOffset)
    : in1_(in1), in2_(in2), in3_(in3), in4_(in4), LeftOffset_(leftOffset), RightOffset_(rightOffset) {}

void MotorDriver::begin() {
    pinMode(in1_, OUTPUT);
    pinMode(in2_, OUTPUT);
    pinMode(in3_, OUTPUT);
    pinMode(in4_, OUTPUT);
    // stop();
}

void MotorDriver::Conductmotor(float leftEN, float rightEN) {
    leftEN = constrain(leftEN, -255, 255);
    rightEN = constrain(rightEN, -255, 255);

    if  (leftEN==0){
        analogWrite(in1_,0);
        analogWrite(in2_,0);
    }
    if (leftEN<0){
        analogWrite(in1_,0);
        analogWrite(in2_,-leftEN);
    }
    if (leftEN>0){
        analogWrite(in1_,leftEN);
        analogWrite(in2_,0);
    }

    if  (rightEN==0){
        analogWrite(in3_,0);
        analogWrite(in4_,0);
    }
    if (rightEN<0){
        analogWrite(in3_,0);
        analogWrite(in4_,-rightEN);
    }
    if(rightEN>0){
        analogWrite(in3_,rightEN);
        analogWrite(in4_,0);
    }
}

void MotorDriver::combinedcontrol(int vertical_pwm, int turn_pwm) {
    float L_pwm, R_pwm;

    if (vertical_pwm >0){
        L_pwm = vertical_pwm + LeftOffset_;
        R_pwm = vertical_pwm + RightOffset_;
    }
    if(vertical_pwm <0){
        L_pwm = vertical_pwm - LeftOffset_;
        R_pwm = vertical_pwm - RightOffset_;
    }
    if (vertical_pwm ==0){
        L_pwm = 0;
        R_pwm = 0;
    }

    L_pwm -= turn_pwm;
    R_pwm += turn_pwm;

    L_pwm = constrain(L_pwm, -255, 255);
    R_pwm = constrain(R_pwm, -255, 255);

    this->lastLeft_ = L_pwm;
    this->lastRight_ = R_pwm;

    Conductmotor(L_pwm, R_pwm);
}

float MotorDriver::lastLeft(){
    return lastLeft_;
}
float MotorDriver::lastRight(){
    return lastRight_;
}