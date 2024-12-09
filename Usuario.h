//
// Created by Francisco Jose on 30/09/2024.
//

#ifndef PRACTICA5_USUARIO_H
#define PRACTICA5_USUARIO_H

#include <string>
#include "Coche.h"
#include "Reanelcar.h"
#include "Trayecto.h"
#include "fecha.h"

#include <map>


using namespace std;

class Reanelcar;

class Usuario {
    private:
        string nif;
        string clave;
        string nombre;
        string direccion;
        int puntos;
        Coche *cocheAlquilado;  ///En UML rent
        Reanelcar *linkReanel;
        multimap<Fecha,Trayecto*> rutas; ///La clave es la Fecha de inicio del Trayecto

    public:

        /**
         * Constructor por defecto
         */
        Usuario();

        /**
         * Constructor parametrizado, por el cual solamente se le pasa el nombre del usuario
         * @param nombre
         */
        Usuario(string nombre);

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

        Reanelcar *getLinkReanel() const;
        void setLinkReanel(Reanelcar *linkReanel);

        int getPuntos() const;
        void setPuntos(int puntos);

        ///Operadores de comparacion
        bool operator==(const Usuario &rhs) const;
        bool operator!=(const Usuario &rhs) const;

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
         * Funcion llamada por Reanelcar::alquilar()
         * Crea un nuevo proyecto a partir de los puntos de recarga de origen y de destino
         * @param puntoOrigen
         * @param puntoDestino
         */
        void crearTrayecto(PuntoRecarga *puntoOrigen, PuntoRecarga *puntoDestino, Fecha fIni, Fecha fFin);

        /**
         * Llama a Reanelcar::alquilar()
         * Una vez determinado el PR desde el que se va a coger el coche se llama a Usuario::craerTrayecto()
         * Tomamos como PROrigen el dado por Reanelcar::alquila() y como PRDestino el dado
         * Llama a Trayecto::addCoche() pasandole el coche asociado (rent)
         * @param idPuntoInicio
         * @param idPuntoFinal
         * @return El coche que el usuario utilizara, el que mas bateria tenga
         */
        Coche* iniciaTrayecto(int idPuntoInicio, int idPuntoFinal, Fecha fIni, Fecha fFin);

        /**
         * Llama a Reanelcar::colocarCochePR() pasandole el PRDestino y elimina la asociacion entre usuario y el coche alquilado
         * Cada hora de retraso supone 2 puntos de penalizacion para el usuario
         * @param c
         * @param pr
         */
        void aparcaCoche(Coche *c, PuntoRecarga *pr);

        /**
         * Metodo que obtiene todos los trayectos realizados en una fecha dada por el usuario
         * @param f
         * @return
         */
        vector<Trayecto*>* getTrayectosFecha(const Fecha& f);


        /**
         * Metodo que contabiliza la cantidad de trayectos realizados por un usuario
         * Utilizado ya que cada trayecto tiene como id el siguiente de la cantidad de trayectos realizados
         * @return
         */
        int trayectosRealizados();

        /**
         * Metodo que busca y asocia un Punto Recarga destino por uno pasado
         * @param f
         * @param fFin
         * @param idOrigen
         * @param idDestino
         * @param pDestino
         * @return
         */
        bool buscarPRDestinoAsociar(const Fecha& f, const Fecha& fFin, int idOrigen, int idDestino, PuntoRecarga *pDestino);


        /**
         * Metodo que decrementa los puntos del usuario
         * Tiene que comparar las fechas, la fecha de entrega con la fecha de fin del trayecto
         * Cada km de retraso supone 2 puntos de penalizacion
         * @param kilometros
         */
        void decrementarPuntos(int kilometros);


        /**
         * Metodo que elimina todos los trayectos que habia hecho el usuario
         */
        void eliminarTrayectos();




};


#endif //PRACTICA5_USUARIO_H
