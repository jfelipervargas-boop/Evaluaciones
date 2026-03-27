cmake_minimum_required(VERSION 3.16)

# ── Información del proyecto ────────────────────────────────────────────────
project(SistemaPanel
        VERSION 1.0.0
        DESCRIPTION "Sistema de gestión de paneles solares fotovoltaicos"
        LANGUAGES CXX)

# ── Estándar C++ ────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Opciones de compilación ──────────────────────────────────────────────────
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# ── Directorios de cabeceras ─────────────────────────────────────────────────
include_directories(${PROJECT_SOURCE_DIR}/include)

# ── Fuentes ──────────────────────────────────────────────────────────────────
set(SOURCES
    src/PanelSolar.cpp
    src/main.cpp
)

# ── Ejecutable ───────────────────────────────────────────────────────────────
add_executable(SistemaPanel ${SOURCES})

# ── Mensaje informativo ──────────────────────────────────────────────────────
message(STATUS "Proyecto : ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Estándar  : C++${CMAKE_CXX_STANDARD}")