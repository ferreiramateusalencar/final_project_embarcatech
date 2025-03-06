<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=00bfbf&height=120&section=header"/>
<h1 align="center"><img align="center" style="border-radius: 100%;" src="https://moodle.embarcatech.cepedi.org.br/pluginfile.php/1/theme_moove/logo/1733422525/Group%20658.png" width="300px;" alt=""><br>Projeto FInal Embarcatech</h1>

<p align="center">
   Este projeto utiliza um Raspberry Pi Pico W (RP2040) para criar uma interface interativa com um joystick, uma tela OLED e um LED RGB. O objetivo principal é ler a posição do joystick, que simula um sensor DHT11 (onde o eixo Y do joystick simula o sensor de Temperatura e o eixo X o sensor de umidade) e enviar essas informações para o Display Oled SDD 1306, além do envio das informações ao monitor serial via UART e ao navegador via Wi-Fi.
</p>

<h4 align="center">
    ✅  Concluído ✅
</h4>

---

Tabela de conteúdos
=================
<!--ts-->
   * [Sobre o projeto](#-sobre-o-projeto)
   * [Layout repositório Github](#-layout-repositório-github)
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
final_project_embarcatech
├── .vscode                   # Configurações do Visual Studio Code para o projeto (extensões, tarefas, etc.)
├── assets                    # Pasta para armazenar recursos estáticos do projeto (imagens, vídeos, etc.)
├── bin                       # Pasta onde os binários compilados serão armazenados
├── inc                       # Pasta com arquivos temporários gerados no Compile
├── inc                       # Diretório para arquivos de cabeçalho (.h)
│   ├── joystick.h            # Cabeçalho para o joystick, definindo funções e estruturas relacionadas ao controle do joystick
│   ├── oled_display.h        # Cabeçalho para controle da tela OLED, declara funções para manipular o display
│   ├── ssd1306_font.h        # Definições de fontes utilizadas na tela OLED (baseadas no chip SSD1306)
│   ├── ssd1306.h             # Cabeçalho principal para controle do display SSD1306
│   ├── wifi_credentials.h    # Arquivo com as credenciais de conexão. ATENÇÃO: esse arquivo deve ser criado, leia comentários no arquivo wifi.h
│   └── wifi.h                # Cabeçalho para a funcionalidade de Wi-Fi, com funções para gerenciar a conexão
├── lib                       # Diretório para as Bibliotecas internas
│   └── lwipopts.h            # Arquivo de configuração das opções do LWIP (pilha de rede) para personalização de rede
├── src                       # Diretório para o código fonte (.c)
│   ├── joystick.c            # Implementação das funções de controle do joystick, leitura de entradas, etc.
│   ├── oled_display.c        # Implementação das funções de controle da tela OLED
│   ├── ssd1306.c             # Implementação das funções de comunicação e controle do display SSD1306
│   └── wifi.c                # Implementação do gerenciamento da conexão Wi-Fi, configuração e reconexão
├── .gitattributes            # Arquivo de configuração do Git para definir atributos de arquivos
├── .gitignore                # Lista de arquivos e pastas a serem ignorados pelo Git
├── CMakeLists.txt            # Script de configuração do CMake, que define como o projeto será compilado
├── diagram.json              # Diagrama relacionada à arquitetura do projeto na simulação Wokwi
├── LICENSE                   # Arquivo de licença do projeto, especificando os termos de uso e distribuição
├── main.c                    # Arquivo principal, contém o ponto de entrada do programa
├── pico_sdk_import.cmake     # Arquivo de configuração do CMake para importar o SDK do Raspberry Pi Pico
├── README.md                 # Documento de documentação do projeto
└── wokwi.toml                # Arquivo de configuração para o simulador Wokwi

```

## Componentes do Projeto

1. **Joystick**: O joystick (simulando um sensor DHT11) é utilizado para capturar a posição do usuário. As coordenadas X e Y são lidas e processadas para controlar outros componentes.

2. **Tela OLED**: A tela OLED exibe informações sobre a posição do joystick e outras mensagens relevantes.

3. **LED RGB**: O LED RGB muda de cor com base na posição no status da condição do ambiente simulado, proporcionando uma indicação visual adicional.

4. **Conexão Wi-Fi**: O projeto se conecta a uma rede Wi-Fi para enviar as informações de posição do joystick para um servidor ou outro dispositivo.

---

## 📄 Documentação de avaliação do projeto para o Embarcatech TIC37

<a href="https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/assets/papers/U7T_TIC370101727_MAF.pdf">Documento do projeto<a/>

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

### 🎲 download do Projeto

#### download do Projeto no Desktop
- Opção 1:
  - Abra o terminal de comando Git Bash 
  - Clone o repositório do GitHub com o comando:
```
$ git clone https://github.com/ferreiramateusalencar/final_project_embarcatech.git
```
- Opção 2:
  - No repositório [Animation-BitDogLab](https://github.com/ferreiramateusalencar/final_project_embarcatech.git) aperte o Botão <i><>code</i>
  - Aperte a opção <i>download ZIP</i>


### 🎲 Rodando a Animação no Wokwi

#### Wokwi Web
- Entre no navegador e digite [Wokwi.com]()
- Faça Upload dos Arquivos <i>diagram.json</i>
- Faça upload do arquivo main <i>main.c</i> e dos arquivos das pastas <i>inc/</i>, <i>lib/</i> e <i>src/</i>

#### Extensão Wokwi
- Abra o Visual Studio Code
- Na aba da extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico), aperte para Importar o projeto
- Compile o projeto
- crie um arquivo (caso não tenha no projeto) <i>wokwi.toml</i> e digite o código:
```
[wokwi]
version = 1
firmware = 'build/final_project_embarcatech.hex'
elf = 'build/final_project_embarcatech.elf'
rfc2217ServerPort = 4000
```
- Abra o arquivo <i>diagram.json</i>


### 🎲 Rodando as Animações na placa BitdogLab

#### Placa BitDogLab
- Através de um cabo USB conecte a placa ao seu dispositivo
- Aperte o Botão Bootsel e Reset 

#### VsCode Studio
- Abra o Visual Studio Code
- Na aba da extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico), aperte para Importar o projeto
- Compile o projeto
- Entre na pasta <i>build/</i>
- Cole o arquivo <i>final_project_embarcatech.uf2</i> no armazenamento placa BitDog
<br>

---

## 🎥 Imagens do Projeto

### 💿 Diagrama Visual do Projeto no Wokwi
<p align="center"><img width="700" height="400" src="https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/assets/image/diagram.png"></p>

### 💿 Monitor Serial
<p align="center"><img width="700" height="400" src="https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/assets/image/image_demonstration_HTTP.jpg"></p>

### 💿 Foto da BitDogLab com o firmware do projeto
<p align="center"><img width="700" height="400" src="https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/assets/image/board_demonstration_BitDogLab.jpg"></p>

### 💿 Video do Projeto






https://github.com/user-attachments/assets/b1a8d7e9-92f7-416e-b1aa-07604f263ffa





- download do vídeo completo em Alta qualidade (HD): https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/assets/video/demonstration.mp4

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
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/86336670?v=4" width="100px;"/><br/><a href="https://github.com/ferreiramateusalencar">Mateus A. Ferreira<a/><br/><br/><a href="https://github.com/ferreiramateusalencar/Conversor-de-Unidades-C" title="Líder & desenvolvedor">🌐</a></td>
  </tr>
</table>
      
---

## 📄 Licença

Este projeto está sob a licença do discente Mateus Alencar ferreira, da Formação Básica em Software Embarcado da Embarcatech - Veja o arquivo <a href="https://github.com/ferreiramateusalencar/final_project_embarcatech/blob/main/LICENSE">License.md<a/>

<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=00bfbf&height=120&section=footer"/>
