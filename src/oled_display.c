#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "./inc/joystick.h"
#include "./inc/sensor_data.h"
#include "./inc/ssd1306.h"
#include "./inc/ssd1306_font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

#define WIDTH 128
#define HEIGHT 64

extern float temperatura;
extern float umidade;

static ssd1306_t ssd;

int oled_display_init() {
    printf("Inicializando display OLED...\n");
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    return 0;
}

void oled_display_update() {
    char temp_str[32];
    char hum_str[32];

    snprintf(temp_str, sizeof(temp_str), "TEMPERATURA: %.2f%%", temperatura);
    snprintf(hum_str, sizeof(hum_str), "UMIDADE: %.2f%%", umidade);

    ssd1306_fill(&ssd, false);
    ssd1306_draw_string(&ssd, "DADOS DO SENSOR", 8, 10);
    ssd1306_draw_string(&ssd, temp_str, 20, 30);
    ssd1306_draw_string(&ssd, hum_str, 15, 48);
    ssd1306_send_data(&ssd);
}