#include <Arduino.h>
#include <lvgl.h>
#include "TFT_eSPI.h"
#include <SPI.h>
#include "XPT2046_Touchscreen.h"
// Resolución de la pantalla
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;


// SPI personalizado para el touch
#define TOUCH_CS   33
#define TOUCH_IRQ  36
#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CLK  25


void iniciarPantalla(void);
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void my_touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);
void actualiazarPantalla();