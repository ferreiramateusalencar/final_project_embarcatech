#ifndef SSD1306_H
#define SSD1306_H

#include "ssd1306_i2c.h"

void ssd1306_init();
void ssd1306_clear();
void ssd1306_draw_string(int x, int y, const char* str, int size);
void ssd1306_show();

#endif // SSD1306_H