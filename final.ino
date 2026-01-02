#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Arduino.h>
#include <NimBLEDevice.h>
#include "blueuart.h"

#include "config.h"
#include "MotorDriver.h"
#include "Imureader.h"
#include "BalanceController.h"
#include "Turncontroller.h"
#include "commandcontrol.h"

static MotorDriver motor(IN1, IN2, IN3, IN4, left_motor_offset, right_motor_offset);
static Imureader mpu;
static BalanceController balancer;
static Turncontroller turner;
static commandcontrol commander(balancer, turner, mpu);

void debug_serial(){
  static unsigned long t = 0;
  if (millis() - t <= 1000) return;
  t = millis();

  Serial.print("AngleY:");
  Serial.println(mpu.getAngleY());
  Serial.print(" leftpwm:");
  Serial.println(motor.lastLeft());
  Serial.print(" rightpwm:");
  Serial.println(motor.lastRight());
}

void setup(){
    Serial.begin(115200);
    delay(5000);
    BleUart::begin("ESP32S3-BLE");
    motor.begin();
    mpu.begin(SDA_PIN, SCL_PIN);
    balancer.setKeepAngle(1.2);
}

void loop(){
    commander.getandhandleonechar(); // read instructions from bluetooth
    mpu.update();
    float vertical_pwm = balancer.computeverticalPWM(mpu.getAngleY(), mpu.getGyroY());
    float turn_pwm = turner.computeTurnPWM(mpu.getGyroZ());

    if (balancer.Bias() > 45 || balancer.Bias() < -45) {// fall down
        motor.combinedcontrol(0, 0);
        balancer.resetIntegrate();
    } else {
        motor.combinedcontrol(vertical_pwm, turn_pwm);
    }
    debug_serial();
}