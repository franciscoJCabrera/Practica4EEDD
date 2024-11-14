cmake_minimum_required(VERSION 3.28)
project(Practica5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Practica5 main.cpp
        Coche.cpp
        Coche.h
        Usuario.h
        Usuario.cpp
        UTM.h
        UTM.cpp
        PuntoRecarga.h
        PuntoRecarga.cpp
        AVL.h
        NodoAVL.h
        VDinamico.h
        Reanelcar.h
        Reanelcar.cpp
        Nodo.h
        ListaDEnlazada.h
        Trayecto.cpp
        Trayecto.h
        fecha.cpp
        fecha.h
        TablaHash.cpp
        TablaHash.h
)
