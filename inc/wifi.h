#ifndef WIFI_H
#define WIFI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

// Função para inicializar o Wi-Fi
void wifi_init();

// Função para atualizar os dados de temperatura e umidade
void wifi_update_data(float nova_temperatura, float nova_umidade);

// Função para limpar recursos do Wi-Fi
void wifi_cleanup();

#endif // WIFI_H