#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "inc/joystick.h"
#include "inc/oled_display.h"
#include "inc/wifi.h"
#include "inc/sensor_data.h"

// Variáveis globais para armazenar os dados do sensor
float temperatura = 0;
float umidade = 0;

int main() {
    stdio_init_all();
    printf("Inicializando sistema...\n");

    // Inicializa o joystick
    if (joystick_init() != 0) {
        printf("Erro ao inicializar o joystick\n");
        return 1;
    }
    printf("Joystick inicializado com sucesso\n");
    
    // Inicializa o Wi-Fi e o servidor HTTP
    wifi_init();

    // Inicializa o display OLED
    if (oled_display_init() != 0) {
        printf("Erro ao inicializar o display OLED\n");
        return 1;
    }
    printf("Display OLED inicializado com sucesso\n");

    while (1) {
        // Processa os dados do joystick
        printf("Processando dados do joystick...\n");
        process_joystick_data();

        // Atualiza a tela OLED com os dados de temperatura, umidade e status
        printf("Atualizando display OLED...\n");
        oled_display_update();

        // Aguarda um curto período antes da próxima leitura
        sleep_ms(1000);
    }

    return 0;
}