#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>



// ====== CONFIG WIFI ======
const char* WIFI_SSID = "Ogas";
const char* WIFI_PASS = "Vero.0405";

// ====== CONFIG MQTT (SIN TLS) ======
const char* MQTT_HOST = "prueba-ogas.sytes.net"; // o IP del broker
const uint16_t MQTT_PORT = 7070;                 // SIN TLS
const char* MQTT_USER = "Marcelo";               // opcional
const char* MQTT_PASS = "Vema.0405";                 // opcional
const char* MQTT_CLIENT_ID = "ESP32-CarrascoRojas";

// Topics
const char* TOPIC_LWT       = "pruebas/equipo2/status";
const char* TOPIC_PUB       = "pruebas/equipo2/salida";
const char* TOPIC_SUB_1     = "pruebas/equipo2/in";
const char* TOPIC_SUB_2     = "pruebas/equipo2/comandos";
const char* TOPIC_SUB_WILDC = "pruebas/equipo2/#"; // comodín (opcional)

// Mensajes LWT
const char* LWT_MSG_OFF = "offline";
const char* LWT_MSG_ON  = "online";

WiFiClient net;             // <<< SIN TLS
PubSubClient mqtt(net);

// ---- Conexión WiFi ----
void connectWiFi() {
  Serial.printf("Conectando a WiFi '%s'...\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
    if (millis() - t0 > 30000) {
      Serial.println("\nTimeout WiFi. Reiniciando...");
      ESP.restart();
    }
  }
  Serial.printf("\nWiFi OK. IP: %s  GW: %s  DNS: %s\n",
    WiFi.localIP().toString().c_str(),
    WiFi.gatewayIP().toString().c_str(),
    WiFi.dnsIP().toString().c_str());
}

// ---- Callback de mensajes entrantes ----
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  Serial.printf("[MQTT] Mensaje en '%s' (%u bytes): ", topic, length);
  for (unsigned i = 0; i < length; i++) Serial.write(payload[i]);
  Serial.println();

  // Ejemplo: discriminar por tópico
  if (strcmp(topic,TOPIC_SUB_1) == 0) {
    int valor= payload[0];
    if (valor==49)
    {
      digitalWrite(15,HIGH);
    }else
    {
      digitalWrite(15,LOW);
    }
    

  } else if (strcmp(topic, TOPIC_SUB_2) == 0) {
    // hacer algo con TOPIC_SUB_2
  }
}

// ---- Re-conexión MQTT robusta ----
void ensureMqtt() {
  while (!mqtt.connected()) {
    Serial.printf("[MQTT] Conectando a %s:%u ...\n", MQTT_HOST, MQTT_PORT);

    // Con credenciales (si no usás, pasá NULL,NULL)
    bool ok = mqtt.connect(
      MQTT_CLIENT_ID,
      MQTT_USER, MQTT_PASS,
      TOPIC_LWT, 1, true, LWT_MSG_OFF, // LWT: QoS1 + retained
      true                             // clean session
    );

    if (ok) {
      Serial.println("[MQTT] Conectado ✔");
      mqtt.publish(TOPIC_LWT, LWT_MSG_ON, true); // avisar online

     
      mqtt.subscribe(TOPIC_SUB_1, 1);     // QoS 1
     
    } else {
      Serial.printf("[MQTT] Falló (rc=%d). Reintento en 3s...\n", mqtt.state());
      delay(3000);
    }
  }
}

void setup() {
  pinMode(15,OUTPUT);
  Serial.begin(115200);
  delay(100);
  connectWiFi();

  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setBufferSize(1024);
  mqtt.setCallback(onMqttMessage);


}

void loop() {
  if (!mqtt.connected()) ensureMqtt();
  mqtt.loop();

  // Publicación periódica cada 5 s
  static uint32_t t0 = 0;
  if (millis() - t0 > 5000) {
    t0 = millis();
    mqtt.publish(TOPIC_PUB,"Prueba de mensaje desde ESP32...");
  }
}
