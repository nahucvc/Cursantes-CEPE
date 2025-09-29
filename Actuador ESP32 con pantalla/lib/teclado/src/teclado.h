#ifndef Teclado_H
#define Teclado_H
#include <Arduino.h>

#include <lvgl.h>
#include <vector>
#include "screens.h"

void IniciarTeclado();
void encoder_read_cb(lv_indev_t * indev, lv_indev_data_t * data);
void actualizarGrupo(const std::vector<lv_obj_t*>& objetos);
#endif