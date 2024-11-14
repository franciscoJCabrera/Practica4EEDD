
#ifndef PRACTICA5_VDINAMICO_H
#define PRACTICA5_VDINAMICO_H

#include <algorithm>
#include <iostream>


using namespace std;

template<class T>
    class VDinamico{

    private:
        T *mem;
        ///tamaF -> tamaño reservado para el vector
        ///tamaL -> tamaño realmente utilizado del vector
        int tamaF{};
        int tamaL{};


    public:

        /**
         * Constructor por defecto inicializando el tamaño fisico a 1 y el logico a 0
         */
        VDinamico();

        /**
         * Constructor por defecto
         * @param n
         */
        VDinamico(unsigned int n);

        /**
         * Constructor copia
         * Se le pasa un vector como parametro para realizar una copia de este
         * @param origen
         */
        VDinamico(const VDinamico<T> &origen);

        /**
         * Constructor parcial
         * Dado un vector como parametro, se le va a copiar una serie de elementos desde una posicion inicial, ambos datos dados como parametros
         * @param origen
         * @param posicionInicial
         * @param numElementos
         */
        VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos);

        /**
         * Operador de asignacion
         * Se le pasa como parametro un vector, del cual se va a crear una copia identica
         * Se va a devolver la referencia del vector nuevo
         * @param nVector
         * @return
         */
        VDinamico &operator=(VDinamico<T> &nVector);

        /**
         * Operador [], utilizado para lectura/escritura
         * @param pos
         * @return
         */
        //const T &operator[](int pos) const ;
        T &operator[](int pos);

        /**
         * Metodo que ordena el vector de menor a mayor empleando la funcion sort de <algorithm>
         */
        void ordenar();

        /**
         * Metodo que ordena el vector al reves, de mayor a menor
         */
        void ordenReves();

        /**
         * Metodo para ordenar el vector mediante el algoritmo burbuja
         */
        void burbuja();

        /**
         * Metodo empleado para insertar datos en el vector
         * En caso de que no se le indique la posicion, se insertara en la ultima posicion del vector
         */
        void insertar(const T &dato, unsigned int posicion = UINT_MAX);

        /**
         * Metodo que borra un dato dada una posicion como parametro
         * En caso de que no se le indique la posicion, se eliminara el ultimo dato del vector
         * @param pos
         * @return
         */
        T borrar(unsigned int pos = UINT_MAX);

        /**
         * Busqueda de un dato empleando el algoritmo de la busqueda binaria
         * Devuelve la posicion en la que se encuentra el dato a buscar
         * En caso de que no este en el vector, devolvera -1
         * @param dato
         * @return
         */
        int busquedaBin(T &dato);

        /**
         * Metodo que devuelve el tamaño logico del vector
         * @return
         */
        unsigned int tamLog();

        /**
         * Destructor del vector
         */
        ~VDinamico();

    };

///Constructor por defecto, inicializando tamaFisico a 1 y tamaLogico a 0
template<class T>
VDinamico<T>::VDinamico() {
    this->tamaF = 1;
    this->tamaL = 0;
    mem = new T[tamaF];

}

///Constructor por defecto
template<class T>
VDinamico<T>::VDinamico(unsigned int n){

    ///Inicializamos el tamaño Fisico a 1 para que encuentre el multiplo de 2 que es mayor al tamaño Logico
    tamaF = 1;
    tamaL = n;

    ///El Tamaño Fisico siempre tiene que ser multiplo de 2 y mayor que el tamaño Logico
    while (tamaL >= tamaF) {
        tamaF = tamaF * 2;
    }

    mem = new T [tamaF];

}

///Constructor copia
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen) {
    tamaF = origen.tamaF;
    tamaL = origen.tamaL;
    ///Creamos el vector con el tamaño Fisico
    mem = new T [tamaF];

    ///Copiamos todos los elementos de un vector al otro
    for (int i = 0; i < origen.tamaL; i++) {
        mem[i] = origen.mem[i];
    }
}

///Constructor de copia parcial
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos) {

    tamaL = numElementos;
    tamaF = 1;

    ///Como sabemos, el tamaño Fisico debe ser siempre multiplo de dos
    while(tamaL >= tamaF){
        tamaF = tamaF * 2;
    }
    mem = new T [tamaF];

    int indice = 0;
    ///Copiamos los elementos desde la posicion indicada
    for (int i = posicionInicial; i < posicionInicial + numElementos ; i++) {
        if (i >= 0 && i <= tamaF){
            mem[indice] = origen[i];
            indice++;
            tamaL++;
        }
    }
}

