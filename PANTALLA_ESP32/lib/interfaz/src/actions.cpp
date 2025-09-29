#include <Arduino.h>
#include <actions.h>
#include <ui.h>
#include "vars.h"
#include <WiFi.h>


void action_enceder_led(lv_event_t *e)
{
  static bool inicio = true;
  if (inicio)
  {
    ledcAttachPin(17, 1);
    ledcChangeFrequency(1, 20, 8);
    ledcWrite(1, 255);
    inicio = false;
  }

  static bool estado = false;
  
  if (estado)
  {
    ledcWrite(1, 255);
    estado = false;
  }
  else
  {
    ledcWrite(1, 0);
    estado = true;
  }

  printf("boton Presionado\n");
}

void action_page_config(lv_event_t *e)
{
  lv_scr_load(objects.config);
}

void action_ver_qr(lv_event_t *e)
{
  lv_obj_clear_flag(objects.qr, LV_OBJ_FLAG_HIDDEN);
}

void action_habilitar_ap(lv_event_t *e)
{
  static bool estado = true;
  if (estado)
  {
    lv_obj_clear_state(objects.qr_boton, LV_STATE_DISABLED);
    estado = false;
  }
  else
  {
    lv_obj_add_state(objects.qr_boton, LV_STATE_DISABLED);
    estado = true;
  }
}

void action_ocultar_qr(lv_event_t *e) 
{
    lv_obj_add_flag(objects.qr, LV_OBJ_FLAG_HIDDEN);
}

void action_page_home(lv_event_t *e) 
{
    lv_scr_load(objects.main);
}

