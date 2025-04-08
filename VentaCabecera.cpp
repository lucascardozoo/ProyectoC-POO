#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Cliente.h"
#include "Vendedor.h"
#include "VentaCabecera.h"
#include "constantes.h"
#include "ArchivoClientes.h"
#include "ArchivoVendedores.h"
#include "ArchivoVentaCabecera.h"

using namespace std;

VentaCabecera::VentaCabecera(){
    _numeroFactura = 0;
    _numeroCliente = 0;
    _legajoVendedor = 0;
    _totalVenta = 0;
    _estado = 0;
}

///GETTER:
int VentaCabecera::getNumeroFactura(){
    return _numeroFactura;
}

Fecha VentaCabecera::getFechaVenta(){
    return _fechaVenta;
}

int VentaCabecera::getNumeroCliente(){
    return _numeroCliente;
}

int VentaCabecera::getLegajoVendedor(){
    return _legajoVendedor;
}

float VentaCabecera::getTotalVenta(){
    return _totalVenta;
}

bool VentaCabecera::getEstado(){
    return _estado;
}


///SETTER
void VentaCabecera::setNumeroFactura(int numeroFactura){
    _numeroFactura = numeroFactura;
}

void VentaCabecera::setFechaVenta(Fecha fechaVenta){
    _fechaVenta = fechaVenta;
}

void VentaCabecera::setNumeroCliente(int numeroCliente){
    _numeroCliente = numeroCliente;
}

void VentaCabecera::setLegajoVendedor(int legajoVendedor){
    _legajoVendedor = legajoVendedor;
}

void VentaCabecera::setTotalVenta(float totalVenta){
    _totalVenta = totalVenta;
}

void VentaCabecera::setEstado(bool estado){
    _estado = estado;
}

void VentaCabecera::asignacionNumeroFactura(){
    ArchivoVentaCabecera archivoVentaCabecera;
    int cantidadRegistros = archivoVentaCabecera.ContarRegistros();
    _numeroFactura = cantidadRegistros + 1;
}

void VentaCabecera::Cargar(){
    ArchivoClientes archivoClientes;
    ArchivoVendedores archivoVendedores;
    int posicion, anioActual, mesActual, diaActual, anioVenta, mesVenta, diaVenta;

    ///OBTENGO FECHA ACTUAL
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActual = fechaActual.tm_year + 1900;
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    ///Asignacion de numero de factura automatico
    asignacionNumeroFactura();

    ///Verificamos fecha que no sea mayor a la actual
    cout << "Ingrese la fecha de la venta (DD/MM/AAAA)" << endl;
    _fechaVenta.Cargar();
    if(_fechaVenta.getAnio() == -1){
        _numeroFactura = -1;
        return;
    }
    anioVenta = _fechaVenta.getAnio();
    mesVenta = _fechaVenta.getMes();
    diaVenta = _fechaVenta.getDia();
    if (anioVenta > anioActual || (anioVenta == anioActual && mesVenta > mesActual) || (anioVenta == anioActual && mesVenta == mesActual && diaVenta > diaActual)) {
        cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl;
        _numeroFactura = -1;
        return;
    }

    ///Verificamos que el numero cliente este en ArchivoClientes
    cout << "Ingrese el numero de cliente: ";
    cin >> _numeroCliente;
    if (cin.fail() || _numeroCliente < 1) {//Verificar si la entrada es valida
        cout << endl << "Error: Debe ingresar un numero valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _numeroFactura = -1;
        return;
    } else {
        posicion = archivoClientes.BuscarRegistro(_numeroCliente, ACTIVOS);
        if(posicion == -1){
            cout << endl << "NUMERO DE CLIENTE INEXISTENTE" << endl;
            _numeroFactura = -1;
            return;
        } else if (posicion == -2){
            cout << endl << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl;
            _numeroFactura = -1;
            return;
        }
    }

    ///Verificamos que el legajo este en ArchivoVendedores
    cout << "Ingrese el legajo del vendedor: ";
    cin >> _legajoVendedor;
    if (cin.fail() || _legajoVendedor < 1) {//Verificar si la entrada es valida
        cout << endl << "Error: Debe ingresar un numero valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _numeroFactura = -1;
        return;
    } else {
        posicion = archivoVendedores.BuscarRegistro(_legajoVendedor, ACTIVOS);
        if(posicion == -1){
            cout << endl << "LEGAJO DE VENDEDOR INEXISTENTE" << endl;
            _numeroFactura = -1;
            return;
        } else if (posicion == -2){
            cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl;
            _numeroFactura = -1;
            return;
        }
    }

    ///ESTADO
    _estado = true;
}

void VentaCabecera::Mostrar(){
    cout << "Numero de factura: " << _numeroFactura << endl;
    cout << "Fecha: ";
    _fechaVenta.Mostrar();
    cout << "Numero de cliente: " << _numeroCliente << endl;
    cout << "Legajo del Vendedor: " << _legajoVendedor << endl;
    cout << fixed << setprecision(2) << "Total venta: $ " << _totalVenta << endl;
    if(_estado == 1){
        cout << "Estado: Activo" << endl << endl;
    }
    if(_estado == 0){
        cout << "Estado: Desactivo" << endl << endl;
    }
}

void VentaCabecera::operator+=(float totalPorProducto){
    _totalVenta += totalPorProducto;
}

void VentaCabecera::operator-=(float totalPorProducto){
    _totalVenta -= totalPorProducto;
    if (_totalVenta < 0){
        _totalVenta = 0;
    }
}
