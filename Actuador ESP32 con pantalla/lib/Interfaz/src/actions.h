#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_action_configurar(lv_event_t * e);
extern void action_action_verdatos_red(lv_event_t * e);
extern void action_action_volver_menu(lv_event_t * e);
extern void action_foco(lv_event_t * e);
extern void action_cambiar_estado_rele(lv_event_t * e);
extern void action_activar_ap(lv_event_t * e);
extern void action_volver_menu_config(lv_event_t * e);
extern void action_action_ver_qr(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/