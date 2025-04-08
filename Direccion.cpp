#include <iostream>
#include <cstring>
#include <limits>//Para numeric_limits

#include "Direccion.h"

using namespace std;

Direccion::Direccion(){
    strcpy(_nombreCalle, "Sin calle");
    strcpy(_nombreCiudad,"Sin ciudad");
    strcpy(_provinciaDireccion, "Sin provincia");
    _alturaCalle = 0;
    _codigoPostal = 0;

}

///Getter:
const char* Direccion::getNombreCalle(){
    return _nombreCalle;
}

int Direccion::getAlturaCalle(){
    return _alturaCalle;
}

const char* Direccion::getNombreCuidad(){
    return _nombreCiudad;
}

int Direccion::getCodigoPostal(){
    return _codigoPostal;
}

const char* Direccion::getProvinciaDireccion(){
    return _provinciaDireccion;
}

///Setter:
void Direccion::setNombreCalle(const char* nombreCalle){
    strcpy( _nombreCalle, nombreCalle);
}

void Direccion::setAlturaCalle(int alturaCalle){
    _alturaCalle = alturaCalle;
}

void Direccion::setNombreCiudad(const char* nombreCiudad){
    strcpy(_nombreCiudad, nombreCiudad);
}

void Direccion::setCodigoPostal(int codigoPostal){
    _codigoPostal = codigoPostal;
}

void Direccion::setProvinciaDireccion(const char* provinciaDireccion){
    strcpy(_provinciaDireccion, provinciaDireccion);
}

void Direccion::Cargar(){
    cout << "Ingrese provincia (50 caracteres maximo): ";
    cin.getline(_provinciaDireccion, 50);
    ///VERIFICACION DE LA PROVINCIA
    int tam = strlen(_provinciaDireccion);
    if(tam < 2){
        cout << endl << "ERROR: EL NOMBRE DE LA PROVINCIA DEBE TENER AL MENOS 2 CARACTERES" << endl;
        _codigoPostal = -1;
        return;
    }

    cout << "Ingrese ciudad (50 caracteres maximo): ";
    cin.getline(_nombreCiudad, 50);
    ///VERIFICACION DE LA CIUDAD
    tam = strlen(_nombreCiudad);
    if(tam < 2){
        cout << endl << "ERROR: EL NOMBRE DE LA CIUDAD DEBE TENER AL MENOS 2 CARACTERES" << endl;
        _codigoPostal = -1;
        return;
    }

    cout << "Ingrese codigo postal: ";
    cin >> _codigoPostal;
    ///Verificar si la entrada es valida
    if (cin.fail() || _codigoPostal < 1000 || _codigoPostal > 999999999) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _codigoPostal = -1;
        return;
    }

    cout << "Ingrese calle (50 caracteres maximo): ";
    cin.ignore();
    cin.getline(_nombreCalle, 50);
    ///VERIFICACION DE LA CALLE
    tam = strlen(_nombreCalle);
    if(tam < 2){
        cout << endl << "ERROR: EL NOMBRE DE LA CALLE DEBE TENER AL MENOS 2 CARACTERES" << endl;
        _codigoPostal = -1;
        return;
    }

    cout << "Ingrese altura de la calle: ";
    cin >> _alturaCalle;
    ///Verificar si la entrada es valida
    if (cin.fail() || _alturaCalle < 1 || _alturaCalle > 99999) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _codigoPostal = -1;
        return;
    }
}

void Direccion::Mostrar(){
    cout << endl << "DIRECCION" << endl;
    cout << "Provincia: " << _provinciaDireccion << endl;
    cout << "Ciudad: " << _nombreCiudad << endl;
    cout << "Codigo Postal: " << _codigoPostal << endl;
    cout << "Calle: " << _nombreCalle << endl;
    cout << "Altura de la calle: " << _alturaCalle << endl;
}
