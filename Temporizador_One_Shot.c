#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos Botões e LEDs
#define BUTTON_A 5       // Pino do botão A
#define LED_VERMELHO 13  // Pino do LED Vermelho
#define LED_VERDE 11     // Pino do LED Verde
#define LED_AZUL 12      // Pino do LED Azul

// Variáveis globais
bool leds_active = false;  // Indica se os LEDs estão em execução
bool leds_all_off = true;  // Indica se todos os LEDs estão apagados

// Funções de callback para desligar os LEDs
int64_t turn_off_callback1(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, false);
    return 0;
}

int64_t turn_off_callback2(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, false);
    return 0;
}

int64_t turn_off_callback3(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, false);
    leds_active = false; // Permite novos ciclos após o último LED apagar
    leds_all_off = true; // Todos os LEDs foram apagados
    printf("Todos os LEDs foram desligados. Pronto para um novo ciclo.\n");
    return 0;
}

// Função para inicializar os pinos GPIO
void gpio_init_all() {
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, false);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, false);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, false);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
}

// Função para verificar o estado do botão com debounce
bool button_pressed() {
    if (gpio_get(BUTTON_A) == 0) {
        sleep_ms(50); // Debounce simples
        if (gpio_get(BUTTON_A) == 0) {
            while (gpio_get(BUTTON_A) == 0); // Aguarda o botão ser solto
            return true;
        }
    }
    return false;
}

int main() {
    stdio_init_all();
    gpio_init_all();

    while (true) {
        // Verifica se o botão foi pressionado e se os LEDs não estão ativos
        if (button_pressed() && !leds_active && leds_all_off) {
            printf("Botão pressionado, iniciando ciclo de LEDs...\n");
            leds_active = true;
            leds_all_off = false;

            // Liga todos os LEDs
            gpio_put(LED_VERMELHO, true);
            gpio_put(LED_VERDE, true);
            gpio_put(LED_AZUL, true);

            // Configura os alarmes para desligar os LEDs em sequência
            add_alarm_in_ms(3000, turn_off_callback1, NULL, false);
            add_alarm_in_ms(6000, turn_off_callback2, NULL, false);
            add_alarm_in_ms(9000, turn_off_callback3, NULL, false);
        }
        sleep_ms(10);
    }

    return 0;
}
