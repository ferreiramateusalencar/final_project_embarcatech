#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "lwip/tcp.h"
#include "./lib/lwipopts.h"
#include "./inc/wifi.h"
#include "./inc/wifi_credentials.h" //Crie esse arquivo e adicione suas credenciais de rede Wi-Fi, conforme o exemplo comentado no final do código
#include "./inc/joystick.h"

extern float temperatura;
extern float umidade;

#define HTTP_RESPONSE_TEMPLATE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" \
                               "<!DOCTYPE html><html><body>" \
                               "<h1>Dados do sensor</h1>" \
                               "<p>Temperatura: %d &deg;C</p>" \
                               "<p>Umidade: %d%%</p>" \
                               "</body></html>\r\n" 

static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (p == NULL) {
        tcp_close(tpcb);
        return ERR_OK;
    }

    char http_response[256];
    snprintf(http_response, sizeof(http_response), HTTP_RESPONSE_TEMPLATE, (int)temperatura, (int)umidade);
    tcp_write(tpcb, http_response, strlen(http_response), TCP_WRITE_FLAG_COPY);
    pbuf_free(p);

    return ERR_OK;
}

static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, http_callback);
    return ERR_OK;
}

static void start_http_server(void) {
    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("Erro ao criar PCB\n");
        return;
    }

    if (tcp_bind(pcb, IP_ADDR_ANY, 80) != ERR_OK) {
        printf("Erro ao ligar o servidor na porta 80\n");
        return;
    }

    pcb = tcp_listen(pcb);
    tcp_accept(pcb, connection_callback);

    printf("Servidor HTTP rodando na porta 80...\n");
}

void wifi_init() {
    // Inicializa o chip Wi-Fi
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return;
    }
    // Habilita o modo estação
    cyw43_arch_enable_sta_mode();

    printf("Conectando o Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Falha na conexão.\n");
        return;
    } else {
        printf("Conectado!\n");
        uint8_t *ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
        printf("IP address %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    }

    printf("Sistema de monitoramento está Online\n");
    start_http_server(); // Inicia o servidor HTTP após conectar ao Wi-Fi
}

void wifi_update_data(float nova_temperatura, float nova_umidade) {
    temperatura = nova_temperatura;
    umidade = nova_umidade;
}

// Função para limpar recursos do Wi-Fi
void wifi_cleanup() {
    cyw43_arch_deinit();
}

/*
#ifndef WIFI_CREDENTIALS_H
#define WIFI_CREDENTIALS_H

#define WIFI_SSID "nome_da_rede"
#define WIFI_PASSWORD "senha_da_rede"

#endif // WIFI_CREDENTIALS_H
*/