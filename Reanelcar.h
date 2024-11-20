//
// Created by Francisco Jose on 30/09/2024.
//

#ifndef PRACTICA4_REANELCAR_H
#define PRACTICA4_REANELCAR_H


#include "Coche.h"
#include "PuntoRecarga.h"
#include "Usuario.h"
#include "fecha.h"

#include <iostream>
#include <vector>
#include <map>
#include <list>

#include <cstdlib>


class Usuario;
class TablaHash;

using namespace std;

class Reanelcar {

    private:
        map<string,Coche*> coches;   ///La clave es la matricula
        list<Usuario*> usuarios; ///Los usuarios son insertados en una lista
        vector<PuntoRecarga> sitiosPuntoRecarga;    ///En este caso es solo un punto de recarga
        TablaHash *usuariosTabla;   ///Relacion de asociacion mediante tabla hash


        /**
         * Metodo que busca un punto de recarga dado un id
         * @param id
         * @return
         */
        PuntoRecarga* buscarPuntoRecarga(int id);

    public:

        /**
         * Constructor por defecto
         * Se va a hacer la lectura de los CSV
         */
        Reanelcar(string nCoches, string nPR, string nUsuarios);

        /**
         * Constructor
         */
        ~Reanelcar();

        /**
         * Metodo que busca un usuario pasado un NIF
         * En caso de no existir devolver null
         * @param nif
         * @return
         */
        Usuario* buscarUsrNif(string nif);

        /**
         * Metodo que devuelve una lista doblemente enlazada con todos los usuarios dado un nombre
         * Si pasas "Man" devolvera todas las palabras que empiecen por esa subcadena como Manolo, Mandy ...
         * @param nombre
         * @return
         */
        list<Usuario>* buscarUsrNombre(string nombre);

        /**
         * Metodo que busca un Coche dada una matricula
         * En caso de no existir devuelve nulo
         * @param matricula
         * @return
         */
        Coche* buscarCocheMatricula(string matricula);

        /**
         * Metodo que devuelve un vector con todos los coches de un modelo indicado
         * @param modelo
         * @return
         */
        vector<Coche>* buscarCocheModelo(string modelo);

        /**
         * Metodo que enlaza un Usuario a un Coche que alquila
         * @param u
         * @param c
         * @return
         */
        Coche* alquilar(Usuario *u, int idPROrigen, int idPRDestino, Fecha fIni, Fecha fFin);

        /**
         * Busca el coche con mayor bateria disponible en el punto de recarga y lo devuelve
         * El coche con mayor bateria es indicado por puntoRecarga::getMaxBateria()
         * @param usr
         * @return
         */
        Coche* alquila(Usuario *usr);

        /**
         * Metodo que añade el coche indicado al Punto de Recarga
         * Es realizado mediante el metodo puntoRecarga::addCoche()
         * @param c
         */
        bool colocarCochePR(Coche *c, PuntoRecarga *pr);

        /**
         * Metodo que recorre el arbol con el metodo inorden y devuelve un VDinamico con las matriculas ordenadas
         * @return
         */
        vector<Coche*> primerasMatriculas();

        /**
         * Metodo que busca el Punto de Recarga con menos coches
         * @return
         */
        PuntoRecarga* obtenerPRMenosCoches();

        /**
         * Metodo que distribuye todos los coches de forma secuencial en los PR
         * Cuando llegue al PR 49 vuelve a iniciar el ciclo
         * En cada ciclo se inserta un coche en cada PR
         */
        void distribuirCoches();

        /**
         * Metodo utilizado para que los usuarios cogan coches de forma secuencial de los Puntos de Recarga
         * El usuario 1 coge del PROrigen 1 y tiene como PRDestino 2, el usuario 2 tiene como PROrigen 2 y como PRDestino 3
         * Se hace ciclicamente hasta agotar todos los coches de todos los Puntos de Recarga
         * @param ultimoPR
         * @param u
         * @param cantidad
         * @return
         */
        int cogerCocheSecuencial(int ultimoPR, Usuario *u, int cantidad);

        /**
         * Metodo que llama al metodo privado.
         * Necesario para que el usuario pueda realizar la busqueda de un PuntoRecarga deseado
         * @param id
         * @return
         */
        PuntoRecarga* obtenerPuntoRecarga(int id);

        /**
         * Metodo que busca y devuelve un usuario dado su NIF en la tabla hash
         * @param nif
         * @return
         */
        Usuario* buscarUsuarioNIFTablaHash(string nif);

        /**
         * Metodo que borra un usuario y toda su informacion
         * Se debe de borrar los trayectos y coches alquilados
         * Se borra en todas las estructuras en las que se tenga dicho usuario
         * @param nif
         * @return
         */
        bool borrarUsuarioTablaHash(string nif);

        /**
         * Metodo por el cual se muestra el estado de la tabla hash
         * @return
         */
        void mostrarEstadoTablaHash();



};


#endif //PRACTICA4_REANELCAR_H
