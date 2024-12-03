//
// Created by Francisco Jose on 30/09/2024.
//

#include <fstream>
#include <sstream>

#include "Reanelcar.h"
#include "TablaHash.h"

///Constructor por defecto + lectura de CSV
Reanelcar::Reanelcar(string nCoches, string nPR, string nUsuarios): usuarios(), coches(), sitiosPuntoRecarga(),
                                                                    usuariosTabla(), cochesLocalizados(){

    usuariosTabla = new TablaHash(10050);

    ///Lectura de los Coches y lo insertamos en un map
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;

    std::string id_matricula = "";
    std::string marca="";
    std::string modelo="";
    std::string nivelBateria="";    ///Lo ponemos como string, mas tarde lo convertimos a int


    is.open(nCoches); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, id_matricula, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, marca,',');
                getline(columnas, modelo,',');
                getline(columnas,nivelBateria, ',');

                ///Convertimos el string por el cual obteniamos el nivel de bateria a entero
                int bateria = std::stoi(nivelBateria);


                fila="";
                columnas.clear();

                Coche *coche = new Coche(id_matricula, marca, modelo, bateria);

                try{
                    ///Al insertar el nuevo dato se gestiona automaticamente
                    coches.insert(pair<string,Coche*>(coche->getMatricula(),coche));
                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar los coches: " << e.what() << endl;
                }

            }
        }

        is.close();

        //std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error al abrir el fichero de coches.csv" << std::endl;
    }

    ///Lectura de los Usuarios para insertarlos en la lista
    std::string nif = "";
    std::string clave="";
    std::string nombre="";
    std::string direccion="";
    Coche *cocheAlquilado = nullptr;


    is.open(nUsuarios); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, nif, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, clave,',');
                getline(columnas, nombre,',');
                getline(columnas, direccion,',');


                fila="";
                columnas.clear();

                Usuario *usuario = new Usuario(nif, clave, nombre, direccion, cocheAlquilado);

                try{
                    ///Insertamos los usuarios en nuestra lista
                    usuario->setLinkReanel(this);
                    usuarios.push_back(usuario);

                    ///Tambien tenemos que insertar los usuarios ahora en la tabla hash
                    unsigned long int clave = djb2(usuario->getNif());
                    string claveUsuario = usuario->getNif();
                    usuariosTabla->insertar(clave, claveUsuario, *usuario);

                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar los usuarios: " << e.what() << endl;
                }

            }
        }

        is.close();

        //cout << "Todos los coches han sido insertados, la altura del AVL es -> " << alturaAVL() << endl;

        //std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error al abrir el fichero de usuarios1.csv" << std::endl;
    }

    ///Lectura de los Puntos de recarga para insertarlos en el vector
    std::string id = "";
    ///Latitud y Longitud forma un objeto de la clase UTM
    std::string latitud="";
    std::string longitud="";
    std::string maxCoches="";   ///Vamos a tener que convertirlo en un entero mas adelante

    is.open(nPR); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_matricula;marca;modelo;

                getline(columnas, id, ','); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, latitud,',');
                getline(columnas, longitud,',');
                getline(columnas, maxCoches,',');


                ///Convertimos el string en entero
                int maximoCoches = std::stoi(maxCoches);

                ///Se indica que el numero de capacidad maxima de coches sea el doble de la leida en el fichero
                maximoCoches = maximoCoches * 2;
                int idPunto = std::stoi(id);

                ///Convertimos la latitud y longitud en float
                float latitudUTM = std::stof(latitud);
                float longitudUTM = std::stof(longitud);

                fila="";
                columnas.clear();

                ///Creamos el UTM y lo insertamos al Punto de Recarga
                UTM utmDato(latitudUTM, longitudUTM);
                PuntoRecarga punto(idPunto, maximoCoches, utmDato);

                try{
                    ///Insertamos los puntos de recarga en nuestro vector
                    sitiosPuntoRecarga.push_back(punto);
                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar los puntos de recarga: " << e.what() << endl;
                }

            }
        }

        is.close();

        //std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error al abrir el fichero de puntos_recarga.csv" << std::endl;
    }

}

///Destructor
Reanelcar::~Reanelcar() {

}

