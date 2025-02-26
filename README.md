# rp2040 Joystick Project

Este projeto utiliza um Raspberry Pi Pico (RP2040) para criar uma interface interativa com um joystick, uma tela OLED e um LED RGB. O objetivo principal é ler a posição do joystick, que simula um sensor DHT11 (onde o eixo Y do joystick simula o sensor de Temperatura e o eixo X o sensor de umidade) e enviar essas informações via Wi-Fi.

## Estrutura do Projeto

O projeto é organizado da seguinte forma:

```
rp2040-joystick-project
├── src
│   ├── main.c               # Ponto de entrada do projeto
│   ├── joystick.c           # Implementação das funções do joystick
│   ├── oled_display.c       # Controle da tela OLED
│   ├── led_matrix.c         # Controle da matriz de LED 5x5
│   ├── rgb_led.c            # Controle do LED RGB
│   ├── wifi.c               # Gerenciamento da conexão Wi-Fi
│   └── include
│       ├── joystick.h       # Cabeçalho para o joystick
│       ├── oled_display.h   # Cabeçalho para a tela OLED
│       ├── rgb_led.h        # Cabeçalho para o LED RGB
│       └── wifi.h           # Cabeçalho para a funcionalidade Wi-Fi
├── CMakeLists.txt           # Script de configuração do CMake
├── pico_sdk_import.cmake    # Importação do SDK do Raspberry Pi Pico
└── README.md                # Documentação do projeto
```

## Componentes do Projeto

1. **Joystick**: O joystick é utilizado para capturar a posição do usuário. As coordenadas X e Y são lidas e processadas para controlar outros componentes.

2. **Tela OLED**: A tela OLED exibe informações sobre a posição do joystick e outras mensagens relevantes.

3. **LED RGB**: O LED RGB muda de cor com base na posição do joystick, proporcionando uma indicação visual adicional.

4. **Conexão Wi-Fi**: O projeto se conecta a uma rede Wi-Fi para enviar as informações de posição do joystick para um servidor ou outro dispositivo.

## Instruções de Instalação

1. Clone este repositório em sua máquina local.
2. Certifique-se de ter o SDK do Raspberry Pi Pico instalado.
3. Navegue até o diretório do projeto e execute o CMake para configurar o ambiente de construção.
4. Compile o projeto usando o comando apropriado para sua plataforma.
5. Carregue o firmware no seu Raspberry Pi Pico.

## Uso

Após a instalação, conecte os componentes de hardware conforme indicado na documentação do projeto. Execute o firmware no Raspberry Pi Pico e utilize o joystick para interagir com a interface. As informações de posição serão enviadas via Wi-Fi.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias e correções.