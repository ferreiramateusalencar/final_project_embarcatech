#include "include/joystick.h"
#include "include/wifi.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int joystick_init() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    return 0;
}

void joystick_read(int *x, int *y) {
    adc_select_input(0);
    *y = adc_read();
    adc_select_input(1);
    *x = adc_read();
}

int main() {
    joystick_init();
    wifi_init();

    while (1) {
        int x, y;
        joystick_read(&x, &y);

        int temperature = y * 50 / 4095;
        int humidity = x * 100 / 4095;

        // Atualiza os dados de temperatura e umidade no Wi-Fi
        wifi_update_data(temperature, humidity);

        sleep_ms(1000); // Ajuste o tempo conforme necessário
    }

    wifi_cleanup();
    return 0;
}