///Busqueda de Usuario dado un NIF
Usuario *Reanelcar::buscarUsrNif(string nif) {
    ///Obtenemos el iterador
    list<Usuario*>::iterator iterador= usuarios.begin();
    while (iterador != usuarios.end()){
        ///Guardamos el usuario para comprobar si es el del NIF pasado
        Usuario *usuario = *iterador;
        if (usuario->getNif() == nif){
            return usuario;
        }
        iterador++; ///Avanzamos el iterador
    }
    ///En caso de no encontrar el Usuario devolvemos nullptr
    return nullptr;
}

///Busqueda de Usuarios dado un nombre
list<Usuario>* Reanelcar::buscarUsrNombre(string nombre) {
    list<Usuario> *listaUsuarios = new list<Usuario>();  ///Lista que vamos a devolver
    list<Usuario*>::iterator iteraUsuarios = usuarios.begin();
    while (iteraUsuarios != usuarios.end()){
        Usuario *usuario = *iteraUsuarios;
        ///Obtenemos el nombre del usuario para comprobar si empieza por la subcadena indicada por parametro
        string nombreUsuario = usuario->getNombre();
        if (nombreUsuario.find(nombre) == 0){   ///find() devuelve 0 si la subcadena se encuentra al inicio del nombre de este Usuario
            listaUsuarios->push_back(*usuario);
        }
        iteraUsuarios++;
    }
    return listaUsuarios;
}

///Busqueda de un Coche dada una matricula
Coche* Reanelcar::buscarCocheMatricula(string matricula) {
    map<string,Coche*>::iterator itera = coches.find(matricula);
    if (itera == coches.end()){
        return nullptr;
    }else{
        return itera->second;
    }
}

///Busqueda de Coches dado un modelo
vector<Coche>* Reanelcar::buscarCocheModelo(string modelo) {
    vector<Coche> *cochesEncontrados = new vector<Coche>();
    map<string,Coche*>::iterator itera = coches.begin();
    while (itera != coches.end()){
        if (itera->second->getModelo() == modelo){
            ///Al encontrar un coche de ese modelo lo insertamos en el vector a devolver
            cochesEncontrados->push_back(*itera->second);
        }
        itera++;
    }
    return cochesEncontrados;
}

///Metodo que relaciona un Usuario con un Coche
Coche* Reanelcar::alquilar(Usuario *u, int idPROrigen, int idPRDestino, Fecha fIni, Fecha fFin) {
    ///Buscamos los Puntos de Recarga de dos Id dados, uno de origen y otro de destino
    PuntoRecarga *p1 = buscarPuntoRecarga(idPROrigen);
    PuntoRecarga *p2 = buscarPuntoRecarga(idPRDestino);

    Coche *c1 = p1->getMaxBateria();
    u->setCoche(c1);
    ///Borramos el coche que ha sido asociado al usuario
    p1->deleteCoche(c1);
    return c1;
}

///Metodo que busca el coche con maxima bateria
Coche *Reanelcar::alquila(Usuario *usr) {
    ///Buscamos el coche con mayor bateria y lo asocia a un usuario
    Coche *cocheDevolver = sitiosPuntoRecarga.operator[](0).getMaxBateria();
    for (int i = 0; i < sitiosPuntoRecarga.size(); ++i) {
        if (sitiosPuntoRecarga[i].getMaxBateria()->getNivelBateria() > cocheDevolver->getNivelBateria()){
            cocheDevolver = sitiosPuntoRecarga.operator[](i).getMaxBateria();
        }
    }
    ///Le asociamos el coche al usuario pasado como parametro
    usr->setCoche(cocheDevolver);
    return cocheDevolver;
}

///Metodo que coloca un coche en el punto de recarga
bool Reanelcar::colocarCochePR(Coche *c, PuntoRecarga *pr) {
    if (pr->addCoche(c)){
        ///En caso de que se pueda añadir el coche pasado al punto de recarga indicado se devuelve true
        c->aparcar(pr);
        return true;
    } else{
        return false;
    }
}

///Metodo que busca un PR dado un ID. METODO PRIVADO
PuntoRecarga *Reanelcar::buscarPuntoRecarga(int id) {
    ///Si no tenemos Puntos de Recarga se devuelve null
    ///En otro caso, buscamos a ver si esta el PR con el id pasado
    PuntoRecarga *puntoDevolver = nullptr;
    for (int i = 0; i < sitiosPuntoRecarga.size(); ++i) {
        if (sitiosPuntoRecarga.operator[](i).getId() == id){
            puntoDevolver = &sitiosPuntoRecarga.operator[](i);
        }
    }

    return puntoDevolver;
}

