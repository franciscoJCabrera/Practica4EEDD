cmake_minimum_required(VERSION 3.28)
project(Practica3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Practica3 main.cpp
        Coche.h
        Coche.cpp
        ListaDEnlazada.h
        Nodo.h
        Reanelcar.cpp
        Reanelcar.h
        Usuario.cpp
        Usuario.h
        VDinamico.h
        NodoAVL.h
        AVL.h
        PuntoRecarga.cpp
        PuntoRecarga.h
        Trayecto.cpp
        Trayecto.h
)
