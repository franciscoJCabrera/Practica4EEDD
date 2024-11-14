//
// Created by Francisco Jose on 30/09/2024.
//

#include "Nodo.h"

#ifndef PRACTICA5_LISTADENLAZADA_H
#define PRACTICA5_LISTADENLAZADA_H


using namespace std;

template<class T>
class ListaDEnlazada{

    private:
        Nodo<T> *cabecera;
        Nodo<T> *cola;
        int nElementos; ///Atributo para conocer el numero de elementos

    public:

        class Iterador{
            private:
                Nodo<T> *nodo;
                friend class ListaDEnlazada;

            public:

                /**
                 * Constructor parametrizado
                 * @param aNodo
                 */
                Iterador(Nodo<T> *aNodo):
                    nodo(aNodo){

                }

                /**
                 * Metodo para comprobar si hay un nodo anterior
                 * @return
                 */
                bool  hayAnterior(){
                    return nodo != 0;
                }

                /**
                 * Metodo para comprobar si hay un nodo siguiente
                 * @return
                 */
                bool haySiguiente(){
                    return nodo != 0;
                }

                /**
                 * Metodo para ir al nodo anterior
                 */
                void anterior(){
                    nodo = nodo->anterior;
                }

                /**
                 * Metodo para ir al nodo siguiente
                 */
                void siguiente(){
                    nodo = nodo->siguiente;
                }

                /**
                 * Metodo que devuelve el dato del nodo
                 * @return
                 */
                T &dato(){
                    return nodo->dato;
                }

        };

        /**
         * Constructor por defecto de la lista doblemente enlazada
         */
        ListaDEnlazada();

        /**
         * Constructor copia
         * @param origen
         */
        ListaDEnlazada(const ListaDEnlazada &origen);

        /**
         * Operador de asignacion
         * @param origen
         * @return
         */
        ListaDEnlazada &operator=(ListaDEnlazada &origen);

        /**
         * Destructor de la lista.
         * Para borrar una lista tenemos que borrar tanto la cabecera como la cola
         */
        ~ListaDEnlazada();

        /**
         * Metodo que devuelve el iterador situado en la cabecera
         * @return
         */
        Iterador iteradorInicio(){
            return Iterador(cabecera);
        }

        /**
         * Metodo que devuelve el iterador situado en la cola
         * @return
         */
        Iterador iteradorFinal(){
            return Iterador(cola);
        }

        /**
         * Metodo que inserta el dato indicado al principio de la lista
         * @param dato
         */
        void insertarInicio (T &dato);

        /**
         * Metodo que inserta el dato indicado al final de la lista
         * @param dato
         */
        void insertarFinal (T &dato);

        /**
         * Metodo que inserta un dato en la posicion del iterador pasada
         * @param i
         * @param dato
         */
        void insertar (Iterador &i, T &dato);

        /**
         * Metodo que borra el primer nodo, la cabecera
         */
        void borrarInicio();

        /**
         * Metodo que borra el ultimo nodo, la cola
         */
        void borrarFinal();

        /**
         * Metodo que borra la posicion indicada mediante el iterador pasado
         * @param i
         */
        void borrar(Iterador &i);

        /**
         * Metodo que devuelve el dato del primer nodo, de la cabecera
         * @return
         */
        T &inicio(){
            return this->cabecera->dato;
        }

        /**
         * Metodo que devuelve el dato del ultimo nodo, de la cola
         * @return
         */
        T &final(){
            return this->cola->dato;
        }

        /**
         * Metodo que devuelve el numero de elementos de la lista
         * @return
         */
        int tam();

        /**
         * Metodo que concatena la lista actual con la lista pasada como parametro
         * @param lista
         * @return
         */
        ListaDEnlazada<T> *concatena(ListaDEnlazada<T> &lista);

        /**
         * Operador + que vamos a sobrecargar para poder concatenar listas
         * @param lista
         * @return
         */
        ListaDEnlazada<T> operator+(ListaDEnlazada<T> &lista);

};

///Constructor por defecto
template<class T>
ListaDEnlazada<T>::ListaDEnlazada() {
    this->cabecera = 0;
    this->cola = 0;
    this->nElementos = 0;
}

///Constructor copia
template<class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T> &origen) {
    Nodo<T> *nodoPresente = origen.cabecera;
    while (nodoPresente){
        insertarFinal(nodoPresente->dato);
        nodoPresente = nodoPresente->siguiente;
    }
}

///Destructor
template<class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    delete this->cabecera, this->cola;
}

