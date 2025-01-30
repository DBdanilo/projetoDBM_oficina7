# Versão mínima do CMake
cmake_minimum_required(VERSION 3.13)

# Configurações padrão
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configurações específicas para o VS Code (não editar)
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Define a placa como Pico W
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Inclui o SDK do Pico (apenas uma vez)
include(pico_sdk_import.cmake)

# Define o projeto
project(projetoDBM_oficina7 C CXX ASM)

# Inicializa o SDK do Pico
pico_sdk_init()

# Adiciona o executável
add_executable(projetoDBM_oficina7 projetoDBM_oficina7.c)

# Configura o nome e versão do programa
pico_set_program_name(projetoDBM_oficina7 "projetoDBM_oficina7")
pico_set_program_version(projetoDBM_oficina7 "0.1")

# Habilita stdio via USB (desabilita UART)
pico_enable_stdio_uart(projetoDBM_oficina7 0)
pico_enable_stdio_usb(projetoDBM_oficina7 1)

# Vincula as bibliotecas necessárias
target_link_libraries(projetoDBM_oficina7
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_gpio
    hardware_i2c
    hardware_spi
    pico_multicore
    pico_cyw43_arch_lwip_threadsafe_background
)

# Adiciona diretórios de include
target_include_directories(projetoDBM_oficina7 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Gera arquivos adicionais (UF2, HEX, etc.)
pico_add_extra_outputs(projetoDBM_oficina7)