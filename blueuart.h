#pragma once
#include <Arduino.h>

namespace BleUart {
  void begin(const char* deviceName);
  bool connected();

  // 手机->ESP32：是否有新消息
  bool available();
  String read();          // 读取并清空“新消息”标志（读一次消费一次）

  // ESP32->手机：发送通知
  bool send(const String& s);
}