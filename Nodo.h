//
// Created by Francisco Jose on 30/09/2024.
//

#ifndef PRACTICA5_NODO_H
#define PRACTICA5_NODO_H

using namespace std;

template<class T>
    class Nodo{
        public:
            ///Al ser doblemente enlazada tenemos un puntero tanto al nodo anterior como al nodo siguiente
            T dato;
            Nodo *anterior;
            Nodo *siguiente;

            ///Constructor parametrizado
            Nodo(T &aDato, Nodo *aAnterior, Nodo *aSiguiente = 0):
                dato(aDato), anterior(aAnterior), siguiente(aSiguiente){

            }

};

#endif //PRACTICA5_NODO_H

