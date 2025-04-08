#include <iostream>
#include <iomanip>
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
#include "funcionesVentas.h"

using namespace std;

///FUNCIONES GENERALES PARA VENTAS
void nuevaVenta(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    ArchivoProductos archivoProductos;
    VentaCabecera ventaCabecera;
    VentaDetalle ventaDetalle;
    Producto registroProducto;
    int numeroFactura, posicion;
    bool seguirCargando = true;

    ventaCabecera.Cargar();
    if(ventaCabecera.getNumeroFactura() == -1){
        return;
    }
    numeroFactura = ventaCabecera.getNumeroFactura();

    while(seguirCargando){
        ventaDetalle.setNumeroFactura(numeroFactura);
        ventaDetalle.Cargar();
        if(ventaDetalle.getIdProducto() == -1){
            return;
        }

        posicion = archivoVentaDetalle.BuscarRegistro(numeroFactura, ventaDetalle.getIdProducto(), ACTIVOS);
        if(posicion >= 0){
            cout << "ESTE PRODUCTO YA EXISTE EN EL DETALLE" << endl << endl;
            system("pause");

            system("cls");
            cout << "¿Desea cargando otro producto en el detalle? (1-SI 0-NO): ";
            cin >> seguirCargando;
            ///Verificar si la entrada es valida
            while (cin.fail() || (seguirCargando != 1 && seguirCargando != 0)) {
                cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
                system("pause");
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos

                system("cls");
                cout << "¿Desea cargando otro producto en el detalle? (1-SI 0-NO): ";
                cin >> seguirCargando;
            }
        } else {
            ventaCabecera += ventaDetalle.getTotalPorProducto();

            ///REGISTRO Y ACTUALIZACION DE STOCK DEL INVENTARIO
            posicion = archivoProductos.BuscarRegistro(ventaDetalle.getIdProducto(), ACTIVOS);
            registroProducto = archivoProductos.LeerRegistro(posicion);
            registroProducto -= ventaDetalle.getCantidadProducto();
            if(archivoVentaDetalle.GrabarRegistro(ventaDetalle)){
                cout << endl << "PRODUCTO AGREGADO EXITOSAMENTE EN EL DETALLE DE VENTA" << endl << endl;
                system("pause");
                if(!archivoProductos.EditarRegistro(registroProducto, posicion)){
                    cout << "ERROR AL ACTUALIZAR EL STOCK DEL PRODUCTO" << endl << endl;
                    system("pause");
                    return;
                }
            } else {
                cout << endl << "ERROR AL AGREGAR EL PRODUCTO EN EL DETALLE DE VENTA" << endl << endl;
                system("pause");
            }

            system("cls");
            cout << "¿Desea cargando otro producto en el detalle? (1-SI 0-NO): ";
            cin >> seguirCargando;
            while (cin.fail() || (seguirCargando != 1 && seguirCargando != 0)) {
                cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
                system("pause");
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos

                system("cls");
                cout << "¿Desea cargando otro producto en el detalle? (1-SI 0-NO): ";
                cin >> seguirCargando;
            }
        }
        cout << endl;
    }

    if(archivoVentaCabecera.GrabarRegistro(ventaCabecera)){
        cout << "VENTA REGISTRADA EXITOSAMENTE" << endl;
        return;
    } else {
        cout << "ERROR AL REGISTRAR LA VENTA" << endl;
        return;
    }
}

void agregarProductoAlDetalle(){
    ArchivoVentaDetalle archivoVentaDetalle;
    archivoVentaDetalle.AltaRegistro();
}

void darBajaVenta(){
    ArchivoVentaCabecera ArchivoVentaCabecera;
    ArchivoVentaCabecera.BajaRegistro();
}

void darBajaProductoDeVenta(){
    ArchivoVentaDetalle ArchivoVentaDetalle;
    ArchivoVentaDetalle.BajaRegistro();
}

void modificarCabecera(){
    ArchivoVentaCabecera archivoVentaCabecera;
    archivoVentaCabecera.ModificarRegistro();
}

void modificarDetalle(){
    ArchivoVentaDetalle archivoVentaDetalle;
    archivoVentaDetalle.ModificarRegistro();
}


