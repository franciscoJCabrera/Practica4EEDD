//
// Created by Francisco Jose on 14/10/2024.
//

#ifndef PRACTICA5_NODOAVL_H
#define PRACTICA5_NODOAVL_H

using namespace std;

template<class T>
class NodoAVL{
    public:

        NodoAVL<T> *izq = nullptr;  ///Puntero a la izq
        NodoAVL<T> *der = nullptr;  ///Puntero a la der
        T dato; ///Dato que contiene el nodo
        char bal =' ';  ///Valor -1,0,1 para conocer el balanceo/factor de equilibrio

        /**
         * Constructor parametrizado, pasandole el dato del nodo
         * @param _dato
         */
        NodoAVL(T &_dato): izq(nullptr), der(nullptr), bal(),dato(_dato){}

        /**
         * Constructor copia de un Nodo, se le pasa el Nodo origen
         * @param orig
         */
        NodoAVL(NodoAVL<T> &orig): izq(0), der(0), bal(orig.bal), dato(orig.dato) {}
};

#endif //PRACTICA5_NODOAVL_H

