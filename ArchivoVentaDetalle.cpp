#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
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
ArchivoVentaDetalle::ArchivoVentaDetalle(const char *nombreArchivo){
    int tam = strlen(nombreArchivo) + 1;
    _nombreArchivo = new char[tam];
    if(_nombreArchivo == nullptr){
        exit(1);
    }
    strcpy(_nombreArchivo, nombreArchivo);
    _tamanioRegistro = sizeof(VentaDetalle);
}

char* ArchivoVentaDetalle::getNombreArchivo(){
    return _nombreArchivo;
}

int ArchivoVentaDetalle::getTamanioRegistro(){
    return _tamanioRegistro;
}

bool ArchivoVentaDetalle::CrearDeCero(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

int ArchivoVentaDetalle::BuscarRegistro(int numeroFactura, bool activosOtodos){
    FILE *pArchivo;
    VentaDetalle registro;
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

int ArchivoVentaDetalle::BuscarRegistro(int numeroFactura, int idProducto, bool activosOtodos){
    FILE *pArchivo;
    VentaDetalle registro;
    int posicion = 0;
    pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -2;
    }
    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getNumeroFactura() == numeroFactura && registro.getIdProducto() == idProducto && registro.getEstado()){
                fclose(pArchivo);
                cout << endl;
                return posicion;
            }
            posicion++;
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getNumeroFactura() == numeroFactura && registro.getIdProducto() == idProducto){
                fclose(pArchivo);
                cout << endl;
                return posicion;
            }
            posicion++;
        }
    }
    fclose(pArchivo);
    return -1;
}

VentaDetalle ArchivoVentaDetalle::LeerRegistro(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO VENTA DETALLE" << endl;
        return VentaDetalle();
    }
    VentaDetalle registro;
    fseek(pArchivo, _tamanioRegistro * posicion, SEEK_SET);
    fread(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return registro;
}

void ArchivoVentaDetalle::LeerArchivo(int cantidadRegistros, VentaDetalle *vector){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO VENTA DETALLE" << endl;
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], _tamanioRegistro, 1, pArchivo);
    }
    fclose(pArchivo);
}

bool ArchivoVentaDetalle::ListarRegistros(bool activosOtodos){
    VentaDetalle registro;
    bool encabezado = true;
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO VENTA DETALLE" << endl;
        return 0;
    }

    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getEstado()){
                registro.Mostrar(encabezado);
                encabezado = false;
            }
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            registro.Mostrar(encabezado);
            encabezado = false;
        }
    }

    fclose(pArchivo);
    return true;
}

int ArchivoVentaDetalle::ContarRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(VentaDetalle);
    fclose(pArchivo);
    return cantidadRegistros;
}

bool ArchivoVentaDetalle::GrabarRegistro(VentaDetalle registro){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;

}

