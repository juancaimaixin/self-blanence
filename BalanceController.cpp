#include "BalanceController.h"

void BalanceController::setKeepAngle(float angle) {
    keep_angle_ = angle;
}

float BalanceController::KeepAngle() const {
    return keep_angle_;
}

float BalanceController::computeverticalPWM(float angley, float gyro_y) {
    bias_ = angley - keep_angle_;
    integrate_ += bias_;
    integrate_ = constrain(integrate_, -1000, 1000);
    output_ = Kp * bias_ + Ki * integrate_ + Kd * gyro_y;
    return output_;
}

float BalanceController::Bias() const {
    return bias_;
}

void BalanceController::resetIntegrate() {
    integrate_ = 0;
}