//
// Created by Francisco Jose on 12/11/2024.
//

#ifndef PRACTICA5_TABLAHASH_H
#define PRACTICA5_TABLAHASH_H

#include "cmath"
#include "string"
#include "vector"
#include "Usuario.h"


#include <iostream>

using namespace std;

/**
 * Metodo djb2
 * Utilizado para convertir un string a un objeto de tipo unsigned long, ya que las claves son de ese tipo
 * @param str
 * @return
 */
unsigned long int djb2(const string &str);

/**
 * Metodo para saber si un numero pasado es primo
 * @param num
 * @param div
 * @return
 */
bool esPrimo(int num, int div);

/**
 * Metodo para conocer el siguiente numero primo a uno pasado por parametro
 * @param num
 * @return
 */
int siguientePrimo(int num);

///Diferentes estados en los que se puede encontrar un hueco
enum Estado {libre, ocupado, disponible};



class TablaHash {

    private:

        class Entrada{



        };

        ///Cubetas (lista simplemente enlazada)
        vector<Entrada> _tablaDispersion;    ///VectorDinámico que contiene las cubetas (una cubeta no es una entrada)
        int _numElementosContenidos = 0;

        ///Atributos de ajuste y estadistica de tabla
        unsigned int _maximoColisiones = 0;
        unsigned int _numMax10 = 0;
        float _promedioColisiones = 0;
        float _factorCarga = 0;
        unsigned int _tamTabla = 0;
        float _lambda=0.6;
        int _numColisiones = 0;



        /**
         * Funcion privada con la funcion de dispersion
         * En nuestro caso, se ha decidido probar con la funcion cuadratica
         * @param clave
         * @param intento
         * @return
         */
        unsigned long int hash(unsigned long int clave, int intento){
            return (clave + (intento * intento)) % this->_tamTabla;
        };



    public:

        ///Constructores
        TablaHash(int maxElementos, float lambda=0.7);
        TablaHash(const TablaHash &thash);

        ///Destructor
        virtual ~TablaHash();

        /**
         * Operador de asignacion
         * @param orig
         */
        void operator=(const TablaHash &orig);

        ///Getter y Setter
        void setTablaDispersion(const vector<Entrada> &tablaDispersion);

        int getNumElementosContenidos() const;
        void setNumElementosContenidos(int numElementosContenidos);

        unsigned int getMaximoColisiones() const;
        void setMaximoColisiones(unsigned int maximoColisiones);

        unsigned int getNumMax10() const;
        void setNumMax10(unsigned int numMax10);

        float getPromedioColisiones() const;
        void setPromedioColisiones(float promedioColisiones);

        float getFactorCarga() ;
        void setFactorCarga(float factorCarga);

        unsigned int getTamTabla() const;
        void setTamTabla(unsigned int tamTabla);

        void setLambda(float lambda);

        int getContadorRedispersion() const;
        void setContadorRedispersion(int contadorRedispersion);


        ///Metodos de ajuste de la tabla -- PROGRAMA 1

        /**
         * Metodo que devuelve el numero maximo de colisiones que se han producido
         * en la operacion de insercion mas costosa realizada sobre la tabla
         * @return
         */
        unsigned int maxColisiones();

        /**
         * Metodo que devuelve el numero de veces que se superan 10 colisiones
         * al intentar realizar la operacion de insercion sobre la tabla de un dato
         * @return
         */
        unsigned int numMax10();

        /**
         * Metodo que devuelve el promedio de colisiones por operacion de insercion realizada
         * sobre la tabla
         * @return
         */
        float promedioColisiones();

        /**
         * Metodo que devuelve el factor de carga de la tabla de dispersion
         * @return
         */
        float factorCarga();

        /**
         * Metodo que devuelve el tamaño de la tabla de dispersion
         * @return
         */
        unsigned int tamTabla();

        /**
         * Metodo que muestra diferentes parametros de la tabla hash
         * Utilizar este metodo en main tras cargar los datos en Reanelcar
         */
        void mostrarEstadoTabla();

        int contadorRedispersion = 0;

        /**
         *
         * @param clave
         * @param claveUsuario
         * @param usuario
         * @return
         */
        bool insertar(unsigned long clave, string &claveUsuario, Usuario &usuario);

        /**
         *
         * @param clave
         * @param id
         * @param a
         * @return
         */
        Usuario* buscar(unsigned long int clave, string &claveUsuario);

        /**
         *
         * @param clave
         * @param id
         * @return
         */
        bool borrar(unsigned long clave,const string &claveBuscar);






};


#endif //PRACTICA5_TABLAHASH_H
