
#ifndef LV_CONF_H
#define LV_CONF_H

/*====================
   VERSION INFO
 *====================*/


/*====================
   GENERAL SETTINGS
 *====================*/
#define LV_USE_OS                         0
#define LV_COLOR_DEPTH                    16
#define LV_COLOR_16_SWAP                  0
#define LV_COLOR_SCREEN_TRANSP            1
#define LV_MEM_SIZE                       (32U * 2024U)
#define LV_MEM_CUSTOM                     0
#define LV_MEMCPY_MEMSET_STD              0
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE       1
#define LV_ATTRIBUTE_MEM_ALIGN
#define LV_HOR_RES_MAX                    160
#define LV_VER_RES_MAX                    128
#define LV_DPI_DEF                        130
#define LV_USE_ASSERT_NULL                1
#define LV_USE_ASSERT_MALLOC              1
#define LV_USE_ASSERT_OBJ                 0
#define LV_USE_USER_DATA                  1
#define LV_USE_LOG                        0

/*====================
   TICK SETTINGS
 *====================*/
#define LV_TICK_CUSTOM                    1
#if LV_TICK_CUSTOM
    #define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
    #define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif

/*====================
   DRAW SETTINGS
 *====================*/
#define LV_DRAW_COMPLEX                   1
#define LV_CIRCLE_CACHE_SIZE              4
#define LV_LAYER_SIMPLE_BUF_SIZE          (8 * 1024)
#define LV_LAYER_SIMPLE_FALLBACK_BUF_SIZE (2 * 1024)
#define LV_DISP_ROT_MAX_BUF               (8 * 1024)

/*====================
   FONT SETTINGS
 *====================*/
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_DEFAULT &lv_font_montserrat_14
#define LV_USE_FONT_PLACEHOLDER 1
#define LV_USE_QRCODE 1
/*====================
   TEXT SETTINGS
 *====================*/
#define LV_TXT_ENC LV_TXT_ENC_UTF8
#define LV_TXT_BREAK_CHARS " ,.;:-_"
#define LV_TXT_COLOR_CMD "#"

/*====================
   WIDGET SETTINGS
 *====================*/
#define LV_USE_BTN        1
#define LV_USE_LABEL      1
#define LV_USE_SLIDER     1
#define LV_USE_SWITCH     1
#define LV_USE_CHECKBOX   1
#define LV_USE_DROPDOWN   1
#define LV_USE_TEXTAREA   1
#define LV_USE_TABLE      1
#define LV_USE_ARC        1
#define LV_USE_BAR        1
#define LV_USE_CHART      1
#define LV_USE_IMG        1
#define LV_USE_CANVAS     1
#define LV_USE_ROLLER     1
#define LV_USE_LIST       1
#define LV_USE_METER      1

/*====================
   THEMES
 *====================*/
#define LV_USE_THEME_DEFAULT    1
#if LV_USE_THEME_DEFAULT
    #define LV_THEME_DEFAULT_DARK    0
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif

/*====================
   DEMO SETTINGS
 *====================*/
#define LV_BUILD_EXAMPLES 0
#define LV_USE_DEMO_WIDGETS 0
#define LV_USE_DEMO_BENCHMARK 0
#define LV_USE_DEMO_MUSIC 0
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0
#define LV_USE_DEMO_STRESS 0

#endif /* LV_CONF_H */
