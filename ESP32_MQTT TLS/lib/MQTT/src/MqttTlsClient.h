#pragma once
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// =========================
// Macros configurables
// =========================
#ifndef WIFI_SSID
#define WIFI_SSID "DESKTOP-PP5LO6R 1839"
#endif

#ifndef WIFI_PASS
#define WIFI_PASS "|36i07L8"
#endif

#ifndef MQTT_HOST
#define MQTT_HOST "prueba-ogas.sytes.net"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 8883
#endif

#ifndef MQTT_USER
#define MQTT_USER "Marcelo"
#endif

#ifndef MQTT_PASS
#define MQTT_PASS "Vema.0405"
#endif

#ifndef MQTT_CLIENT_ID
#define MQTT_CLIENT_ID "Marcelo"
#endif

#ifndef MQTT_SUB_TOPIC
#define MQTT_SUB_TOPIC "CEPE/ESP32_1/Rele1"
#endif

#ifndef MQTT_PUB_TOPIC
#define MQTT_PUB_TOPIC "CEPE/ESP32_1/Sernsor"
#endif

#ifndef MQTT_LWT_TOPIC
#define MQTT_LWT_TOPIC "CEPE/ESP32_1/status"
#endif

#ifndef MQTT_LWT_MSG_OFF
#define MQTT_LWT_MSG_OFF "offline"
#endif

#ifndef MQTT_LWT_MSG_ON
#define MQTT_LWT_MSG_ON "online"
#endif

// Certificado raíz
extern const char MQTT_TLS_ROOT_CA[];

// Inicialización MQTT
void initMqtt();
void mqttLoop();
