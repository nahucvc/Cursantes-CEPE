
#ifndef PANTALLA_H

#include <Arduino.h>
#include <lvgl.h>

#include <SPI.h>

// Resolución de la pantalla
static const uint16_t screenWidth  = 160;
static const uint16_t screenHeight = 128;





void iniciarPantalla(void);
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void actualiazarPantalla();

#endif