///Operador de asignacion
template<class T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator=(ListaDEnlazada<T> &origen) {
    if (this != &origen){
        cabecera = origen.cabecera;
        cola = origen.cola;
        nElementos = origen.nElementos;
        Nodo<T> newNodo = origen;
    }
}

///Metodo para insertar un dato al inicio
template<class T>
void ListaDEnlazada<T>::insertarInicio(T &dato) {
    Nodo<T> *newNodo = new Nodo<T>(dato, 0, cabecera);  ///Dato-Anterior-Siguiente
    if (cola == 0){
        cola = newNodo;
    }

    if (cabecera != 0){
        cabecera->anterior = newNodo;
    }
    cabecera = newNodo;
    nElementos++;
}

///Metodo para insertar un dato al final
template<class T>
void ListaDEnlazada<T>::insertarFinal(T &dato) {
    Nodo<T> *newNodo = new Nodo<T>(dato, cola, 0);
    if (cabecera == 0){
        cabecera = newNodo;
    }

    if (cola != 0){
        cola->siguiente = newNodo;
    }
    cola = newNodo;
    nElementos++;
}

///Metodo para insertar un dato en una posicion indicada por iterador
///COMPROBAR
template<class T>
void ListaDEnlazada<T>::insertar(ListaDEnlazada::Iterador &i, T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato, i.nodo->anterior, i.nodo);
    i.nodo->anterior->siguiente = nuevo;
    i.nodo->anterior = nuevo;
    nElementos++;
}

///Metodo para borrar el primer nodo de la lista
template<class T>
void ListaDEnlazada<T>::borrarInicio() {
    Nodo<T> *nodoBorrado = cabecera;

    cabecera = cabecera->siguiente;
    delete nodoBorrado;

    ///¿?
    if (cabecera != 0){
        cabecera->anterior = 0;
    } else{
        cola = 0;
    }
    nElementos--;
}

///Metodo para borrar el ultimo nodo de la lista
template<class T>
void ListaDEnlazada<T>::borrarFinal() {
    Nodo<T> *nodoBorrado = cola;

    cola = cola->anterior;
    delete nodoBorrado;

    if (cola != 0){
        cola->siguiente = 0;
    } else{
        cabecera = 0;
    }
    nElementos--;
}

///Metodo para borrar una posicion indicada por iterador
template<class T>
void ListaDEnlazada<T>::borrar(ListaDEnlazada::Iterador &i) {
    if (i.nodo == cola){    ///El nodo esta situado al final
        borrarFinal();
        i.nodo = 0;
    } else if (i.nodo == cabecera){ ///El nodo esta situado al principio
        borrarInicio();
        i.nodo = cabecera;
    } else{ ///No esta ni al final ni al principio
        Nodo<T> *nodo = cabecera;
        ///Recorremos la lista hasta que encontramos el nodo apuntado por el iterador
        while (nodo->siguiente != i.nodo){
            nodo = nodo->siguiente;
        }
        nodo->siguiente = i.nodo->siguiente;
        i.nodo->siguiente->anterior = nodo->siguiente;
        delete i.nodo;
        i.nodo = nodo->siguiente;
    }
    //nElementos--;
}

///Metodo para devolver el numero de elementso de la lista
template<class T>
int ListaDEnlazada<T>::tam() {
    return this->nElementos;
}

///Metodo que concatena la lista actual con la pasada por parametro
template<class T>
ListaDEnlazada<T> *ListaDEnlazada<T>::concatena(ListaDEnlazada<T> &lista) {
    ListaDEnlazada<T> *nuevaLista = new ListaDEnlazada<T>();   ///Lista que se va a devolver
    //Nodo<T> *newNodo = this->cabecera;
    ///Colocamos el iterador en la primera posicion
    ListaDEnlazada<T>::Iterador itera = this->iteradorInicio();
    while (itera.haySiguiente()){
        ///Vamos insertando los nodos en la nueva lista
        nuevaLista->insertarFinal(itera.dato());
        ///Avanzamos tanto nodo como iterador a la siguiente posicion
        //newNodo = newNodo->siguiente;
        itera.siguiente();
    }

    ///Ahora recorremos la lista pasada como parametro
    //Nodo<T> *nodo2 = lista.cabecera;
    ListaDEnlazada<T>::Iterador itera2 = lista.iteradorInicio();
    while (itera2.haySiguiente()){
        nuevaLista->insertarFinal(itera2.dato());
        //nodo2 = nodo2->siguiente;
        itera2.siguiente();
    }

    return nuevaLista;
}

///Operador + sobrecargado
template<class T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator+(ListaDEnlazada<T> &lista) {
    return this->concatena(lista);
}



#endif //PRACTICA5_LISTADENLAZADA_H

