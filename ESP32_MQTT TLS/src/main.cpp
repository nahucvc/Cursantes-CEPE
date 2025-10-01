#include <Arduino.h>
#include "MqttTlsClient.h"
#include "WifiSetup.h"
#include "NtpSync.h"
#include "MqttDiagnostics.h"

#define LED 15

void setup() {
  pinMode(15, OUTPUT);
  Serial.begin(115200);
  connectWiFi();
  syncTime();
 // runDiagnostics();
  initMqtt();
}

void loop() {
  mqttLoop();
}
