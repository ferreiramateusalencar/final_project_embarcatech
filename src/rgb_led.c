#include "include/rgb_led.h"
#include "pico/stdlib.h"

#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12

int rgb_led_init() {
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    return 0;
}

void rgb_led_set_color(int temperature, int humidity) {
    if (temperature > 35 || temperature < 15 || humidity > 80 || humidity < 20) {
        gpio_put(RED_PIN, 1);
        gpio_put(GREEN_PIN, 0);
        gpio_put(BLUE_PIN, 0);
    } else if (temperature > 30 || temperature < 20 || humidity > 70 || humidity < 30) {
        gpio_put(RED_PIN, 1);
        gpio_put(GREEN_PIN, 1);
        gpio_put(BLUE_PIN, 0);
    } else {
        gpio_put(RED_PIN, 0);
        gpio_put(GREEN_PIN, 1);
        gpio_put(BLUE_PIN, 0);
    }
}