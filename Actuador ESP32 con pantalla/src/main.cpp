#include <Arduino.h>
#include "pantalla.h"
#include <ui.h>
#include <teclado.h>
#include "interruptores.h"
void setup(void)
{
Serial.begin(115200);
iniciarPantalla();
ui_init();
IniciarTeclado();

}

void loop()
{
lv_timer_handler();
delay(10);
}