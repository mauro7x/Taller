# CMake

Herramienta multiplataforma para generar makefiles y otros archivos de compilación

---

# CMake

* Provee lenguaje de más alto nivel que un makefile, dedicado a tareas de compilación

* Permite modularizar proyectos de forma sencilla.

* Provee herramientas para detectar bibliotecas del sistema (/usr/share/cmake-nnn/*.cmake)

* Utilizado de forma nativa por algunos IDEs (CLion, Kdevelop, QtCreator)

* Puede ser exportado a formatos compatibles con otros IDEs (eclipse, VBStudio)

---

# Hola mundo

## CMake vs Make

.col-6[
CMakeLists.txt

~~~.cmake
cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

add_executable(ej0 main.cpp)
~~~
]

.col-6[
Makefile

~~~.make
all: build

build:
    g++ -o ej0 main.cpp 

clean:
    rm *.o ej0

.PHONY: all clean build
~~~
]

Ejecutando cmake <path> genera un makefile bastante más elaborado que el de la derecha.

---

# CMake

## Comandos principales

* `add_executable(nombre srcs)`: genera un ejecutable a partir de las fuentes

* `add_library(nombre src)`: genera una biblioteca a partir de las fuentes

* `target_link_libraries(ejecutable/lib libs_a_linkear)`: al momento de compilar el ejecutable (o biblioteca) le pasa una lista de bibliotecas para la etapa de link

* `add_subdirectory(dir)`: permite agregar un subdirectorio como módulo

---

# CMake

## Ejemplo con subdirectorios

.col-6[
**ej1/CMakeLists.txt**

~~~.cmake
cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

add_executable(ej1 main.cpp)
add_subdirectory(classes)

target_link_libraries(ej1 myclasses)
~~~
]

.col-6[
**ej1/classes/CMakeLists.txt**

~~~.cmake
project(cmake-demo) 

add_library(myclasses
  class0.cpp
  class1.cpp
  class2.cpp
  class3.cpp
)
~~~
]

---

## Uso de wildcards

Puedo utilizar el comando FILE(GLOB) para leer los nombres de archivos que respondan a un patrón.

~~~.cmake
project(cmake-demo) 

FILE(GLOB myFiles "*.cpp")
message (STATUS "Cargué ${myFiles}")

add_library(myclasses
  ${myFiles}
)
~~~
