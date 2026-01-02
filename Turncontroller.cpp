#include "Turncontroller.h"

float Turncontroller::computeTurnPWM(float gyro_z) {
    output_ = turn_Kp * (gyro_z - turn_speed);
    return output_;
}