///Operador de asignacion
template<class T>
VDinamico<T>& VDinamico<T>::operator=(VDinamico<T> &nVector) {
    if (&nVector != this){
        delete[] mem;
        tamaF = nVector.tamaF;
        tamaL = nVector.tamaL;
        mem = new T [tamaF];

        for (int i = 0; i <= nVector.tamaL; i++) {
            mem[i] = nVector.mem[i];
        }
    }
    return *this;
}

///Operador []
template<class T>
T& VDinamico<T>::operator[](int pos) {
  return mem[pos];
}


///Metodo para ordenar el vector de menor a mayor empleando la funcion sort
template<class T>
void VDinamico<T>::ordenar() {
    sort(this->mem, this->mem + this->tamLog());
}

///Metodo que ordena al reves el vector, de mayor a menor
template<class T>
void VDinamico<T>::ordenReves() {
    this->ordenar();
    reverse(this->mem, this->mem+this->tamLog());
}

///Metodo para ordenar el vector pero mediante el algoritmo burbuja
template<class T>
void VDinamico<T>::burbuja() {
    for (int i = 0; i < tamaL - 1; i++) {
        for (int j = 0; j < tamaL - 1 - i; j++) {
            ///Comparamos para ver cuál es mayor
            if (mem[j] > mem[j + 1]) {
                ///Intercambiamos los elementos colocando primero los menores
                T auxiliar = mem[j];
                mem[j] = mem[j + 1];
                mem[j + 1] = auxiliar;
            }
        }
    }
}

///Metodo que inserta un dato en una posicion indicada
template<class T>
void VDinamico<T>::insertar(const T &dato,unsigned int posicion) {
    try{
        if(this->tamaF == this->tamaL){
            ///Si son iguales, aumentamos x2 el tamaFisico
            this->tamaL++;
            this->tamaF = this->tamaF * 2;
            T* nVector = new T[tamaF];

            for (int i = 0; i < this->tamaL-1; i++){
                nVector[i] = this->mem[i];
            }
            delete [] this->mem;
            this->mem = nVector;
            this->mem[tamaL-1] = dato;
        }else{
            ///Metemos el dato en la ultima posicion del vector
            this->tamaL++;
            this->mem[tamaL-1] = dato;
        }
    } catch (bad_alloc &e) {
        cout << "Error al INSERTAR un dato" << endl;
    }
}

///Metodo que borra un dato de una posicion indicada
template<class T>
T VDinamico<T>::borrar(unsigned int pos) {

    ///Lo que devolvemos es el dato que va a ser eliminado
    T datoEliminado = mem[pos];

    try{
        tamaL--;
        ///Comprobamos que el tamaño logico no es menor que 1/3 del tamaño fisico
        if(tamaL*3 < tamaF){
            tamaF = tamaF/2;
            T* nVector = new T[tamaF];

            for(int i = 0; i < pos; i++){
                nVector[i] = mem[i];
            }

            for(int i = pos+1; i < tamaL; i++){
                nVector[i-1] = this->mem[i];
            }

            delete [] this->mem;
            this->mem = nVector;
        }else{
            mem[pos] = mem[tamaL-1];
        }
    }catch (bad_alloc &e){
        cout << "Error en BORRADO" << endl;
    }

    return datoEliminado;
}

///Busqueda binaria de un dato pasado por parametro, en caso de no estar devolver -1
template<class T>
int VDinamico<T>::busquedaBin(T &dato) {
    int inf = 0;
    int sup = tamaL-1;
    int mitad;

    while(inf <= sup) {
        mitad = (inf + sup) / 2;
        if (mem[mitad] == dato) {
            return mitad;
        }else if (mem[mitad] < dato){
            inf = mitad + 1;
        }else {
            sup = mitad - 1;
        }
    }
    return -1;
}

///Metodo que devuelve el tamaño logico del vector
template<class T>
unsigned int VDinamico<T>::tamLog() {
    return this->tamaL;
}

///Destructor del vector dinamico
template<class T>
VDinamico<T>::~VDinamico() {
    delete[] mem;
}


#endif //PRACTICA5_VDINAMICO_H




