#include "blueuart.h"
#include <NimBLEDevice.h>

// UUID
static const char* SERVICE_UUID = "12345678-1234-1234-1234-1234567890ab";
static const char* RX_UUID      = "12345678-1234-1234-1234-1234567890ac";
static const char* TX_UUID      = "12345678-1234-1234-1234-1234567890ad";

static NimBLECharacteristic* txChar = nullptr;
static bool deviceConnected = false;

// 消息缓存（手机->ESP32）
static String rxBuf;
static volatile bool hasRx = false;

class ServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer*, NimBLEConnInfo&) override {
    deviceConnected = true;
    Serial.println("BLE connected");
  }
  void onDisconnect(NimBLEServer*, NimBLEConnInfo&, int) override {
    deviceConnected = false;
    Serial.println("BLE disconnected, advertising again...");
    NimBLEDevice::startAdvertising();
  }
};

class RxCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* c, NimBLEConnInfo&) override {
    std::string s = c->getValue();
    if (s.empty()) return;

    rxBuf = String(s.c_str());
    hasRx = true;

    // Serial.print("RX from phone: ");
    // Serial.println(rxBuf);//返回给电脑串口

    // 可选：回显（返回给手机）
    // if (txChar && deviceConnected) {
    //   txChar->setValue((uint8_t*)s.data(), s.size());
    //   txChar->notify();
    // }
  }
};

namespace BleUart {

void begin(const char* deviceName) {
  NimBLEDevice::init(deviceName);

  NimBLEServer* server = NimBLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());

  NimBLEService* svc = server->createService(SERVICE_UUID);

  txChar = svc->createCharacteristic(TX_UUID, NIMBLE_PROPERTY::NOTIFY);

  NimBLECharacteristic* rxChar = svc->createCharacteristic(
    RX_UUID, NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
  );
  rxChar->setCallbacks(new RxCallbacks());

  svc->start();

  NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->start();

  Serial.println("BLE ready.");
}

bool connected() {
  return deviceConnected;
}

bool available() {
  return hasRx;
}

String read() {
  if (!hasRx) return "";
  hasRx = false;
  return rxBuf;
}

bool send(const String& s) {
  if (!deviceConnected || !txChar) return false;
  if (s.length() == 0) return false;

  txChar->setValue(s.c_str());
  txChar->notify();
  return true;
}

} // namespace BleUart