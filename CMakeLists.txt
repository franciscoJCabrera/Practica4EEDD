cmake_minimum_required(VERSION 3.28)
project(Practica6)

set(CMAKE_CXX_STANDARD 17)

add_executable(Practica6 main.cpp
        AVL.h
        Coche.cpp
        Coche.h
        fecha.cpp
        fecha.h
        ListaDEnlazada.h
        Nodo.h
        NodoAVL.h
        PuntoRecarga.cpp
        PuntoRecarga.h
        Reanelcar.cpp
        Reanelcar.h
        TablaHash.cpp
        TablaHash.h
        Trayecto.h
        Trayecto.cpp
        Usuario.cpp
        Usuario.h
        UTM.cpp
        UTM.h
        VDinamico.h
        MallaRegular.h
)
