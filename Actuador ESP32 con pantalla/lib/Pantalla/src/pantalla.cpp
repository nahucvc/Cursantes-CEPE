#include "pantalla.h"
#include <Arduino_GFX_Library.h>
#define GFX_BL 8 // pin del led de retroiluminacion

Arduino_DataBus *bus = new Arduino_HWSPI(10 /* DC */, 12 /* CS */);
Arduino_GFX *gfx = gfx = new Arduino_ST7735(bus, 13 /* RST */, 1 /* rotation */, false /* IPS */,
                                            128 /* width */, 160 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */,
                                            0 /* col offset 2 */, 0 /* row offset 2 */, false /* BGR */);

#define LV_HOR_RES 160 // Resolución horizontal de tu pantalla
#define LV_VER_RES 128

hw_timer_t *reloj = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
volatile bool flagms = false;

static uint8_t buf[160 * 128 / 10 * 2];

void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);
  flagms = true; // Solo marcamos el flag
  portEXIT_CRITICAL_ISR(&timerMux);
  
}

void iniciar_timer()
{
  reloj = timerBegin(0, 80, true); // 80 MHz / 80 = 1 MHz → 1 tick = 1 µs
  timerAttachInterrupt(reloj, &onTimer, true);
  timerAlarmWrite(reloj, 60000, true); // 10 ms
  timerAlarmEnable(reloj);
}

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
 uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

 gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);

  
  lv_disp_flush_ready(disp);
}


void iniciarPantalla()
{
  lv_init();

  // ✅ Corrección: asignar función de tick correctamente
  lv_tick_set_cb([]() -> uint32_t
                 { return (uint32_t)millis(); });

  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);
  /* Encendido de la retroiluminación */
  /**/  pinMode(GFX_BL, OUTPUT);
  /**/ digitalWrite(GFX_BL, HIGH);

  gfx->setCursor(1, 1);
  gfx->setTextColor(RED);
  gfx->setTextSize(0);
  gfx->println("Hello World!");
  gfx->println("configurando equipo");
  lv_display_t *display = lv_display_create(320, 240);
  lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(display, my_disp_flush);
  iniciar_timer();
}

void actualiazarPantalla()
{
  if (flagms)
  {
    portENTER_CRITICAL(&timerMux);
    flagms = false;
    portEXIT_CRITICAL(&timerMux);

    lv_timer_handler();
  }
}
