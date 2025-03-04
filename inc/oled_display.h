#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

// Definições dos pinos SDA e SCL para I2C
extern const uint I2C_SDA;
extern const uint I2C_SCL;

// Variáveis externas para temperatura e umidade
extern float temperatura;
extern float umidade;

// Função para inicializar o display OLED
int oled_display_init(void);
void oled_display_update();

#endif // OLED_DISPLAY_H
