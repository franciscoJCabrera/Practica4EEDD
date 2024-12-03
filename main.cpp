#include "Reanelcar.h"
#include <iostream>
#include <chrono>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

///TODO: He metido UTM posicion como atributo en coche ¿Revisar constructores o algo mas?
///TODO: Revisar Reanelcar::buscarCochesRadio y hacer Reanelcar::buscarCocheMasCercano
///TODO: Revisar metodo Usuario::aparcaCoche y Usuario::DecrementarPuntos
///TODO: Revisar metodo Reanelcar::lecturaPosiciones(), el final, la creacion de la malla de carga

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "--PRACTICA 6--" << endl;

    ///Apartado 1 - Instanciar Reanelcar
    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");
    cout << endl;

    ///Apartado 2 - Implementar metodos Reanelcar::buscarCochesRadio() y Reanelcar::buscarCocheMasCercano()

    ///Apartado 3 - Leer el fichero destino.csv

    vector<pair<Usuario,UTM>> vectorUsuariosUTM;
    vectorUsuariosUTM = reanelcar.lecturaPosiciones("../destino.csv");


    ///Apartado 4 - Ahora los PR tienen huecos para todos los coches
    reanelcar.distribuirCoches();

    ///Apartado 5 - Los usuarios que empiezan por A alquilan un coche
    cout << "--Todos los usuarios que empiecen por A van a alquilar un nuevo coche--" << endl;
    cout << endl;
    list<Usuario> *listadoUsuariosA = reanelcar.buscarUsrNombre("A");

    list<Usuario>::iterator iteraA = listadoUsuariosA->begin();
    int contador = 0;
    int punto = 0;
    int cantidadUsuariosMostrados = 0;
    int siguiente = 0;
    Fecha fechaInicio(25,11,2024);

    while (iteraA != listadoUsuariosA->end()){
        Usuario &u = iteraA.operator*();
        ///Comprobamos que el nombre del usuario empieza por A
        if (u.getNombre().find("A") == 0){

            ///Creamos la fecha de fin
            int diaSumar = rand() % 2 + 1;
            Fecha fechaFin(fechaInicio.verDia(), fechaInicio.verMes(), fechaInicio.verAnio());
            fechaFin.anadirDias(diaSumar);

            siguiente = iteraA->getLinkReanel()->cogerCocheSecuencial(punto, &u, cantidadUsuariosMostrados);

            cantidadUsuariosMostrados++;
            contador++;
            punto = siguiente;
        }
        iteraA++;
    }

    ///Apartado 6 - Todos los usuarios que empiecen por B van a alquilar un coche
    cout << "--Todos los usuarios que empiecen por B van a alquilar un nuevo coche--" << endl;
    cout << endl;
    list<Usuario> *listadoUsuariosB = reanelcar.buscarUsrNombre("B");

    list<Usuario>::iterator iteraB = listadoUsuariosB->begin();
    contador = 0;
    punto = 0;
    cantidadUsuariosMostrados = 0;
    siguiente = 0;

    while (iteraB != listadoUsuariosB->end()){
        Usuario &u = iteraB.operator*();
        ///Comprobamos que el nombre del usuario empieza por A
        if (u.getNombre().find("B") == 0){

            ///Creamos la fecha de fin
            int diaSumar = rand() % 2 + 1;
            Fecha fechaFin(fechaInicio.verDia(), fechaInicio.verMes(), fechaInicio.verAnio());
            fechaFin.anadirDias(diaSumar);

            siguiente = iteraB->getLinkReanel()->cogerCocheSecuencial(punto, &u, cantidadUsuariosMostrados);

            cantidadUsuariosMostrados++;
            contador++;
            punto = siguiente;
        }
        iteraB++;
    }
    cout << endl;

    ///Apartado 7 - Los usuarios que empiezan por B van a aparcar el coche
    ///aparcan en el prDestino creado en el trayecto,
    ///tras aparcar, se introduce el coche en la malla regular
    cout << "--Todos los usuarios que empiecen por B van a aparcar un coche--" << endl;
    iteraB = listadoUsuariosB->begin();
    contador = 0;
    while (iteraB != listadoUsuariosB->end()){
        bool mostrar = false;
        ///Si empieza el nombre por B aparca el coche en el PRDestino del trayecto
        Usuario &u = iteraB.operator*();
        if (u.getNombre().find("B") == 0){

            ///Obtenemos todos los trayectos de cada usuarios dada una fecha de inicio
            vector<Trayecto*> *trayectosUsuario = u.getTrayectosFecha(fechaInicio);

            ///Solo vamos a mostrar el contenido de los 10 primeros usuarios
            if (contador < 10){
                cout << "Usuario " << contador << endl;
                cout << "El Usuario con DNI: " << iteraB->getNif() << " tiene como nombre: " << iteraB->getNombre() << endl;
                cout << "Coche que tiene: " << u.getCocheAlquilado()->getMatricula() << ", " << u.getCocheAlquilado()->getModelo() << ", " << u.getCocheAlquilado()->getMarca() << endl;

                for (int i = 0; i < trayectosUsuario->size(); ++i) {
                    cout << "Trayecto " << i << ": Fecha Inicio: " << trayectosUsuario->operator[](i)->getFechaInicio() << ", Fecha Fin: " << trayectosUsuario->operator[](i)->getFechaFin() << ", Origen (PR ID): " << trayectosUsuario->operator[](i)->getOrigen()->getId() << ", Destino (PR ID): " << trayectosUsuario->operator[](i)->getDestino()->getId() << endl;
                }
                contador++;

                cout << "Va a dejar el coche en el PRDestino " << endl;

                ///Al aparcar el coche, se calcula la distancia con el prDestino en el que debe estar y se le restan los puntos (1km 2 puntos)
                ///Ademas, al aparcar el coche tenemos que insertarlo en la malla regular
                u.aparcaCoche(u.getCocheAlquilado(), trayectosUsuario->operator[](0)->getDestino());
                cout << "Puntos acumulados del usuario " << u.getNif() << ", " << u.getNombre() << ": " << u.getPuntos() << " puntos" << endl;
                cout << endl;
            } else{
                mostrar = true;
            }

            ///Cuando mostremos los 10 primeros, el resto no se muestra pero siguen aparcando los coches en sus prDestino
            if (mostrar){
                ///TODO: Me peta con Barbabra Coordenadas muy parecidas
                ///El usuario aparca el coche en el PRDestino. Como solamente ha hecho un viaje, sabemos que es en el trayecto 0
                u.aparcaCoche(u.getCocheAlquilado(), trayectosUsuario->operator[](0)->getDestino());
            }


        }
        iteraB++;
    }
    cout << endl;

    ///TODO: A partir de aqui no se ha ejecutado el codigo
    ///Apartado 8 - Los usuarios que empiezan por A aparcan en el coche del destino leido del fichero destino.csv
    vector<pair<Usuario,UTM>>::iterator iteraVector = vectorUsuariosUTM.begin();
    iteraA = listadoUsuariosA->begin();
    contador = 0;

    ///Recorremos todos los usuarios que empiezan por A
    while (iteraA != listadoUsuariosA->end()){
        bool mostrar = false;
        bool encontrado = false;
        iteraVector = vectorUsuariosUTM.begin();

        ///Primero buscamos el usuario leido en destino.csv
        while (!encontrado){
            ///Tenemos que encontrar el usuario en el vector
            if (iteraVector->first.getNif() == iteraA->getNif()){
                encontrado = true;
            }else{
                iteraVector++;
            }
        }

        ///Obtenemos el usuario del vector y las coordenadas en las que va a dejar el coche
        Usuario &u = iteraA.operator*();
        UTM posicionDestino = iteraVector->second;

        ///Obtenemos los trayectos del usuario
        vector<Trayecto*> *trayectosRealizados = u.getTrayectosFecha(fechaInicio);

        ///Mostramos los trayectos de los 10 primeros usuarios unicamente
        if (contador < 10){
            cout << "Usuario: " << contador << endl;
            cout << "-Origen: " << trayectosRealizados->operator[](0)->getOrigen() << ", Destino: " << trayectosRealizados->operator[](0)->getDestino() << endl;
            cout << "-Coche alquilado, Matricula: " << u.getCocheAlquilado()->getMatricula() << ", Modelo:  " << u.getCocheAlquilado()->getModelo() << ", Marca: " << u.getCocheAlquilado()->getMarca() << endl;
            cout <<"-Fecha de inicio del  trayecto: " << trayectosRealizados->operator[](0)->getFechaInicio() << ", Fecha de fin del trayecto: " << trayectosRealizados->operator[](0)->getFechaFin() << endl;

            ///TODO: Hace falta el punto de recarga, tengo el UTM, construir solo con eso?
            PuntoRecarga pDestino(posicionDestino);
            u.aparcaCoche(u.getCocheAlquilado(), &pDestino);
            contador++;
        }else{
            mostrar = true;
        }

        ///El resto de usuarios tambien aparcan, pero no muestran el contenido
        if (mostrar){
            PuntoRecarga pDestino(posicionDestino);
            u.aparcaCoche(u.getCocheAlquilado(), &pDestino);
        }

        iteraA++;
    }
    cout << endl;


    ///Apartado 9 - Buscar los coches aparcado en un radio de 10km de Jaen Capital
    ///Jaen Capital (Longitud -3.7902800, Latitud 37.7692200)
    cout << "--Vamos a mostrar los coches aparcados en un radio de 10km de Jaen Capital--" << endl;
    UTM jaenCapital(37.7692200, -3.7902800);
    vector<Coche*> cochesCercanosJaen = reanelcar.buscarCochesRadio(jaenCapital, 10);
    for (int i = 0; i < cochesCercanosJaen.size() ; ++i) {
        cout << "Coche: " << i << ". Matricula: " <<  cochesCercanosJaen.operator[](i)->getMatricula() << ", Modelo: " << cochesCercanosJaen.operator[](i)->getModelo() << ", Marca: " << cochesCercanosJaen.operator[](i)->getMarca() << endl;
    }
    cout << endl;

    cout << "--Vamos a buscar el coche mas cercano a Jaen Capital--" << endl;
    Coche *cocheMasCercanoJaen = reanelcar.buscarCocheMasCercano(jaenCapital);
    cout << "Matricula: " << cocheMasCercanoJaen->getMatricula() << ", Modelo: " <<cocheMasCercanoJaen->getModelo() << ", Marca: " << cocheMasCercanoJaen->getMarca() << endl;
    cout << endl;

    ///Apartado 10 - Mostrar el coche mas cercano al punto de recarga con ID 43
    cout << "--Vamos a buscar el coche mas cercano al punto de recarga con ID 43--" << endl;
    PuntoRecarga *PR43 = reanelcar.obtenerPuntoRecarga(43);
    UTM utm43(PR43->getPosicion().getLatitud(), PR43->getPosicion().getLongitud());
    Coche *coche43 = reanelcar.buscarCocheMasCercano(utm43);
    cout << "El Punto de Recarga con ID 43 tiene la siguiente informacion: " << endl;
    cout << "ID: " << PR43->getId() << ", Longitud: " << PR43->getPosicion().getLongitud() << ", Latitud: " << PR43->getPosicion().getLatitud() << endl;
    cout << "El coche mas cercano a dicho punto es: Matricula: " << coche43->getMatricula() << ", Modelo: " << coche43->getModelo() << ", Marca: " << coche43->getMarca() << endl;

    ///Apartado 11 - Cual es el punto de recarga con mas coches en un radio de 15km de Jaen Capital
    


    cout << "FIN" << endl;

    return 0;
}
