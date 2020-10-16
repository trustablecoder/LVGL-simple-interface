#include <stdio.h>
#include <string.h>
#if LV_USE_BTN
#if LV_USE_TEXTAREA && LV_USE_KEYBOARD
#if LV_USE_SWITCH

static uint8_t x = 10;
static uint8_t y = 10;
bool t = false;
lv_obj_t *scr3;
static lv_obj_t *ta1;
static lv_obj_t *kb;
static lv_obj_t * deger;
static uint8_t s = 0;
static lv_obj_t * slider;
bool switch_state = false;


static char  str[20] = "default";

static void ta_event_cb(lv_obj_t * ta, lv_event_t event);
static void switch_event(lv_obj_t * obj, lv_event_t event);

//Artırma azaltma fonksiyonları
void x_artirma(lv_obj_t *btn, lv_event_t event){
    if (event == LV_EVENT_CLICKED){
        x++;

        lv_obj_del(lv_scr_act());
        ayarlar();}
}

void x_azaltma(lv_obj_t *btn, lv_event_t event){
    if (event == LV_EVENT_CLICKED){
        x--;
        lv_obj_del(lv_scr_act());
        ayarlar();
    }
    
}

void y_artirma(lv_obj_t *btn, lv_event_t event){
    if (event == LV_EVENT_CLICKED){
        y++;
        lv_obj_del(lv_scr_act());
        ayarlar();
    }
    
}

void y_azaltma(lv_obj_t *btn, lv_event_t event){
    if (event == LV_EVENT_CLICKED){
        y--;
        lv_obj_del(lv_scr_act());
        ayarlar();
    }

   
}

static void cbx_fonksiyonu(lv_obj_t * obj, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED){
       if(t==true){
           t=false;
        }
       else if(t==false){
           t=true;
        }
        lv_obj_del(lv_scr_act());
        ayarlar();
    }
    
}


void anasayfaya_don(lv_obj_t *btn, lv_event_t event){
    
    if(event == LV_EVENT_CLICKED) {
        lv_obj_del(lv_scr_act());
        anasayfa();
    }

}


void menuye_git(lv_obj_t *btn, lv_event_t event){
    
    if(event == LV_EVENT_RELEASED) {
        lv_obj_del(lv_scr_act());
        menu();
    }

}

static void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        //texti yenile
        s = lv_slider_get_value(slider);
        lv_label_set_text_fmt(deger, "%d", s);
    }
}


void menu(){
    lv_obj_t *scr2 = lv_obj_create(NULL, NULL);
    lv_scr_load(scr2);
    lv_obj_t * label1 =  lv_label_create(scr2, NULL);
    lv_label_set_text(label1, "MENU"); //label ismi
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -140); //label konumu

    static lv_style_t style_btn_red;
    static lv_style_t style_btn;
    //stil oluşturma
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 10);
    lv_style_set_bg_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_bg_grad_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_bg_grad_dir(&style_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    //basıldığında renk değiştirir
    lv_style_set_bg_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_grad_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_SILVER);

    //kenar stili
    lv_style_set_border_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_border_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_border_width(&style_btn, LV_STATE_DEFAULT, 2);

    //farklı kenar stili ekle
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED, LV_COLOR_BLUE);
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);

    //text stili ekle
    lv_style_set_text_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    //butona basıldığında daha küçük yap
    lv_style_set_transform_height(&style_btn, LV_STATE_PRESSED, -5);
    lv_style_set_transform_width(&style_btn, LV_STATE_PRESSED, -10);

    //geçiş ekle
    static lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

    lv_style_set_transition_prop_1(&style_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    lv_style_set_transition_prop_2(&style_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_time(&style_btn, LV_STATE_DEFAULT, 300);
    lv_style_set_transition_path(&style_btn, LV_STATE_DEFAULT, &path);

    //style_btn_red 
    lv_style_init(&style_btn_red);
    lv_style_set_bg_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_bg_grad_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_MAROON);
    lv_style_set_bg_color(&style_btn_red, LV_STATE_PRESSED, LV_COLOR_MAROON);
    lv_style_set_bg_grad_color(&style_btn_red, LV_STATE_PRESSED, LV_COLOR_RED);
    lv_style_set_text_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_obj_t * kapatma = lv_btn_create(scr2, NULL); //buton oluşturma
    lv_obj_align(kapatma, NULL, LV_ALIGN_CENTER, 100, -140);  //konum
    lv_obj_set_size(kapatma, 40, 40); //boyut
    lv_obj_reset_style_list(kapatma, LV_BTN_PART_MAIN);  //temadan gelen stili sil
    lv_obj_add_style(kapatma, LV_BTN_PART_MAIN, &style_btn); //style_btn temasını ekle
    lv_obj_add_style(kapatma, LV_BTN_PART_MAIN, &style_btn_red); //style_btn_red temasını ekle
    lv_obj_set_style_local_radius(kapatma, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE); //local stili ekle
    lv_obj_set_event_cb(kapatma, anasayfaya_don); //fonksiyon çağırma

    lv_obj_t * labelk = lv_label_create(kapatma, NULL); //buton labelı
    lv_label_set_text(labelk, "X"); //label ismi


    //slider
    slider = lv_slider_create(lv_scr_act(), NULL);
    lv_obj_set_width(slider, 200);   //genişlik ayarlama
    lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);  //konum
    lv_slider_set_range(slider, 0 , 150);//slider aralığı
    lv_obj_set_event_cb(slider, slider_event_cb); //callback fonksiyonu
    //slider labeli
    deger = lv_label_create(scr2, NULL);
    lv_slider_set_value(slider, s, LV_ANIM_OFF);
    lv_label_set_text_fmt(deger, "%d", s);
    lv_obj_set_auto_realign(slider, true); //To keep center alignment when the width of the text changes
    lv_obj_align(deger, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);  //Align below the slider

    //switch
    lv_obj_t *sw1 = lv_switch_create(scr2, NULL);
    lv_obj_align(sw1, NULL, LV_ALIGN_CENTER, 0, -50);
    lv_obj_set_event_cb(sw1, switch_event);
    if(switch_state==false){
        lv_switch_off(sw1, LV_ANIM_OFF);
    }
    else if(switch_state==true){
        lv_switch_on(sw1, LV_ANIM_OFF);
    }

}

