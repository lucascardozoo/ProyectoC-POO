#include <iostream>
#include <cstring>
#include <ctime>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Producto.h"
#include "VentaCabecera.h"
#include "VentaDetalle.h"
#include "constantes.h"
#include "ArchivoProductos.h"
#include "ArchivoVentaDetalle.h"
#include "ArchivoVentaCabecera.h"

using namespace std;

///Asigna el nombre y el tamaño del vector
ArchivoVentaCabecera::ArchivoVentaCabecera(const char *nombreArchivo){
    int tam = strlen(nombreArchivo) + 1;
    _nombreArchivo = new char[tam];
    if(_nombreArchivo == nullptr){
        exit(1);
    }
    strcpy(_nombreArchivo, nombreArchivo);
    _tamanioRegistro = sizeof(VentaCabecera);
}

char* ArchivoVentaCabecera::getNombreArchivo(){
    return _nombreArchivo;
}

int ArchivoVentaCabecera::getTamanioRegistro(){
    return _tamanioRegistro;
}

bool ArchivoVentaCabecera::CrearDeCero(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

int ArchivoVentaCabecera::BuscarRegistro(int numeroFactura, bool activosOtodos){
    FILE *pArchivo;
    VentaCabecera registro;
    int posicion = 0;
    pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -2;
    }
    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getNumeroFactura() == numeroFactura && registro.getEstado()){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getNumeroFactura() == numeroFactura){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    }
    fclose(pArchivo);
    return -1;
}

VentaCabecera ArchivoVentaCabecera::LeerRegistro(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO VENTA CABECERA" << endl;
        return VentaCabecera();
    }
    VentaCabecera registro;
    fseek(pArchivo, _tamanioRegistro * posicion, SEEK_SET);
    fread(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return registro;
}

void ArchivoVentaCabecera::LeerArchivo(int cantidadRegistros, VentaCabecera *vector){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO VENTA CABECERA" << endl;
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], _tamanioRegistro, 1, pArchivo);
    }
    fclose(pArchivo);
}

bool ArchivoVentaCabecera::ListarRegistros(bool activosOtodos){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    VentaCabecera registro;
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO VENTA CABECERA" << endl;
        return 0;
    }

    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getEstado()){
                registro.Mostrar();
                cout << endl;
            }
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            registro.Mostrar();
            cout << endl;
        }
    }

    fclose(pArchivo);
    return true;
}

int ArchivoVentaCabecera::ContarRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(VentaCabecera);
    fclose(pArchivo);
    return cantidadRegistros;
}

bool ArchivoVentaCabecera::GrabarRegistro(VentaCabecera registro){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoVentaCabecera::EditarRegistro(VentaCabecera registro, int posicion){
    FILE *pArchivo;
    pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO VENTA CABECERA" << endl << endl;
        return false;
    }
    fseek(pArchivo, posicion * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

VentaCabecera ArchivoVentaCabecera::MenuModificarRegistro(VentaCabecera registro){
    Fecha fechaVenta;
    float totalVenta;
    int opcion, anioActual, mesActual, diaActual, anioVenta, mesVenta, diaVenta;

    ///OBTENGO FECHA ACTUAL
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActual = fechaActual.tm_year + 1900;
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    cout << endl << "Que desea modificar?" << endl << endl;
    cout << "1- Modificar fecha de venta." << endl;
    cout << "2- Modificar total de la venta." << endl;
    cout << "0- Salir." << endl;

    cout << endl << "OPCION: ";
    cin >> opcion;
    ///Verificar si la entrada es valida
    if (cin.fail()) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        registro.setNumeroFactura(-1);
        return registro;
    }

    switch(opcion){
        case 1:
            system("cls");
            cout << "Ingrese nueva fecha de venta (DD/MM/AAAA): " << endl << endl;
            fechaVenta.Cargar();
            if(fechaVenta.getAnio() == -1){
                registro.setNumeroFactura(-1);
                break;
            }

            ///Verificamos fecha que no sea mayor a la actual
            anioVenta = fechaVenta.getAnio();
            mesVenta = fechaVenta.getMes();
            diaVenta = fechaVenta.getDia();
            if (anioVenta > anioActual || (anioVenta == anioActual && mesVenta > mesActual) || (anioVenta == anioActual && mesVenta == mesActual && diaVenta > diaActual)) {
                cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl;
                registro.setNumeroFactura(-1);
                break;
            }

            registro.setFechaVenta(fechaVenta);
            break;
        case 2:
            system("cls");
            cout << "Ingrese nuevo total de la venta: ";
            cin >> totalVenta;
            if (cin.fail() || totalVenta < 0) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroFactura(-1);
                break;
            }
            registro.setTotalVenta(totalVenta);
            break;
        case 0:
            registro.setNumeroFactura(-1);
            break;
        default:
            cout << endl << "Opcion no valida." << endl;
            registro.setNumeroFactura(-1);
            break;
    }

    return registro;
}

