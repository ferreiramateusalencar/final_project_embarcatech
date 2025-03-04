#include "inc/joystick.h"
#include "inc/sensor_data.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

// Definição dos pinos dos LEDs RGB
#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12

int joystick_init() {
    stdio_init_all();
    printf("Inicializando joystick...\n");
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);

    // Inicializa os pinos dos LEDs RGB
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);

    return 0;
}

void joystick_read(int *x, int *y) {
    adc_select_input(0);
    *y = adc_read();
    adc_select_input(1);
    *x = adc_read();
}

void rgb_led_set_color(uint8_t r, uint8_t g, uint8_t b) {
    gpio_put(RED_PIN, r);
    gpio_put(GREEN_PIN, g);
    gpio_put(BLUE_PIN, b);
}

void process_joystick_data() {
    int x, y;
    joystick_read(&x, &y);

    temperatura = y * 50 / 4095;
    umidade = x * 100 / 4095;

    const char *status;
    if (temperatura >= 10 && temperatura <= 30 && umidade >= 30 && umidade <= 70) {
        rgb_led_set_color(0, 1, 0); // Verde
        status = "Dentro das condições normais";
    } else if ((temperatura >= 5 && temperatura < 10) || (temperatura > 30 && temperatura <= 35) ||
               (umidade >= 20 && umidade < 30) || (umidade > 70 && umidade <= 80)) {
        rgb_led_set_color(1, 1, 0); // Amarelo
        status = "Condição de alerta";
    } else {
        rgb_led_set_color(1, 0, 0); // Vermelho
        status = "Péssimas condições";
    }
    printf("Temperatura: %.2f Graus Celsius, Umidade: %.2f%%, Status: %s\n", temperatura, umidade, status);
}