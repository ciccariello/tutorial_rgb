/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "lvgl.h"
#include <stdio.h>


#include "lv_example_pub.h"
#include "lv_example_image.h"
#include "bsp/esp-bsp.h"
#include "app_audio.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "widgets/lv_slider.h"

//static lv_obj_t * create_slider(lv_color_t color);

static bool light_2color_layer_enter_cb(void *layer);
static bool light_2color_layer_exit_cb(void *layer);
static void light_2color_layer_timer_cb(lv_timer_t *tmr);
static uint8_t rgbColor[3];
static uint8_t selected_rgbColor[3];
static uint8_t colour = 126;
//lv_obj_t * led1, * led2, * led3, * led4; 
static lv_obj_t * red_slider, * green_slider, * blue_slider, * intense_slider;
static lv_obj_t * slider_dec_label, * slider_hex_label;
typedef enum {
    LIGHT_CCK_WARM,
    LIGHT_CCK_COOL,
    LIGHT_CCK_MAX,
} LIGHT_CCK_TYPE;
typedef struct {
    uint8_t light_pwm;
    LIGHT_CCK_TYPE light_cck;
} light_set_attribute_t;
//typedef struct {
//    const lv_img_dsc_t *img_bg[2];
//
//    const lv_img_dsc_t *img_pwm_25[2];
//    const lv_img_dsc_t *img_pwm_50[2];
//    const lv_img_dsc_t *img_pwm_75[2];
//    const lv_img_dsc_t *img_pwm_100[2];
//} ui_light_img_t;

static lv_obj_t *page;
static time_out_count time_20ms, time_500ms;

static lv_obj_t *img_light_bg, *label_pwm_set;
//static lv_obj_t *img_light_pwm_25, *img_light_pwm_50, *img_light_pwm_75, *img_light_pwm_100, *img_light_pwm_0;

static light_set_attribute_t light_set_conf, light_xor;

//static const ui_light_img_t light_image = {
//    {&light_warm_bg,     &light_cool_bg},
//    {&light_warm_25,     &light_cool_25},
//    {&light_warm_50,     &light_cool_50},
//    {&light_warm_75,     &light_cool_75},
//    {&light_warm_100,    &light_cool_100},
//};

lv_layer_t light_2color_Layer = {
    .lv_obj_name    = "light_2color_Layer",
    .lv_obj_parent  = NULL,
    .lv_obj_layer   = NULL,
    .lv_show_layer  = NULL,
    .enter_cb       = light_2color_layer_enter_cb,
    .exit_cb        = light_2color_layer_exit_cb,
    .timer_cb       = light_2color_layer_timer_cb,
};

