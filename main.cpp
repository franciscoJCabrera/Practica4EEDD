#include "Reanelcar.h"
#include <iostream>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

///TODO: Arreglar busqueda en la lista
///TODO: ¿Como puede tardar mas con vector que con la lista?


using namespace std;

int main(int argc, const char * argv[]) {

    cout << "--PRACTICA 5. TABLA HASH--" << endl;
    cout << "--Programa de prueba 1. Ajuste de la tabla hash--" << endl;

    ///Precargamos los datos del fichero y mostramos el estado interno de la tabla
    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");

    cout << "Ficheros cargados" << endl;
    cout << endl;

    cout <<"--Estado interno de la tabla--" << endl;
    reanelcar.mostrarEstadoTablaHash();
    cout << endl;

    ///Se buscan todos los usuarios con nombre empezado por W y lo metemos en un vector
    cout << "--Busqueda de todos los usuarios que empiezan por W--" << endl;
    list<Usuario> *listaW = reanelcar.buscarUsrNombre("W");
    list<Usuario>::iterator iteraW = listaW->begin();

    vector<string> nifUsuariosW;

    int contador = 0;
    while (iteraW != listaW->end()){

        cout << "Usuario " << contador << ": " <<  iteraW->getNif() << ", " << iteraW->getNombre() << endl;
        nifUsuariosW.push_back(iteraW->getNif());
        cout << "NIF insertado" << endl;
        cout << endl;

        contador++;
        iteraW++;
    }
    cout << endl;

    ///Buscamos las claves gracias al vector
    cout << "--Busqueda de las claves gracias al vector de nifs--" << endl;
    clock_t inicioVector= clock();
    for (int i = 0; i < nifUsuariosW.size(); ++i) {
        Usuario *usuarioW = reanelcar.buscarUsuarioNIFTablaHash(nifUsuariosW.operator[](i));
        cout << "Usuario " << i << ": " << usuarioW->getNif() << " que concuerda con el nif que buscabamos que es: " << nifUsuariosW.operator[](i) << endl;
    }
    clock_t finVector = clock();
    double tiempoVector = static_cast<double>(finVector - inicioVector) / CLOCKS_PER_SEC;
    cout << "Tiempo que tarda en buscar con el vector: " << tiempoVector << endl;
    cout << endl;

    ///Buscamos las claves gracias a la lista
    cout << "--Busqueda mediante la lista--" << endl;
    clock_t inicioLista= clock();

    for (int i = 0; i < nifUsuariosW.size(); ++i) {
        ///Booleano para comprobar si se ha encontrado el usuario de dicho nif
        bool encontrado = false;
        iteraW = listaW->begin();

        ///Hacemos la busqueda de dicho nif en la lista
        while (!encontrado){
            if (iteraW->getNif() == nifUsuariosW.operator[](i)){
                encontrado = true;
                cout << "Usuario " << i << " encontrado en lista: " << iteraW->getNif() << ", " << iteraW->getNombre() << endl;
            }
            iteraW++;
        }
    }

    clock_t finLista = clock();
    double tiempoLista = static_cast<double>(finLista - inicioLista) / CLOCKS_PER_SEC;
    cout << "Tiempo que tarda en buscar con la lista: " << tiempoLista << endl;
    cout << endl;

    cout << "--Programa de prueba 2--" << endl;
    cout << endl;

    ///Tenemos que distribuir los coches en los diferentes puntos de recarga
    cout << "Distribuccion de los coches en los Puntos de Recarga" << endl;
    reanelcar.distribuirCoches();
    cout << endl;


    ///Los usuarios van a coger coches de forma secuencial
    iteraW = listaW->begin();
    int punto = 0;
    int siguiente;
    bool fin;
    ///Se van a mostrar solo los 10 primeros usuarios
    int cantidadUsuariosMostrados = 0;

    cout << "Asignacion de coches a los usuarios, mostramos los 10 primeros" << endl;
    while (iteraW != listaW->end() && !fin){

        ///Cada usuario coge un coche de forma secuencial
        ///El primero coge el Coche de PROrigen 1 y lo va a llevar a PRDestino 2, el segundo usuario desde PROrigen 2 y lo lleva a PRDestino 3
        siguiente = iteraW->getLinkReanel()->cogerCocheSecuencial(punto, iteraW.operator->(), cantidadUsuariosMostrados);
        cantidadUsuariosMostrados++;
        punto = siguiente;

        ///En el momento en el que te devuelve 100 es porque ya no ningun coche en ningun PR
        if (punto == 100){
            fin = true;
        }

        iteraW++;
    }
    cout << endl;

    ///Los usuarios que empiecen por Wi van a aparcar el coche con un retraso de 2h
    cout << "Los usuarios que empiezan por Wi van a aparcar el coche con un retraso de 2h" << endl;
    iteraW = listaW->begin();
    Fecha fechaInicio(12,11,2024);
    contador = 0;
    while (iteraW != listaW->end()){

        ///Si empieza el nombre por Wi aparca el coche en el PRDestino del trayecto
        Usuario &u = iteraW.operator*();
        if (u.getNombre().find("Wi") == 0){

            ///Obtenemos todos los trayectos de cada usuarios dada una fecha de inicio
            vector<Trayecto*> *trayectosUsuario = u.getTrayectosFecha(fechaInicio);

            ///Solo vamos a mostrar el contenido de los 10 primeros usuarios
            if (contador < 10){
                cout << "Usuario " << contador << endl;
                cout << "El Usuario con DNI: " << iteraW->getNif() << " tiene como nombre: " << iteraW->getNombre() << endl;
                cout << "Coche que tiene: " << u.getCocheAlquilado()->getMatricula() << ", " << u.getCocheAlquilado()->getModelo() << ", " << u.getCocheAlquilado()->getMarca() << endl;

                for (int i = 0; i < trayectosUsuario->size(); ++i) {
                    cout << "Trayecto " << i << ": Fecha Inicio: " << trayectosUsuario->operator[](i)->getFechaInicio() << ", Fecha Fin: " << trayectosUsuario->operator[](i)->getFechaFin() << ", Origen (PR ID): " << trayectosUsuario->operator[](i)->getOrigen()->getId() << ", Destino (PR ID): " << trayectosUsuario->operator[](i)->getDestino()->getId() << endl;
                }
                contador++;

                cout << "Va a dejar el coche en el PRDestino " << endl;
                cout << endl;
            }

            ///El usuario aparca el coche en el PRDestino. Como solamente ha hecho un viaje, sabemos que es en el trayecto 0
            u.aparcaCoche(u.getCocheAlquilado(), trayectosUsuario->operator[](0)->getDestino(), 2);
            cout << "Puntos acumulados del usuario " << u.getNif() << ", " << u.getNombre() << ": " << u.getPuntos() << " puntos" << endl;

        }
        iteraW++;
    }
    cout << endl;

    ///Mostramos los datos del usuario con nif "84538382N"
    Usuario *usuarioNIF = reanelcar.buscarUsuarioNIFTablaHash("84538382N");
    if (usuarioNIF != nullptr){
        cout << "-Datos del usuario con NIF 84538382N: " << endl;
        cout << "--Personales: " << usuarioNIF->getNombre() << endl;

        ///Mostramos si tiene un coche alquilado o no
        if (usuarioNIF->getCocheAlquilado() != nullptr){
            cout << "--Tiene el coche: " << usuarioNIF->getCocheAlquilado()->getMatricula() << ", " << usuarioNIF->getCocheAlquilado()->getModelo() << ", " << usuarioNIF->getCocheAlquilado()->getMarca() << ". Tiene un total de " << usuarioNIF->getPuntos() << " puntos" << endl;
        }else{
            cout << "--No tiene un coche asociado " << endl;
        }

        ///Sacamos los trayectos realizados para mostrarlos
        vector<Trayecto*> *trayectosUsuario = usuarioNIF->getTrayectosFecha(fechaInicio);
        if (trayectosUsuario->size() != 0){
            for (int i = 0; i < trayectosUsuario->size(); ++i) {
                cout << "Trayecto " << i << ": Origen: " << trayectosUsuario->operator[](i)->getOrigen()->getId() << ", Destino: " << trayectosUsuario->operator[](i)->getDestino()->getId() << endl;
            }
        }else{
            cout << "--No tiene trayectos realizados" << endl;
        }
    }
    cout << endl;

    ///Vamos a borrar el usuario con nif "84538382N"
    Usuario *usuarioBuscado1 = reanelcar.buscarUsuarioNIFTablaHash("84538382N");

    if (usuarioBuscado1 != nullptr){
        Usuario usuarioCopia = *usuarioBuscado1;

        reanelcar.borrarUsuarioTablaHash("84538382N");
        Usuario *usuarioBuscado = reanelcar.buscarUsuarioNIFTablaHash("84538382N");

        if (usuarioBuscado == nullptr){
            cout << "No se encuentra, se va a volver a insertar" << endl;
            reanelcar.insertarUsuarioTablaHash(usuarioCopia);
            cout << endl;

            ///Ahora lo buscamos y mostramos sus trayectos, que no debe de tener
            Usuario *u = reanelcar.buscarUsuarioNIFTablaHash("84538382N");
            if (u->getTrayectosFecha(fechaInicio)->size() == 0){
                cout << "El usuario con nif " << u->getNif() << " no tiene ningun trayecto" << endl;
                cout << endl;
            }

            ///Mostramos ahora el estado de la tabla al volver a insertar el usuario
            reanelcar.mostrarEstadoTablaHash();
        }
    }
    cout << endl;

    ///Eliminamos todos los usuarios que empiezan por Wa, comprobamos la cantidad de usuarios de antes y de despues y mostramos el estado de la tabla
    cout << "Eliminamos los usuarios que empieza por Wa" << endl;
    cout << "Numero previo a la eliminacion de usuarios que empiezan por Wa: " << listaW->size() << endl;

    iteraW = listaW->begin();
    int contadorBorrados = 0;
    while (iteraW != listaW->end()){
        if (iteraW->getNombre().find("Wa") == 0){
            contadorBorrados++;
            iteraW = listaW->erase(iteraW);
        }else{
            iteraW++;
        }
    }
    cout << "Numero de usuarios despues del borrado: " << listaW->size() << endl;
    cout << endl;

    reanelcar.mostrarEstadoTablaHash();
    cout << endl;








    return 0;
}
