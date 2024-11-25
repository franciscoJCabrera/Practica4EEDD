//
// Created by Francisco Jose on 24/11/2024.
//

#ifndef PRACTICA5_MALLAREGULAR_H
#define PRACTICA5_MALLAREGULAR_H


#include <vector>
#include <list>
#include "cmath"
#include "iostream"

using namespace std;

template<typename T>
class MallaRegular{

private:

    float xMin=0, yMin=0, xMax=0, yMax=0;  ///Tamaño real global
    float tamaCasillaX=0, tamaCasillaY=0; ///Tamaño real de cada casilla
    float nDiv = 1;


    class Casilla {
    public:

        friend class MallaRegular<T>;
        list<T> Puntos;
        Casilla(){};

        /**
         * Metodo para insertar un dato en la lista
         * @param dato
         */
        void insertar(T& dato){
            Puntos.push_back(dato);
        }

        /**
         * Metodo para borrar un dato pasado por parametro dentro de la lista
         * @param dato
         * @return
         */
        bool borrar(T &dato){
            typename list<T>::iterator it;
            it = Puntos.begin();
            for(;it != Puntos.end(); it++){
                if (*it == dato){
                    Puntos.erase(it);
                    return true;
                }
            }
            return false;
        }

        /**
         * Metodo para buscar un dato pasado por parametro dentro de la lista
         * @param dato
         * @return
         */
        T* buscar(T &dato){
            typename list<T>::iterator it;
            it = Puntos.begin();
            for(;it!=Puntos.end(); it++){
                if(*it == dato){
                    return & (*it);
                }
            }
        }

        /**
         * Metodo para obtener la cantidad de elementos que hay en la lista
         * @return
         */
        float NumElementosCasilla(){
            return Puntos.size();
        }

        /**
         * Destructor
         */
        virtual ~Casilla(){

        }

    };

    ///Malla regular, es una matriz
    vector<vector<Casilla>> Malla;

    /**
     * Metodo que dadas unas coordenadas obtenemos la casilla correspondiente
     * @param x
     * @param y
     * @return
     */
    Casilla* ObtenerCasilla(float x, float y){
        int i = (x-xMin) / tamaCasillaX;
        int j = (y-yMin) / tamaCasillaY;
        //return &Malla[i][j];
        Casilla* resultado = nullptr;
        try {
            resultado = &Malla.at(i).at(j);

        } catch (exception &e){
            std::cout<<e.what();
        }
        return resultado;
    }



    public:

        /**
         * Constructor por defecto
         */
        MallaRegular() {}

