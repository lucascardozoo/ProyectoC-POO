#include <iostream>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Vendedor.h"
#include "constantes.h"
#include "ArchivoVendedores.h"

using namespace std;

Vendedor::Vendedor(){
    _legajoVendedor = 0;
    _sueldo = 0.0;
    _estado = false;
}

int Vendedor::getLegajoVendedor(){
    return _legajoVendedor;
}

Fecha Vendedor::getFechaIngreso(){
    return _fechaIngreso;
}

float Vendedor::getSueldo(){
    return _sueldo;
}

bool Vendedor::getEstado(){
    return _estado;
}

void Vendedor::setLegajoVendedor(int legajoVendedor){
    _legajoVendedor = legajoVendedor;
}

void Vendedor::setFechaIngreso(Fecha fechaIngreso){
    _fechaIngreso = fechaIngreso;
}

void Vendedor::setSueldo(float sueldo){
    _sueldo = sueldo;
}

void Vendedor::setEstado(bool estado){
    _estado = estado;
}

void Vendedor::asignacionLegajoVendedor(){
    ArchivoVendedores archivoVendedores;
    int cantidadRegistros = archivoVendedores.ContarRegistros();
    _legajoVendedor = cantidadRegistros + 1;
}

void Vendedor::Cargar(){
    Persona::Cargar();
    if (Persona::getDNI() == -1){
        _legajoVendedor = -1;
        return;
    } else {
        asignacionLegajoVendedor();

        cout << "Ingrese la fecha de ingreso del vendedor (Formato DD/MM/AAAA)" << endl;
        _fechaIngreso.Cargar();
        if(_fechaIngreso.getAnio() == -1){
            cout << endl;
            system("pause");
            _legajoVendedor = -1;
            return;
        }
        ///OBTENGO FECHA ACTUAL
        time_t segDesde1970 = time(0);
        tm *pFechaActual = localtime(&segDesde1970);
        tm fechaActual = *pFechaActual;
        int anioActual = (fechaActual.tm_year + 1900);
        int mesActual = fechaActual.tm_mon + 1;
        int diaActual = fechaActual.tm_mday;
        ///Verificamos fecha que no sea mayor a la actual
        int anioIngreso = _fechaIngreso.getAnio();
        int mesIngreso = _fechaIngreso.getMes();
        int diaIngreso = _fechaIngreso.getDia();
        if (anioIngreso > anioActual || (anioIngreso == anioActual && mesIngreso > mesActual) || (anioIngreso == anioActual && mesIngreso == mesActual && diaIngreso > diaActual)) {
            cout << endl << "LA FECHA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
            system("pause");
            _legajoVendedor = -1;
            return;
        }

        cout << "Ingrese el sueldo del vendedor: ";
        cin >> _sueldo;
        ///Verificar si la entrada es valida
        if (cin.fail() || _sueldo < 0) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            system("pause");
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            _legajoVendedor = -1;
            return;
        }

        _estado =  true;
        return;
    }
}

void Vendedor::Mostrar(){
    cout << "Legajo del vendedor: " << _legajoVendedor << endl;
    cout << "Fecha de ingreso del vendedor: ";
    _fechaIngreso.Mostrar();
    cout << fixed << setprecision(2) << "Sueldo del vendedor: $" << _sueldo << endl;
    if (_estado){
        cout << "Estado del vendedor: Activo" << endl << endl;
    } else {
        cout << "Estado del vendedor: Desactivo" << endl << endl;
    }
    Persona::Mostrar();
}

