#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

class Imureader{
    private:
    MPU6050 mpu_;
    float angleX_ = 0;
    float angleY_ = 0;
    float angleZ_ = 0;
    float gyroX_  = 0;
    float gyroY_  = 0;
    float gyroZ_  = 0;

    public:
    Imureader();
    void begin(int sda_pin, int scl_pin);
    void update();

    float getAngleY() const;
    float getAngleZ() const;
    float getGyroY() const;
    float getGyroZ() const;
};