bool ArchivoVentaDetalle::EditarRegistro(VentaDetalle registro, int posicion){
    FILE *pArchivo;
    pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO VENTA DETALLE" << endl << endl;
        return false;
    }
    fseek(pArchivo, posicion * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

VentaDetalle ArchivoVentaDetalle::MenuModificarRegistro(VentaDetalle registro){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoProductos archivoProductos;
    int opcion, cantidadProducto, posicion, cantidadProductoAnterior, diferenciaCantidadEntreNuevaAnterior;
    float precioProducto, totalPorProducto, totalPorProductoNuevo, totalPorProductoAnterior, diferenciaTotalEntreNuevaAnterior;
    VentaCabecera registroCabecera;
    Producto registroProducto;

    cout << "Que desea Modificar?" << endl << endl;
    cout << "1- Aumetar cantidad del producto" << endl;
    cout << "2- Disminuir cantidad del producto" << endl;
    cout << "3- Modificar cantidad del producto" << endl;
    cout << "4- Modificar precio del producto." << endl;
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
            cout << "Ingrese la cantidad que desea aumetar: ";
            cin >> cantidadProducto;
            if (cin.fail() || cantidadProducto < 1) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroFactura(-1);
                break;
            }
            registro += cantidadProducto;

            ///VERIFICACION DE SI EL STOCK ALCANZA
            posicion = archivoProductos.BuscarRegistro(registro.getIdProducto(), ACTIVOS);
            registroProducto = archivoProductos.LeerRegistro(posicion);
            if(cantidadProducto > registroProducto.getStockProducto()){
                cout << endl << "STOCK INSUFICIENTE" << endl;
                cout << "STOCK ACTUAL: " << registroProducto.getStockProducto() << endl;
                registro.setNumeroFactura(-1);
                break;
            }

            totalPorProducto = registro.getPrecioProducto() * registro.getCantidadProducto();
            registro.setTotalPorProducto(totalPorProducto);

            posicion = archivoVentaCabecera.BuscarRegistro(registro.getNumeroFactura(), TODOS);
            registroCabecera = archivoVentaCabecera.LeerRegistro(posicion);
            registroCabecera += cantidadProducto * registro.getPrecioProducto();
            if(archivoVentaCabecera.EditarRegistro(registroCabecera, posicion)){
                cout << endl << "SE ACTUALIZO EL TOTAL DE LA FACTURA (CABECERA)" << endl;
            } else {
                cout << endl << "ERROR AL ACTUALIZAR EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                registro.setNumeroFactura(-1);
                break;
            }

            ///ACTUALIZACION DE STOCK
            registroProducto -= cantidadProducto;
            if(archivoProductos.EditarRegistro(registroProducto, posicion)){
                cout << "STOCK DEL PRODUCTO ACTUALIZADO" << endl;
                break;
            } else {
                cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO" << endl;
                registro.setNumeroFactura(-1);
                break;
            }
        case 2:
            system("cls");
            cout << "Ingrese la cantidad que desea disminuir: ";
            cin >> cantidadProducto;
            if (cin.fail() || cantidadProducto < 1) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroFactura(-1);
                break;
            }
            cantidadProductoAnterior = registro.getCantidadProducto();
            registro -= cantidadProducto;
            totalPorProducto = registro.getPrecioProducto() * registro.getCantidadProducto();
            registro.setTotalPorProducto(totalPorProducto);

            if (registro.getEstado()){
                posicion = archivoVentaCabecera.BuscarRegistro(registro.getNumeroFactura(), TODOS);
                registroCabecera = archivoVentaCabecera.LeerRegistro(posicion);
                if(registro.getCantidadProducto() == 0){
                    registroCabecera -= cantidadProductoAnterior * registro.getPrecioProducto();
                } else  {
                    registroCabecera -= cantidadProducto * registro.getPrecioProducto();
                }
                if(archivoVentaCabecera.EditarRegistro(registroCabecera, posicion)){
                    cout << endl << "SE ACTUALIZO EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                } else {
                    cout << endl << "ERROR AL ACTUALIZAR EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                    registro.setNumeroFactura(-1);
                    break;
                }
            }

            ///ACTUALIZACION DE STOCK
            posicion = archivoProductos.BuscarRegistro(registro.getIdProducto(), ACTIVOS);
            registroProducto = archivoProductos.LeerRegistro(posicion);
            registroProducto += cantidadProducto;
            if(archivoProductos.EditarRegistro(registroProducto, posicion)){
                cout << "STOCK DEL PRODUCTO ACTUALIZADO" << endl;
                break;
            } else {
                cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO" << endl;
                registro.setNumeroFactura(-1);
                break;
            }
        case 3:
            system("cls");
            cout << "Ingrese la nueva cantidad total: ";
            cin >> cantidadProducto;
            if (cin.fail() || cantidadProducto < 1) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroFactura(-1);
                break;
            }
            cantidadProductoAnterior = registro.getCantidadProducto();
            registro.setCantidadProducto(cantidadProducto);
            totalPorProductoAnterior = registro.getTotalPorProducto();
            totalPorProductoNuevo = registro.getPrecioProducto() * cantidadProducto;
            registro.setTotalPorProducto(totalPorProductoNuevo);
            if (totalPorProductoAnterior > totalPorProductoNuevo) {
                diferenciaTotalEntreNuevaAnterior = totalPorProductoAnterior - totalPorProductoNuevo;
            } else {
                diferenciaTotalEntreNuevaAnterior = totalPorProductoNuevo - totalPorProductoAnterior;
                ///VERIFICACION DE SI EL STOCK ALCANZA
                posicion = archivoProductos.BuscarRegistro(registro.getIdProducto(), ACTIVOS);
                registroProducto = archivoProductos.LeerRegistro(posicion);
                if(cantidadProducto > registroProducto.getStockProducto()){
                    cout << endl << "STOCK INSUFICIENTE, PARA ACTUALIZAR LA CANTIDAD SE NECESITAN AGREGAR " << cantidadProducto - cantidadProductoAnterior << " PRODUCTOS" << endl;
                    cout << "STOCK ACTUAL: " << registroProducto.getStockProducto() << endl;
                    registro.setNumeroFactura(-1);
                    break;
                }
            }

            if (registro.getEstado()){
                posicion = archivoVentaCabecera.BuscarRegistro(registro.getNumeroFactura(), TODOS);
                registroCabecera = archivoVentaCabecera.LeerRegistro(posicion);
                if(totalPorProductoAnterior > totalPorProductoNuevo) {
                    registroCabecera -= diferenciaTotalEntreNuevaAnterior;
                } else {
                    registroCabecera += diferenciaTotalEntreNuevaAnterior;
                }
                if(archivoVentaCabecera.EditarRegistro(registroCabecera, posicion)){
                    cout << endl << "SE ACTUALIZO EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                } else {
                    cout << endl << "ERROR AL ACTUALIZAR EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                    registro.setNumeroFactura(-1);
                    break;
                }
            }

            ///ACTUALIZACION DE STOCK
            if (cantidadProductoAnterior > cantidadProducto) {
                diferenciaCantidadEntreNuevaAnterior = cantidadProductoAnterior - cantidadProducto;
                registroProducto += diferenciaCantidadEntreNuevaAnterior;
            } else {
                diferenciaCantidadEntreNuevaAnterior = cantidadProducto - cantidadProductoAnterior;
                registroProducto -= diferenciaCantidadEntreNuevaAnterior;
            }
            if(archivoProductos.EditarRegistro(registroProducto, posicion)){
                cout << "STOCK DEL PRODUCTO ACTUALIZADO" << endl;
                break;
            } else {
                cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO" << endl;
                registro.setNumeroFactura(-1);
                break;
            }
        case 4:
            system("cls");
            cout << "Ingrese el nuevo precio del producto: ";
            cin >> precioProducto;
            if (cin.fail() || precioProducto < 0) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroFactura(-1);
                break;
            }
            registro.setPrecioProducto(precioProducto);

            totalPorProductoAnterior = registro.getTotalPorProducto();
            totalPorProductoNuevo = precioProducto * registro.getCantidadProducto();
            registro.setTotalPorProducto(totalPorProductoNuevo);
            if (totalPorProductoAnterior > totalPorProductoNuevo) {
                diferenciaTotalEntreNuevaAnterior = totalPorProductoAnterior - totalPorProductoNuevo;
            } else {
                diferenciaTotalEntreNuevaAnterior = totalPorProductoNuevo - totalPorProductoAnterior;
            }

            if (registro.getEstado()){
                posicion = archivoVentaCabecera.BuscarRegistro(registro.getNumeroFactura(), TODOS);
                registroCabecera = archivoVentaCabecera.LeerRegistro(posicion);
                if(totalPorProductoAnterior > totalPorProductoNuevo) {
                    registroCabecera -= diferenciaTotalEntreNuevaAnterior;
                } else {
                    registroCabecera += diferenciaTotalEntreNuevaAnterior;
                }
                if(archivoVentaCabecera.EditarRegistro(registroCabecera, posicion)){
                    cout << endl << "SE ACTUALIZO EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                    break;
                } else {
                    cout << endl << "NO SE PUDO ACTUALIZAR EL TOTAL DE LA FACTURA (CABECERA)" << endl;
                    registro.setNumeroFactura(-1);
                    break;
                }
            }
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

