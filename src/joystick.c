#include "./inc/joystick.h"
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