///LISTADO VENTAS:
void listarSinOrdenamientoVentas(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabecera;
    VentaDetalle ventaDetalle;

    int cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    } else {
        cout << "LISTADO DE VENTAS REGISTRADAS SIN ORDENAMIENTO" << endl << endl;
    }
    for(int i = 0; i < cantidadRegistrosVentaCabecera; i++){
        bool encabezado = true;
        ventaCabecera = archivoVentaCabecera.LeerRegistro(i);
        if (ventaCabecera.getEstado()){
            ventaCabecera.Mostrar();
            int cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
            for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                if(ventaDetalle.getNumeroFactura() == i + 1 && ventaDetalle.getEstado()){
                    ventaDetalle.Mostrar(encabezado);
                    encabezado = false;
                }
            }
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}

void listarPorNumFacturaAscendente(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabecera;
    VentaDetalle ventaDetalle;

    int cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    } else {
        cout << "LISTADO DE VENTAS REGISTRADAS ASCENDENTEMENTE POR NUMERO DE FACTURA" << endl << endl;
    }
    for(int i = 0; i < cantidadRegistrosVentaCabecera; i++){
        bool encabezado = true;
        ventaCabecera = archivoVentaCabecera.LeerRegistro(i);
        if (ventaCabecera.getEstado()){
            ventaCabecera.Mostrar();
            int cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
            for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                if(ventaDetalle.getNumeroFactura() == i + 1 && ventaDetalle.getEstado()){
                    ventaDetalle.Mostrar(encabezado);
                    encabezado = false;
                }
            }
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}

void listarPorNumFacturaDescendente(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabecera;
    VentaDetalle ventaDetalle;

    int cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    } else {
        cout << "LISTADO DE VENTAS REGISTRADAS DESCENDENTEMENTE POR NUMERO DE FACTURA" << endl << endl;
    }
    for(int i = cantidadRegistrosVentaCabecera - 1; i >= 0; i--){
        bool encabezado = true;
        ventaCabecera = archivoVentaCabecera.LeerRegistro(i);
        if (ventaCabecera.getEstado()){
            ventaCabecera.Mostrar();
            int cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
            for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                if(ventaDetalle.getNumeroFactura() == i + 1 && ventaDetalle.getEstado()){
                    ventaDetalle.Mostrar(encabezado);
                    encabezado = false;
                }
            }
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}

void listarPorFechaDeVentaAscendente(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabeceraAux;
    VentaDetalle ventaDetalle;
    int posMin, cantidadRegistrosVentaCabecera, cantidadRegistrosVentaDetalle;
    bool encabezado;

    ///CREAMOS VECTOR DE ARCHIVO VENTA CABECERA
    cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    }else {
        cout << "LISTADO DE VENTAS REGISTRADAS ASCENDENTEMENTE POR FECHA DE VENTA" << endl << endl;
    }
    VentaCabecera *pVecVentaCabecera = new VentaCabecera[cantidadRegistrosVentaCabecera];
    if (pVecVentaCabecera == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoVentaCabecera.LeerArchivo(cantidadRegistrosVentaCabecera, pVecVentaCabecera);

    ///ORDENAMOS
    for(int i = 0; i < cantidadRegistrosVentaCabecera - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistrosVentaCabecera; j++){
            if (pVecVentaCabecera[j].getFechaVenta().getAnio() < pVecVentaCabecera[posMin].getFechaVenta().getAnio()) {
                posMin = j;
            } else if (pVecVentaCabecera[j].getFechaVenta().getAnio() == pVecVentaCabecera[posMin].getFechaVenta().getAnio()) {
                if (pVecVentaCabecera[j].getFechaVenta().getMes() < pVecVentaCabecera[posMin].getFechaVenta().getMes()) {
                    posMin = j;
                } else if (pVecVentaCabecera[j].getFechaVenta().getMes() == pVecVentaCabecera[posMin].getFechaVenta().getMes()) {
                    if (pVecVentaCabecera[j].getFechaVenta().getDia() < pVecVentaCabecera[posMin].getFechaVenta().getDia()) {
                        posMin = j;
                    }
                }
            }
        }
        ventaCabeceraAux = pVecVentaCabecera[i];
        pVecVentaCabecera[i] = pVecVentaCabecera[posMin];
        pVecVentaCabecera[posMin] = ventaCabeceraAux;
    }

    ///MUESTRAMOS
    for(int i = 0; i < cantidadRegistrosVentaCabecera; i++){
        encabezado = true;
        if (pVecVentaCabecera[i].getEstado()){
            pVecVentaCabecera[i].Mostrar();

            cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
            for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                if(ventaDetalle.getNumeroFactura() == pVecVentaCabecera[i].getNumeroFactura() && ventaDetalle.getEstado()){
                    ventaDetalle.Mostrar(encabezado);
                    encabezado = false;
                }
            }
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}