        /**
         * Constructor parametrizado
         * @param aXMin
         * @param aYMin
         * @param aXMax
         * @param aYMax
         * @param nDiv
         */
        MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDiv): xMin(aXMin), yMin(aYMin), xMax(aXMax+0.01), yMax(aYMax+0.01), nDiv(nDiv){
            tamaCasillaX = (xMax-xMin) / (float)nDiv;
            tamaCasillaY = (yMax-yMin) / (float)nDiv;
            Malla.insert(Malla.begin(),nDiv,vector<Casilla>(nDiv));
        }

        /**
         * Metodo para insertar un dato en unas coordenadas indicadas
         * @param x
         * @param y
         * @param dato
         */
        void insertar(float x, float y, T &dato){
            Casilla *c = ObtenerCasilla(x,y);
            c->insertar(dato);
        };

        /**
         * Metodo para buscar un dato pasado en unas coordenadas indicadas
         * @param x
         * @param y
         * @param dato
         * @return
         */
        T *buscar(float x, float y, const T &dato){
            Casilla *c = ObtenerCasilla(x,y);
            return c->buscar(dato);
        };

        /**
         * Metodo para borrar un dato pasado en unas coordenadas pasadas
         * @param x
         * @param y
         * @param dato
         * @return
         */
        bool borrar(float x, float y, const T &dato){
            Casilla *c = ObtenerCasilla(x,y);
            return c->borrar(dato);
        };


        ///Getter y Setter
        float getMaximoY(){
            return yMax;
        }
        float getMaximoX(){
            return xMax;
        }
        float getMinimoY(){
            return yMin;
        }
        float getMinimoX(){
            return xMin;
        }
        float getTamaCasillaX(){
            return tamaCasillaX;
        }
        float getTamaCasillaY(){
            return tamaCasillaY;
        }



        /**
         * Metodo para convertir los grados en radianes
         * @param degree
         * @return
         */
        inline double toRadians(double degree) {
            return degree * M_PI / 180.0;
        }

        /**
         * Función para calcular la distancia Haversine entre dos puntos
         * @param lat1
         * @param lon1
         * @param lat2
         * @param lon2
         * @return
         */
        double haversine(double lat1, double lon1, double lat2, double lon2) {
            ///Radio de la Tierra en kilómetros
            const double earthRadius = 6371.0;

            ///Diferencia de latitud y longitud en radianes
            double dlat = toRadians(lat2 - lat1);
            double dlon = toRadians(lon2 - lon1);

            ///Fórmula Haversine
            double a = sin(dlat / 2) * sin(dlat / 2) +
                       cos(toRadians(lat1)) * cos(toRadians(lat2)) *
                       sin(dlon / 2) * sin(dlon / 2);
            double c = 2 * atan2(sqrt(a), sqrt(1 - a));

            ///Distancia en kilómetros
            double distance = earthRadius * c;

            return distance;
        }

        /**
         * Metodo para buscar el radio de unas coordenadas pasadas
         * @param xcentro
         * @param ycentro
         * @param radio
         * @return
         */
        vector<T> buscarRadio(float xcentro, float ycentro, float radio){

            vector<T> elementosEnRadio;

            ///Iterar sobre las casillas
            for (float i = xMin; i < xMax; i += getTamaCasillaX()) {
                for (float j = yMin; j < yMax; j += getTamaCasillaY()) {
                    Casilla *casilla = ObtenerCasilla(i, j);

                    ///Iterar sobre los elementos en la casilla
                    for (typename list<T>::iterator it = casilla->Puntos.begin(); it != casilla->Puntos.end(); ++it) {
                        T &elemento = *it;

                        ///Calcular la distancia Haversine entre el centro y el elemento
                        double distancia = haversine(ycentro, xcentro, elemento->getPosicionLat(), elemento->getPosicionLong());

                        ///Si la distancia es menor o igual al radio, agregar al vector
                        if (distancia <= radio) {
                            elementosEnRadio.push_back(elemento);
                        }
                    }
                }
            }

            return elementosEnRadio;

        };


        /**
         * Metodo que devuelve la cantidad maxima de elementos por celda
         * @return
         */
        unsigned maxElementosPorCelda(){
            float NElementos=0;
            float MaxElementos=0;

            Casilla *casilla;
            for(float i=xMin; i<xMax; i++){
                for(float j=yMin; j<yMax; j++){
                    casilla = ObtenerCasilla(i,j);
                    NElementos = casilla->NumElementosCasilla();
                    if(NElementos>MaxElementos){
                        MaxElementos = NElementos;
                    }
                }
            }
            return MaxElementos;
        };

        /**
         * Metodo que obtiene la cantidad de elementos promedios por celda
         * @return
         */
        float promedioElementosPorCelda(){

            float NElementos=0;
            Casilla* casilla;
            for(float i=xMin; i<xMax; i++){
                for(float j=yMin; j<yMax; j++){
                    casilla = ObtenerCasilla(i,j);
                    NElementos = NElementos + casilla->NumElementosCasilla();

                }
            }
            return NElementos/nDiv;
        };

        /**
         * Destructor
         */
        virtual ~MallaRegular(){

        };

};


#endif //PRACTICA5_MALLAREGULAR_H