bool ArchivoVentaDetalle::ModificarRegistro(){
    ArchivoVentaCabecera archivoVentaCabecera;
    VentaDetalle registro;
    int numeroFactura, idProducto, cantidadRegistros, posicion;

    cout << "NUMERO DE FACTURA QUE DESEA MODIFICAR: ";
    cin >> numeroFactura;
    posicion = archivoVentaCabecera.BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroFactura < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE NINGUNA VENTA REGISTRADO CON ESTE NUMERO DE FACTURA" << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTA (DETALLE)" << endl;
        return false;
    }

    cout << endl << "DETALLE ACTUAL" << endl;
    cout << setfill((char) 249) << setw(14) << (char) 249 << setfill(' ') << endl;
    cantidadRegistros = ContarRegistros();
    bool encabezado = true;
    for(int i = 0; i < cantidadRegistros; i++){
        registro = LeerRegistro(i);
        if(registro.getNumeroFactura() == numeroFactura && registro.getEstado()){
            registro.Mostrar(encabezado);
            encabezado = false;
        }
    }

    cout << endl << "INGRESE ID DEL PRODUCTO PARA VERIFICAR SI PUEDE MODIFICARLO: ";
    cin >> idProducto;
    posicion = BuscarRegistro(numeroFactura, idProducto, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || idProducto < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE NUNGUN PRODUCTO EN ESTE DETALLE DE FACTURA CON ESTE ID" << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTA (DETALLE)" << endl;
        return false;
    }

    registro = LeerRegistro(posicion);
    registro = MenuModificarRegistro(registro);

    if(registro.getNumeroFactura() == -1){
        return true;
    }

    if(EditarRegistro(registro, posicion)){
        return true;
    } else {
        return false;
    }
}

