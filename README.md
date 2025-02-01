Explicação do Funcionamento do Código:

Este código implementa um sistema de controle de LEDs utilizando um microcontrolador Raspberry Pi Pico. Ele faz com que os LEDs sejam acionados sequencialmente após o usuário pressionar um botão, desligando-os em intervalos de tempo predefinidos.

Vídeo Demonstração:https://youtu.be/Y3LWvs8osoQ

Funcionamento

1)Definição dos Pinos:

BUTTON_A (pino 5): Entrada para detectar a pressão do botão.

LED_VERMELHO (pino 13), LED_VERDE (pino 11) e LED_AZUL (pino 12): Saídas para controle dos LEDs.

2)Inicialização dos GPIOs:

Configura os LEDs como saídas e inicia todos desligados.

Configura o botão como entrada com pull-up ativado.

3)Detecção do Botão:

A função button_pressed() verifica se o botão foi pressionado e usa um atraso de 50ms para debounce.

O loop while (gpio_get(BUTTON_A) == 0); aguarda a liberação do botão antes de continuar.

4)Acionamento dos LEDs:

Quando o botão é pressionado, os LEDs são ligados simultaneamente.

Três funções de callback (turn_off_callback1, turn_off_callback2, turn_off_callback3) são programadas com temporizadores para desligar os LEDs em diferentes momentos:

LED Vermelho apaga após 3 segundos.

LED Azul apaga após 6 segundos.

LED Verde apaga após 9 segundos e libera o sistema para um novo ciclo.

5)Loop Principal:

O loop principal verifica constantemente se o botão foi pressionado e se os LEDs estão aptos a um novo ciclo.

O atraso sleep_ms(10) evita processamento excessivo.

Fluxo de Execução

1)O sistema inicia com todos os LEDs apagados e aguardando interação do usuário.

2)O usuário pressiona o botão, ativando os LEDs e iniciando os temporizadores.

3)Os LEDs se apagam um por vez após 3, 6 e 9 segundos, respectivamente.

4)Quando todos os LEDs estão apagados, o sistema fica pronto para um novo ciclo.