///Metodo que obtiene el PR con menos coches de todos los que se tienen
PuntoRecarga *Reanelcar::obtenerPRMenosCoches() {
    ///En caso de que no haya puntos de recarga devolver nullptr
    if (sitiosPuntoRecarga.empty()){
        return nullptr;
    }

    ///En otro caso, buscamos el PR con menor cantidad de coches
    PuntoRecarga *puntoDevolver = nullptr;
    int cantidadCoches = 5000;
    for (int i = 0; i < sitiosPuntoRecarga.size(); ++i) {
        if (sitiosPuntoRecarga.operator[](i).getNumCoches() < cantidadCoches){
            cantidadCoches = sitiosPuntoRecarga.operator[](i).getNumCoches();
            puntoDevolver = &sitiosPuntoRecarga.operator[](i);
        }
    }

    return puntoDevolver;
}


void Reanelcar::distribuirCoches() {
    map<string,Coche*>::iterator iteraCoches = coches.begin();
    int indicePR = 0;
    int nCoches = 0;

    while (iteraCoches != coches.end()){
        ///Si estamos en el ultimo PR, empezamos el ciclo
        if (indicePR == 49){
            indicePR = 0;
        }else{
            ///Si se ha añadido al PR el coche es porque su capacidad lo permite (nCoches < max)
            ///Por lo que se sumara
            if (sitiosPuntoRecarga.operator[](indicePR).addCoche(iteraCoches->second)){
                cout << "Inserccion " << nCoches <<  endl;
                cout << "Coche -> " << iteraCoches->second->getMatricula() << ", " << iteraCoches->second->getMarca() << ", " << iteraCoches->second->getModelo() << endl;
                cout << "Punto de recarga -> " << sitiosPuntoRecarga.operator[](indicePR).getId() << ", MAX: " << sitiosPuntoRecarga.operator[](indicePR).getMax() << ", nCoches: " << sitiosPuntoRecarga.operator[](indicePR).getNumCoches() << endl;
                cout << endl;
                nCoches++;
            }
            indicePR++;
        }
        iteraCoches++;
    }

}

///Metodo para que los Usuarios cogan un coche de manera secuencial de los PR
int Reanelcar::cogerCocheSecuencial(int ultimoPR, Usuario *u, int cantidad) {
    int nDevolver;

    ///Comprobamos si el PR actual tiene algun coche disponible
    ///Cuando obtenemos un coche es cuando se acaba la busqueda
    bool obtenido = false;
    int buscando = 0;

    while (!obtenido){

        ///Si el ultimo coche ha sido sacado del PR 49, el siguiente es el 0
        if (ultimoPR == 50){
            ultimoPR = 0;
        }

        if (sitiosPuntoRecarga.operator[](ultimoPR).getNumCoches() > 0){
            ///Tener en cuenta que el PRDestino sera el siguiente al obtenido
            PuntoRecarga pOrigen = sitiosPuntoRecarga.operator[](ultimoPR);
            nDevolver = ultimoPR + 1;
            if (nDevolver == 50){
                nDevolver = 0;
            }
            PuntoRecarga *pDestino = buscarPuntoRecarga(sitiosPuntoRecarga.operator[](nDevolver).getId());

            ///La fecha inicio es 29/10/2024 y la fecha fin es la misma pero sumando 1 o 2 dias aleatoriamente
            Fecha fechaInicio(25,11,2024);
            int diasASumar = rand() % 2 + 1;
            Fecha fechaFin(fechaInicio.verDia(), fechaInicio.verMes(), fechaInicio.verAnio());
            fechaFin.anadirDias(diasASumar);

            ///Iniciar trayecto asigna el coche y configura el trayecto
            ///Obtenemos el Coche para mostrar los datos del coche con el que va a hacer el trayecto
            u->iniciaTrayecto(pOrigen.getId(), pDestino->getId(), fechaInicio, fechaFin);
            u->buscarPRDestinoAsociar(fechaInicio, fechaFin, pOrigen.getId(), pDestino->getId(), pDestino);
            u->getCocheAlquilado()->setPosicion(pOrigen.getPosicion());
            obtenido = true;

            ///Mostramos los datos de los 10 primeros usuarios
            if (cantidad < 10){
                cout << "Datos del Usuario " << cantidad << ": " << u->getNif() << ", " << u->getNombre() << endl;
                cout << "-Coche: " << u->getCocheAlquilado()->getMatricula() << ", " << u->getCocheAlquilado()->getModelo() << ", " << u->getCocheAlquilado()->getMarca() << endl;
                cout << "-Trayecto: FechaInicio -> " << fechaInicio << ", FechaFin -> " << fechaFin << ", ID Origen -> " << pOrigen.getId() << ", ID Destino -> " << pDestino->getId() << endl;
                cout << endl;
            }
            return nDevolver;

        } else{
            ///En caso de que el PR no tenga coches, avanzamos al siguiente PR para ver si tiene
            ultimoPR++;
            buscando++;
        }

        ///En caso de que se haya buscado en todos los PR y no queden coches, se sale y devuelve 100 (Señal de que no quedan mas coches en los PR)
        if (buscando >= 49){
            obtenido = true;
        }
    }
    return 100;
}

