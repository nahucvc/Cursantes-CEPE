#include "interruptores.h"
#include "screens.h"
void escribirRele(int rele, uint8_t Estado)
{
    static bool PinesConfigurados = 1;

    if (PinesConfigurados)
    {
        pinMode(SW1, OUTPUT);
        digitalWrite(SW1,HIGH);
        pinMode(SW2, OUTPUT);
        digitalWrite(SW2,HIGH);
        pinMode(SW3, OUTPUT);
        digitalWrite(SW3,HIGH);
        pinMode(SW4, OUTPUT);
        digitalWrite(SW4,HIGH);
        PinesConfigurados = 0;
    }

    digitalWrite(rele, !Estado);

    if (rele == SW1)
    {
        if (Estado)
        {
            lv_obj_set_style_bg_color(objects.luz_rele1, lv_color_hex(0xff80bd9b), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(objects.luz_rele1, lv_color_hex(0xffec0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    if (rele == SW2)
    {
        if (Estado)
        {
            lv_obj_set_style_bg_color(objects.luz_rele2, lv_color_hex(0xff80bd9b), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(objects.luz_rele2, lv_color_hex(0xffec0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    if (rele == SW3)
    {
        if (Estado)
        {
            lv_obj_set_style_bg_color(objects.luz_rele3, lv_color_hex(0xff80bd9b), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(objects.luz_rele3, lv_color_hex(0xffec0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    if (rele == SW4)
    {
        if (Estado)
        {
            lv_obj_set_style_bg_color(objects.luz_rele4, lv_color_hex(0xff80bd9b), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(objects.luz_rele4, lv_color_hex(0xffec0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    Serial.printf("pin precionado %d, estado %d\n", rele, Estado);
    Serial.printf("estado de los pines %d, %d, %d,%d\n", digitalRead(SW1), digitalRead(SW2), digitalRead(SW3), digitalRead(SW4));
}