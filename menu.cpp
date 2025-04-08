#include <iostream>
#include <limits>//Para numeric_limits

#include "rlutil.h"
#include "funcionesVentas.h"
#include "funcionesClientes.h"
#include "funcionesVendedores.h"
#include "funcionesProductos.h"
#include "constantes.h"
#include "menu.h"

using namespace std;

///CONSTANTE:
const int altoConsola = rlutil::trows();


///FUNCION PARA MOSTRAR ITEMS DE LOS MENUS:
void showItem(const char *text, int posX, int posY, bool seleccionado){
    if(seleccionado){
        rlutil::locate(posX, posY);
        rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
        rlutil::setColor(rlutil::BLACK);
        cout << (char) 175 << " " << text;
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    } else {
        rlutil::locate(posX , posY);
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        cout << "  " << text;;
    }
}


///MENU:
void menu(){
    int y = 0;
    int x = 1;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();
    rlutil::hidecursor();
    while(true) {
        showItem("---- MENU PRINCIPAL ----", x, 1, false);
        showItem("Ventas", x + 2, 2, y == 0);
        showItem("Clientes", x + 2, 3, y == 1);
        showItem("Vendedores", x + 2, 4, y == 2);
        showItem("Productos", x + 2, 5, y == 3);
        showItem("Salir del programa", x + 2, 6, y == 4);
        showItem("------------------------", x, 7, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 4){
                    y = 4;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        subMenuVentas();
                        break;
                    case 1:
                        rlutil::cls();
                        subMenuClientes();
                        break;
                    case 2:
                        rlutil::cls();
                        subMenuVendedores();
                        break;
                    case 3:
                        rlutil::cls();
                        subMenuProductos();
                        break;
                    case 4:
                        rlutil::locate(1, altoConsola - 3);
                        return;
                        break;
                }
                break;
        }
    }
}


