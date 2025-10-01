#include "MqttTlsClient.h"

const char MQTT_TLS_ROOT_CA[] PROGMEM = R"PEM(
-----BEGIN CERTIFICATE-----
MIIFGzCCAwOgAwIBAgIUGBKDnkh8ZjTCcvr+ePhuQ7d2FVwwDQYJKoZIhvcNAQEL
BQAwHTEbMBkGA1UEAwwSTW9zcXVpdHRvLUxvY2FsLUNBMB4XDTI1MDkyOTIwMjA0
N1oXDTM1MDkyNzIwMjA0N1owHTEbMBkGA1UEAwwSTW9zcXVpdHRvLUxvY2FsLUNB
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAvt89cxndjlR0r39TFOb7
WJ9TzWrChuKrDhXPg0G7K78HTbWX9UP7N/dtNxwuizhP83fuIU67fTa8+ImK5YsM
XRKntjQ+q70cczKwQSfAP0281B6gm4whxxULEUwqGRhUj60tTVqep6d8j/s86cHq
jCVoYt/Zu7Dp8/elffO5YSealRUxj19SGDwLBIZatmxhPAdPWJJeBKqiadIxEP9N
ZhK3AFcFcsz3wY3ieTfxOJXnsxoOo6POcMqGEneDSQon2ncVqQlBOQMpIJAvTkH3
eeCsv1EnKyg3GQFvBPtaPwGx7hw9zXLGPuxBJIS51j4edExygrQuPOFBEIR0e8bw
f+8MvKUYYZu1k3eRoT92Yz/iPH2xm5o9DvvuXbmz8aNui/yeIwOguF9Kg3l4wTpt
TaLhZX9om/jTnkEZoEjn/nQGDNaO719H7vrUoGnflgR0mUFerLYz6NiodEXZBVou
hKDJ3PqZw7/mKyNr5z4009fLJrH6DOSlMJt6hV5CRw2QnX5s7ha2GSSDmH9WPiba
GCXdwGhAUt224A3U6SCAncmjuhlbuH1n1a84+HyMPW1a9diNLD5r2qHGjVCMy1W4
2yZbUlUfiP47TdsrAqAi1kQKfg1/wbo1bMyfjnSCe3zoCF1HjV0cE7HXI8otmLSG
LtwRn1VQnL33olNIua4h+s0CAwEAAaNTMFEwHQYDVR0OBBYEFJ2qTrK++GryCJgf
YZ9CKnbNjkDuMB8GA1UdIwQYMBaAFJ2qTrK++GryCJgfYZ9CKnbNjkDuMA8GA1Ud
EwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggIBAGz0iHDeBlBMLstlEb7QW7TN
KZJciiuYnylC5fUYpK7GyTUBux3Ll2s219mKThlgvs21UkJDlwKZ0je+pV7kuy5Y
HVke1Pa03HXiFYvZP5GsqSGZFBNpTLVAzUMCBqUnCLs/Gc/vb1+rPDrCrGZ2f9G9
W+D8FHmoFrFEsvYqad7ElXclogBpVN93Ho9f6wYA6+JSxOnNk37MX+XBcHq619RD
rjQVl2m/LHfO3aaOwZ5/Epdac2NbW5ViNiqdslmCkB2PRHqkPY7AZSHk/e5jVttw
jtL3RCf8T9YekgvDdHsOvHijEKHyQl0o3dIKkIKDWqPF0mTiTfisR+NEhjFZm3D2
VT/54WxXxgS+i0UbGU3n0SHmnX6u6Fo56zJk2DQOw2jxn9kj2eeHxKZdsbutwrYD
AgbwhrxxFcb82MeLgiLthMfpvHmPD/9Jhd47s0dwEkRVFGY2TFrioHbIDMgVd4+E
YH8S+Js8akw6e7pfPFrkRHwZEp7Nb3Y1DfpFffobahbG0w7lYOASXUx93ukIQbI4
w7JzybHfAOtM8/kftaNh9CtEYsxPuGevlPHJXPP4v1VjF8AJaEkP0zOfg/rupPFK
De05y1SlxrTMpox8mKlCC6a4oL2XRKeAOYcInnLLJPyGHF6qskqP6FmDp8r1PPfQ
Ijv+0n6tPl53K4sYDJO1
-----END CERTIFICATE-----
)PEM";