void listarPorFechaDeVentaDescendente(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabeceraAux;
    VentaDetalle ventaDetalle;
    int posMin, cantidadRegistrosVentaCabecera, cantidadRegistrosVentaDetalle;
    bool encabezado;

    ///CREAMOS VECTOR DE ARCHIVO VENTA CABECERA
    cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    } else {
        cout << "LISTADO DE VENTAS REGISTRADAS DESCENDENTEMENTE POR FECHA DE VENTA" << endl << endl;
    }

    VentaCabecera *pVecVentaCabecera = new VentaCabecera[cantidadRegistrosVentaCabecera];
    if (pVecVentaCabecera == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoVentaCabecera.LeerArchivo(cantidadRegistrosVentaCabecera, pVecVentaCabecera);

    ///ORDENAMOS
    for(int i = 0; i < cantidadRegistrosVentaCabecera - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistrosVentaCabecera; j++){
            if (pVecVentaCabecera[j].getFechaVenta().getAnio() > pVecVentaCabecera[posMin].getFechaVenta().getAnio()) {
                posMin = j;
            } else if (pVecVentaCabecera[j].getFechaVenta().getAnio() == pVecVentaCabecera[posMin].getFechaVenta().getAnio()) {
                if (pVecVentaCabecera[j].getFechaVenta().getMes() > pVecVentaCabecera[posMin].getFechaVenta().getMes()) {
                    posMin = j;
                } else if (pVecVentaCabecera[j].getFechaVenta().getMes() == pVecVentaCabecera[posMin].getFechaVenta().getMes()) {
                    if (pVecVentaCabecera[j].getFechaVenta().getDia() > pVecVentaCabecera[posMin].getFechaVenta().getDia()) {
                        posMin = j;
                    }
                }
            }
        }
        ventaCabeceraAux = pVecVentaCabecera[i];
        pVecVentaCabecera[i] = pVecVentaCabecera[posMin];
        pVecVentaCabecera[posMin] = ventaCabeceraAux;
    }

    ///MUESTRAMOS
    for(int i = 0; i < cantidadRegistrosVentaCabecera; i++){
        encabezado = true;

        if (pVecVentaCabecera[i].getEstado()){
            pVecVentaCabecera[i].Mostrar();

            cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
            for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                if(ventaDetalle.getNumeroFactura() == pVecVentaCabecera[i].getNumeroFactura() && ventaDetalle.getEstado()){
                    ventaDetalle.Mostrar(encabezado);
                    encabezado = false;
                }
            }
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}


///CONSULTAS VENTAS:
void consultaPorNumeroFactura(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabecera;
    VentaDetalle ventaDetalle;
    int numeroFactura, posicion, cantidadRegistrosVentaDetalle;
    bool encabezado;

    cout << "INGRESAR NUMERO DE FACTURA: ";
    cin >> numeroFactura;

    posicion = archivoVentaCabecera.BuscarRegistro(numeroFactura, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroFactura < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return;
        } else {
            cout << endl << "NO SE REGISTRARON FACTURAS CON ESTE NUMERO" << endl << endl;
            return;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    } else {
        cout << endl << "COINCIDENCIA REGISTRADA CON ESTE NUMERO DE FACTURA " << endl << endl;
    }

    ventaCabecera = archivoVentaCabecera.LeerRegistro(posicion);
    ventaCabecera.Mostrar();

    cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
    encabezado = true;
    for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
        ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
        if(ventaDetalle.getNumeroFactura() == numeroFactura && ventaDetalle.getEstado()){
            ventaDetalle.Mostrar(encabezado);
            encabezado = false;
        }
    }
    cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
}

