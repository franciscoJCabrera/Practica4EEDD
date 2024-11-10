#include "Reanelcar.h"
#include <iostream>

using namespace std;

/**
 * @Author Francisco José Cabrera Bermejo (fjcb0015)
 */

/**
 * TODO: Comprobar metodo Usuario::CogeCoche(), la llamada a alquila se puede sustituir a alquilar
 * TODO: Preguntar, se pueden hacer metodos para cargar EEDD en parametros pasados
 * TODO: Mirar la creacion del Trayecto, el ID del trayecto depende del numero de trayectos realizados por ese usuario
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

    ///Tenemos que distribuir 10.000 coches en todos los PR (En total tiene una capacidad de 3690)
    cout << "--Vamos a distribuir todos los coches en los PR de forma secuencial--" << endl;
    reanelcar.distribuirCoches();
    cout << "--Coches distribuidos correctamente--" << endl;













    return 0;
}