static void light_2color_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (LV_EVENT_FOCUSED == code) {
        lv_group_set_editing(lv_group_get_default(), true);
    } else if (LV_EVENT_KEY == code) {
        uint32_t key = lv_event_get_key(e);
        if (is_time_out(&time_500ms))
         {

            if (LV_KEY_RIGHT == key)
             {
                if( lv_slider_get_value(red_slider) > 0x13 )
                 {
 				    lv_slider_set_value( red_slider, lv_slider_get_value(red_slider) + 15, false);
 				    rgbColor[light_set_conf.light_cck] = lv_slider_get_value(red_slider) + 15;	
                 }			
//                lv_slider_set_value( red_slider, colour, false);

 				rgbColor[light_set_conf.light_cck] = lv_slider_get_value(red_slider);	
//                if( light_set_conf.light_pwm < 50 ) 
//                {
//                    light_set_conf.light_pwm += 25;
////                    lv_slider_set_value( red_slider, light_set_conf.light_pwm * 2, false);
////                    colour += 63; 
//                }
            } 
           else if (LV_KEY_LEFT == key) 
            {
//                colour -= 63;				
//			    lv_slider_set_value( red_slider, colour, false);
 			    if( lv_slider_get_value(red_slider) > 0x13 )
                 {
 				    lv_slider_set_value( red_slider, lv_slider_get_value(red_slider) - 15, false);
 				    rgbColor[light_set_conf.light_cck] = lv_slider_get_value(red_slider) - 15;	
                 }	
                 
 				rgbColor[light_set_conf.light_cck] = lv_slider_get_value(red_slider) ;		
//                if( light_set_conf.light_pwm > 0 ) 
//                 {
//                    light_set_conf.light_pwm -= 25;
////                    lv_slider_set_value( red_slider, light_set_conf.light_pwm * 2, false);
////                    colour -= 63; 
//             
//    }
            }
    char buf2[8];
    lv_snprintf(buf2, sizeof(buf2), "0x%02X\n", (int)lv_slider_get_value(red_slider));
    lv_label_set_text(slider_hex_label, buf2);            
            
//    lv_obj_align_to(slider_dec_label, slider_hex_label, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, +3);
                char buf[8];
                
    lv_snprintf(buf, sizeof(buf), "%d\n", (int)lv_slider_get_value(red_slider));
    lv_label_set_text(slider_dec_label, buf);
    lv_obj_align_to(slider_dec_label, slider_hex_label, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, -24);

    
    bsp_led_rgb_set(rgbColor[0],rgbColor[1] ,rgbColor[2]);         
            
        }
     } 
    else if( LV_EVENT_CLICKED == code ) 
     {
		
		                
		      if( light_set_conf.light_pwm < 100 ) 
                {
					selected_rgbColor[light_set_conf.light_cck] = lv_slider_get_value(red_slider);
                    light_set_conf.light_pwm += 25;
//                    lv_slider_set_value( red_slider, light_set_conf.light_pwm * 2, false);
//                    colour += 63; 
                }
               else
                {
                    light_set_conf.light_pwm = 0;
//                    lv_slider_set_value( red_slider, light_set_conf.light_pwm * 2, false);
//                    colour += 63; 
                }
		                                 // if is true returns LIGHT_CCK_COOL else it returns LIGHT_CCK_WARM , is a toggler
//        light_set_conf.light_cck = ( LIGHT_CCK_WARM == light_set_conf.light_cck ) ? (LIGHT_CCK_COOL) : (LIGHT_CCK_WARM);
//        if( light_set_conf.light_cck == LIGHT_CCK_COOL )
//         {
//            lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_GREEN), LV_PART_KNOB);
//            lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_GREEN), LV_OPA_40), LV_PART_INDICATOR);   		
//		 }
//		else 
//		 {
//            lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_RED ), LV_PART_KNOB);
//            lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_RED ), LV_OPA_40), LV_PART_INDICATOR); 
//         }
//        lv_slider_set_value( red_slider, light_set_conf.light_pwm * 1, false);	
     } 
    else if( LV_EVENT_LONG_PRESSED == code ) 
     {
        lv_indev_wait_release(lv_indev_get_next(NULL));
        ui_remove_all_objs_from_encoder_group();
        lv_func_goto_layer(&menu_layer);
     }
}

