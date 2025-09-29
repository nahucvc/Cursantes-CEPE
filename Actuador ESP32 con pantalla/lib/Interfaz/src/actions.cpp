#include "actions.h"
#include "screens.h"
#include <teclado.h>
#include "interruptores.h"
#include <WiFi.h>

void action_action_configurar(lv_event_t *e)
{

    lv_scr_load(objects.menu_config);
    actualizarGrupo({objects.volver_menu1, objects.boton_activar_ap});
}

void action_foco(lv_event_t *e)
{
    // Hacemos un cast explícito porque devuelve void *
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);

    if (lv_event_get_code(e) == LV_EVENT_FOCUSED)
    {
        lv_obj_set_style_bg_color(obj, lv_color_hex(0xff001ff9), LV_PART_MAIN | LV_STATE_DEFAULT);
        return;
    }
    if (lv_event_get_code(e) == LV_EVENT_DEFOCUSED)

    {
        lv_obj_set_style_bg_color(obj, lv_color_hex(0xffece2e2), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (obj == objects.luz_rele1)
        {
            escribirRele(SW1, !digitalRead(SW1));
        }
        if (obj == objects.luz_rele2)
        {
            escribirRele(SW2, !digitalRead(SW2));
        }
        if (obj == objects.luz_rele3)
        {
            escribirRele(SW3, !digitalRead(SW3));
        }
        if (obj == objects.luz_rele4)
        {
            escribirRele(SW4, !digitalRead(SW4));
        }
    }
}

void action_action_verdatos_red(lv_event_t *e)
{
}

void action_cambiar_estado_rele(lv_event_t *e)
{
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);
    int pin;
    if (obj == objects.luz_rele1)
        pin = SW1;
    if (obj == objects.luz_rele2)
        pin = SW2;
    if (obj == objects.luz_rele3)
        pin = SW3;
    if (obj == objects.luz_rele4)
        pin = SW4;
    escribirRele(pin, (digitalRead(pin)));
    Serial.printf("pin precionado %d\n", pin);
}

//-----------------menu Configuración----------------------
void action_action_volver_menu(lv_event_t *e)
{
    // TODO: Implement action action_volver_menu here
    lv_scr_load(objects.main);
    actualizarGrupo({objects.boton_config, objects.boton_de_red, objects.luz_rele1, objects.luz_rele2, objects.luz_rele3, objects.luz_rele4});
}

void action_activar_ap(lv_event_t *e)
{
    WiFi.softAP("RELE", "12345678");
    lv_obj_clear_flag(objects.ver_qr, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_state(objects.ver_qr, LV_STATE_DISABLED);
    actualizarGrupo({objects.boton_activar_ap, objects.ver_qr, objects.volver_menu1});
}
void action_volver_menu_config(lv_event_t *e)
{
    lv_scr_load(objects.menu_config);
    actualizarGrupo({objects.ver_qr, objects.boton_activar_ap, objects.volver_menu1});
}

void action_action_ver_qr(lv_event_t *e)
{
    lv_scr_load(objects.page_qr);
    actualizarGrupo({objects.volver_menuconfig});
}