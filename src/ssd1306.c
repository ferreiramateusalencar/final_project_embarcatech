#include "inc/ssd1306.h"
#include "inc/ssd1306_i2c.h"
#include "inc/ssd1306_font.h"
#include <string.h> // Incluir o cabeçalho string.h

static uint8_t ssd1306_buffer[ssd1306_buffer_length];

void ssd1306_write_command(ssd1306_t *ssd, uint8_t command) {
    uint8_t buffer[2] = {0x00, command};
    i2c_write_blocking(ssd->i2c_port, ssd->address, buffer, 2, false);
}

void ssd1306_init(ssd1306_t *ssd, uint8_t width, uint8_t height, bool external_vcc, uint8_t address, i2c_inst_t *i2c_port) {
    ssd->width = width;
    ssd->height = height;
    ssd->external_vcc = external_vcc;
    ssd->address = address;
    ssd->i2c_port = i2c_port;
    ssd->bufsize = ssd1306_buffer_length;
    ssd->ram_buffer = ssd1306_buffer;

    // Inicializa o I2C
    i2c_init(i2c_port, ssd1306_i2c_clock * 1000);
    gpio_set_function(14, GPIO_FUNC_I2C); // Corrigir o nome da constante I2C_SDA
    gpio_set_function(15, GPIO_FUNC_I2C); // Corrigir o nome da constante I2C_SCL
    gpio_pull_up(14);
    gpio_pull_up(15);

    // Envia comandos de inicialização para o display OLED
    ssd1306_write_command(ssd, ssd1306_set_display | 0x00); // Display off
    ssd1306_write_command(ssd, ssd1306_set_display_clock_divide_ratio);
    ssd1306_write_command(ssd, 0x80); // Suggested ratio
    ssd1306_write_command(ssd, ssd1306_set_mux_ratio); // Corrigir o nome da constante
    ssd1306_write_command(ssd, ssd1306_height - 1);
    ssd1306_write_command(ssd, ssd1306_set_display_offset);
    ssd1306_write_command(ssd, 0x00); // No offset
    ssd1306_write_command(ssd, ssd1306_set_display_start_line | 0x00); // Start line
    ssd1306_write_command(ssd, ssd1306_set_charge_pump);
    ssd1306_write_command(ssd, 0x14); // Enable charge pump
    ssd1306_write_command(ssd, ssd1306_set_memory_mode);
    ssd1306_write_command(ssd, 0x00); // Horizontal addressing mode
    ssd1306_write_command(ssd, ssd1306_set_segment_remap | 0x01); // Column address 127 is mapped to SEG0
    ssd1306_write_command(ssd, ssd1306_set_common_output_direction | 0x08); // Corrigir o nome da constante
    ssd1306_write_command(ssd, ssd1306_set_common_pin_configuration); // Corrigir o nome da constante
    ssd1306_write_command(ssd, 0x12); // Alternative COM pin configuration
    ssd1306_write_command(ssd, ssd1306_set_contrast);
    ssd1306_write_command(ssd, 0xCF); // Set contrast
    ssd1306_write_command(ssd, ssd1306_set_precharge);
    ssd1306_write_command(ssd, 0xF1); // Set pre-charge period
    ssd1306_write_command(ssd, ssd1306_set_vcomh_deselect_level);
    ssd1306_write_command(ssd, 0x40); // Set VCOMH deselect level
    ssd1306_write_command(ssd, ssd1306_set_entire_on); // Entire display ON
    ssd1306_write_command(ssd, ssd1306_set_normal_display); // Set normal display
    ssd1306_write_command(ssd, ssd1306_set_display | 0x01); // Display on

    ssd1306_clear(ssd);
    ssd1306_show(ssd);
}

void ssd1306_clear(ssd1306_t *ssd) {
    memset(ssd->ram_buffer, 0, ssd->bufsize);
}

void ssd1306_show(ssd1306_t *ssd) {
    for (uint8_t page = 0; page < ssd1306_n_pages; page++) {
        ssd1306_write_command(ssd, ssd1306_set_page_address + page);
        ssd1306_write_command(ssd, ssd1306_set_column_address);
        ssd1306_write_command(ssd, 0);
        ssd1306_write_command(ssd, ssd1306_width - 1);

        uint8_t buffer[ssd1306_width + 1];
        buffer[0] = 0x40;
        memcpy(buffer + 1, ssd->ram_buffer + (page * ssd1306_width), ssd1306_width);
        i2c_write_blocking(ssd->i2c_port, ssd->address, buffer, sizeof(buffer), false);
    }
}

void ssd1306_draw_string(ssd1306_t *ssd, int x, int y, const char* str) {
    // Implementação da função para desenhar uma string no display
    // Esta função deve desenhar a string no buffer ssd->ram_buffer
    while (*str) {
        for (int i = 0; i < 8; i++) {
            ssd->ram_buffer[x + (y / 8) * ssd1306_width + i] = font[*str * 8 + i];
        }
        x += 8;
        str++;
    }
}

void ssd1306_fill(ssd1306_t *ssd, bool color) {
    memset(ssd->ram_buffer, color ? 0xFF : 0x00, ssd->bufsize);
}

void ssd1306_rect(ssd1306_t *ssd, int x, int y, int w, int h, bool color, bool fill) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            if (fill || i == x || i == x + w - 1 || j == y || j == y + h - 1) {
                ssd->ram_buffer[i + (j / 8) * ssd1306_width] |= (1 << (j % 8));
            }
        }
    }
}

void ssd1306_send_data(ssd1306_t *ssd) {
    ssd1306_show(ssd);
}