void consultaPorFecha(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabecera;
    VentaDetalle ventaDetalle;
    int cantidadRegistrosVentaCabecera, cantidadRegistrosVentaDetalle, anioActual, mesActual, diaActual, anioVenta, mesVenta, diaVenta;
    bool encabezado, coincidencia = false;
    Fecha fechaConsulta;

    ///OBTENGO FECHA ACTUAL
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActual = fechaActual.tm_year + 1900;
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    }

    cout << "INGRESAR LA FECHA DE VENTA/S QUE DESEA CONSULTAR: " << endl;
    cout << setfill((char) 196) << setw(49) << (char) 196 << endl;
    fechaConsulta.Cargar();
    if(fechaConsulta.getAnio() == -1){
        return;
    }
    cout << setfill((char) 196) << setw(49) << (char) 196 << endl;
    anioVenta = fechaConsulta.getAnio();
    mesVenta = fechaConsulta.getMes();
    diaVenta = fechaConsulta.getDia();
    if (anioVenta > anioActual || (anioVenta == anioActual && mesVenta > mesActual) || (anioVenta == anioActual && mesVenta == mesActual && diaVenta > diaActual)) {
        cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
        return;
    }

    for(int i = 0; i < cantidadRegistrosVentaCabecera; i++){
        ventaCabecera = archivoVentaCabecera.LeerRegistro(i);
        encabezado = true;
        if(ventaCabecera.getEstado()){
            if(ventaCabecera.getFechaVenta().getAnio() == fechaConsulta.getAnio() && ventaCabecera.getFechaVenta().getMes() == fechaConsulta.getMes() && ventaCabecera.getFechaVenta().getDia() == fechaConsulta.getDia()){
                if(!coincidencia){
                    cout << "COINCIDENCIA/S REGISTRADA/S EN ESTA FECHA" << endl << endl;
                }
                coincidencia = true;
                ventaCabecera.Mostrar();

                cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
                for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                    ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                    if(ventaDetalle.getNumeroFactura() == ventaCabecera.getNumeroFactura() && ventaDetalle.getEstado()){
                        ventaDetalle.Mostrar(encabezado);
                        encabezado = false;
                    }
                }
                cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
            }
        }
    }

    if(!coincidencia){
        cout << "NO SE REGISTRARON VENTAS EN ESTA FECHA" << endl << endl;
    }
}

