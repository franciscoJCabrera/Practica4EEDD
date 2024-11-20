//
// Created by Francisco Jose on 14/10/2024.
//

#include "NodoAVL.h"
#include "VDinamico.h"

#ifndef PRACTICA5_AVL_H
#define PRACTICA5_AVL_H


using namespace std;

template<class T>
class AVL{

private:

    NodoAVL<T> *raiz;
    void rotDer(NodoAVL<T>* &p);
    void rotIzq(NodoAVL<T>* &p);
    int numElementos = 0;
    int insertaNum(NodoAVL<T>* &c, T &dato);

    void inorden(NodoAVL<T> *p, VDinamico<T*> &vInorden);

    VDinamico<T*> VectorAux;


    /**
     * Metodo llamado al realizar la llamada al destructor de un objeto
     * @param nodo
     */
    void DestructorPostorden(NodoAVL<T>* nodo) {
        if (nodo) {
            DestructorPostorden(nodo->izq);
            DestructorPostorden(nodo->der);

            delete nodo;
        }
    }

    /**
     * Metodo que se realiza al crearse un objeto mediante el constructor copia
     * @param NodoOrigen
     * @param Copia
     */
    void ConstructorPreorden(NodoAVL<T>* NodoOrigen, NodoAVL<T>* Copia) {
        if (Copia) {
            NodoOrigen = new NodoAVL<T>(Copia->dato);

            ConstructorPreorden(NodoOrigen->izq, Copia->izq);
            ConstructorPreorden(NodoOrigen->der, Copia->der);
        }
    }


public:

    /**
     * Constructor por defecto
     */
    AVL();

    /**
     * Constructor copia
     * Realizado en PreOrden
     * @param AVLOrigen
     */
    AVL(AVL<T> &AVLOrigen);

    /**
     * Destructor del AVL.
     * Realizado en PostOrden
     */
    ~AVL();

    /**
     * Operador de asignacion
     * @param i
     * @return
     */
    AVL<T> &operator = (AVL<T> &i);

    /**
     * Metodo para obtener la raiz del AVL
     * @return
     */
    NodoAVL<T>* getRaiz() const {
        return raiz;
    }

    /**
     * Metodo para insertar un dato
     * @param dato
     * @return
     */
    bool inserta(T &dato);

    /**
     * Busqueda recursiva de un dato pasado como parametro
     * @param dato
     * @return
     */
    T* buscaRec(T &dato);
    T* Rec(NodoAVL<T>* nodo, T& datoBuscar);    ///Llamado buscaClave en PDF


    /**
     * Busqueda iterativa de un dato pasado como parametro
     * @param dato
     * @return
     */
    T* buscaIt(T &dato);

    /**
     * Recorrido en inorden
     * Devuelve un VDinamico de punteros a los elementos del AVL haciendo un recorrido en Inorden
     * @return
     */
    VDinamico<T*> &recorreInorden();

    /**
     * Metodo que devuelve la cantidad de elementos del AVL
     * @return
     */
    unsigned int nElementos();

    /**
     * Metodo que aumenta el contador de elementos que tiene el AVL
     */
    void aumentaContadorElementos();

    /**
     * Metodo que devuelve la altura del AVL
     * @return
     */
    unsigned int altura();
    unsigned int alturaRec(NodoAVL<T> *nodo);


    ///Operadores de comparacion
    bool operator==(const AVL &rhs) const {
        return raiz == rhs.raiz &&
               numElementos == rhs.numElementos;
    }

    bool operator<(const AVL &rhs) const {
        if (raiz < rhs.raiz)
            return true;
        if (rhs.raiz < raiz)
            return false;
        return numElementos < rhs.numElementos;
    }

    bool operator>(const AVL &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const AVL &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const AVL &rhs) const {
        return !(*this < rhs);
    }

    bool operator!=(const AVL &rhs) const {
        return !(rhs == *this);
    }



};

///Constructor por defecto
template<class T>
AVL<T>::AVL() {
    raiz = nullptr;
    numElementos = 0;
}

///Constructor copia
template<class T>
AVL<T>::AVL( AVL<T> &origen) {
    ConstructorPreorden(raiz,origen);
    numElementos = origen.numElementos;
}

///Destructor
template<class T>
AVL<T>::~AVL() {
    DestructorPostorden(raiz);  ///Se indica en el PDF que el destructor se hace en postOrden
    numElementos = 0;
}

///Operador de asignacion
template<class T>
AVL<T> &AVL<T>::operator=(AVL<T> &i) {
    if(this != i){
        DestructorPostorden(raiz);
        numElementos = i.numElementos;
        ConstructorPreorden(raiz,i.raiz);
    }else{
        throw ("(Operator =) Los dos objetos son iguales, no se pueden copiar");
    }
}

