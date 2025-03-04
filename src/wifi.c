#include "wifi.h"
#include <stdio.h>
#include <string.h>
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "lwip/tcp.h"
#include "./inc/wifi_credentials.h"
#include "./inc/joystick.h"

#define LED_PIN 12

#define HTTP_RESPONSE_TEMPLATE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" \
                               "<!DOCTYPE html><html><body>" \
                               "<h1>Dados do Sensor</h1>" \
                               "<p>Temperatura: %.2f Graus Celsius</p>" \
                               "<p>Umidade: %.2f%%</p>" \
                               "<p><a href=\"/led/on\">Ligar LED</a></p>" \
                               "<p><a href=\"/led/off\">Desligar LED</a></p>" \
                               "</body></html>\r\n"

static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (p == NULL) {
        tcp_close(tpcb);
        return ERR_OK;
    }

    char *request = (char *)p->payload;

    if (strstr(request, "GET /led/on")) {
        gpio_put(LED_PIN, 1);
    } else if (strstr(request, "GET /led/off")) {
        gpio_put(LED_PIN, 0);
    }

    char http_response[512];
    snprintf(http_response, sizeof(http_response), HTTP_RESPONSE_TEMPLATE, temperatura, umidade);
    tcp_write(tpcb, http_response, strlen(http_response), TCP_WRITE_FLAG_COPY);
    pbuf_free(p);

    return ERR_OK;
}

static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, http_callback);
    return ERR_OK;
}

void start_http_server(void) {
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
    stdio_init_all();
    sleep_ms(10000);
    printf("Iniciando servidor HTTP\n");

    if (cyw43_arch_init()) {
        printf("Erro ao inicializar o Wi-Fi\n");
        return;
    }

    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi-Fi SSID: %s\n", WIFI_SSID);

    int result = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000);
    if (result) {
        printf("Falha ao conectar ao Wi-Fi, código de erro: %d\n", result);
        return;
    } else {
        printf("Conectado ao Wi-Fi\n");
        uint8_t *ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
        printf("Endereço IP %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    }

    printf("Wi-Fi conectado!\n");
    printf("Para ligar ou desligar o LED acesse o Endereço IP seguido de /led/on ou /led/off\n");

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    start_http_server();
}

// criei um arquivo chamado wifi_credentials.h dentro de inc/
/*
#ifndef WIFI_CREDENTIALS_H
#define WIFI_CREDENTIALS_H

#define WIFI_SSID "Embarcatech" // Substitua pelo nome da sua rede Wi-Fi
#define WIFI_PASS "sua_senha_wifi" // Substitua pela senha da sua rede Wi-Fi

#endif // WIFI_CREDENTIALS_H
*/