bool ArchivoVentaCabecera::ModificarRegistro(){
    VentaCabecera registro;
    int numeroFactura, posicion;

    cout << "INGRESAR NUMERO DE FACTURA: ";
    cin >> numeroFactura;
    posicion = BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroFactura < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NUMERO DE FACTURA INEXISTENTE" << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTA CABECERA" << endl;
        return false;
    }
    registro = LeerRegistro(posicion);

    registro = MenuModificarRegistro(registro);

    if(registro.getNumeroFactura() == -1){
        return true;
    }

    if(EditarRegistro(registro, posicion)){
        cout << endl << "MODIFICACION DE FACTURA EXITOSA"  << endl;
        return true;
    } else {
        return false;
    }
}

bool ArchivoVentaCabecera::AltaRegistro(){
    VentaCabecera registro;
    int numeroFactura;
    cout << "INGRESAR NUMERO DE FACTURA A DAR DE ALTA: ";
    cin >> numeroFactura;
    int posicion = BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion >= 0){
        cout << "NO PODES DAR DE ALTA UNA FACTURA CON NUMERO DE FACTURA EXISTENTE" << endl;
        return false;
    } else if (posicion == -2){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS CABECERA" << endl;
        return false;
    }

    registro.Cargar();
    if(GrabarRegistro(registro)){
        cout << endl << "ALTA DE VENTA CABECERA EXITOSA" << endl;
        return true;
    } else {
        cout << endl << "ERROR AL DAR ALTA LA VENTA CABECERA" << endl;
        return false;
    }
}

bool ArchivoVentaCabecera::BajaRegistro(){
    ArchivoVentaDetalle archivoVentaDetalle;
    ArchivoProductos archivoProductos;
    VentaDetalle registroVentaDetalle;
    VentaCabecera registroVentaCabecera;
    Producto registroProducto;

    int numeroFactura;
    cout << "INGRESAR NUMERO DE FACTURA A DAR DE BAJA: ";
    cin >> numeroFactura;
    int posicion = BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroFactura < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE UNA VENTA REGISTRADO CON ESTE NUMERO DE FACTURA" << endl << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return false;
    }

    registroVentaCabecera = LeerRegistro(posicion);
    registroVentaCabecera.setEstado(false);
    if(EditarRegistro(registroVentaCabecera, posicion)){
        cout << endl << "BAJA DE VENTA EXITOSA" << endl << endl;
        ///ACTUALIZACION DE STOCK DEL INVENTARIO
        int cantidadRegistros = archivoVentaDetalle.ContarRegistros();
        for(int i = 0; i < cantidadRegistros; i++){
            registroVentaDetalle = archivoVentaDetalle.LeerRegistro(i);
            if(registroVentaDetalle.getNumeroFactura() == numeroFactura && registroVentaDetalle.getEstado()){
                int posicion = archivoProductos.BuscarRegistro(registroVentaDetalle.getIdProducto(), ACTIVOS);
                registroProducto = archivoProductos.LeerRegistro(posicion);
                registroProducto += registroVentaDetalle.getCantidadProducto();
                if(!archivoProductos.EditarRegistro(registroProducto, posicion)){
                    cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO CON ID: " << registroVentaDetalle.getIdProducto() << endl << endl;
                    system("pause");
                    return false;
                }
            }
        }
    } else {
        cout << endl << "ERROR NO AL DAR DE BAJA LA VENTA" << endl << endl;
        return false;
    }
    return true;
}

ArchivoVentaCabecera::~ArchivoVentaCabecera(){
    delete []_nombreArchivo;
}
