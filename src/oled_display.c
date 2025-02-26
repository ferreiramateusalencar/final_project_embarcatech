#include "oled_display.h"
#include "ssd1306.h"
#include "ssd1306_font.h"
#include "ssd1306_i2c.h"

int oled_display_init() {
    ssd1306_init();
    ssd1306_clear();
    return 0;
}

void oled_display_show_position(int x, int y) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "X: %d, Y: %d", x, y);
    ssd1306_clear();
    ssd1306_draw_string(0, 0, buffer, 1);
    ssd1306_show();
}