///VENTAS:
void subMenuVentas(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("----------------------- SUBMENU VENTAS ----------------------", x, 1, false);
        showItem("Nueva venta", x + 2, 2, y == 0);
        showItem("Alta de un producto en el detalle de venta", x + 2, 3, y == 1);
        showItem("Baja venta", x + 2, 4, y == 2);
        showItem("Baja producto en el detalle de venta", x + 2, 5, y == 3);
        showItem("Modificar atributo/s de una venta", x + 2, 6, y == 4);
        showItem("Modificar atributo/s de un producto en el detalle de venta", x + 2, 7, y == 5);
        showItem("Listado ventas", x + 2, 8, y == 6);
        showItem("Consulta ventas", x + 2, 9, y == 7);
        showItem("Informes ventas", x + 2, 10, y == 8);
        showItem("Salir", x + 2, 11, y == 9);
        showItem("-------------------------------------------------------------", x, 12, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 9){
                    y = 9;
                }
                break;
            case 1:
                switch(y){
                    case 0:
                        rlutil::cls();
                        nuevaVenta();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        agregarProductoAlDetalle();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        darBajaVenta();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        darBajaProductoDeVenta();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 4:
                        rlutil::cls();
                        modificarCabecera();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 5:
                        rlutil::cls();
                        modificarDetalle();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 6:
                        rlutil::cls();
                        subMenuListadoVentas();
                        break;
                    case 7:
                        rlutil::cls();
                        subMenuConsultaVentas();
                        break;
                    case 8:
                        rlutil::cls();
                        subMenuInformesVentas();
                        break;
                    case 9:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuListadoVentas(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("---------- SUBMENU LISTADO DE VENTAS ----------", x, 1, false);
        showItem("Listar sin aplicar ordenamiento.", x + 2, 2, y == 0);
        showItem("Listar por numero de factura de menor a mayor.", x + 2, 3, y == 1);
        showItem("Listar por numero de factura de mayor a menor.", x + 2, 4, y == 2);
        showItem("Listar por fecha de venta de menor a mayor.", x + 2, 5, y == 3);
        showItem("Listar por fecha de venta de mayor a menor.", x + 2, 6, y == 4);
        showItem("Salir", x + 2, 7, y == 5);
        showItem("-----------------------------------------------", x, 8, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 5){
                    y = 5;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        listarSinOrdenamientoVentas();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        listarPorNumFacturaAscendente();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        listarPorNumFacturaDescendente();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        listarPorFechaDeVentaAscendente();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 4:
                        rlutil::cls();
                        listarPorFechaDeVentaDescendente();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 5:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuConsultaVentas(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("-- Elija el parametro por el que desea filtrar ---", x, 1, false);
        showItem("Por numero de factura", x + 2, 2, y == 0);
        showItem("Por fecha", x + 2, 3, y == 1);
        showItem("Por rango de fecha", x + 2, 4, y == 2);
        showItem("Salir", x + 2, 5, y == 3);
        showItem("----------------------------------------------------", x, 6, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 3){
                    y = 3;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        consultaPorNumeroFactura();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        consultaPorFecha();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        consultaPorRangoFecha();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuInformesVentas(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("---- SUBMENU DE INFORMES DE VENTA ----", x, 1, false);
        showItem("Informe de recaudacion diaria" , x + 2, 2, y == 0);
        showItem("Informe de recaudacion semanal", x + 2, 3, y == 1);
        showItem("Informe de recaudacion mensual", x + 2, 4, y == 2);
        showItem("Informe de recaudacion anual", x + 2, 5, y == 3);
        showItem("Salir", x + 2, 6, y == 4);
        showItem("--------------------------------------", x, 7, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 4){
                    y = 4;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        informeRecaudacionDiaria();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        informeRecaudacionSemanal();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        informeRecaudacionMensual();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        informeRecaudacionAnual();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 4:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}


///CLIENTES:
void subMenuClientes(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("---------- SUBMENU CLIENTES ----------", x, 1, false);
        showItem("Nuevo cliente", x + 2, 2, y == 0);
        showItem("Baja cliente", x + 2, 3, y == 1);
        showItem("Modificar atributo/s de un cliente", x + 2, 4, y == 2);
        showItem("Listado clientes", x + 2, 5, y == 3);
        showItem("Consulta clientes", x + 2, 6, y == 4);
        showItem("Salir", x + 2, 7, y == 5);
        showItem("--------------------------------------", x, 8, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 5){
                    y = 5;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        nuevoCliente();
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        bajaCliente();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        modificarCliente();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        subMenuListadoClientes();
                        break;
                    case 4:
                        rlutil::cls();
                        subMenuConsultaClientes();
                        break;
                    case 5:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuListadoClientes(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("-------------- SUBMENU LISTADO DE CLIENTES --------------", x, 1, false);
        showItem("Listar sin aplicar ordenamiento", x + 2, 2, y == 0);
        showItem("Listar alfabeticamente por apellido (Ascendentemente)", x + 2, 3, y == 1);
        showItem("Listar alfabeticamente por apellido (Descendentemente)", x + 2, 4, y == 2);
        showItem("Salir", x + 2, 5, y == 3);
        showItem("---------------------------------------------------------", x, 6, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 3){
                    y = 3;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        listarSinOrdenamientoClientes();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        listarPorApellidoAscendentementeClientes();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        listarPorApellidoDescendentementeClientes();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }


    }
}

void subMenuConsultaClientes(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("--- Elija el parametro por el que desea filtrar ---", x, 1, false);
        showItem("Por numero de cliente", x + 2, 2, y == 0);
        showItem("Por DNI", x + 2, 3, y == 1);
        showItem("Por genero", x + 2, 4, y == 2);
        showItem("Por rango de edad", x + 2, 5, y == 3);
        showItem("Salir" , x + 2, 6, y == 4);
        showItem("---------------------------------------------------", x, 7, false);

                switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 4){
                    y = 4;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        consultaClientesPorNumeroCliente();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        consultaaClientesPorDNI();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        consultaaClientesPorGenero();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        consultaClientesPorRangoEdad();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 4:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}


///VENDEDORES:
void subMenuVendedores(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("---------- SUBMENU VENDEDORES ----------", x, 1, false);
        showItem("Nuevo vendedor", x + 2, 2, y == 0);
        showItem("Baja vendedor", x + 2, 3, y == 1);
        showItem("Modificar atributo/s de un vendedor", x + 2, 4, y == 2);
        showItem("Listado vendedores", x + 2, 5, y == 3);
        showItem("Consulta vendedores", x + 2, 6, y == 4);
        showItem("Salir", x + 2, 7, y == 5);
        showItem("----------------------------------------", x, 8, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 5){
                    y = 5;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        nuevoVendedor();
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        bajaVendedor();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        modificarVendedor();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        subMenuListadoVededores();
                        break;
                    case 4:
                        rlutil::cls();
                        subMenuConsultaVendedores();
                        break;
                    case 5:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuListadoVededores(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("-------------- SUBMENU LISTADO DE VENDEDORES --------------", x, 1, false);
        showItem("Listar sin aplicar ordenamiento", x + 2, 2, y == 0);
        showItem("Listar alfabeticamente por apellido (Ascendentemente)", x + 2, 3, y == 1);
        showItem("Listar alfabeticamente por apellido (Descendentemente)", x + 2, 4, y == 2);
        showItem("Salir", x + 2, 5, y == 3);
        showItem("-----------------------------------------------------------", x, 6, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 3){
                    y = 3;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        listarSinOrdenamientoVendedores();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        listarPorApellidoAscendentementeVendedores();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        listarPorApellidoDescendentementeVendedores();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuConsultaVendedores(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("-- Elija el parametro por el que desea filtrar --", x, 1, false);
        showItem("Por legajo", x + 2, 2, y == 0);
        showItem("Por DNI", x + 2, 3, y == 1);
        showItem("Por genero", x + 2, 4, y == 2);
        showItem("Por rango de edad", x + 2, 5, y == 3);
        showItem("Salir", x + 2, 6, y == 4);
        showItem("-------------------------------------------------", x, 7, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 4){
                    y = 4;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        consultaVendedorPorLegajo();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        consultaVendedorPorDNI();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        consultaVendedorPorGenero();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        consultaVendedorPorRangoEdad();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 4:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}


///PRODUCTOS:
void subMenuProductos(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("---------- SUBMENU DE PRODUCTOS ----------", x, 1, false);
        showItem("Nuevo producto", x + 2, 2, y == 0);
        showItem("Baja producto", x + 2, 3, y == 1);
        showItem("Modificar atributo/s de un producto", x + 2, 4, y == 2);
        showItem("Listado productos", x + 2, 5, y == 3);
        showItem("Consulta productos", x + 2, 6, y == 4);
        showItem("Salir", x + 2, 7, y == 5);
        showItem("------------------------------------------", x, 8, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 5){
                    y = 5;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        nuevoProducto();
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        darBajaProducto();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        modificarProducto();
                        cout << endl;
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        subMenuListadoProductos();
                        break;
                    case 4:
                        rlutil::cls();
                        subMenuConsultaProductos();
                        break;
                    case 5:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuListadoProductos(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("---- SUBMENU LISTADO DE PRODUCTOS ----", x, 1, false);
        showItem("Listar sin aplicar ordenamiento.", x + 2, 2, y == 0);
        showItem("Listar por precio de menor a mayor.", x + 2, 3, y == 1);
        showItem("Listar por precio de mayor a menor.", x + 2, 4, y == 2);
        showItem("Salir", x + 2, 5, y == 3);
        showItem("--------------------------------------", x, 6, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 3){
                    y = 3;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        listadoProductoSinOrden();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        listadoProductoMenMay();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        listadoProductoMayMen();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 3:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}

void subMenuConsultaProductos(){
    int y = 0;
    int x = 1;

    while(true){
        showItem("--- Elija el parametro por el que desea filtrar ---", x, 1, false);
        showItem("Por ID", x + 2, 2, y == 0);
        showItem("Por categoria", x + 2, 3, y == 1);
        showItem("Salir", x + 2, 4, y == 2);
        showItem("----------------------------------------------------", x, 5, false);

        switch(rlutil::getkey()) {
            case 14:
                rlutil::locate(x, 3 + y);
                y--;
                if(y < 0){
                    y = 0;
                }
                break;
            case 15:
                rlutil::locate(x, 3 + y);
                y++;
                if(y > 2){
                    y = 2;
                }
                break;
            case 1:
                switch(y) {
                    case 0:
                        rlutil::cls();
                        consultaProductoPorId();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 1:
                        rlutil::cls();
                        consultaProductoPorCategoria();
                        system("pause");
                        rlutil::cls();
                        break;
                    case 2:
                        rlutil::cls();
                        return;
                        break;
                }
                break;
        }
    }
}
