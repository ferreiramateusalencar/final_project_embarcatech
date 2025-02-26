#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <stdio.h>
#include "ssd1306.h"

// Função para inicializar o display OLED
int oled_display_init();

// Função para mostrar a posição do joystick no display OLED
void oled_display_show_position(const char* buffer);

#endif // OLED_DISPLAY_H