void ui_light_2color_init(lv_obj_t *parent)
{
    light_xor.light_pwm = 0xFF;
    light_xor.light_cck = LIGHT_CCK_MAX;
    rgbColor[0] = 51;
    rgbColor[1] = 0;
	rgbColor[2] = 0;
    light_set_conf.light_pwm = 0;
    light_set_conf.light_cck = LIGHT_CCK_WARM;

    page = lv_obj_create(parent);
    lv_obj_set_size(page, LV_HOR_RES, LV_VER_RES);
    //lv_obj_set_size(page, lv_obj_get_width(lv_obj_get_parent(page)), lv_obj_get_height(lv_obj_get_parent(page)));

    lv_obj_set_style_border_width(page, 5, 0);
    lv_obj_set_style_border_color(page,  lv_color_make(255, 0, 0), 0);
    lv_obj_set_style_radius(page, LV_RADIUS_CIRCLE, 0);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_center(page);
    lv_obj_refr_size(page);

//    img_light_bg = lv_img_create(page);
//    lv_img_set_src(img_light_bg, &light_warm_bg);
//    lv_obj_align(img_light_bg, LV_ALIGN_CENTER, 0, 0);

    label_pwm_set = lv_label_create(page);
    lv_obj_set_style_text_font(label_pwm_set, &HelveticaNeue_Regular_24, 0);
    if (light_set_conf.light_pwm) {
        lv_label_set_text_fmt(label_pwm_set, "%d%%", light_set_conf.light_pwm);
    } else {
        lv_label_set_text(label_pwm_set, "--");
    }
    lv_obj_align(label_pwm_set, LV_ALIGN_CENTER, 0, 65);
//    img_light_pwm_0 = lv_img_create(page);
//    lv_img_set_src(img_light_pwm_0, &light_close_status);
//    lv_obj_add_flag(img_light_pwm_0, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_align(img_light_pwm_0, LV_ALIGN_TOP_MID, 0, 0);
//
//    img_light_pwm_25 = lv_img_create(page);
//    lv_img_set_src(img_light_pwm_25, &light_warm_25);
//    lv_obj_align(img_light_pwm_25, LV_ALIGN_TOP_MID, 0, 0);
//
//    img_light_pwm_50 = lv_img_create(page);
//    lv_img_set_src(img_light_pwm_50, &light_warm_50);
//    lv_obj_align(img_light_pwm_50, LV_ALIGN_TOP_MID, 0, 0);
//
//    img_light_pwm_75 = lv_img_create(page);
//    lv_img_set_src(img_light_pwm_75, &light_warm_75);
//    lv_obj_add_flag(img_light_pwm_75, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_align(img_light_pwm_75, LV_ALIGN_TOP_MID, 0, 0);
//
//    img_light_pwm_100 = lv_img_create(page);
//    lv_img_set_src(img_light_pwm_100, &light_warm_100);
//    lv_obj_add_flag(img_light_pwm_100, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_align(img_light_pwm_100, LV_ALIGN_TOP_MID, 0, 0);
    

    red_slider = lv_slider_create(page);
    lv_slider_set_range(red_slider, 0, 255);
    lv_obj_set_size(red_slider, 200, 10);
    lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_RED), LV_PART_KNOB);
    lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_RED), LV_OPA_40), LV_PART_INDICATOR);    
//    red_slider = create_slider(lv_palette_main(LV_PALETTE_RED));
        
        
    lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
    
    lv_obj_align(red_slider, LV_ALIGN_LEFT_MID, 3, -35);
    

    
          slider_hex_label = lv_label_create(page);
        lv_obj_set_style_text_font(slider_hex_label, &HelveticaNeue_Regular_24, 0);
      lv_obj_set_style_text_color(slider_hex_label, lv_color_hex(0xff0000), LV_PART_MAIN);        
    lv_label_set_text(slider_hex_label, "0x3A");

    lv_obj_align_to(slider_hex_label, red_slider, LV_ALIGN_OUT_TOP_MID, 0, -35);  
    
//            slider_dec_label = lv_label_create(page);
//        lv_obj_set_style_text_font(slider_dec_label, &HelveticaNeue_Regular_24, 0);
//      lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0xff0000), LV_PART_MAIN);        
//    lv_label_set_text(slider_dec_label, "50");
//
//    lv_obj_align_to(slider_dec_label, red_slider, LV_ALIGN_OUT_TOP_MID, -7, -8);

            slider_dec_label = lv_label_create(page);
        lv_obj_set_style_text_font(slider_dec_label, &HelveticaNeue_Regular_24, 0);
      lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0xff0000), LV_PART_MAIN);        
    lv_label_set_text(slider_dec_label, "51");

    lv_obj_align_to(slider_dec_label, slider_hex_label, LV_ALIGN_OUT_BOTTOM_RIGHT, -3, +3);
    
    