bool ArchivoVentaDetalle::AltaRegistro(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoProductos archivoProductos;
    Producto registroProducto;
    VentaDetalle registroDetalle;
    VentaCabecera registroCabecera;
    int numeroFactura, idProducto, cantidadRegistros, posicion;

    cout << "INGRESE EL NUMERO DE FACTUTA AL QUE DESEA AGREGAR UN PRODUCTO" << endl << endl;
    cout << "NUMERO DE FACTURA: ";
    cin >> numeroFactura;

    ///Verificacion existencia de numero de factura
    posicion = archivoVentaCabecera.BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroFactura < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE NINGUN FACTURA CON ESTA NUMERO" << endl;
            return false;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTAS" << endl;
        return false;
    }
    cout << endl;

    ///Mostramos detalle de factura
    cout << "DETALLE ACTUAL" << endl;
    cout << setfill((char) 249) << setw(14) << (char) 249 << setfill(' ') << endl;
    cantidadRegistros = ContarRegistros();
    bool encabezado = true;
    for(int i = 0; i < cantidadRegistros; i++){
        registroDetalle = LeerRegistro(i);
        if(registroDetalle.getNumeroFactura() == numeroFactura && registroDetalle.getEstado()){
            registroDetalle.Mostrar(encabezado);
            encabezado = false;
        }
    }

    ///VERIFICACION DE SI YA HAY UN PRODUCTO CON ESTE ID EN EL DETALLE
    cout << endl << "INGRESE ID DEL PRODUCTO PARA VERIFICAR SI PUEDE DARLO DE ALTA: ";
    cin >> idProducto;
    if (cin.fail() || idProducto < 1) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return false;
    }

    posicion = BuscarRegistro(numeroFactura, idProducto, ACTIVOS);
    if(posicion >= 0){
        cout << "NO PUEDE DAR DE ALTA UN PRODUCTO CON UN ID EXISTENTE EN EL DETALLE" << endl;
        return false;
    } else if(posicion == -2){
        cout << "ERROR AL ABRIR EL ARCHIVO DETALLES DE VENTAS" << endl;
        return false;
    }

    ///VERIFICACION DE SI EXISTE UN PRODUCTO CON ESTE ID EN EL INVENTARIO
    posicion = archivoProductos.BuscarRegistro(idProducto, ACTIVOS);
    if(posicion == -1){
        cout << endl << "NO PUEDE DAR DE ALTA UN PRODUCTO CON ID INEXISTENTE" << endl;
        return false;
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTO"<< endl;
        return false;
    }

    cout << endl << "PUEDE DAR DE ALTA EL PRODUCTO EN EL DETALLE" << endl << endl;
    system("pause");
    system("cls");
    cout << "Para Continuar Con El Alta, Nuevamente ";
    registroDetalle.Cargar();
    if(registroDetalle.getIdProducto() == -1){
        return true;
    }
    registroDetalle.setNumeroFactura(numeroFactura);

    ///Actualizacion del stock del producto en el inventario
    posicion = archivoProductos.BuscarRegistro(registroDetalle.getIdProducto(), ACTIVOS);
    registroProducto = archivoProductos.LeerRegistro(posicion);
    registroProducto -= registroDetalle.getCantidadProducto();
    if(GrabarRegistro(registroDetalle)){
        cout << endl << "ALTA EXITOSA";
        if(!archivoProductos.EditarRegistro(registroProducto, posicion)){
            cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO" << endl;
            return false;
        }
    } else {
        cout << endl << "ERROR AL REGISTRAR EL ALTA DEL PRODUCTO EN EL DETALLE" << endl;
        return false;
    }


    ///Actualizacion del total de la factura
    posicion = archivoVentaCabecera.BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        cout << endl << "NO EXISTE UNA VENTA REGISTRADO CON ESTE NUMERO DE FACTURA" << endl  << endl;
        return false;
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (DETALLE)" << endl << endl;
        return false;
    }
    registroCabecera = archivoVentaCabecera.LeerRegistro(posicion);
    registroCabecera += registroDetalle.getTotalPorProducto();
    if(archivoVentaCabecera.EditarRegistro(registroCabecera, posicion)){
        cout << ", SE ACTUALIZO EL TOTAL DE LA FACTURA" << endl;
        return true;
    } else {
        cout << "ERROR AL ACTUALIZAR EL TOTAL DE LA FACTURA" << endl;
        return false;
    }
}