void ayarlara_git(lv_obj_t *btn, lv_event_t event){
    
    if(event == LV_EVENT_RELEASED) {
        lv_obj_del(lv_scr_act());
        ayarlar();
    }

}



void ayarlar(){
    scr3 = lv_obj_create(NULL, NULL);
    lv_scr_load(scr3);
    lv_obj_t * label1 =  lv_label_create(scr3, NULL);
    lv_label_set_text(label1, "AYARLAR"); //label ismi
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -140); //label konumu

    //X
    lv_obj_t * xl =  lv_label_create(scr3, NULL);
    lv_label_set_text_fmt(xl, "X: %d", x); //label ismi
    lv_obj_align(xl, NULL, LV_ALIGN_CENTER, 0, -100); //label konumu
        
    //artı butonu
    lv_obj_t * btn_arti_x = lv_btn_create(scr3, NULL);
    lv_obj_set_event_cb(btn_arti_x, x_artirma); //fonksiyon çağırma
    lv_obj_align(btn_arti_x, NULL, LV_ALIGN_CENTER, 130, -100); //konum ayarlama
    lv_obj_set_size(btn_arti_x, 40, 40); //buton boyutu
    lv_obj_t * label3 = lv_label_create(btn_arti_x, NULL);
    lv_label_set_text(label3, "+");
    //eksi butonu
    lv_obj_t * btn_eksi_x = lv_btn_create(scr3, NULL);
    lv_obj_set_event_cb(btn_eksi_x, x_azaltma); //fonksiyon çağırma
    lv_obj_align(btn_eksi_x, NULL, LV_ALIGN_CENTER, 80, -100); //konum ayarlama
    lv_obj_set_size(btn_eksi_x, 40, 40); //buton boyutu
    lv_obj_t * label4 = lv_label_create(btn_eksi_x, NULL);
    lv_label_set_text(label4, "-");

    //Y
    lv_obj_t * yl =  lv_label_create(scr3, NULL);
    lv_label_set_text_fmt(yl, "Y: %d", y); //label ismi
    lv_obj_align(yl, NULL, LV_ALIGN_CENTER, 0, -60); //label konumu

    //artı butonu
    lv_obj_t * btn_arti_y = lv_btn_create(scr3, NULL);
    lv_obj_set_event_cb(btn_arti_y, y_artirma); //fonksiyon çağırma
    lv_obj_align(btn_arti_y, NULL, LV_ALIGN_CENTER, 130, -60); //konum ayarlama
    lv_obj_set_size(btn_arti_y, 40, 40); //buton boyutu
    lv_obj_t * label5 = lv_label_create(btn_arti_y, NULL);
    lv_label_set_text(label5, "+");
    //eksi butonu
    lv_obj_t * btn_eksi_y = lv_btn_create(scr3, NULL);
    lv_obj_set_event_cb(btn_eksi_y, y_azaltma); //fonksiyon çağırma
    lv_obj_align(btn_eksi_y, NULL, LV_ALIGN_CENTER, 80, -60); //konum ayarlama
    lv_obj_set_size(btn_eksi_y, 40, 40); //buton boyutu
    lv_obj_t * label6 = lv_label_create(btn_eksi_y, NULL);
    lv_label_set_text(label6, "-");

        
    //Checkbox
    lv_obj_t * cb1 = lv_checkbox_create(scr3, NULL);
    lv_checkbox_set_checked(cb1, t);
    lv_obj_align(cb1, NULL, LV_ALIGN_CENTER, -40, -60); //checkbox konumu
    lv_checkbox_set_text(cb1, " "); //checkbox yazısı
    lv_obj_set_event_cb(cb1, cbx_fonksiyonu); //checkbox callback


    //Text
    ta1 = lv_textarea_create(scr3, NULL); //text yaratma
    lv_obj_set_size(ta1, 100, 30); //boyut ayarlama
    lv_obj_align(ta1, NULL, LV_ALIGN_CENTER, 0, -10); //konum ayarlama
    lv_textarea_set_text(ta1, str); 
    lv_obj_set_event_cb(ta1, ta_event_cb); //callback

    //geri butonu
    lv_obj_t * ayarlar_buton = lv_btn_create(scr3, NULL);
    lv_obj_set_event_cb(ayarlar_buton, anasayfaya_don); //fonksiyon çağırma
    lv_obj_align(ayarlar_buton, NULL, LV_ALIGN_CENTER, -40, -100); //konum
    lv_obj_set_size(ayarlar_buton, 50, 40);//buton boyutu
    lv_obj_t * label = lv_label_create(ayarlar_buton, NULL);
    lv_label_set_text(label, "Geri");

}

