#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_enceder_led(lv_event_t * e);
extern void action_page_config(lv_event_t * e);
extern void action_ver_qr(lv_event_t * e);
extern void action_habilitar_ap(lv_event_t * e);
extern void action_ocultar_qr(lv_event_t * e);
extern void action_page_home(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/