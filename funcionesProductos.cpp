#include <iostream>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Producto.h"
#include "constantes.h"
#include "ArchivoProductos.h"
#include "funcionesProductos.h"

using namespace std;

///FUNCIONES GENERALES PARA PRODUCTOS
void nuevoProducto(){
    ArchivoProductos archivoProductos;
    Producto producto;
    producto.Cargar();
    if(producto.getIdProducto() == -1){
        return;
    }

    if(archivoProductos.GrabarRegistro(producto)){
        cout << endl << "SE REGISTRO EXITOSAMENTE EL PRODUCTO" << endl << endl;
        system("pause");
    } else {
        cout << endl << "ERROR AL REGISTRAR EL PRODUCTO" << endl << endl;
        system("pause");
    }
}

void darBajaProducto(){
    ArchivoProductos archivoProductos;
    archivoProductos.BajaRegistro();
}

void modificarProducto(){
    ArchivoProductos archivoProductos;
    archivoProductos.ModificarRegistro();
}


///LISTADOS PRODUCTOS:
void listadoProductoSinOrden(){
    ArchivoProductos archivoProductos;
    cout << endl;
    if(archivoProductos.ListarRegistros(ACTIVOS)){
        cout << "SE LISTO EXITOSAMENTE EL ARCHIVO DE PRODUCTOS: SIN ORDEN" << endl << endl;
    }
}

void listadoProductoMenMay(){
    ArchivoProductos archivoProductos;
    Producto registro, registroAux;
    int cantidadRegistros;
    int posPrecioMin;

    cantidadRegistros = archivoProductos.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS" << endl << endl;
        return ;
    }

    Producto *pVecProductos = new Producto[cantidadRegistros];
    if (pVecProductos == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoProductos.LeerArchivo(cantidadRegistros, pVecProductos);

    for(int i = 0; i < cantidadRegistros - 1; i++){
        posPrecioMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if(pVecProductos[j].getPrecioProducto() < pVecProductos[posPrecioMin].getPrecioProducto()){
               posPrecioMin = j;
            }
        }
        registroAux = pVecProductos[i];
        pVecProductos[i] = pVecProductos[posPrecioMin];
        pVecProductos[posPrecioMin] = registroAux;
    }

    ///Imprimir:
    cout << endl;
    for(int i = 0; i < cantidadRegistros; i++){
        if(pVecProductos[i].getEstado()){
            pVecProductos[i].Mostrar();
            cout << endl << setfill((char) 220) << setw(100) << (char) 220 << endl << endl;
        }
    }
}

void listadoProductoMayMen(){
    ArchivoProductos archivoProductos;
    Producto registro, registroAux;
    int cantidadRegistros;
    int posPrecioMin;

    cantidadRegistros = archivoProductos.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS" << endl << endl;
        return ;
    }

    Producto *pVecProductos = new Producto[cantidadRegistros];
    if (pVecProductos == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoProductos.LeerArchivo(cantidadRegistros, pVecProductos);

    for(int i = 0; i < cantidadRegistros - 1; i++){
        posPrecioMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if(pVecProductos[j].getPrecioProducto() > pVecProductos[posPrecioMin].getPrecioProducto()){
               posPrecioMin = j;
            }
        }
        registroAux = pVecProductos[i];
        pVecProductos[i] = pVecProductos[posPrecioMin];
        pVecProductos[posPrecioMin] = registroAux;
    }

    /// imprimir:
    cout << endl;
    for(int i = 0; i < cantidadRegistros; i++){
        if(pVecProductos[i].getEstado()){
            pVecProductos[i].Mostrar();
            cout << endl << setfill((char) 220) << setw(100) << (char) 220 << endl << endl;
        }
    }
}


///CONSULTA PRODUCTOS:
void consultaProductoPorId(){
    ArchivoProductos archivoProductos;
    Producto producto;
    int id, posicion;

    cout << "INGRESE EL ID DEL PRODUCTO QUE DESEA CONSULTAR: ";
    cin >> id;

    posicion = archivoProductos.BuscarRegistro(id, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || id < 1) {//Verificar si la entrada es valida
            cout << endl << "Error: Debe ingresar un numero valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return;
        } else {
            cout << endl << "ID INEXISTENTE" << endl << endl;
            return;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS" << endl << endl;
        return;
    } else {
        cout << endl << "CONSULTA DE ID PRODUCTO ENCONTRADA" << endl << endl;
        producto = archivoProductos.LeerRegistro(posicion);
        producto.Mostrar();
        cout << endl << setfill((char) 220) << setw(100) << (char) 220 << endl << endl;
        return;
    }
}

void consultaProductoPorCategoria(){
    ArchivoProductos archivoProductos;
    Producto producto;
    int categoria, cantRegistros;

    cout << "1- Zapatillas" << endl;
    cout << "2- Remeras" << endl;
    cout << "3- Buzos" << endl;
    cout << "4- Shorts" << endl << endl;

    cout << "Ingrese una categoria para el producto: ";
    cin >> categoria;
    ///Verificar si la entrada es valida
    if (cin.fail() || (categoria != 1 && categoria != 2 && categoria != 3 && categoria != 4)) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }

    cantRegistros = archivoProductos.ContarRegistros();
    if(cantRegistros == 0){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS" << endl << endl;
        return ;
    }

    cout << endl;
    for(int i = 0; i<cantRegistros; i++){
        producto = archivoProductos.LeerRegistro(i);
        if(producto.getCategoriaProducto() == categoria && producto.getEstado()){
            producto.Mostrar();
            cout << endl << setfill((char) 220) << setw(100) << (char) 220 << endl << endl;
        }
    }
}
