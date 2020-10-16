#include "lvgl.h"
#include "app_hal.h"
#include "touchpad.h"

#include "lvgl_ornek.c"

int main(void)
{
	lv_init();

	hal_setup();
    anasayfa();
	hal_loop();
  
}
