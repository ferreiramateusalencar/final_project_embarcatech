<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=00bfbf&height=120&section=header"/>
<h1 align="center"><img align="center" style="border-radius: 100%;" src="https://moodle.embarcatech.cepedi.org.br/pluginfile.php/1/theme_moove/logo/1733422525/Group%20658.png" width="300px;" alt=""><br>Projeto FInal Embarcatech</h1>

<p align="center">
   Este projeto utiliza um Raspberry Pi Pico (RP2040) para criar uma interface interativa com um joystick, uma tela OLED e um LED RGB. O objetivo principal é ler a posição do joystick, que simula um sensor DHT11 (onde o eixo Y do joystick simula o sensor de Temperatura e o eixo X o sensor de umidade) e enviar essas informações via Wi-Fi.
</p>

<h4 align="center">
    ✅  Concluído ✅
</h4>

---

Tabela de conteúdos
=================
<!--ts-->
   * [Sobre o projeto](#-sobre-o-projeto)
   * [Layout Repositorio Github](#-layout-repositorio-github)
   * [Funcionalidades](#-Funcionalidades)
   * [Como executar o projeto](#-como-executar-o-projeto)
   * [Imagens do Projeto](#-imagens-do-projeto)
     * [Imagem](#-projeto-na-extensão-wokwi-simulator-no-visual-studio)
     * [Vídeo](#-video-do-projeto)
   * [Tecnologias](#-tecnologias)
     * [Websites](#-websites)
     * [Utilitários](#user-content-server--nodejs----typescript)
   * [Contribuidores](#-contribuidores)
   * [Licença](#-licença)
<!--te-->

---

## 💻 Estrutura do Projeto

O projeto é organizado da seguinte forma:

```
rp2040-joystick-project
├── .vscode
├── assets                   #
├── bin                      #
├── inc
│   ├── joystick.h           # Cabeçalho para o joystick
│   ├── lwipopts.h           # 
│   ├── oled_display.h       # Cabeçalho para a tela OLED
│   ├── ssd1306_font.h       # 
│   ├── ssd1306_i2c.h        # 
│   ├── ssd1306.h            #
│   └── wifi.h               # Cabeçalho para a funcionalidade
├── src
│   ├── joystick.c           # Implementação das funções do 
|   ├── oled_display.c       # Controle da tela OLED
│   ├── wifi.c               # Gerenciamento da conexão Wi-Fi
│   ├── ssd1306.c            # ssd1306
|
├── .gitattributes           # 
├── .gitignore               # 
├── CMakeLists.txt           # Script de configuração do CMake
├── diagram.json             # 
├── LICENSE                  #
├── main.c                   # 
├── pico_sdk_import.cmake    # Importação do SDK do Raspberry Pi 
├── README.md                # Documentação do projeto
└── wokwi.toml               # 
```

## Componentes do Projeto

1. **Joystick**: O joystick é utilizado para capturar a posição do usuário. As coordenadas X e Y são lidas e processadas para controlar outros componentes.

2. **Tela OLED**: A tela OLED exibe informações sobre a posição do joystick e outras mensagens relevantes.

3. **LED RGB**: O LED RGB muda de cor com base na posição do joystick, proporcionando uma indicação visual adicional.

4. **Conexão Wi-Fi**: O projeto se conecta a uma rede Wi-Fi para enviar as informações de posição do joystick para um servidor ou outro dispositivo.

---

## 🚀 Como executar o projeto

💡Siga as instruções abaixo para configurar, compilar e executar o programa.

### Pré-requisitos

Antes de começar, você vai precisar ter instalado em sua máquina as seguintes ferramentas:
  - Sistema operacional Linux, macOS ou Windows (com suporte a Makefile).
  - [Git](https://git-scm.com) (Opcional, mas recomendado),
  - [GCC compilador](https://gcc.gnu.org)
  - [Biblioteca Pico-Sdk](https://github.com/raspberrypi/pico-sdk.git) (OBS: Necessário caso queira modificar o projeto)

Além disto é bom ter um editor para trabalhar com o código como [VSCode](https://code.visualstudio.com/) com a extensão [Raspberry](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)  e usar o simulador web [Wokwi](https://wokwi.com) (ou a extensão do Vscode [Wokwi Simulator](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode))

### 🎲 Dowload do Projeto

#### Dowload do Projeto no Desktop
- Opção 1:
  - Abra o terminal de comando Git Bash 
  - Clone o repositório do GitHub com o comando:
```
$ git clone https://github.com/ferreiramateusalencar/RP2040-UART.git
```
- Opção 2:
  - No repósitorio [Animation-BitDogLab](https://github.com/ferreiramateusalencar/RP2040-UART) aperte o Botão <i><>code</i>
  - Aperte a opção <i>Dowload ZIP</i>


### 🎲 Rodando a Animação no Wokwi

#### Wokwi Web
- Entre no navegador e digite [Wokwi.com]()
- Faça Upload dos Arquivos <i>diagram.json</i>
- Faça upload do aquivo RP2040-UART <i>RP2040-UART.c</i> e da pasta <i>src/</i>

#### Extensão Wokwi
- Abra o Visual Studio
- Na aba da extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico), aperte para Importar o projeto
- Compile o projeto
- crie um arquivo (caso não tenha no projeto) <i>wokwi.toml</i> e digite o código:
```
[wokwi]
version = 1
firmware = 'build/main.hex'
elf = 'build/main.elf'
```
- Abra o arquivo <i>diagram.json</i>


### 🎲 Rodando as Animações na placa BitdogLab

#### Placa BitDogLab
- Através de um cabo USB conecte a placa ao seu Disposito
- Aperte o Botão Bootsel e Reset 

#### VsCode Studio
- Abra o Visual Studio
- Na aba da extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico), aperte para Importar o projeto
- Compile o projeto
- Entre na pasta <i>build/</i>
- Cole o arquivo <i>main.uf2</i> no armazenamento placa BitDog
<br>

---

## 🎥 Imagens do Projeto

### 💿 Diagrama Visual do Projeto
<p align="center"><img width="700" height="400" src="https://github.com/ferreiramateusalencar/RP2040-UART/blob/main/assets/image/diagram.png"></p>

### 💿 Video do Projeto na Extensão Wokwi



https://github.com/user-attachments/assets/1cb5ff3f-3bc1-4b1f-a468-651a5e83f5a7





- Dowload HD video completo: https://github.com/ferreiramateusalencar/RP2040-UART/blob/main/assets/video/demonstration.mp4

---

## 🛠 Tecnologias

As seguintes ferramentas foram usadas na construção do projeto:

#### **Websites**
-   **[Visual Studio code](https://code.visualstudio.com)**
-   **[Github](https://github.com)**
-   **[Wokwi Web](https://gcc.gnu.org)**


#### **Utilitários**

-   Editor:  **[Visual Studio Code](https://code.visualstudio.com/)**  → Extensions:  **[C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools), [C/C++ Compile Run](https://marketplace.visualstudio.com/items?itemName=danielpinto8zz6.c-cpp-compile-run), [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico) e [Wokwi Simulator](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode)**
-   **[Git](https://git-scm.com)**


---

## 👨‍💻 Membro

GRUPO 1, SUBGRUPO 3 da Embarcatech <br/>
Mentor: MANOEL MESSIAS DA SILVA JUNIOR

<table>
  <tr>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/86336670?v=4" width="100px;"/><br/><a href="https://github.com/ferreiramateusalencar">Mateus A. Ferreira<a/><br/><br/><a href="https://github.com/ferreiramateusalencar/Conversor-de-Unidades-C" title="Líder">🌐</a></td>
  </tr>
</table>
      
---

## 📄 Licença

Este projeto está sob a licença do discente Mateus Alencar ferreira, da Formação Básica em Software Embarcado da Embarcatech - Veja o arquivo <a href="https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/LICENSE">License.md<a/>

<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=00bfbf&height=120&section=footer"/>
