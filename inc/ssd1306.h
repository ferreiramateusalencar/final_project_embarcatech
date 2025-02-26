#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware/i2c.h"

#define ssd1306_height 64 // Define a altura do display (64 pixels)
#define ssd1306_width 128 // Define a largura do display (128 pixels)

typedef struct {
    uint8_t width, height, pages, address;
    i2c_inst_t *i2c_port;
    bool external_vcc;
    uint8_t *ram_buffer;
    size_t bufsize;
    uint8_t port_buffer[2];
} ssd1306_t;

void ssd1306_init(ssd1306_t *ssd, uint8_t width, uint8_t height, bool external_vcc, uint8_t address, i2c_inst_t *i2c_port);
void ssd1306_clear(ssd1306_t *ssd);
void ssd1306_show(ssd1306_t *ssd);
void ssd1306_draw_string(ssd1306_t *ssd, int x, int y, const char* str);
void ssd1306_fill(ssd1306_t *ssd, bool color);
void ssd1306_rect(ssd1306_t *ssd, int x, int y, int w, int h, bool color, bool fill);
void ssd1306_send_data(ssd1306_t *ssd);

#endif // SSD1306_H