void consultaPorRangoFecha(){
    ArchivoVentaCabecera archivoVentaCabecera;
    ArchivoVentaDetalle archivoVentaDetalle;
    VentaCabecera ventaCabeceraAux;
    VentaDetalle ventaDetalle;
    int posMin, cantidadRegistrosVentaCabecera, cantidadRegistrosVentaDetalle;
    bool encabezado, coincidencia = false;
    Fecha fechaExtremoMinima, fechaExtremoMaximo;

    ///OBTENGO FECHA ACTUAL
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    int anioActual = fechaActual.tm_year + 1900;
    int mesActual = fechaActual.tm_mon + 1;
    int diaActual = fechaActual.tm_mday;

    ///CREAMOS VECTOR DE ARCHIVO VENTA CABECERA
    cantidadRegistrosVentaCabecera = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistrosVentaCabecera == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return;
    }

    VentaCabecera *pVecVentaCabecera = new VentaCabecera[cantidadRegistrosVentaCabecera];
    if (pVecVentaCabecera == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoVentaCabecera.LeerArchivo(cantidadRegistrosVentaCabecera, pVecVentaCabecera);
    ///ORDENAMOS PARA DESPUES MOSTRAR ENTRE EL RANGO DE FECHA OTORGADO DE MANERA ASCENDENTE
    for(int i = 0; i < cantidadRegistrosVentaCabecera - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistrosVentaCabecera; j++){
            if (pVecVentaCabecera[j].getFechaVenta().getAnio() < pVecVentaCabecera[posMin].getFechaVenta().getAnio()) {
                posMin = j;
            } else if (pVecVentaCabecera[j].getFechaVenta().getAnio() == pVecVentaCabecera[posMin].getFechaVenta().getAnio()) {
                if (pVecVentaCabecera[j].getFechaVenta().getMes() < pVecVentaCabecera[posMin].getFechaVenta().getMes()) {
                    posMin = j;
                } else if (pVecVentaCabecera[j].getFechaVenta().getMes() == pVecVentaCabecera[posMin].getFechaVenta().getMes()) {
                    if (pVecVentaCabecera[j].getFechaVenta().getDia() < pVecVentaCabecera[posMin].getFechaVenta().getDia()) {
                        posMin = j;
                    }
                }
            }
        }
        ventaCabeceraAux = pVecVentaCabecera[i];
        pVecVentaCabecera[i] = pVecVentaCabecera[posMin];
        pVecVentaCabecera[posMin] = ventaCabeceraAux;
    }

    cout << "INGRESAR EL RANGO DE FECHA DE VENTA/S QUE DESEA CONSULTAR" << endl;

    cout << setfill((char) 196) << setw(57) << (char) 196 << endl;
    cout << "Extremo Minima: " << endl << endl;
    fechaExtremoMinima.Cargar();
    if(fechaExtremoMinima.getAnio() == -1){
        return;
    }
    int anioMinimo = fechaExtremoMinima.getAnio();
    int mesMinimo = fechaExtremoMinima.getMes();
    int diaMinimo = fechaExtremoMinima.getDia();
    if (anioMinimo > anioActual || (anioMinimo == anioActual && mesMinimo > mesActual) || (anioMinimo == anioActual && mesMinimo == mesActual && diaMinimo > diaActual)) {
        cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
        return;
    }
    cout << setfill((char) 196) << setw(19) << (char) 196 << endl;

    cout << "Extremo Maximo: " << endl << endl;
    fechaExtremoMaximo.Cargar();
    if(fechaExtremoMaximo.getAnio() == -1){
        return;
    }
    int anioMaximo = fechaExtremoMaximo.getAnio();
    int mesMaximo = fechaExtremoMaximo.getMes();
    int diaMaximo = fechaExtremoMaximo.getDia();
    if (anioMaximo > anioActual || (anioMaximo == anioActual && mesMaximo > mesActual) || (anioMaximo == anioActual && mesMaximo == mesActual && diaMaximo > diaActual)) {
        cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
        return;
    }
    cout << setfill((char) 196) << setw(57) << (char) 196 << endl << endl;

    for(int i = 0; i < cantidadRegistrosVentaCabecera; i++){
        encabezado = true;
        if(pVecVentaCabecera[i].getEstado()){
            if(pVecVentaCabecera[i].getFechaVenta().getAnio() > anioMinimo || (pVecVentaCabecera[i].getFechaVenta().getAnio() == anioMinimo && pVecVentaCabecera[i].getFechaVenta().getMes() > mesMinimo) || (pVecVentaCabecera[i].getFechaVenta().getAnio() == anioMinimo && pVecVentaCabecera[i].getFechaVenta().getMes() == mesMinimo && pVecVentaCabecera[i].getFechaVenta().getDia() >= diaMinimo)){
                if(pVecVentaCabecera[i].getFechaVenta().getAnio() < anioMaximo || (pVecVentaCabecera[i].getFechaVenta().getAnio() == anioMaximo && pVecVentaCabecera[i].getFechaVenta().getMes() < mesMaximo) || (pVecVentaCabecera[i].getFechaVenta().getAnio() == anioMaximo && pVecVentaCabecera[i].getFechaVenta().getMes() == mesMaximo && pVecVentaCabecera[i].getFechaVenta().getDia() <= diaMaximo)){
                    if(!coincidencia){
                        cout << "COINCIDENCIA/S REGISTRADA/S EN ESTE RANGO DE FECHA" << endl << endl;
                    }
                    coincidencia = true;
                    pVecVentaCabecera[i].Mostrar();

                    cantidadRegistrosVentaDetalle = archivoVentaDetalle.ContarRegistros();
                    for(int x = 0; x < cantidadRegistrosVentaDetalle; x++){
                        ventaDetalle = archivoVentaDetalle.LeerRegistro(x);
                        if(ventaDetalle.getNumeroFactura() == pVecVentaCabecera[i].getNumeroFactura() && ventaDetalle.getEstado()){
                            ventaDetalle.Mostrar(encabezado);
                            encabezado = false;
                        }
                    }
                    cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
                }
            }
        }
    }

    if(!coincidencia){
        cout << "NO SE REGISTRARON VENTAS EN ESTE RANGO DE FECHA" << endl << endl;
    }
}


///INFORMES VENTAS:
bool bisiesto(int anio){
    if (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) {
        return true;
    } else {
        return false;
    }
}

