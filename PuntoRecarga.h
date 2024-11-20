//
// Created by Francisco Jose on 14/10/2024.
//

#ifndef PRACTICA5_PUNTORECARGA_H
#define PRACTICA5_PUNTORECARGA_H

#include "UTM.h"

#include <queue>

using namespace std;

class Coche;

class PuntoRecarga {
    private:

        int id;
        int max;
        UTM posicion;

        ///Relacion de asociacion con la clase coche organizada en una cola de prioridad (Prioridad mayor bateria del coche)
        priority_queue<Coche*> cochesAparcados;

public:

        /**
         * Constructor parametrizado, se le pasa solamente el id
         */
        PuntoRecarga(int id);
        PuntoRecarga(int id, int max);

        /**
         * Constructor parametrizado
         * @param id2
         * @param max2
         * @param posicion2
         */
        PuntoRecarga(int id2, int max2, UTM &posicion2);

        /**
         * Destructor
         */
        ~PuntoRecarga();

        /**
         * Devuelve el coche con mayor cantidad de bateria
         * En caso de empate entre varios coches, cualquiera es valido
         * @return
         */
        Coche* getMaxBateria();

        /**
         * Añade un coche a un punto de recarga siempre que no se haya llegado al limite indicado por el valor max
         * @param c
         * @return
         */
        bool addCoche(Coche *c);

        /**
         * Quita un coche de la estacion de carga
         * @param c
         * @return True si se encuentra y False en caso contrario
         */
        bool deleteCoche(Coche *c);

        /**
         * Metodo que devuelve la cantidad de coches que se tiene en un punto de recarga
         * @return
         */
        int getNumCoches();

        ///Getter y Setter
        int getId() const;
        void setId(int id);

        int getMax() const;
        void setMax(int max);

        const UTM &getPosicion() const;
        void setPosicion(const UTM &posicion);

};


#endif //PRACTICA5_PUNTORECARGA_H
