#include "Imureader.h"

Imureader::Imureader(): mpu_(Wire) {}

void Imureader::begin(int sda_pin, int scl_pin) {
    Wire.begin(sda_pin, scl_pin);
    mpu_.begin();
    mpu_.calcGyroOffsets(true);
}

void Imureader::update() {
    mpu_.update();
    angleX_ = mpu_.getAngleX();
    angleY_ = mpu_.getAngleY();
    angleZ_ = mpu_.getAngleZ();
    gyroX_  = mpu_.getGyroX();
    gyroY_  = mpu_.getGyroY();
    gyroZ_  = mpu_.getGyroZ();
}

float Imureader::getAngleY() const { return angleY_; }
float Imureader::getAngleZ() const { return angleZ_; }
float Imureader::getGyroY() const { return gyroY_; }
float Imureader::getGyroZ() const { return gyroZ_; }