void anasayfa(){
    lv_obj_t *scr1 = lv_obj_create(NULL, NULL);
    lv_scr_load(scr1);
    lv_obj_t * label1 =  lv_label_create(scr1, NULL);
    lv_label_set_text(label1, "ANASAYFA"); //label ismi
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -140); //label konumu

    
    //X
    lv_obj_t * xl =  lv_label_create(scr1, NULL);
    lv_label_set_text_fmt(xl, "X: %d", x); //label ismi
    lv_obj_align(xl, NULL, LV_ALIGN_CENTER, 0, -120); //label konumu
    //Y
    lv_obj_t * yl =  lv_label_create(scr1, NULL);
    lv_label_set_text_fmt(yl, "Y: %d", y); //label ismi
    lv_obj_align(yl, NULL, LV_ALIGN_CENTER, 0, -100); //label konumu
    //T
    lv_obj_t * tl =  lv_label_create(scr1, NULL);
    lv_label_set_text_fmt(tl, "T: %d", t); //label ismi
    lv_obj_align(tl, NULL, LV_ALIGN_CENTER, 0, -80); //label konumu
    //Text
    lv_obj_t * tx =  lv_label_create(scr1, NULL);
    lv_label_set_text_fmt(tx, "Z: %s ", str); //label ismi
    lv_obj_align(tx, NULL, LV_ALIGN_CENTER, 0, -60); //label konumu
    //Slider(s)
    lv_obj_t * sl =  lv_label_create(scr1, NULL);
    lv_label_set_text_fmt(sl, "S: %d", s); //label ismi
    lv_obj_align(sl, NULL, LV_ALIGN_CENTER, 0, -40); //label konumu
    //Switch
    lv_obj_t * swl =  lv_label_create(scr1, NULL);
    lv_label_set_text_fmt(swl, "Switch: %d", switch_state); //label ismi
    lv_obj_align(swl, NULL, LV_ALIGN_CENTER, 0, -20); //label konumu

    
    //Menü butonu
    lv_obj_t * btn1 = lv_btn_create(scr1, NULL);
    lv_obj_set_event_cb(btn1, menuye_git); //fonksiyon çağırma
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 30);
    lv_obj_set_size(btn1, 120, 50);
    lv_obj_t * label2 = lv_label_create(btn1, NULL);
    lv_label_set_text(label2, "Menu");

    //Ayarlar butonu
    lv_obj_t * btn2 = lv_btn_create(scr1, NULL);
    lv_obj_set_event_cb(btn2, ayarlara_git); //fonksiyon çağırma-callback
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 100); //konum ayarlama
    lv_obj_set_size(btn2, 120, 50); //buton boyutu
    lv_obj_t * label3 = lv_label_create(btn2, NULL);
    lv_label_set_text(label3, "Ayarlar");


}



static void ta_event_cb(lv_obj_t * ta, lv_event_t event)

{
    if(event== LV_EVENT_CLICKED){
        //klavye
        kb = lv_keyboard_create(scr3, NULL);
        lv_keyboard_set_cursor_manage(kb, true);
        lv_keyboard_set_textarea(kb, ta);
        
    }

    if(event == LV_EVENT_VALUE_CHANGED){
        strcpy(str, lv_textarea_get_text(ta));
    }
}

static void switch_event(lv_obj_t * obj, lv_event_t event){
    if (event == LV_EVENT_VALUE_CHANGED){
       if(switch_state==true){
           switch_state=false;
        }
       else if(switch_state==false){
           switch_state=true;
        }
        lv_obj_del(lv_scr_act());
        menu();
    }

}



#endif
#endif
#endif