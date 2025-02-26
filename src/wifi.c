#include "include/wifi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "lwip/tcp.h"
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include "lwip/inet.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#define WIFI_SSID "your_ssid"
#define WIFI_PASSWORD "your_password"
#define SERVER_IP "192.168.1.100" // IP do servidor para onde os dados serão enviados
#define SERVER_PORT 8080

static int temperature = 0;
static int humidity = 0;

// Buffer para respostas HTTP
#define HTTP_RESPONSE_TEMPLATE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" \
                               "<!DOCTYPE html><html><body>" \
                               "<h1>Dados de Temperatura e Umidade</h1>" \
                               "<p>Temperatura: %d</p>" \
                               "<p>Umidade: %d</p>" \
                               "</body></html>\r\n"

// Função de callback para processar requisições HTTP
static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (p == NULL) {
        // Cliente fechou a conexão
        tcp_close(tpcb);
        return ERR_OK;
    }

    // Prepara a resposta HTTP com os dados de temperatura e umidade
    char http_response[256];
    snprintf(http_response, sizeof(http_response), HTTP_RESPONSE_TEMPLATE, temperature, humidity);

    // Envia a resposta HTTP
    tcp_write(tpcb, http_response, strlen(http_response), TCP_WRITE_FLAG_COPY);

    // Libera o buffer recebido
    pbuf_free(p);

    return ERR_OK;
}

// Callback de conexão: associa o http_callback à conexão
static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, http_callback);  // Associa o callback HTTP
    return ERR_OK;
}

// Função de setup do servidor TCP
static void start_http_server(void) {
    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("Erro ao criar PCB\n");
        return;
    }

    // Liga o servidor na porta 80
    if (tcp_bind(pcb, IP_ADDR_ANY, 80) != ERR_OK) {
        printf("Erro ao ligar o servidor na porta 80\n");
        return;
    }

    pcb = tcp_listen(pcb);  // Coloca o PCB em modo de escuta
    tcp_accept(pcb, connection_callback);  // Associa o callback de conexão

    printf("Servidor HTTP rodando na porta 80...\n");
}

int wifi_init() {
    if (cyw43_arch_init()) {
        printf("Failed to initialize Wi-Fi\n");
        return -1;
    }

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect to Wi-Fi\n");
        return -1;
    }

    printf("Connected to Wi-Fi\n");
    start_http_server(); // Inicia o servidor HTTP após conectar ao Wi-Fi
    return 0;
}

void wifi_update_data(int new_temperature, int new_humidity) {
    temperature = new_temperature;
    humidity = new_humidity;
}

void wifi_cleanup() {
    cyw43_arch_deinit();
}