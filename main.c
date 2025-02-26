#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "inc/joystick.h"
#include "inc/oled_display.h"
#include "inc/rgb_led.h"
#include "inc/ssd1306.h"

// I2C defines
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define SSD1306_ADDRESS 0x3C

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display OLED
    if (oled_display_init() != 0) {
        printf("Erro ao inicializar o display OLED\n");
        return 1;
    }

    // Timer example code - This example fires off the callback after 2000ms
    add_alarm_in_ms(2000, alarm_callback, NULL, false);

    printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));

    // Inicializa os componentes do sistema
    if (joystick_init() != 0) {
        printf("Erro ao inicializar o joystick\n");
        return 1;
    }
    if (rgb_led_init() != 0) {
        printf("Erro ao inicializar o LED RGB\n");
        return 1;
    }

    while (1) {
        // Lê a posição do joystick
        int x, y;
        joystick_read(&x, &y);

        // Calcula a temperatura e a umidade com base na posição do joystick
        int temperatura = y * 50 / 4095;
        int umidade = x * 100 / 4095;

        // Determina o status das condições
        const char *status;
        if (temperatura >= 10 && temperatura <= 30 && umidade >= 30 && umidade <= 70) {
            // Valores normais
            rgb_led_set_color(0, 255, 0); // Verde
            status = "Dentro das condições normais";
        } else if ((temperatura >= 5 && temperatura < 10) || (temperatura > 30 && temperatura <= 35) ||
                   (umidade >= 20 && umidade < 30) || (umidade > 70 && umidade <= 80)) {
            // Valores alterados
            rgb_led_set_color(255, 255, 0); // Amarelo
            status = "Condição de alerta";
        } else {
            // Valores muito alterados
            rgb_led_set_color(255, 0, 0); // Vermelho
            status = "Péssimas condições";
        }

        // Exibe as informações no console serial
        printf("Temperatura: %d Graus Celsius, Umidade: %d%%, Status: %s\n", temperatura, umidade, status);

        // Atualiza a tela OLED com os dados de temperatura, umidade e status
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "Temperatura: %d Graus Celsius\nUmidade: %d%%", temperatura, umidade);
        oled_display_show_position(buffer);

        // Aguarda um curto período antes da próxima leitura
        sleep_ms(1000);
    }

    return 0;
}