//        green_slider = create_slider(lv_palette_main(LV_PALETTE_GREEN));
//        
//        
//    lv_slider_set_value(green_slider, LV_OPA_20, LV_ANIM_OFF);
//    
//    lv_obj_align(green_slider, LV_ALIGN_LEFT_MID, 8, 0);
    
// led1 = lv_led_create(lv_scr_act());
//lv_obj_align(led1, LV_ALIGN_CENTER, 0, -82);
//lv_led_set_brightness(led1, 255);
//lv_led_set_color(led1, lv_color_make(colour , 0x0, 0x0));
//lv_led_on(led1);
//
///*Copy the previous LED and set a brightness*/
// led2 = lv_led_create(lv_scr_act());
//lv_obj_align(led2, LV_ALIGN_CENTER, 0, -50);
//lv_led_set_brightness(led2, 255);
//lv_led_set_color(led2, lv_color_make( 0x0,colour , 0x0));
//lv_led_on(led2);
//
///*Copy the previous LED and set a brightness*/
// led3 = lv_led_create(lv_scr_act());
//lv_obj_align(led3, LV_ALIGN_CENTER, 0, -18);
//lv_led_set_brightness(led3, 255);
//lv_led_set_color(led3, lv_color_make( 0x0, 0x0,colour ));
//lv_led_on(led3);
//
///*Copy the previous LED and set a brightness*/
// led4 = lv_led_create(lv_scr_act());
//lv_obj_align(led4, LV_ALIGN_CENTER, 0, 16);
//lv_led_set_brightness(led4, 255);
//lv_led_set_color(led4, lv_color_make(colour , colour ,colour ));
//lv_led_on(led4);
    

    lv_obj_add_event_cb(red_slider, light_2color_event_cb, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(red_slider, light_2color_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(red_slider, light_2color_event_cb, LV_EVENT_KEY, NULL);
//    lv_obj_add_event_cb(red_slider, light_2color_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    ui_add_obj_to_encoder_group(red_slider); 


//    lv_obj_add_event_cb(page, light_2color_event_cb, LV_EVENT_FOCUSED, NULL);
//    lv_obj_add_event_cb(page, light_2color_event_cb, LV_EVENT_KEY, NULL);
//    lv_obj_add_event_cb(page, light_2color_event_cb, LV_EVENT_LONG_PRESSED, NULL);
//    lv_obj_add_event_cb(page, light_2color_event_cb, LV_EVENT_CLICKED, NULL);
//    ui_add_obj_to_encoder_group(page);    
    
//    lv_obj_add_event_cb(red_slider, light_2color_event_cb, LV_EVENT_CLICKED, NULL);
//    lv_obj_add_event_cb(red_slider, light_2color_event_cb, LV_EVENT_KEY, NULL);
//  
//    ui_add_obj_to_encoder_group(red_slider);    

}


static bool light_2color_layer_enter_cb(void *layer)
{
    bool ret = false;

    LV_LOG_USER("");
    lv_layer_t *create_layer = layer;
    if (NULL == create_layer->lv_obj_layer) {
        ret = true;
        create_layer->lv_obj_layer = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(create_layer->lv_obj_layer);
        lv_obj_set_size(create_layer->lv_obj_layer, LV_HOR_RES, LV_VER_RES);

        ui_light_2color_init(create_layer->lv_obj_layer);
        set_time_out(&time_20ms, 20);
        set_time_out(&time_500ms, 250);
                /*Copy the previous LED and set a brightness*/

    }

    return ret;
}

static bool light_2color_layer_exit_cb(void *layer)
{
    LV_LOG_USER("");
    bsp_led_rgb_set(0x00, 0x00, 0x00);
    return true;
}

static void light_2color_layer_timer_cb(lv_timer_t *tmr)
{
    uint32_t RGB_color = 0xFF;

    feed_clock_time();

    if( is_time_out(&time_20ms) ) 
     {
        // bitwise XOR operation  1 ^ 1 = 0
        if( (light_set_conf.light_pwm ^ light_xor.light_pwm) || (light_set_conf.light_cck ^ light_xor.light_cck) ) 
         {
            light_xor.light_pwm = light_set_conf.light_pwm;
            light_xor.light_cck = light_set_conf.light_cck;

//            if( LIGHT_CCK_COOL == light_xor.light_cc k) 
//             {
//                RGB_color = (0xFF * light_xor.light_pwm / 100) << 16 | (0xFF * light_xor.light_pwm / 100) << 8 | (0xFF * light_xor.light_pwm / 100) << 0;
//             } 
//            else 
//             {
//                RGB_color = (0xFF * light_xor.light_pwm / 100) << 16 | (0xFF * light_xor.light_pwm / 100) << 8 | (0x33 * light_xor.light_pwm / 100) << 0;
//             }

//            lv_obj_add_flag(img_light_pwm_100, LV_OBJ_FLAG_HIDDEN);
//            lv_obj_add_flag(img_light_pwm_75, LV_OBJ_FLAG_HIDDEN);
//            lv_obj_add_flag(img_light_pwm_50, LV_OBJ_FLAG_HIDDEN);
//            lv_obj_add_flag(img_light_pwm_25, LV_OBJ_FLAG_HIDDEN);
//            lv_obj_add_flag(img_light_pwm_0, LV_OBJ_FLAG_HIDDEN);

            if( light_set_conf.light_pwm ) 
             {
                lv_label_set_text_fmt(label_pwm_set, "%d%%", light_set_conf.light_pwm);
             } 
            else 
             {
                lv_label_set_text(label_pwm_set, "--");
             }

//            uint8_t cck_set = (uint8_t)light_xor.light_cck;


//            if( light_set_conf.light_pwm == 50 ) 
//             {
//                  lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_BLUE), LV_PART_KNOB);
//                  lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_BLUE), LV_OPA_40), LV_PART_INDICATOR); 
//                  lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
//                  lv_obj_set_style_text_color(slider_dec_label, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_PART_MAIN);        
//                  bsp_led_rgb_set(0x00, 0x00, colour );    
//             }
//             else if (light_set_conf.light_pwm == 25 ) 
//             {
//				  lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_GREEN), LV_PART_KNOB);
//                  lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_GREEN), LV_OPA_40), LV_PART_INDICATOR);
//                  lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
//                  lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0x00ff00), LV_PART_MAIN);        
//                  lv_label_set_text(slider_dec_label, "50");
//                  bsp_led_rgb_set(0x00,colour, 0x00 );   
//
//
//             } 
//            else if (light_set_conf.light_pwm == 0) 
//            {
// 				  lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_RED ), LV_PART_KNOB);
//                  lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_RED ), LV_OPA_40), LV_PART_INDICATOR);
//                  lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
//                  lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0xff0000), LV_PART_MAIN);        
//                  lv_label_set_text(slider_dec_label, "50");    
//                  bsp_led_rgb_set(colour,0x00, 0x00 );   
//            }

            switch( light_set_conf.light_pwm ) 
             {
				
            case 100:
////                lv_obj_clear_flag(img_light_pwm_100, LV_OBJ_FLAG_HIDDEN);
////                lv_img_set_src(img_light_pwm_100, light_image.img_pwm_100[cck_set]);
////                lv_obj_set_style_img_recolor_opa(img_light_pwm_100, 128, 0);
////                lv_obj_set_style_img_recolor( img_light_pwm_100, lv_color_make(0xFF,0x00,0x00), 0 );
                  ui_remove_all_objs_from_encoder_group();
                  lv_func_goto_layer(&menu_layer);
                  break;
            case 75:
//                  selected_rgbColor[2] = rgbColor[2];
                  lv_obj_add_flag(red_slider, LV_OBJ_FLAG_HIDDEN);
                  lv_obj_add_flag(slider_hex_label, LV_OBJ_FLAG_HIDDEN);
                  lv_obj_add_flag(slider_dec_label, LV_OBJ_FLAG_HIDDEN);
                  
                  lv_obj_set_style_border_width(page, 7, 0);
                  lv_obj_set_style_border_color(page,  lv_color_make( selected_rgbColor[0], selected_rgbColor[1], selected_rgbColor[2] ), 0);
                  lv_obj_set_style_radius(page, LV_RADIUS_CIRCLE, 0);
                  lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
                  lv_obj_center(page);
                  lv_obj_refr_size(page);

                  bsp_led_rgb_set(selected_rgbColor[0],selected_rgbColor[1],selected_rgbColor[2] );              
                  break;
                  
             case 50:
//                  selected_rgbColor[1] = rgbColor[1];
                  rgbColor[0] = 0;
			      rgbColor[1] = 0;
			      rgbColor[2] = 0;  
                  lv_obj_set_style_border_width(page, 5, 0);
                  lv_obj_set_style_border_color(page,  lv_color_make(0, 0, 255), 0);
                  lv_obj_set_style_radius(page, LV_RADIUS_CIRCLE, 0);
                  lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
                  lv_obj_center(page);
                  lv_obj_refr_size(page);             
                  lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_BLUE), LV_PART_KNOB);
                  lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_BLUE), LV_OPA_40), LV_PART_INDICATOR); 
                  lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
                  lv_obj_set_style_text_color(slider_hex_label, lv_color_hex(0x0000ff), LV_PART_MAIN);      
                  lv_label_set_text(slider_hex_label, "0x33");                
                  lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0x0000ff), LV_PART_MAIN);      
                  lv_label_set_text(slider_dec_label, "51"); 
                  lv_obj_align_to(slider_dec_label, slider_hex_label, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 0);
                  light_set_conf.light_cck = LIGHT_CCK_MAX; 
                                    
