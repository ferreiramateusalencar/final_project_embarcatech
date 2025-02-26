#include "inc/oled_display.h"
#include "inc/ssd1306.h"
#include "inc/ssd1306_font.h"
#include "inc/ssd1306_i2c.h"

static ssd1306_t ssd;

int oled_display_init() {
    ssd1306_init(&ssd, ssd1306_width, ssd1306_height, false, ssd1306_i2c_address, i2c1);
    ssd1306_clear(&ssd);
    return 0;
}

void oled_display_show_position(const char *str) {
    ssd1306_clear(&ssd);
    ssd1306_draw_string(&ssd, 0, 0, "DADOS DO SENSOR");
    ssd1306_draw_string(&ssd, 0, 16, str);
    ssd1306_show(&ssd);
}