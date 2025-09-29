#include "pantalla.h"

SPIClass touchSPI(VSPI);
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

static uint8_t buf[320 * 240 / 10 * 2];

#define TOUCH_MIN_X 200
#define TOUCH_MAX_X 3750
#define TOUCH_MIN_Y 332
#define TOUCH_MAX_Y 3853

#define LV_HOR_RES 320 // Resolución horizontal de tu pantalla
#define LV_VER_RES 240

hw_timer_t *reloj = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
volatile bool flagms = false;

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
  timerAlarmWrite(reloj, 15000, true); // 10 ms
  timerAlarmEnable(reloj);
}

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)px_map, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  if (touch.touched())
  {
    TS_Point p = touch.getPoint();
    int16_t cal_x = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, LV_HOR_RES);
    int16_t cal_y = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, LV_VER_RES);
    data->point.x = cal_x;
    data->point.y = cal_y;
    data->state = LV_INDEV_STATE_PR;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void iniciarPantalla()
{
  lv_init();

  // ✅ Corrección: asignar función de tick correctamente
  lv_tick_set_cb([]() -> uint32_t
                 { return (uint32_t)millis(); });

  tft.begin();
  tft.setRotation(1);

  // ✅ Corrección: crear display después de lv_init
  lv_display_t *display = lv_display_create(320, 240);
  lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(display, my_disp_flush);

  // Inicializar touch
  touchSPI.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);
  touch.begin(touchSPI);
  touch.setRotation(1);
  lv_indev_t *touch_indev = lv_indev_create();
  lv_indev_set_type(touch_indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(touch_indev, my_touchpad_read);

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