//                lv_obj_clear_flag(img_light_pwm_25, LV_OBJ_FLAG_HIDDEN);
//                lv_img_set_src(img_light_pwm_25, light_image.img_pwm_25[cck_set]);
//                lv_img_set_src(img_light_bg, light_image.img_bg[cck_set]); 
                  bsp_led_rgb_set(0x00, 0x00, 55 );              
                break;           
              case 25:
//                  selected_rgbColor[0] = rgbColor[0];
                  rgbColor[0] = 0;
			      rgbColor[1] = 0;
			      rgbColor[2] = 0; 
                  lv_obj_set_style_border_width(page, 5, 0);
                  lv_obj_set_style_border_color(page,  lv_color_make(0, 255, 0), 0);
                  lv_obj_set_style_radius(page, LV_RADIUS_CIRCLE, 0);
                  lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
                  lv_obj_center(page);
                  lv_obj_refr_size(page);              
                  lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_GREEN), LV_PART_KNOB);
                  lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_GREEN), LV_OPA_40), LV_PART_INDICATOR);
                  lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
                  lv_obj_set_style_text_color(slider_hex_label, lv_color_hex(0x00ff00), LV_PART_MAIN);      
                  lv_label_set_text(slider_hex_label, "0x33");                   
                  lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0x00ff00), LV_PART_MAIN);        
                  lv_label_set_text(slider_dec_label, "51");
                  lv_obj_align_to(slider_dec_label, slider_hex_label, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 0);
                  light_set_conf.light_cck = LIGHT_CCK_COOL;
            
                  bsp_led_rgb_set(0x00,55 , 0x00 ); 
