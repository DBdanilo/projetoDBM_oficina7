#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Defina o SSID e a senha da rede Wi-Fi
#define WIFI_SSID "Danilo"
#define WIFI_PASSWORD "55863192Dbm@"

int main() {
    // Inicializa a saída padrão (para printf)
    stdio_init_all();

    // Inicializa o hardware do Wi-Fi
    if (cyw43_arch_init()) {
        printf("Erro ao inicializar o Wi-Fi\n");
        return 1;
    }

    // Configura o Wi-Fi como Station Mode (modo cliente)
    cyw43_arch_enable_sta_mode();

    // Tenta conectar ao Wi-Fi
    printf("Conectando ao Wi-Fi: %s...\n", WIFI_SSID);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Falha ao conectar ao Wi-Fi\n");
        return 1;
    }

    // Conexão bem-sucedida
    printf("Conectado ao Wi-Fi!\n");

    // Exibe o endereço IP atribuído
    ip_addr_t ip_address = cyw43_state.netif[0].ip_addr;
    printf("Endereço IP: %s\n", ip4addr_ntoa(&ip_address));

    // Loop principal
    while (true) {
        // Mantém o Wi-Fi ativo
        cyw43_arch_poll();

        // Pisca o LED para indicar atividade
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }

    // Desliga o Wi-Fi (não será alcançado neste exemplo)
    cyw43_arch_deinit();
    return 0;
}