#include "MqttDiagnostics.h"
#include "MqttTlsClient.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>

static bool tcpReachable(const char* host, uint16_t port, uint32_t timeoutMs = 5000) {
  WiFiClient tcp;
  tcp.setTimeout(timeoutMs / 1000);
  bool ok = tcp.connect(host, port);
  tcp.stop();
  return ok;
}

void runDiagnostics() {
  IPAddress brokerIP;
  if (WiFi.hostByName(MQTT_HOST, brokerIP) == 1)
    Serial.printf("[DIAG] DNS %s -> %s\n", MQTT_HOST, brokerIP.toString().c_str());

  bool tcpOK = tcpReachable(MQTT_HOST, MQTT_PORT);
  Serial.printf("[DIAG] TCP reachability: %s\n", tcpOK ? "OK" : "FALLO");

  WiFiClientSecure test;
  test.setCACert(MQTT_TLS_ROOT_CA);
  if (test.connect(MQTT_HOST, MQTT_PORT)) {
    Serial.println("[DIAG] TLS preflight OK");
    test.stop();
  } else {
    Serial.println("[DIAG] TLS preflight FALLO");
  }
}
