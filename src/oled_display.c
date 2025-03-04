#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "./inc/ssd1306.h"
#include "hardware/i2c.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

extern float temperatura;  // Variável externa para temperatura
extern float umidade;      // Variável externa para umidade

int oled_display_init() {
    stdio_init_all();  // Inicializa os tipos stdio padrão presentes ligados ao binário

    // Inicialização do I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000); 
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // Zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // Inicializa o texto a ser exibido
    char temp_text[20];  // Buffer para a string da temperatura
    char hum_text[20];   // Buffer para a string da umidade

    // Formatar a string com os valores de temperatura e umidade
    sprintf(temp_text, "Temperatura: %.2f C", temperatura);
    sprintf(hum_text, "Umidade: %.2f%%", umidade);

    // Exibir as mensagens no display
    int y = 0;
    ssd1306_draw_string(ssd, 5, y, temp_text);
    y += 8;  // Aumenta o y para a próxima linha
    ssd1306_draw_string(ssd, 5, y, hum_text);

    // Renderizar as informações no display
    render_on_display(ssd, &frame_area);

    // Espera infinitamente para manter as informações no display
    while (true) {
        sleep_ms(1000);  // Aguarda 1 segundo entre atualizações
    }

    return 0;
}
