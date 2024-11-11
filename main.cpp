#include "Reanelcar.h"
#include <iostream>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

/**
 * TODO: Mirar usuario::obtenerTrayecto(), alomejor se puede borrar
 */

int main(int argc, const char * argv[]) {

//
//    cout << "--CONTENIDO DE LA PRACTICA 3 ACTUALIZADO PARA UTILIZAR STL--" << endl;
//
//    ///Mostramos las primeras 1000 matriculas
//    VDinamico<Coche*> primerasMatriculas = reanelcar.primerasMatriculas();
//    cout << "--Vamos a mostrar las 1000 primeras matriculas tras recorrer el AVL en inorden--" << endl;
//    for (int i = 0; i < 1000; ++i) {
//        cout << "Coche " << i << " : " << primerasMatriculas.operator[](i)->getMatricula() << endl;
//    }
//    cout << endl;
//
//    ///Instanciamos un PuntoRecarga con un maximo de 50 plazas
//    PuntoRecarga puntoRecarga(50);
//
//    ///Creamos un vector que va a contener todas las matriculas que vamos a buscar en el AVL
//    Coche* matriculas[50];
//    int pos = 0;
//
//    ///Inicializamos el vector a null todo
//    for (int i=0; i<50; i++){
//        matriculas[i] = nullptr;
//    }
//
//    /** MATRICULAS Y DATOS DE LOS COCHES
//     * 6028 ZXL -> BMW X5
//     * 6795 MLS -> Hyundai i30
//     * 0209 GZT -> Ford Mustang
//     * 2171 ZDC -> Honda HR-V
//     * 4649 HJH -> Renault Clio
//     * 8953 YRT -> BMW M3
//     * 6698 XKM -> Volkswagen Golf
//     * 5830 MNZ -> Honda Accord
//     * 7690 DKN -> Honda HR-V
//     * 6557 BGW -> Honda Civic
//     * 4680 BBC -> Mercedes-Benz E-Class
//     * 1045 GYK -> BMW X5
//     * 9400 HRX -> Honda HR-V
//     * 9856 FLG -> BMW X3
//     * 3704 RWK -> Honda Civic
//     * 8514 HLL -> Audi A3
//     * 7048 YYY -> BMW X3
//     * 2910 ZXN -> Volkswagen Golf
//     * 7358 DZN -> BMW X3
//     * 2966 LTL -> Ford Explorer
//     * 4268 MGX -> Hyundai i30
//     * 4155 DFX -> Renault Captur
//     * 7891 XXB -> Audi Q5
//     * 2140 SNB -> Mercedes-Benz E-Class
//     * 9838 THH -> Renault Kadjar
//     * 3168 LNC -> Volkswagen Polo
//     * 9150 HNB -> Honda Accord
//     * 1691 FHS -> Audi A3
//     */
//
//    ///Hacemos la busqueda de las matriculas y las metemos en el vector uno a uno
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("6028 ZXL");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("6795 MLS");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("0209 GZT");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("2171 ZDC");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("4649 HJH");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("8953 YRT");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("6698 XKM");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("5830 MNZ");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("7690 DKN");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("6557 BGW");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("4680 BBC");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("1045 GYK");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("9400 HRX");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("9856 FLG");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("3704 RWK");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("8514 HLL");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("7048 YYY");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("2910 ZXN");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("7358 DZN");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("2966 LTL");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("4268 MGX");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("4155 DFX");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("7891 XXB");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("2140 SNB");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("9838 THH");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("3168 LNC");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("9150 HNB");
//    matriculas[pos++] = reanelcar.buscarCocheMatricula("1691 FHS");
//
//    cout << "--Los siguientes coches han sido buscados por sus matriculas--" << endl;
//    ///Mostramos todos los coches que han sido buscados por sus matriculas
//    for (int i = 0; i < pos; ++i) {
//        if (matriculas[i] != nullptr) {
//            cout << "Coche: " << i << ". Tiene los siguientes datos -> "
//                 << matriculas[i]->getMatricula() << ", "
//                 << matriculas[i]->getMarca() << ", "
//                 << matriculas[i]->getModelo() << endl;
//        }
//    }
//
//    cout << endl;
//
//    cout << "--Los coches que han sido buscados van a ser aniadidos al Punto de Recarga--" << endl;
//    ///Metemos los coches en el Punto de Recarga mediante el metodo reanelcar::colocarCochePR()
//    for (int i = 0; i < pos; ++i) {
//        reanelcar.colocarCochePR(matriculas[i]);
//        cout << "Coche con matricula " << matriculas[i]->getMatricula() << " ha sido aniadida al punto de recarga" << endl;
//    }
//
//    cout << endl;
//
//    cout << "--Se va a buscar el usuario con DNI 91477235Q para asignarle el coche con mayor carga--" << endl;
//    ///El usuario con NIF 91477235Q (Rafael Luckwell, 25576) va a alquilar un coche, el que Reanelcar le devuelva con mayor bateria
//    Usuario *usuarioDeseado = reanelcar.buscarUsrNif("91477235Q");
//    cout << "El usuario: " << usuarioDeseado->getNombre() << " (" << usuarioDeseado->getNif() << "), va a alquilar un coche" << endl;
//    reanelcar.alquila(usuarioDeseado);
//    cout << "El coche: " << usuarioDeseado->getCocheAlquilado()->getMatricula() << "," << usuarioDeseado->getCocheAlquilado()->getMarca() << "," << usuarioDeseado->getCocheAlquilado()->getModelo() << " es el coche con mayor bateria y se le va a asociar con un " << usuarioDeseado->getCocheAlquilado()->getNivelBateria() << "% de bateria." <<  endl;

    cout << "-- PRACTICA 4 --" << endl;
    cout << endl;

    ///Lectura de los CSV pasados por parametro, cargando las diferentes EEDD
    Reanelcar reanelcar("../coches_v2.csv", "../puntos_recarga.csv", "../usuarios1.csv");

    cout << "Ficheros cargados" << endl;
    cout << endl;

    ///APARTADO 1)
    ///Tenemos que distribuir 10.000 coches en todos los PR (En total tiene una capacidad de 3623)
    cout << "--Vamos a distribuir todos los coches en los PR de forma secuencial--" << endl;
    reanelcar.distribuirCoches();
    cout << "--Coches distribuidos correctamente--" << endl;
    cout << endl;

    ///APARTADO 2)
    ///Hay un total de 204 usuarios cuyo nombre empieza por W
    cout << "--Todos los usuarios que empiezan por W van a coger un coche--" << endl;
    list<Usuario>* usuariosW = reanelcar.buscarUsrNombre("W");
    cout << "Cantidad de usuarios encontrados que empiezan por W: " << usuariosW->size() << endl;

    list<Usuario>::iterator iteraUsuarios = usuariosW->begin();
    int punto = 0;
    int siguiente;
    bool fin;
    int cantidadUsuariosMostrados = 0;
    while (iteraUsuarios != usuariosW->end() && !fin){

        siguiente = iteraUsuarios->getLinkReanel()->cogerCocheSecuencial(punto, iteraUsuarios.operator->(), cantidadUsuariosMostrados);
        cantidadUsuariosMostrados++;
        punto = siguiente;

        ///En el momento en el que te devuelve 100 es porque ya no ningun coche en ningun PR
        if (punto == 100){
            fin = true;
        }

        iteraUsuarios++;
    }

    ///APARTADO 3)
    cout << "--Los Usuarios que empiezan por Wa van a aparcar el coche--" << endl;
    cout << endl;

    iteraUsuarios = usuariosW->begin();
    Fecha fechaInicio(29,10,2024);
    int contador = 0;
    while (iteraUsuarios != usuariosW->end()){

        ///Si empieza el nombre por Wa aparca el coche en el PRDestino del trayecto
        Usuario u = iteraUsuarios.operator*();
        if (u.getNombre().find("Wa") == 0){

            ///Obtenemos todos los trayectos de cada usuarios dada una fecha de inicio
            ///TODO: El destino se pasa mal
            vector<Trayecto> * trayectosUsuario = u.getTrayectosFecha(fechaInicio);

            ///Solo vamos a mostrar el contenido de los 10 primeros usuarios
            if (contador < 10){
                cout << "Usuario " << contador << endl;
                cout << "El Usuario con DNI: " << iteraUsuarios->getNif() << " tiene como nombre: " << iteraUsuarios->getNombre() << endl;
                cout << "Coche que tiene: " << u.getCocheAlquilado()->getMatricula() << ", " << u.getCocheAlquilado()->getModelo() << ", " << u.getCocheAlquilado()->getMarca() << endl;

                for (int i = 0; i < trayectosUsuario->size(); ++i) {
                    cout << "Trayecto " << i << ": Fecha Inicio: " << trayectosUsuario->operator[](i).getFechaInicio() << ", Fecha Fin: " << trayectosUsuario->operator[](i).getFechaFin() << ", Origen (PR ID): " << trayectosUsuario->operator[](i).getOrigen()->getId() << ", Destino (PR ID): " << trayectosUsuario->operator[](i).getDestino()->getId() << endl;
                }
                cout << endl;
                contador++;
            }

            ///El usuario aparca el coche en el PRDestino. Como solamente ha hecho un viaje, sabemos que es en el trayecto 0
            ///TODO: Meter PRDestino en el que se deja el coche
            iteraUsuarios->aparcaCoche(u.getCocheAlquilado(), trayectosUsuario->operator[](0).getDestino() );


        }

        iteraUsuarios++;

    }
    cout << endl;

    ///APARTADO 4)
    cout << "--Los 10 primeros Usuarios con nombre empezado en Wa van a volver a alquilar un coche--" << endl;
    iteraUsuarios = usuariosW->begin();
    contador = 0;
    int indicePR = 0;
    while (contador < 10){
        ///Los 10 primeros Usuarios cuyo nombre empiece por Wa van a volver a alquilar un coche
        if (iteraUsuarios->getNombre().find("Wa") == 0){
            ///El PRDestino va a ser el siguiente al de Origen
            ///El de Origen es llevado por
            int siguientePR = indicePR + 1;
            ///El nombre del Usuario empieza por Wa
            ///Creamos el Usuario y la fecha para la que van a coger los nuevos coches
            Usuario *u = iteraUsuarios.operator->();
            int diasASumar = rand() % 2 + 1;
            Fecha fechaFin(fechaInicio.verDia(), fechaInicio.verMes(), fechaInicio.verAnio());
            fechaFin.anadirDias(diasASumar);

            ///El usuario va a alquilar un nuevo coche
            if (indicePR == 50){
                indicePR = 0;
            }

            if (siguientePR == 50){
                siguientePR = 0;
            }
            iteraUsuarios->getLinkReanel()->alquilar(u, indicePR, siguientePR, fechaInicio, fechaFin);
            indicePR++;
            contador++;
        }
    }
    cout << endl;

    ///APARTADO 5)
    cout << "--Vamos a mostrar la cantidad de Usuarios que han realizado mas de un trayecto hoy--" << endl;

    ///Como bien sabemos, los usuarios que empiezan por W son los unicos que han hecho trayectos
    iteraUsuarios = usuariosW->begin();
    contador = 0;
    while (iteraUsuarios != usuariosW->end()){
        if (iteraUsuarios->getTrayectosFecha(fechaInicio)->size() > 1){
            cout << "El usuario " << contador << " con DNI: " << iteraUsuarios->getNif() << " y nombre: " << iteraUsuarios->getNombre() << " ha hecho un total de " << iteraUsuarios->getTrayectosFecha(fechaInicio)->size() << " de trayectos el dia de hoy" << endl;
            contador++;
            cout << endl;
        }
        iteraUsuarios++;
    }
    cout << endl;


    ///APARTADO 6)

    cout << "--Se va a buscar el coche con matricula 6698 XKM y a mostrar toda su informacion--" << endl;
    ///El coche existe y es un Golf
    Coche *cocheBuscado = reanelcar.buscarCocheMatricula("6698 XKM");

    cout << "Informacion del Coche: " << endl;
    cout << "- Matricula: " << cocheBuscado->getMatricula() << ", Modelo: " << cocheBuscado->getModelo() << ", Marca: " << cocheBuscado->getMarca() << endl;

    if (cocheBuscado->getCocheCargando()){
        cout << "- Se encuentra en el Punto de Recarga: " << cocheBuscado->getCocheCargando()->getId() << ", donde hay un total de " << cocheBuscado->getCocheCargando()->getNumCoches() << " coches cargando" << endl;
    }

    ///Busqueda para ver si el coche lo tiene alguien alquilado
    iteraUsuarios = usuariosW->begin();
    while (iteraUsuarios != usuariosW->end()){
        if (iteraUsuarios->getCocheAlquilado()->getMatricula() == cocheBuscado->getMatricula() && iteraUsuarios->getCocheAlquilado()->getModelo() == cocheBuscado->getModelo() && iteraUsuarios->getCocheAlquilado()->getMarca() == cocheBuscado->getMarca()){
            cout << "- El coche esta alquilado, lo tiene actualmente: " << iteraUsuarios->getNif() <<", "  << iteraUsuarios->getNombre() << endl;
        }
        iteraUsuarios++;
    }

    cout << "FIN" << endl;


    return 0;
}
