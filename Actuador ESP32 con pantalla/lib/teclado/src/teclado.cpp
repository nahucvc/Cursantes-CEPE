#include "teclado.h"
//--------------------Variables Globales---------------------------
static int32_t encoder_diff = 0;     // movimiento del encoder
static bool encoder_pressed = false; // estado del botón
hw_timer_t *timer1 = NULL;
portMUX_TYPE timerMux1 = portMUX_INITIALIZER_UNLOCKED;

lv_indev_t * teclas;   // dispositivo de entrada global
lv_group_t * group_main;  // grupo del menú principal
 




// Función de interrupción (se ejecuta cada 40 ms)
void IRAM_ATTR onTimer1()
{
    portENTER_CRITICAL_ISR(&timerMux1);
    float valor1 = touchRead(2); // Lee el valor capacitivo
    float valor2 = touchRead(4); // Lee el valor capacitivo
    float valor3 = touchRead(6); // Lee el valor capacitivo

    //loat f1 = kf.update(0, valor1);
   // float f2 = kf.update(1, valor2);
    //float f3 = kf.update(2, valor3);
    Serial.printf(">P1:%f\n>P2:%f\n>P3:%f\n", valor1, valor2, valor3);
    

    if (valor1>=11500)
    {
        encoder_diff=-1;
    }else
    if (valor3>=11800)
    {
       encoder_diff=1;
    }

    if (valor2>=12300&&valor3<11400&&valor1<11400)
    {
        encoder_pressed=true;
    }
    else
    {
        encoder_pressed=false;
    }
    

    portEXIT_CRITICAL_ISR(&timerMux1);
}

void IniciarTeclado()
{
    
    timer1 = timerBegin(1, 80, true);

    // Asocia la función de interrupción
    timerAttachInterrupt(timer1, &onTimer1, true);

    // Configura alarma: 40.000 µs = 40 ms
    timerAlarmWrite(timer1, 150000, true);

    // Habilita la alarma
    timerAlarmEnable(timer1);

    Serial.println("Timer configurado cada 10 ms");
    teclas = lv_indev_create();
    lv_indev_set_type(teclas, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(teclas, encoder_read_cb);
    group_main = lv_group_create();
    
    actualizarGrupo({objects.boton_config, objects.boton_de_red,objects.luz_rele1,objects.luz_rele2,objects.luz_rele3,objects.luz_rele4});
    lv_indev_set_group(teclas, group_main);
}

// Callback que LVGL llama para leer el encoder
void encoder_read_cb(lv_indev_t * indev, lv_indev_data_t * data) {
    data->enc_diff = encoder_diff;
    data->state = encoder_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    
    // Reiniciamos el movimiento una vez leído
    encoder_diff = 0;
}

void actualizarGrupo(const std::vector<lv_obj_t*>& objetos) {
    if(group_main == NULL) return;

    // 1️⃣ Eliminar todos los objetos actuales del grupo
    lv_group_remove_all_objs(group_main);

    // 2️⃣ Agregar los nuevos objetos del vector
    for(auto obj : objetos) {
        if(obj != NULL) {
            lv_group_add_obj(group_main, obj);
        }
    }

    // 3️⃣ (Opcional) enfocar el primer objeto del vector
    if(!objetos.empty() && objetos[0] != NULL) {
        lv_group_focus_obj(objetos[0]);
    }
}