//                lv_obj_clear_flag(img_light_pwm_50, LV_OBJ_FLAG_HIDDEN);
//                lv_img_set_src(img_light_pwm_50, light_image.img_pwm_50[cck_set]);
//                lv_obj_set_style_img_recolor_opa(img_light_pwm_50, 255, 0);
//                lv_obj_set_style_img_recolor( img_light_pwm_50, lv_color_make(0x00,0xFF,0x00), 0 );
                break;
            case 0:
                  lv_obj_set_style_border_width(page, 5, 0);
                  lv_obj_set_style_border_color(page,  lv_color_make(255, 0, 0), 0);
                  lv_obj_set_style_radius(page, LV_RADIUS_CIRCLE, 0);
                  lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
                  lv_obj_center(page);
                  lv_obj_refr_size(page);
                  lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_RED ), LV_PART_KNOB);
                  lv_obj_set_style_bg_color(red_slider, lv_color_darken(lv_palette_main(LV_PALETTE_RED ), LV_OPA_40), LV_PART_INDICATOR);
                  lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
                  lv_obj_set_style_text_color(slider_hex_label, lv_color_hex(0xff0000), LV_PART_MAIN);      
                  lv_label_set_text(slider_hex_label, "0x33");                  
                  lv_obj_set_style_text_color(slider_dec_label, lv_color_hex(0xff0000), LV_PART_MAIN);        
                  lv_label_set_text(slider_dec_label, "51");
