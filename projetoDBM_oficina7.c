#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"
#include "./ssd1306.h"
#include "hardware/sync.h"
#include "mqtt_client.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definições dos pinos
#define LED_VERDE 15
#define LED_VERMELHO 14
#define BUZZER 13

// Definições dos limites de temperatura
#define TEMP_MIN 10
#define TEMP_MAX 25

// Função para inicializar os periféricos
void init_peripherals() {
    stdio_init_all();
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    
    adc_init();
    adc_select_input(4); // Assume que o sensor de temperatura está no canal 4
    bi_decl(bi_1pin_with_name(LED_VERDE, "Green LED"));
    bi_decl(bi_1pin_with_name(LED_VERMELHO, "Red LED"));
    bi_decl(bi_1pin_with_name(BUZZER, "Buzzer"));
}
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Example to turn on the Pico W LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
// Função para obter a temperatura do sensor
float read_temperature() {
    uint16_t raw = adc_read();
    float voltage = raw * 3.3 / (1 << 12);
    float temperature = (voltage - 0.5) * 100;
    return temperature;
}

// Função para controlar os LEDs e o buzzer
void control_leds_and_buzzer(float temperature) {
    if (temperature >= TEMP_MIN && temperature <= TEMP_MAX) {
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_VERMELHO, 0);
        gpio_put(BUZZER, 0);
    } else {
        gpio_put(LED_VERDE, 0);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(BUZZER, 1);
    }
}

// Função para exibir mensagem no display OLED
void display_message(float temperature) {
    ssd1306_clear();
    ssd1306_draw_string(0, 0, "Embarcatch");
    char buffer[20];
    sprintf(buffer, "Temp: %.2f C", temperature);
    ssd1306_draw_string(0, 10, buffer);
    ssd1306_show();
}

// Função para enviar log via MQTT
void send_log(float temperature, bool alert) {
    // Configurar e enviar log via MQTT
}

// Função principal
int main() {
    init_peripherals();
    ssd1306_init();
    mqtt_client_init();

    while (1) {
        float temperature = read_temperature();
        control_leds_and_buzzer(temperature);
        display_message(temperature);
        send_log(temperature, (temperature < TEMP_MIN || temperature > TEMP_MAX));
        sleep_ms(5000);
    }
    return 0;
}