bool ArchivoVentaDetalle::BajaRegistro(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoProductos archivoProductos;
    VentaDetalle registroDetalle;
    VentaCabecera registroCabecera;
    Producto registroProducto;

    int numeroFactura, idProducto;
    cout << "INGRESE EL NUMERO DE FACTUTA DONDE DESEA DAR DE BAJA UN PRODUCTO" << endl << endl;
    cout << "NUMERO DE FACTURA: ";
    cin >> numeroFactura;

    ///VERIFICACION DE SI EXISTE UNA FACTURA CON EL NUMERO OTORGADO
    int posicion = archivoVentaCabecera.BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroFactura < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE NINGUNA VENTA REGISTRADA CON ESTE NUMERO DE FACTURA" << endl  << endl;
            return false;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO VENTAS CABECERA" << endl << endl;
        return false;
    }

    ///VERIFICACION DE SI EXISTEN PRODUCTOS DE EL DETALLE DE FACTURA CON EL NUMERO OTORGADO
    posicion = BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        cout << endl << "NO EXISTE NINGUN PRODUCTO EN EL DETALLE DE ESTA FACTURA" << endl << endl;
        return false;
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DETALLES DE VENTAS" << endl << endl;
        return false;
    }

    cout << endl << "DETALLE ACTUAL" << endl;
    cout << setfill((char) 249) << setw(14) << (char) 249 << setfill(' ') << endl;
    int cantidadRegistros = ContarRegistros();
    bool encabezado = true;
    for(int i = 0; i < cantidadRegistros; i++){
        registroDetalle = LeerRegistro(i);
        if(registroDetalle.getNumeroFactura() == numeroFactura && registroDetalle.getEstado()){
            registroDetalle.Mostrar(encabezado);
            encabezado = false;
        }
    }

    cout << endl << "INGRESE ID DEL PRODUCTO QUE DESEA DAR DE BAJA: ";
    cin >> idProducto;

    ///VERIFICACION DE ID
    posicion = BuscarRegistro(numeroFactura, idProducto, ACTIVOS);
    if(posicion == -1){
         if (cin.fail() || idProducto < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE NINGUN PRODUCTO CON ESTE ID EN EL DETALLE DE FACTURA" << endl << endl;
            return false;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DETALLES DE VENTAS" << endl << endl;
        return false;
    }

    ///BAJA DE REGISTRO EN EL DETALLE
    registroDetalle = LeerRegistro(posicion);
    registroDetalle.setEstado(false);
    if(EditarRegistro(registroDetalle, posicion)){
        cout << "BAJA DEL PRODUCTO EN DETALLE DE VENTA EXITOSA" << endl;
        ///ACTUALIZACION DEL TOTAL DE LA FACTURA
        posicion = archivoVentaCabecera.BuscarRegistro(numeroFactura, ACTIVOS);
        registroCabecera = archivoVentaCabecera.LeerRegistro(posicion);
        if(registroCabecera.getEstado()){
            registroCabecera -= registroDetalle.getTotalPorProducto();
            if(archivoVentaCabecera.EditarRegistro(registroCabecera, posicion)){
                cout << "SE ACTUALIZO EL TOTAL VENTA CABECERA" << endl << endl;
            } else {
                cout << "ERROR AL ACTUALIZAR EL TOTAL VENTA CABECERA" << endl << endl;
                return false;
            }
        }
        ///ACTUALIZACION DE STOCK DEL INVENTARIO
        posicion = archivoProductos.BuscarRegistro(registroDetalle.getIdProducto(), ACTIVOS);
        registroProducto = archivoProductos.LeerRegistro(posicion);
        registroProducto += registroDetalle.getCantidadProducto();
        if(!archivoProductos.EditarRegistro(registroProducto, posicion)){
            cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO CON ID: " << registroDetalle.getIdProducto() << endl << endl;
            system("pause");
            return false;
        }
    } else {
        cout << "ERROR AL DAR DE BAJA EL PRODUCTO EN DETALLE DE VENTA" << endl;
        return false;
    }

    return true;
}

ArchivoVentaDetalle::~ArchivoVentaDetalle(){
    delete []_nombreArchivo;
}
