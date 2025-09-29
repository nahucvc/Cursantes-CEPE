#include <Arduino.h>
#include "pantalla.h"
#include <ui.h>
#include <WiFi.h>

void setup()
{
  Serial.begin(115200);
  iniciarPantalla();
  ui_init();
}

void loop()
{
  actualiazarPantalla();

  delay(1);
}
