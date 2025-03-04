#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/joystick.h"
#include "inc/oled_display.h"
#include "inc/wifi.h"

int main() {
    stdio_init_all();
    printf("Inicializando sistema...\n");

    // Inicializa os componentes do sistema
    if (joystick_init() != 0) {
        printf("Erro ao inicializar o joystick\n");
        return 1;
    }
    printf("Joystick inicializado com sucesso\n");

    if (oled_display_init() != 0) {
        printf("Erro ao inicializar o display OLED\n");
        return 1;
    }
    printf("Display OLED inicializado com sucesso\n");

    wifi_init();

    while (1) {
        process_joystick_data();
        sleep_ms(1000);
    }

    return 0;
}