///Metodo que busca un PR dado un ID
PuntoRecarga *Reanelcar::obtenerPuntoRecarga(int id){
    return buscarPuntoRecarga(id);
}


///Metodo que nos devuelve el AVL
vector<Coche*> Reanelcar::primerasMatriculas() {
    vector<Coche*> vectorDevolver;
    map<string,Coche*>::iterator iteraCoches = coches.begin();
    int contador = 0;
    while (contador < 1000 && iteraCoches != coches.end()){
        vectorDevolver.push_back(iteraCoches->second);
        contador++;
    }
    return vectorDevolver;
}



///Metodo que dado un NIF busca su usuario en la tabla hash
Usuario *Reanelcar::buscarUsuarioNIFTablaHash(std::string nif) {
    ///Para hacer la busqueda de un usuario necesitamos la clave por lo que se lo pasamos a djb2
    unsigned long  int clave = djb2(nif);
    Usuario *usuarioDevolver = usuariosTabla->buscar(clave, nif);
    return usuarioDevolver;
}

///Metodo que dado un NIF tenemos que buscarlo y borrarlo
bool Reanelcar::borrarUsuarioTablaHash(std::string nif) {

    unsigned long int clave = djb2(nif);
    Usuario *usuarioBuscado = usuariosTabla->buscar(clave, nif);

    ///Ahora tenemos que buscar el usuario en la lista
    list<Usuario*>::iterator iteraUsuarios = usuarios.begin();
    while (iteraUsuarios != usuarios.end()){
        if (iteraUsuarios.operator*()->getNif() == usuarioBuscado->getNif()){
            if (iteraUsuarios.operator*()->getCocheAlquilado() != nullptr){
                ///Si el usuario tiene un coche alquilado se lo quitamos
                iteraUsuarios.operator*()->setCoche(nullptr);
            }
            ///Le tenemos que quitar los trayectos
            iteraUsuarios.operator*()->eliminarTrayectos();

            usuarios.erase(iteraUsuarios);
            ///Ahora borramos el usuario de la tabla hash
            usuariosTabla->borrar(clave, nif);
            return true;

        }
        iteraUsuarios++;
    }

    return false;
}

///Metodo por el cual obtenemos los usuarios de la tabla has
void Reanelcar::mostrarEstadoTablaHash() {
    usuariosTabla->mostrarEstadoTabla();
}

///Metodo que busca e inserta un usuario dado su nif en la tabla hash
void Reanelcar::insertarUsuarioTablaHash(Usuario u) {
    ///Lo insertamos en la tabla hash
    unsigned long int clave = djb2(u.getNif());
    string claveUsuario = u.getNif();
    usuariosTabla->insertar(clave, claveUsuario, u);

    ///Lo insertamos en la lista
    usuarios.push_back(&u);
}

///Metodo que rellena la malla regular
void Reanelcar::rellenarMalla() {

}