//                  lv_obj_align_to(slider_dec_label, slider_hex_label, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, -24);
                  light_set_conf.light_cck = LIGHT_CCK_WARM;                  
                  rgbColor[0] = 0;
			      rgbColor[1] = 0;
			      rgbColor[2] = 0;
//                lv_obj_clear_flag(img_light_pwm_0, LV_OBJ_FLAG_HIDDEN);
//                lv_img_set_src(img_light_bg, &light_close_bg);
////
////                audio_handle_info(SOUND_TYPE_SNORE ); 
                  bsp_led_rgb_set(55 ,0x00, 0x00 );           
                break;
            default:
                break;
//            
             }
             
//              bsp_led_rgb_set(colour,0x00, 0x00 );        
        /*Copy the previous LED and set a brightness*/
//lv_led_set_color(led1, lv_color_make(colour , 0x0, 0x0));
////lv_led_on(led1);
//
///*Copy the previous LED and set a brightness*/
//
//lv_led_set_color(led2, lv_color_make( 0x0,colour , 0x0));
//lv_led_on(led2);
//
///*Copy the previous LED and set a brightness*/
//
//lv_led_set_color(led3, lv_color_make( 0x0, 0x0,colour ));
////lv_led_on(led3);
//
///*Copy the previous LED and set a brightness*/
//
//lv_led_set_color(led4, lv_color_make(0x00 , colour ,0x00 ));
//lv_led_on(led4);            
       
        }
        
        

    }
}

//static lv_obj_t * create_slider(lv_color_t color)
//{
//    lv_obj_t * slider = lv_slider_create(lv_scr_act());
//    lv_slider_set_range(slider, 0, 255);
//    lv_obj_set_size(slider, 200, 10);
//    lv_obj_set_style_bg_color(slider, color, LV_PART_KNOB);
//    lv_obj_set_style_bg_color(slider, lv_color_darken(color, LV_OPA_40), LV_PART_INDICATOR);
////    lv_event_send(slider, LV_EVENT_VALUE_CHANGED, NULL);
////    lv_event_send(slider, LV_EVENT_KEY, NULL);
////    lv_obj_add_event_cb(slider, light_2color_event_cb, LV_EVENT_FOCUSED, NULL);
////    lv_obj_add_event_cb(slider, light_2color_event_cb, LV_EVENT_CLICKED, NULL);
////    lv_obj_add_event_cb(slider, light_2color_event_cb, LV_EVENT_KEY, NULL);
////    lv_obj_add_event_cb(slider, light_2color_event_cb, LV_EVENT_LONG_PRESSED, NULL);
////    ui_add_obj_to_encoder_group(slider); 
//    return slider;
//}