///Rotacion hacia la izquierda
template<class T>
void AVL<T>::rotIzq(NodoAVL<T>* &p) {
    NodoAVL<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if(r->bal < 0){
        q->bal += -r->bal;
    }
    r->bal++;
    if(q->bal > 0){
        r->bal += q->bal;
    }
}

///Rotacion hacia la derecha
template<class T>
void AVL<T>::rotDer(NodoAVL<T>* &p) {
    NodoAVL<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if(l->bal > 0){
        q->bal -= l->bal;
    }
    l->bal--;
    if(q->bal < 0){
        l->bal -= -q->bal;
    }
}

///Metodo que inserta un dato en el AVL
template<class T>
bool AVL<T>::inserta(T &dato){
    return insertaNum(raiz, dato);
};

///Metodo empleado para insertar un dato
template<class T>
int AVL<T>::insertaNum(NodoAVL<T>* &c,T &dato) {
    NodoAVL<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new NodoAVL<T>(dato);
        c = p;
        deltaH = 1;
    } else if (dato > p->dato) {
        if (insertaNum(p->der, dato)) {
            p->bal--;
            if (p->bal == -1) {
                deltaH = 1;
            } else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der);
                rotIzq(c);
            }
        }
    } else if (dato < p->dato) {
        if (insertaNum(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1) {
                deltaH = 1;
            } else if (p->bal == 2) {
                if (p->izq->bal == -1) {
                    rotIzq(p->izq);
                }
                rotDer(c);
            }
        }
    }
    return deltaH;
}

///Busqueda recursiva de un dato pasado
template<class T>
T* AVL<T>::buscaRec(T &datoBuscar) {
    return Rec(raiz,datoBuscar);
}

///Metodo que realiza una busqueda recursiva
template<class T>
T* AVL<T>::Rec(NodoAVL<T>* nodo,T& datoBuscar) {

    ///Si llegamos a un nodo nulo podemos decir que el dato a buscar no se encuentra en el arbol
    if(nodo == nullptr){
        return nullptr;
    }

    ///Primero comprobamos que el dato a buscar no este en el nodo actual
    if(datoBuscar == nodo->dato){
        return &(nodo->dato);
    }else{
        if(datoBuscar < nodo->dato){
            ///Al ser recursiva tenemos que ir llamando al mismo metodo una y otra vez
            return buscaRec(nodo->izq,datoBuscar);
        }else{
            return buscaRec(nodo->der,datoBuscar);
        }
    }
}

///Metodo que realiza la busqueda iterativa
template<typename T>
T* AVL<T>::buscaIt(T &datoBuscar) {
    NodoAVL<T>* nodo = raiz;
    ///Al ser iterativa se hace la busqueda sin tener que llamar constantemente a la funcion
    while (nodo != nullptr){
        if(datoBuscar == nodo->dato){
            return &(nodo->dato);
        }else{
            if(datoBuscar < nodo->dato){
                nodo = nodo->izq;
            }else{
                nodo = nodo->der;
            }
        }
    }
    return nullptr;
}

///Metodo que recorre en inorden el AVL y nos devuelve un VDinamico
template<typename T>
VDinamico<T*> &AVL<T>::recorreInorden() {
    inorden(this->raiz, this->VectorAux);
    return VectorAux;
}

///Metodo que nos devuelve la cantidad de elementos del AVL
template<typename T>
unsigned int AVL<T>::nElementos() {
    return this->ContadorElementos;
}

///Metodo que nos devuelve la altura del AVL
template<typename T>
unsigned int AVL<T>::altura(){
    return alturaRec(raiz);
}

///Metodo que nos da la altura del AVL
template<typename T>
unsigned int AVL<T>::alturaRec(NodoAVL<T> *nodo) {
    ///Cuando el nodo es nulo, no existe, la altura es 0
    if (nodo == nullptr) {
        return 0;
    }

    ///Calcular la altura de los subárboles izquierdo y derecho
    unsigned int alturaIzq = alturaRec(nodo->izq);  ///Llamamos constantemente al subarbol izquierdo hasta llegar al nodo hoja mas profundo
    unsigned int alturaDer = alturaRec(nodo->der);  ///Llamamos constantemente al subarbol derecho hasta llegar al nodo hoja mas profundo

    ///La altura del nodo actual es la mayor altura de sus hijos más uno ya que se incluye el nodo actual, el nodo raiz
    return std::max(alturaIzq, alturaDer) + 1;
}

///Metodo que aumenta el contador de elementos del AVL
template<typename  T>
void AVL<T>::aumentaContadorElementos(){
    numElementos++;
}

///Recorrido en Inorde
template<typename T>
void AVL<T>::inorden(NodoAVL<T> *p, VDinamico<T*> &vectorInorden) {
    if(p != 0){
        inorden(p->izq, vectorInorden);
        T* ptr = new T(p->dato);
        vectorInorden.insertar(ptr);
        inorden(p->der, vectorInorden);
    }
}

#endif //PRACTICA5_AVL_H

