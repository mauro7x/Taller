# =============================================================================
# Trabajo Práctico Final - Taller de Programación I
# =============================================================================

#------------------------------------------------------------------------------
# CONFIGURACIÓN DEL PROYECTO

cmake_minimum_required(VERSION 2.8.12)
project(sdl_tests)
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# FLAGS DE COMPILACIÓN

# Estándar a utilizar
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags para el manejo de errores
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors")

# Optimizaciones
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline")
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# ARCHIVOS FUENTE

FILE(GLOB src "*.cpp")
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# LIBRERÍAS NECESARIAS


#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# SDL_TEST

add_executable(sdl_test ${src})
target_link_libraries(sdl_test SDL2 SDL2_image)
#------------------------------------------------------------------------------