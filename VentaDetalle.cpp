#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Producto.h"
#include "VentaCabecera.h"
#include "VentaDetalle.h"
#include "constantes.h"
#include "ArchivoProductos.h"
#include "ArchivoVentaCabecera.h"
#include "ArchivoVentaDetalle.h"

using namespace std;

VentaDetalle::VentaDetalle(){
    _numeroFactura = 0;
    _idProducto = 0;
    _cantidadProducto = 0;
    _precioProducto = 0;
    _totalPorProducto = 0;
    _estado = 0;
}

///GETTER:
int VentaDetalle::getNumeroFactura(){
    return _numeroFactura;
}

int VentaDetalle::getIdProducto(){
    return _idProducto;
}

float VentaDetalle::getPrecioProducto(){
    return _precioProducto;
}

int VentaDetalle::getCantidadProducto(){
    return _cantidadProducto;
}

float VentaDetalle::getTotalPorProducto(){
    return _totalPorProducto;
}

bool VentaDetalle::getEstado(){
    return _estado;
}


///SETTER
void VentaDetalle::setNumeroFactura(int numeroFactura){
    _numeroFactura = numeroFactura;
}

void VentaDetalle::setIdProducto(int idProducto){
    _idProducto = idProducto;
}

void VentaDetalle::setPrecioProducto(float precioProducto){
    _precioProducto = precioProducto;
}

void VentaDetalle::setCantidadProducto(int cantidadProducto){
    _cantidadProducto = cantidadProducto;
}

void VentaDetalle::setTotalPorProducto(float totalPorProducto){
    _totalPorProducto = totalPorProducto;
}

void VentaDetalle::setEstado(bool estado){
    _estado = estado;
}

void VentaDetalle::Cargar(){
    ArchivoProductos archivoProductos;
    Producto registroProducto;
    int posicion;
    bool seguirIntentando;

    ///Usamos _idProducto para asignar el precio de un producto cargado previamente en ArchivoPrdoductos
    cout << "Ingrese el ID del producto: ";
    cin >> _idProducto;
    while(true){
        posicion = archivoProductos.BuscarRegistro(_idProducto, ACTIVOS);
        if(posicion == -1){
            if (cin.fail() || _idProducto < 1) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un numero valido." << endl << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            } else {
                cout << endl << "NO EXISTE UN PRODUCTO CON ESTE ID" << endl << endl;
            }
            cout << "Desea seguir intentando o cancelar carga? 1-Seguir 0-Cancelar: ";
            cin >> seguirIntentando;
            if (!seguirIntentando){
                cin.clear();
                cin.ignore();
                _idProducto = -1;
                return;
            }
        } else if(posicion == -2){
            cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTO" << endl;
            _idProducto = -1;
            return;
        } else {
            registroProducto = archivoProductos.LeerRegistro(posicion);
            _precioProducto = registroProducto.getPrecioProducto();
            break;
        }

        system("cls");
        cout << "Ingrese nuevamente un ID de producto: ";
        cin >> _idProducto;
    }

    ///Ingresamos cantidad
    cout << "Ingrese La Cantidad Del Producto: ";
    cin >> _cantidadProducto;
    if(_cantidadProducto > registroProducto.getStockProducto()){
        cout << endl << "STOCK INSUFICIENTE" << endl;
        cout << "STOCK ACTUAL: " << registroProducto.getStockProducto() << endl;
        _idProducto = -1;
        return;
    }

    ///Calculamos el total con el precio y cantidad previamente asignados
    _totalPorProducto = _precioProducto * _cantidadProducto;

    _estado = true;
}

void VentaDetalle::Mostrar(bool encabezado){
    if (encabezado){
        cout << left << setfill(' ') << setw(20) << "Numero de factura" << setw(14) << "Id producto" << setw(21) << "Precio de producto" << setw(24) << "Cantidad de productos" << setw(21) << "Total por producto" << setw(10) << "Estado" << endl;
    }

    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;

    cout << fixed << setprecision(2) << setw(1) << "" << setw(19) << _numeroFactura << setw(1) << "" << setw(13) << _idProducto << setw(3) << " $" << setw(18) << _precioProducto << setw(1) << "" << setw(23) << _cantidadProducto << setw(3) << " $" << setw(18) << _totalPorProducto;
    if (_estado) {
        cout << setw(10) << "Activo" << endl;
    } else {
        cout << setw(10) << "Desactivo" << endl;
    }
}

void VentaDetalle::operator+=(int cantidadProducto){
    _cantidadProducto += cantidadProducto;
}

void VentaDetalle::operator-=(int cantidadProducto){
    _cantidadProducto -= cantidadProducto;
    if(_cantidadProducto < 0){
        _cantidadProducto = 0;
    }
}
