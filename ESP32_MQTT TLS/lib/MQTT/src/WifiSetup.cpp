#include "WifiSetup.h"
#include "MqttTlsClient.h"
#include <WiFi.h>

void connectWiFi() {
  Serial.printf("Conectando a WiFi '%s'...\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
    if (millis() - t0 > 30000) {
      Serial.println("\nTiempo de espera WiFi excedido. Reiniciando...");
      ESP.restart();
    }
  }
  Serial.printf("\nWiFi OK. IP: %s  GW: %s  DNS: %s\n",
                WiFi.localIP().toString().c_str(),
                WiFi.gatewayIP().toString().c_str(),
                WiFi.dnsIP().toString().c_str());
}