///Metodo quedevuelve los coches encontrados en esa posicion con un rango pasado
vector<Coche*> Reanelcar::buscarCochesRadio(UTM posicion, float radioKm) {
    vector<Coche*> cochesRadio;

    double latCentro = posicion.getLatitud();
    double lonCentro = posicion.getLongitud();

    ///Obtenemos todos los coches dentro de ese radio
    vector<Coche*> cochesCercanos = cochesLocalizados.buscarRadio(latCentro, lonCentro, radioKm);

    ///Lo insertamos en nuestro vector a devolver
    for (int i = 0; i < cochesCercanos.size(); ++i) {
        cochesRadio.push_back(cochesCercanos.operator[](i));
    }

    return cochesRadio;
}

///Metodo que dada una posicion busca el coche mas cercano a dicha posicion
Coche *Reanelcar::buscarCocheMasCercano(UTM posicion) {
    Coche *cocheCercano = nullptr;
    double distancia = 9999;

    double latCentro = posicion.getLatitud();
    double lonCentro = posicion.getLongitud();

    ///Recorremos todos los PR
    map<string,Coche*>::iterator iteraCoches = coches.begin();
    ///Recorremos todos los coches para buscar el mas cercano al punto pasado como parametro
    while (iteraCoches != coches.end()){
        ///Obtenemos la posicion del coche y calculamos la diferencia con la pasada
        double latCoche = iteraCoches->second->getPosicionLat();
        double lonCoche = iteraCoches->second->getPosicionLong();

        ///Calculamos la distancia a la que esta el coche de dicha coordenada
        double distanciaCoche = calcularDistancias(latCoche, lonCoche, latCentro, lonCentro);

        ///Comprobamos si ese coche esta mas cerca que el ultimo
        if (distanciaCoche < distancia){
            distancia = distanciaCoche;
            ///Obtenemos el coche para devolverlo
            cocheCercano = iteraCoches->second;
        }

        iteraCoches++;
    }

    return cocheCercano;
}

///Metodo que calcula la distancia entre dos puntos
double Reanelcar::calcularDistancias(double lat1, double lon1, double lat2, double lon2) {
    double distanciaObtenida = cochesLocalizados.haversine(lat1,lon1,lat2,lon2);
    return distanciaObtenida;
}

///Metodo para leer destino.csv
vector<pair<Usuario,UTM>> Reanelcar::lecturaPosiciones(std::string fichero) {

    ///Vector que almacena un usuario y sus correspondientes coordenadas de destino
    vector<pair<Usuario,UTM>> vectorAsociadoUsuariosUTM;

    float latMin = 9999;
    float latMax = -9999;
    float lonMin = 9999;
    float lonMax = -9999;

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;

    ///Lectura de las coordenadas
    std::string nombre = "";
    std::string latitud="";
    std::string longitud="";


    is.open(fichero); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                getline(columnas, nombre,',');
                getline(columnas, latitud,',');
                getline(columnas, longitud,',');

                ///Transformamos la latitud y longitud a float
                float latitud2 = std::stof(latitud);
                float longitud2 = std::stof(longitud);

                ///Comprobamos para sacar las coordenadas X,Y mas pequeñas y mas grandes
                if(latitud2 > latMax){
                    latMax = latitud2;
                }else{
                    if(latitud2 < latMin){
                        latMin = latitud2;
                    }
                }
                if(longitud2 > lonMax){
                    lonMax = longitud2;
                }else{
                    if(longitud2 < lonMin){
                        lonMin = longitud2;
                    }
                }

                fila="";
                columnas.clear();

                UTM utmCoordenada(latitud2, longitud2);
                Usuario usuario(nombre);

                try{
                    std::pair<Usuario,UTM> usuarioUTM = std::make_pair(usuario, utmCoordenada);
                    vectorAsociadoUsuariosUTM.push_back(usuarioUTM);
                } catch(bad_alloc &e){
                    cout<<"Error al intentar insertar las coordenadas de los usuarios: " << e.what() << endl;
                }

            }
        }

        is.close();

    } else {
        std::cout << "Error al abrir el fichero de destino.csv" << std::endl;
    }


    ///Creamos la malla regular
    int nDivisiones = 1489;
    MallaRegular<Coche*> MallaCarga(lonMin,latMin,lonMax,latMax,nDivisiones);
    this->cochesLocalizados = MallaCarga;

    //rellenarMalla();

    return vectorAsociadoUsuariosUTM;
}

///Metodo que inserta un coche en la malla regular
void Reanelcar::insertarCocheMalla(Coche *c) {
    cochesLocalizados.insertar(c->getPosicionLong(), c->getPosicionLat(), c);
}



