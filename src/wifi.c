#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "lwip/tcp.h"
#include "./lib/lwipopts.h"
#include "./inc/wifi.h"
#include "./inc/sensor_data.h"
#include "./inc/wifi_credentials.h"

extern float temperatura;
extern float umidade;

#define HTTP_RESPONSE_TEMPLATE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" \
                               "<!DOCTYPE html><html><body>" \
                               "<h1>Dados de Temperatura e Umidade</h1>" \
                               "<p>Temperatura: %d</p>" \
                               "<p>Umidade: %d</p>" \
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
    if (cyw43_arch_init()) {
        printf("Erro ao inicializar o Wi-Fi\n");
        return;
    }

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Falha ao conectar ao Wi-Fi\n");
        return;
    }

    printf("Conectado ao Wi-Fi\n");
    start_http_server();
}

// Função para atualizar os dados de temperatura e umidade
void wifi_update_data(int nova_temperatura, int nova_umidade) {
    temperatura = nova_temperatura;
    umidade = nova_umidade;
}

// Função para limpar recursos do Wi-Fi
void wifi_cleanup() {
    cyw43_arch_deinit();
}