void informeRecaudacionDiaria(){
    ArchivoVentaCabecera archivoVentaCabecera;
    VentaCabecera ventaCabecera;
    Fecha fechaInformeDiario;
    float totalDia = 0;
    int dia, mes, anio, cantidadRegistros, anioActual, mesActual, diaActual, anioInforme, mesInforme, diaInforme;
    bool coincidencia = false;

    ///OBTENGO FECHA ACTUAL
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActual = fechaActual.tm_year + 1900;
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    cantidadRegistros = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return ;
    }

    cout << "Ingrese la fecha del dia del informe que desea generar:" << endl << endl;
    fechaInformeDiario.Cargar();
    if(fechaInformeDiario.getAnio() == -1){
        return;
    }
    anioInforme = fechaInformeDiario.getAnio();
    mesInforme = fechaInformeDiario.getMes();
    diaInforme = fechaInformeDiario.getDia();
    if (anioInforme > anioActual || (anioInforme == anioActual && mesInforme > mesActual) || (anioInforme == anioActual && mesInforme == mesActual && diaInforme > diaActual)) {
        cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
        return;
    }

    for(int x = 0; x < cantidadRegistros; x++){
        ventaCabecera = archivoVentaCabecera.LeerRegistro(x);
        dia = ventaCabecera.getFechaVenta().getDia();
        mes = ventaCabecera.getFechaVenta().getMes();
        anio = ventaCabecera.getFechaVenta().getAnio();

        if (ventaCabecera.getEstado()){
            if (dia == diaInforme && mes == mesInforme && anio == anioInforme){
                if(!coincidencia){
                    coincidencia = true;
                }
                totalDia += ventaCabecera.getTotalVenta();
            }
        }
    }

    if (!coincidencia){
        system("cls");
        cout << "NO SE ENCONTRARON VENTAS EN ESTA FECHA" << endl << endl;
        return;
    } else {
        system("cls");
        cout << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        cout << "Fecha de informe generado: ";
        fechaInformeDiario.Mostrar();
        cout << fixed << setprecision(2) << "Total recaudado diario: $" << totalDia << endl;
        cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
    }
}

void informeRecaudacionSemanal(){
    ArchivoVentaCabecera archivoVentaCabecera;
    VentaCabecera ventaCabecera;
    Fecha fechaInicioInformeSemanal, fechaInformeSemanal;
    float totalSemana = 0;
    int dia, diasMes, mes, anio, cantidadRegistros, anioActual, mesActual, diaActual, anioInforme, mesInforme, diaInforme;
    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool coincidencia = false;

    ///OBTENGO FECHA ACTUAL
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActual = fechaActual.tm_year + 1900;
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    cantidadRegistros = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return ;
    }

    cout << "Ingrese la fecha a partir de la cual desea generar el informe semanal:" << endl << endl;
    fechaInicioInformeSemanal.Cargar();
    if(fechaInicioInformeSemanal.getAnio() == -1){
        return;
    }
    anioInforme = fechaInicioInformeSemanal.getAnio();
    mesInforme = fechaInicioInformeSemanal.getMes();
    diaInforme = fechaInicioInformeSemanal.getDia();
    if (anioInforme > anioActual || (anioInforme == anioActual && mesInforme > mesActual) || (anioInforme == anioActual && mesInforme == mesActual && diaInforme > diaActual)) {
        cout << endl << "LA FECHA DE LA VENTA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
        return;
    }

    fechaInformeSemanal = fechaInicioInformeSemanal;
    if (bisiesto(fechaInformeSemanal.getAnio())) {
        diasPorMes[1] = 29;
    }
    diasMes = diasPorMes[fechaInformeSemanal.getMes() - 1];

    for(int i = 0; i < 7; i++){
        for(int x = 0; x < cantidadRegistros; x++){
            ventaCabecera = archivoVentaCabecera.LeerRegistro(x);
            dia = ventaCabecera.getFechaVenta().getDia();
            mes = ventaCabecera.getFechaVenta().getMes();
            anio = ventaCabecera.getFechaVenta().getAnio();

            if (ventaCabecera.getEstado()){
                if (dia == fechaInformeSemanal.getDia() && mes == fechaInformeSemanal.getMes() && anio == fechaInformeSemanal.getAnio()){
                    if(!coincidencia){
                        coincidencia = true;
                    }
                    totalSemana += ventaCabecera.getTotalVenta();
                }
            }
        }

        fechaInformeSemanal.setDia(fechaInformeSemanal.getDia() + 1);
        if (fechaInformeSemanal.getDia() > diasMes){
            fechaInformeSemanal.setDia(1);
            fechaInformeSemanal.setMes(fechaInformeSemanal.getMes() + 1);
            if (fechaInformeSemanal.getMes() > 12) {
                fechaInformeSemanal.setMes(1);
                fechaInformeSemanal.setAnio(fechaInformeSemanal.getAnio() + 1);
            }
        }
    }

    if (!coincidencia){
        system("cls");
        cout << "NO SE ENCONTRARON VENTAS UNA SEMANA A PARTIR DE ESTA FECHA" << endl << endl;
        return;
    } else {
        system("cls");
        cout << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        cout << "Fecha de informe generado: ";
        fechaInicioInformeSemanal.Mostrar();
        cout << fixed << setprecision(2) << "Total recaudado semanal: $" << totalSemana << endl;
        cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
    }
}

