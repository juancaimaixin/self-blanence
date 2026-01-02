#include "commandcontrol.h"

commandcontrol::commandcontrol(BalanceController& balancer, Turncontroller& turner, Imureader& mpu)
    : balancer_(balancer), turner_(turner), mpu_(mpu) {}

void commandcontrol::begin() {} //蓝牙已经在setup中初始化

void commandcontrol::getandhandleonechar(){
    if (BleUart::available()){
        char data = BleUart::read().charAt(0);
        handleonechar(data);

        if (balancer_.Kp<0){
            balancer_.Kp=0;
        }
        if (balancer_.Kd<0){
            balancer_.Kd=0;
        }
        if (balancer_.Ki<0){
            balancer_.Ki=0;
        }

        String msg="ka:"+String(balancer_.KeepAngle(),2)+
                   " Kp:"+String(balancer_.Kp,2)+
                   " Ki:"+String(balancer_.Ki,3)+
                   " Kd:"+String(balancer_.Kd,2)+
                   " tKp:"+String(turner_.turn_Kp,2)+
                   "a:"+String(mpu_.getAngleY())+
                   "w:"+String(mpu_.getGyroY())+"\n";

        BleUart::send(msg);
    }
}

void commandcontrol::handleonechar(char data){
    switch(data){
        case 'u': this->balancer_.setKeepAngle(this->balancer_.KeepAngle() + 0.2); break;
        case 'd': this->balancer_.setKeepAngle(this->balancer_.KeepAngle() - 0.2); break;
        case '0': this->balancer_.Kp += 1; break;
        case '1': this->balancer_.Kp -= 1; break;
        case '2': this->balancer_.Ki += 0.1; break;
        case '3': this->balancer_.Ki -= 0.1; break;
        case '4': this->balancer_.Kd += 0.1; break;
        case '5': this->balancer_.Kd -= 0.1; break;
        case '6': this->turner_.turn_Kp += 0.1; break;
        case '7': this->turner_.turn_Kp -= 0.1; break;
        case 's': this->balancer_.setKeepAngle(raw_balance_angle); break;
        case 'a': this->balancer_.setKeepAngle(raw_balance_angle + energy); break;
        case 'b': this->balancer_.setKeepAngle(raw_balance_angle - energy); break;
        case 'l': this->turner_.turn_speed = turn_energy; break;
        case 'r': this->turner_.turn_speed = -turn_energy; break;
        case 'n': this->turner_.turn_speed = 0; break;
        case 'p': this->balancer_.resetIntegrate(); break;
    }
}