WiFiClientSecure secureClient;  
// Cliente seguro basado en TLS/SSL, usado para conexiones cifradas.

PubSubClient mqtt(secureClient);  
// Cliente MQTT que se apoya en secureClient para conectarse con TLS al broker.

// =====================================================================
// CALLBACK: se ejecuta cada vez que llega un mensaje al ESP32 desde MQTT
// =====================================================================
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  Serial.printf("[MQTT] Mensaje en '%s': ", topic);  
  // Imprime el tópico donde llegó el mensaje.

  for (unsigned i = 0; i < length; i++) Serial.write(payload[i]);  
  // Recorre el payload recibido y lo imprime por el puerto serie.
  if (length > 0 && isdigit(payload[0])) {
    int num = payload[0] - '0';  // Convierte el primer caracter a número (0-9)
    digitalWrite(15, num);
  }
  Serial.println();  
  // Salto de línea después del mensaje.

  mqtt.publish(MQTT_PUB_TOPIC, "OK, recibido por ESP32");  
  // Envía una confirmación al tópico de salida definido en las macros.
}

// =====================================================================
// ensureMqtt: mantiene la conexión MQTT activa, con reintentos
// =====================================================================
static void ensureMqtt() {
  while (!mqtt.connected()) {  
    // Mientras no esté conectado al broker...
    Serial.printf("[MQTT] Conectando a %s:%u ...\n", MQTT_HOST, MQTT_PORT);

    // Intenta conectarse con credenciales y configurando Last Will & Testament
    bool ok = mqtt.connect(
      MQTT_CLIENT_ID,       // Identificador del cliente
      MQTT_USER, MQTT_PASS, // Usuario y contraseña
      MQTT_LWT_TOPIC,       // Tópico LWT (última voluntad)
      1, true,              // QoS=1, Retained=true
      MQTT_LWT_MSG_OFF,     // Mensaje que enviará el broker si se desconecta abruptamente
      true                  // clean session
    );

    if (ok) {
      // Si se conectó con éxito:
      Serial.println("[MQTT] Conectado ✔");
      mqtt.publish(MQTT_LWT_TOPIC, MQTT_LWT_MSG_ON, true);  
      // Publica "online" en el tópico LWT para avisar que está vivo.

      mqtt.subscribe(MQTT_SUB_TOPIC);  
      // Se suscribe al tópico de entrada definido en macros.
    } else {
      // Si falló la conexión:
      Serial.printf("[MQTT] Falló (rc=%d). Reintento...\n", mqtt.state());
      delay(3000);  
      // Espera 3 segundos antes de intentar nuevamente.
    }
  }
}

// =====================================================================
// initMqtt: inicializa TLS + configuración MQTT
// =====================================================================
void initMqtt() {
  secureClient.setCACert(MQTT_TLS_ROOT_CA);  
  // Carga el certificado raíz para validar al broker.

  secureClient.setTimeout(15);  
  // Configura el timeout general de conexión.

  secureClient.setHandshakeTimeout(15);  
  // Timeout específico para el handshake TLS.

  mqtt.setBufferSize(1024);  
  // Aumenta el tamaño máximo de payload MQTT a 1024 bytes.

  mqtt.setServer(MQTT_HOST, MQTT_PORT);  
  // Configura el host y puerto del broker MQTT.

  mqtt.setCallback(onMqttMessage);  
  // Define la función que manejará mensajes entrantes.

  ensureMqtt();  
  // Intenta conectarse al broker con la configuración previa.
}

// =====================================================================
// mqttLoop: mantener conexión y publicar mensajes periódicos
// =====================================================================
void mqttLoop() {
  if (!mqtt.connected()) ensureMqtt();  
  // Si se perdió la conexión, vuelve a intentar.

  mqtt.loop();  
  // Mantiene la conexión viva y procesa mensajes entrantes.

  static uint32_t t0 = 0;  
  // Marca de tiempo para controlar publicaciones periódicas.

  if (millis() - t0 > 5000) {  
    // Cada 5 segundos...
    t0 = millis();
    mqtt.publish(MQTT_PUB_TOPIC, "Hola desde ESP32 por TLS 8883");  
    // Publica un mensaje al tópico de salida.
  }
}