/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai); CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#ifndef LV_EXAMPLE_IMAGE_H
#define LV_EXAMPLE_IMAGE_H

#ifdef __cplusplus
extern "C"
 {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
LV_IMG_DECLARE(icon_light);
LV_IMG_DECLARE(icon_washing);
LV_IMG_DECLARE(segnale);
LV_IMG_DECLARE(icon_washing_ns);
LV_IMG_DECLARE(icon_thermostat_ns);
LV_IMG_DECLARE(icon_light_ns);

LV_IMG_DECLARE(light_close_bg);
LV_IMG_DECLARE(light_close_pwm);
LV_IMG_DECLARE(light_close_status);
LV_IMG_DECLARE(light_cool_100);
LV_IMG_DECLARE(light_cool_25);
LV_IMG_DECLARE(light_cool_50);
LV_IMG_DECLARE(light_cool_75);
LV_IMG_DECLARE(light_cool_bg);
LV_IMG_DECLARE(light_warm_100);
LV_IMG_DECLARE(light_warm_25);
LV_IMG_DECLARE(light_warm_50);
LV_IMG_DECLARE(light_warm_75);
LV_IMG_DECLARE(light_warm_bg);

LV_IMG_DECLARE(light_pwm_00);
LV_IMG_DECLARE(light_pwm_25);
LV_IMG_DECLARE(light_pwm_50);
LV_IMG_DECLARE(light_pwm_75);
LV_IMG_DECLARE(light_pwm_100);

LV_IMG_DECLARE(img_washing_bg);
LV_IMG_DECLARE(img_washing_wave1);
LV_IMG_DECLARE(img_washing_wave2);
LV_IMG_DECLARE(img_washing_bubble1);
LV_IMG_DECLARE(img_washing_bubble2);
LV_IMG_DECLARE(img_washing_stand);
LV_IMG_DECLARE(img_washing_shirt);
LV_IMG_DECLARE(img_washing_underwear);
LV_IMG_DECLARE(wash_underwear1);
LV_IMG_DECLARE(wash_underwear2);
LV_IMG_DECLARE(wash_shirt);
LV_IMG_DECLARE(wash_basic);
LV_IMG_DECLARE(wash_blouse);
LV_IMG_DECLARE(wash_briefs);

LV_IMG_DECLARE(AC_BG);
LV_IMG_DECLARE(AC_temper);
LV_IMG_DECLARE(AC_unit);

//LV_IMG_DECLARE(standby_eye_left);
//LV_IMG_DECLARE(standby_eye_right);
//LV_IMG_DECLARE(standby_eye_1);
//LV_IMG_DECLARE(standby_eye_2);
//LV_IMG_DECLARE(standby_eye_close);
////LV_IMG_DECLARE(standby_face);
LV_IMG_DECLARE(jojo);
LV_IMG_DECLARE(park);
LV_IMG_DECLARE(segnale);
LV_IMG_DECLARE(segnale_ns);
LV_IMG_DECLARE(parking);
LV_IMG_DECLARE(parking_ns);
LV_IMG_DECLARE(reverse);
//LV_IMG_DECLARE(standby_eye_1_fade);
//LV_IMG_DECLARE(standby_eye_3);
//LV_IMG_DECLARE(standby_eye_open);
//LV_IMG_DECLARE(standby_mouth_1);

LV_IMG_DECLARE(language_bg);
LV_IMG_DECLARE(language_bg_dither);
LV_IMG_DECLARE(language_select);
LV_IMG_DECLARE(language_unselect);

/********************************
 * font
********************************/
LV_FONT_DECLARE(font_cn_32);//ç¯å…‰
LV_FONT_DECLARE(font_cn_48);//æ´—æ¶¤å‰©ä½™æ—¶é—´

/*long press to end*/
//LV_FONT_DECLARE(HelveticaNeue_Regular_24);
LV_FONT_DECLARE(ui_font_Number);
/*0x20-0x7F*/
LV_FONT_DECLARE(HelveticaNeue_Regular_24);

/*0123456789ï¼š-*/
//LV_FONT_DECLARE(HelveticaNeue_Regular_24);

/*ä¸­æ–‡å·²æ¢å¤å‡ºåŽ‚*/
//LV_FONT_DECLARE(ui_font_Number);

/*0x20-0x7F*/
/*
é•¿æŒ‰ç»“æŸæ´—è¡£æ¨¡å¼æ’æ¸©å™¨ç…§æ˜Žæ¨¡å¼çº¢å¤–èƒŒå…‰å–‡å­ç¼–ç å™¨æˆåŠŸå¤±è´¥å·¦å³æŒ‰ä¸‹
å±å¹•æ­£å¸¸äº®æš—ä¸‹ä¸€æ­¥å·¦å³æ—‹æŒ‰ä¸‹å±å¹•æ­£å¸¸äº®æš—ä¸‹ä¸€æ­¥è·³å¸½å…ˆæŽ¥åŽå†ç­‰å¾…ç»“æžœ
*/
//LV_FONT_DECLARE(HelveticaNeue_Regular_24);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_EXAMPLE_IMAGE_H*/