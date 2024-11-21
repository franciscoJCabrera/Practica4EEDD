//
// Created by Francisco Jose on 12/11/2024.
//

#include "TablaHash.h"

///djb2
unsigned long int djb2(const string &str){
    unsigned long hash = 5381;

    for(int i = 0; i < str.length(); i++){
        hash=((hash << 5) + hash ) + str[i];
    }

    return hash;
}

///Metodo que comprueba si un numero es primo
bool esPrimo(int num, int div){
    if ( num % div == 0 ){
        return false;
    }else{
        if (div > sqrt(num)){
            return true;
        } else {
            return esPrimo(num,++div);
        }
    }
}

///Metodo por el cual se sabe el siguiente primo dado un numero por parametro
int siguientePrimo(int num){
    while(!esPrimo(num,2)){
        num++;
    }
    return num;
}


///Constructores
TablaHash::TablaHash(int maxElementos, float lambda): _tablaDispersion(siguientePrimo(maxElementos)/lambda), _lambda(lambda) {
    _tamTabla = _tablaDispersion.size();
}

TablaHash::TablaHash(const TablaHash &thash): _tablaDispersion(thash._tamTabla) {
    this->_tamTabla = thash._tamTabla;
    this->_factorCarga = thash._factorCarga;
    this->_promedioColisiones = thash._promedioColisiones;
    this->_numMax10 = thash._numMax10;
    this->_numElementosContenidos = thash._numElementosContenidos;

    for (int i = 0; i < _tamTabla; i++){
        this->_tablaDispersion.at(i) = thash._tablaDispersion.at(i);
    }
}

///Destructor
TablaHash::~TablaHash() {

}

///Sobrecarga de operadores
void TablaHash::operator=(const TablaHash &orig) {
    this->_tablaDispersion.resize(orig._tamTabla);
    for (int i = 0; i < orig._tamTabla; i++){
        this->_tablaDispersion.at(i) = orig._tablaDispersion.at(i);
    }

    this->_tamTabla = orig._tamTabla;
    this->_factorCarga = orig._factorCarga;
    this->_promedioColisiones = orig._promedioColisiones;
    this->_numMax10 = orig._numMax10;
    this->_numElementosContenidos = orig._numElementosContenidos;
}

///Getter y Setter
void TablaHash::setTablaDispersion(const vector<Entrada> &tablaDispersion) {
    _tablaDispersion = tablaDispersion;
}

unsigned int TablaHash::getNumElementosContenidos() const {
    return _numElementosContenidos;
}

void TablaHash::setNumElementosContenidos(int numElementosContenidos) {
    _numElementosContenidos = numElementosContenidos;
}

unsigned int TablaHash::getMaximoColisiones() const {
    return _maximoColisiones;
}

void TablaHash::setMaximoColisiones(unsigned int maximoColisiones) {
    _maximoColisiones = maximoColisiones;
}

unsigned int TablaHash::getNumMax10() const {
    return _numMax10;
}

void TablaHash::setNumMax10(unsigned int numMax10) {
    _numMax10 = numMax10;
}

float TablaHash::getPromedioColisiones() const {
    return _promedioColisiones;
}

void TablaHash::setPromedioColisiones(float promedioColisiones) {
    _promedioColisiones = promedioColisiones;
}

float TablaHash::getFactorCarga()  {
    return _factorCarga;
}

void TablaHash::setFactorCarga(float factorCarga) {
    _factorCarga = factorCarga;
}

unsigned int TablaHash::getTamTabla() const {
    return _tamTabla;
}

void TablaHash::setTamTabla(unsigned int tamTabla) {
    _tamTabla = tamTabla;
}

int TablaHash::getContadorRedispersion() const {
    return contadorRedispersion;
}

void TablaHash::setContadorRedispersion(int contadorRedispersion) {
    TablaHash::contadorRedispersion = contadorRedispersion;
}

void TablaHash::setLambda(float lambda) {
    _lambda = lambda;
}


///Metodos de ajuste y estadistica de la tabla
unsigned int TablaHash::maxColisiones() {
    return this->_maximoColisiones;
}

unsigned int TablaHash::numMax10() {
    return this->_numMax10;
}

float TablaHash::promedioColisiones() {
    _promedioColisiones = ((float)_maximoColisiones/_tamTabla);
    return _promedioColisiones;
}


float TablaHash::factorCarga() {
    return _factorCarga;
}

unsigned int TablaHash::tamTabla() {
    return _tablaDispersion.size();
}

///Metodo que muestra el estado interno de la tabla
void TablaHash::mostrarEstadoTabla() {
    cout << "***** ESTADO DE LA TABLA HASH CERRADA *****" << endl;
    cout << "   - Numero maximo de colisiones: " << this->_maximoColisiones << endl;
    cout << "   - Numero de veces que se han superado las 10 colisiones: " << this->_numMax10 << endl;
    cout << "   - Promedio de colisiones por operacion de insersion: " << this->_promedioColisiones << endl;
    cout << "   - Factor de carga: " << this->_factorCarga << endl;
    cout << "   - Tamanio de la tabla: " << this->_tamTabla << endl;
    cout << "   - Numero de redispersiones ocurridas: " << this->contadorRedispersion << endl;
    cout << "*******************************************" << endl;
}


