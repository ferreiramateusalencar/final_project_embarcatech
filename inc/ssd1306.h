#ifndef SSD1306_H
#define SSD1306_H

#include "hardware/i2c.h"
#include "ssd1306_i2c.h"

typedef struct {
    int width;
    int height;
    int pages;
    uint8_t address;
    i2c_inst_t *i2c_port;
    uint8_t *ram_buffer;
    uint8_t port_buffer[2];
    int bufsize;
} ssd1306_t;

extern void calculate_render_area_buffer_length(struct render_area *area);
extern void ssd1306_send_command(uint8_t cmd);
extern void ssd1306_send_command_list(uint8_t *ssd, int number);
extern void ssd1306_send_buffer(uint8_t ssd[], int buffer_length);
extern void ssd1306_init(ssd1306_t *ssd, uint8_t width, uint8_t height, bool external_vcc, uint8_t address, i2c_inst_t *i2c);
extern void ssd1306_scroll(bool set);
extern void render_on_display(uint8_t *ssd, struct render_area *area);
extern void ssd1306_set_pixel(uint8_t *ssd, int x, int y, bool set);
extern void ssd1306_draw_line(uint8_t *ssd, int x_0, int y_0, int x_1, int y_1, bool set);
extern void ssd1306_draw_char(ssd1306_t *ssd, char c, uint8_t x, uint8_t y);
extern void ssd1306_draw_string(ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y);
extern void ssd1306_command(ssd1306_t *ssd, uint8_t command);
extern void ssd1306_config(ssd1306_t *ssd);
extern void ssd1306_init_bm(ssd1306_t *ssd, uint8_t width, uint8_t height, bool external_vcc, uint8_t address, i2c_inst_t *i2c);
extern void ssd1306_send_data(ssd1306_t *ssd);
extern void ssd1306_draw_bitmap(ssd1306_t *ssd, const uint8_t *bitmap);
extern void ssd1306_fill(ssd1306_t *ssd, bool value);

#endif // SSD1306_H