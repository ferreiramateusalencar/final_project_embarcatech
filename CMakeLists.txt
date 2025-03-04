# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Arquivo gerado pelo CMake para o projeto Pico

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializa o pico_sdk a partir da localização instalada
# (note que isso pode vir do ambiente, cache do CMake, etc.)

# == NÃO EDITAR AS LINHAS ABAIXO para a extensão VS Code do Raspberry Pi Pico funcionar ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Tipo de placa")

# Puxa o SDK do Raspberry Pi Pico (deve ser antes do projeto)
include(pico_sdk_import.cmake)

project(final_project_embarcatech C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Adiciona o executável. O nome padrão é o nome do projeto, versão 0.1

add_executable(final_project_embarcatech
    main.c
    src/joystick.c
    src/oled_display.c
    src/ssd1306_i2c.c
    src/wifi.c
)

pico_set_program_name(final_project_embarcatech "final_project_embarcatech")
pico_set_program_version(final_project_embarcatech "0.1")

# Modifica as linhas abaixo para habilitar/desabilitar saída via UART/USB
pico_enable_stdio_uart(final_project_embarcatech 0)
pico_enable_stdio_usb(final_project_embarcatech 1)

# Adiciona a biblioteca padrão ao build
target_link_libraries(final_project_embarcatech
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

# Adiciona os arquivos de inclusão padrão ao build
target_include_directories(final_project_embarcatech PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${PICO_SDK_PATH}/src/rp2_common/hardware_adc/include
)

# Adiciona qualquer biblioteca solicitada pelo usuário
target_link_libraries(final_project_embarcatech 
        hardware_i2c
        hardware_timer
        hardware_clocks
        hardware_adc
        pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(final_project_embarcatech)