void informeRecaudacionMensual(){
    ArchivoVentaCabecera archivoVentaCabecera;
    VentaCabecera ventaCabecera;
    Fecha fechaInformeMensual;
    float totalMes = 0;
    int mes, mesInforme, anio, anioInforme, cantidadRegistros;
    bool coincidencia = false;

    cantidadRegistros = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return ;
    }

    cout << "Ingrese mes u anio del informe que desea generar (MM/AAAA):" << endl << endl;
    cout << "Ingrese mes: ";
    cin >> mesInforme;
    if (cin.fail() || mesInforme < 1 || mesInforme > 12) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }

    cout << "Ingrese anio: ";
    cin >> anioInforme;
    if (cin.fail() || anioInforme < 1) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }

    for(int x = 0; x < cantidadRegistros; x++){
        ventaCabecera = archivoVentaCabecera.LeerRegistro(x);
        mes = ventaCabecera.getFechaVenta().getMes();
        anio = ventaCabecera.getFechaVenta().getAnio();

        if (ventaCabecera.getEstado()){
            if (mes == mesInforme && anio == anioInforme){
                if(!coincidencia){
                    coincidencia = true;
                }
                totalMes += ventaCabecera.getTotalVenta();
            }
        }
    }

    if (!coincidencia){
        system("cls");
        cout << "NO SE ENCONTRARON VENTAS EN ESTA FECHA" << endl << endl;
        return;
    } else {
        system("cls");
        cout << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        cout << "Mes de informe generado: ";
        switch(mesInforme){
            case 1:
                cout << "Enero del " << anioInforme << endl;
                break;
            case 2:
                cout << "Febrero del " << anioInforme << endl;
                break;
            case 3:
                cout << "Marzo del " << anioInforme << endl;
                break;
            case 4:
                cout << "Abril del " << anioInforme << endl;
                break;
            case 5:
                cout << "Mayo del " << anioInforme << endl;
                break;
            case 6:
                cout << "Junio del " << anioInforme << endl;
                break;
            case 7:
                cout << "Julio del " << anioInforme << endl;
                break;
            case 8:
                cout << "Agosto del " << anioInforme << endl;
                break;
            case 9:
                cout << "Septiembre del " << anioInforme << endl;
                break;
            case 10:
                cout << "Octubre del " << anioInforme << endl;
                break;
            case 11:
                cout << "Noviembre del " << anioInforme << endl;
                break;
            case 12:
                cout << "Diciembre del " << anioInforme << endl;
                break;
            default:
                break;
        }
        cout << fixed << setprecision(2) << "Total recaudado diario: $" << totalMes << endl;
        cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
    }
}

void informeRecaudacionAnual(){
    ArchivoVentaCabecera archivoVentaCabecera;
    VentaCabecera ventaCabecera;
    float totalAnual = 0;
    int anio, anioInforme, cantidadRegistros;
    bool coincidencia = false;

    cantidadRegistros = archivoVentaCabecera.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS (CABECERA)" << endl << endl;
        return ;
    }

    cout << "Ingrese anio del informe que desea generar (AAAA): ";
    cin >> anioInforme;
    if (cin.fail() || anioInforme < 1900) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }

    for(int x = 0; x < cantidadRegistros; x++){
        ventaCabecera = archivoVentaCabecera.LeerRegistro(x);
        anio = ventaCabecera.getFechaVenta().getAnio();
        if (ventaCabecera.getEstado()){
            if (anio == anioInforme){
                if(!coincidencia){
                    coincidencia = true;
                }
                totalAnual += ventaCabecera.getTotalVenta();
            }
        }
    }

    if (!coincidencia){
        system("cls");
        cout << "NO SE ENCONTRARON VENTAS EN ESTA FECHA" << endl << endl;
        return;
    } else {
        system("cls");
        cout << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        cout << "Anio de informe generado: " << anioInforme << endl;
        cout << fixed << setprecision(2) << "Total recaudado diario: $" << totalAnual << endl;
        cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
    }
}
