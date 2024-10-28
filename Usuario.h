//
// Created by Francisco Jose on 30/09/2024.
//

#ifndef PRACTICA3_USUARIO_H
#define PRACTICA3_USUARIO_H

#include <string>
#include "Coche.h"
#include "Reanelcar.h"
#include "Trayecto.h"


using namespace std;

class Reanelcar;

class Usuario {
    private:
        string nif;
        string clave;
        string nombre;
        string direccion;
        Coche *cocheAlquilado;  ///En UML rent
        Reanelcar *linkReanel;
        Trayecto rutas;

    public:

        /**
         * Constructor por defecto
         */
        Usuario();

        /**
         * Constructor parametrizado
         * @param nif2
         * @param clave2
         * @param nombre2
         * @param direccion2
         * @param coche2
         */
        Usuario(string nif2, string clave2, string nombre2, string direccion2, Coche *coche2);

        ///Sobrecargamos el Constructor parametrizado para la lectura del CSV
        Usuario(string nif2, string clave2, string nombre2, string direccion2);

        /**
         * Constructor copia
         * @param origen
         */
        Usuario(const Usuario &origen);

        /**
         * Destructor
         */
        ~Usuario();

        /**
         * Metodo por el que se le asigna un Coche a un Usuario
         * @param c
         */
        void setCoche(Coche *c);

        ///Getter y Setter de todos los atributos
        const string &getNif() const;
        void setNif(const string &nif);

        const string &getClave() const;
        void setClave(const string &clave);

        const string &getNombre() const;
        void setNombre(const string &nombre);

        const string &getDireccion() const;
        void setDireccion(const string &direccion);

        /**
         * Metodo por el cual se obtiene el coche alquilado
         * @return
         */
        Coche *getCocheAlquilado() const;

        /**
         * Metodo que solicita un coche
         * Llama al metodo alquilar de ReanelCar que llama al metodo getBateriaMaxima de PuntoRecarga
         * @return El coche con mas bateria que se tiene en el punto de recarga
         */
        Coche* cogeCoche();

        /**
         * Metodo que crea un trayecto
         * @param puntoOrigen
         * @param puntoDestino
         */
        void crearTrayecto(PuntoRecarga *puntoOrigen, PuntoRecarga *puntoDestino);

        /**
         * Metodo que inicia un trayecto
         * @param idPuntoInicio
         * @param idPuntoFinal
         * @return
         */
        Coche* iniciaTrayecto(int idPuntoInicio, int idPuntoFinal);

        /**
         * Metodo que aparca un coche en un punto de recarga
         * @param c
         * @param pr
         */
        void aparcaCoche(Coche *c, PuntoRecarga *pr);

        /**
         * Metodo que devuelve todos los proyectos dada una fecha
         * @param f
         * @return
         */
        vector<Trayecto>* getTrayectosFecha(Fecha f);



};


#endif //PRACTICA3_USUARIO_H