///Metodos funcionales de la tabla hash
///Metodo que inserta un usuario en la tabla hash
bool TablaHash::insertar(unsigned long clave, string &claveUsuario, Usuario &usuario) {
    int intento = 0;
    unsigned long posicion = 0;

    int contadorRedis = 0;

    while (true) {
        ///Buscamos la posicion con la funcion de dispersion
        posicion = this->hashDispersionDoble2(clave, intento);

        ///Si se puede insertar el dato en la cubeta lo insertamos y ponemos la cubeta en ocupado
        if ((this->_tablaDispersion[posicion]._estado == libre) || (this->_tablaDispersion[posicion]._estado == disponible)) {

            ///Asignamos dato y ponemos a ocupado
            this->_tablaDispersion[posicion]._dato= usuario;
            this->_tablaDispersion[posicion]._estado = ocupado;
            this->_tablaDispersion[posicion]._clave = clave;
            _numElementosContenidos++;

            ///Recalculamos el factor de carga (numeroElementosTabla / tamañoTabla)
            float auxNumCont = this->getNumElementosContenidos();
            float auxTamTabla = this->getTamTabla();
            _factorCarga = auxNumCont / auxTamTabla;

            ///Si el factor de carga es mayor que lambda se tiene que redispersar la tabla
            if (this->_factorCarga > _lambda) {
                contadorRedis++;
                this->contadorRedispersion = contadorRedis;
                this->redispersar(siguientePrimo(this->getTamTabla() + (this->getTamTabla() * 0.3)));
            }

            if (intento > _maximoColisiones) {
                _maximoColisiones = intento;
            }

            ///Actualizamos cuando hay mas de 10 intentos para insertar un dato
            if (intento > 10) {
                _numMax10++;
            }

            ///Calculamos el promedio de colisiones
            _promedioColisiones = (float)this->_numColisiones / this->_numElementosContenidos;

            return true;
        } else {
            ///No se permiten repetidos, por lo que no se realiza la insercion y devuelve falso
            if (this->_tablaDispersion[posicion]._dato == usuario) {
                return false;
            }
            _numColisiones++;
            _promedioColisiones = (float)this->_numColisiones / this->_numElementosContenidos;
            intento++;
        }
    }
}


///Metodo para buscar un dato en la tabla hash
Usuario* TablaHash::buscar(unsigned long clave, string &claveUsuario) {
    int _intento = 0;
    unsigned long _posEncontrar = 0;


    while (_intento < _tamTabla){

        ///Empleamos la funcion de dispersion
        _posEncontrar = hashDispersionDoble2(clave, _intento);

        ///La cubeta debe de estar ocupada obviamente para comprobar el dato
        if ( _tablaDispersion[_posEncontrar]._estado == ocupado || _tablaDispersion[_posEncontrar]._estado == disponible ) {
            ///Comprobamos si el nif de la cubeta concuerda con la clave del usuario
            if(_tablaDispersion[_posEncontrar]._dato.getNif() == claveUsuario) {
                ///Obtenemos el usuario para devolverlo
                Usuario *usuario = &(_tablaDispersion[_posEncontrar]._dato);
                return usuario;
            }
        }
        _intento++;

    }

    ///En caso de que no se encuentre, se devuelve nullptr
    return nullptr;
}


///Metodo para borrar un dato en una tabla hash
bool TablaHash::borrar(unsigned long clave,const string &claveBuscar) {
    int _intento = 0;
    unsigned long int _posBorrar = 0;

    while( _intento < _tamTabla ){
        ///Empleamos la funcion de dispersion doble para obtener la posicion
        _posBorrar = hashDispersionDoble2(clave, _intento);

        ///Comprobamos si la cubeta esta ocupada, si tiene esa clave y si coincide el nif
        if ( (_tablaDispersion[_posBorrar]._clave == clave) && (_tablaDispersion[_posBorrar]._estado == ocupado) && (_tablaDispersion[_posBorrar])._dato.getNif() == claveBuscar ) {
            ///Para borrar el dato, le damos a la cubeta el valor inicial, vacia y de estado libre
            _tablaDispersion[_posBorrar] = Entrada();
            _numElementosContenidos--;

            ///Recalculamos el factor de carga
            _factorCarga = (float)_numElementosContenidos/_tamTabla;

            return true;
        } else {
            _intento++;
        }
    }
    return false;
}

///Metodo para redispersar la tabla
void TablaHash::redispersar(unsigned int tam) {
    vector<Usuario> backupUsuarios;

    int tamTablaInicial = this->_tamTabla;
    for (int i = 0; i < tamTablaInicial; i++) {
        if (this->_tablaDispersion[i]._estado == ocupado) {
            backupUsuarios.push_back(this->_tablaDispersion[i]._dato);

            borrar(this->_tablaDispersion[i]._clave, this->_tablaDispersion[i]._dato.getNif());
        }
    }

    this->_tablaDispersion.resize(tam);
    this->_tamTabla = this->_tablaDispersion.size();

    this->_factorCarga = (float)this->_numElementosContenidos / this->_tamTabla;

    for (int i = 0; i < backupUsuarios.size(); i++) {
        Usuario usuarioInsertar = backupUsuarios.operator[](i);
        string claveUsuario = usuarioInsertar.getNif();
        this->insertar(djb2(usuarioInsertar.getNif()), claveUsuario, usuarioInsertar);
    }
}