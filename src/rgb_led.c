#include "inc/rgb_led.h"
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

void rgb_led_set_color(int red, int green, int blue) {
    gpio_put(RED_PIN, red ? 1 : 0);
    gpio_put(GREEN_PIN, green ? 1 : 0);
    gpio_put(BLUE_PIN, blue ? 1 : 0);
}