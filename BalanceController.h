#pragma once
#include <Arduino.h>

class BalanceController {
    private:
    float keep_angle_ = 0;
    float bias_ = 0;
    float integrate_ = 0;
    float output_ = 0;

    public:
    float Kp = 14;
    float Ki = 0.2;
    float Kd = 0.6;

    void setKeepAngle(float angle);
    float KeepAngle() const;
    float computeverticalPWM(float angley, float gyro_y);
    float Bias() const;
    void resetIntegrate();
};