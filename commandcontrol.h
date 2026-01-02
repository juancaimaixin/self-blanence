#pragma once
#include <Arduino.h>
#include "blueuart.h"
#include "BalanceController.h"
#include "Turncontroller.h"
#include "Imureader.h"

class commandcontrol{
    public:
    commandcontrol(BalanceController& balancer, Turncontroller& turner, Imureader& mpu);

    void begin(); //蓝牙已经在setup中初始化
    void getandhandleonechar();

    private:
    void handleonechar(char data);

    BalanceController& balancer_;
    Turncontroller& turner_;
    Imureader& mpu_;

    float raw_balance_angle = 1.2; //初始平衡角度
    float energy = 8; //前进能量
    float turn_energy = 300; //转弯能量
};