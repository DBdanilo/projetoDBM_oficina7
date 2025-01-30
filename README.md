# Projeto DBM Oficina 7

Este é um projeto desenvolvido para aferição de temperatura utilizando a Raspberry Pi Pico W. O projeto inclui funcionalidades de verificação de temperatura, controle de LEDs, geração de alerta sonoro, exibição de mensagens em um display OLED, e registro de dados via MQTT.

## Componentes Utilizados

- Raspberry Pi Pico W
- Módulo 5x5 Leds RGB WS2812B
- Display OLED 128x64 0.96"
- Joystick KY-023 (Opcional)
- Microfone analógico GY-MAX4466
- Módulo carregador de Bateria 2A 5v HW-775
- Botões Push (12x12x7.5mm e 6x6x5mm)
- Buzzers Passivo
- LED RGB 5mm cátodo comum
- Case de bateria 18650
- Bateria Li-Ion 18650 3.800 mAh 3.7V
- Capacitor 100 uF 16V eletrolítico
- Resistores (220 ohm, 150 ohm, 330 ohm, 100 ohm)
- Transistor NPN BC337
- Transistor DMG2305UX (P-Channel)
- Conectores JST-XH 2.54mm macho e IDC Macho 2x7 180°
- Barras de pinos (1x20 fêmea, 1x40 macho, 1x40 90º)
- Mini Jumper c/ Haste 2.54mm
- Diodo Schottky 1N5817
- Diodo Zenner 1N5231
- Regulador de tensão 3V3 LM1117

## Funcionalidades

- **Leitura de Temperatura:** Utiliza um sensor de temperatura integrado.
- **Verificação de Limites de Temperatura:** Checa se a temperatura está entre 10°C e 25°C.
- **Controle de LEDs:** Acende um LED verde se a temperatura estiver dentro do limite e um LED vermelho caso contrário.
- **Geração de Alerta Sonoro:** Ativa um alerta sonoro se a temperatura estiver fora do limite.
- **Exibição no Display OLED:** Mostra a mensagem "Embarcatch" e a temperatura medida.
- **Registro via MQTT:** Envia logs de temperatura via Wi-Fi utilizando o protocolo MQTT.

## Como Usar

1. Clone o repositório no seu ambiente local.
2. Instale o SDK do Pico e configure o ambiente de desenvolvimento.
3. Atualize o arquivo `CMakeLists.txt` conforme necessário.
4. Compile o projeto utilizando os comandos:
    ```sh
    mkdir build
    cd build
    cmake -DPICO_SDK_PATH=../../pico-sdk ..
    make
    ```
5. Carregue o arquivo `.uf2` gerado na Raspberry Pi Pico W.

## Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
