#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Vendedor.h"
#include "constantes.h"
#include "ArchivoVendedores.h"
#include "funcionesVendedores.h"

using namespace std;

///FUNCION PARA CALCULAR EDAD DE VENDEDORES
int calcularEdadVendedor(int dia, int mes, int anio){
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;

    int edad = (fechaActual.tm_year + 1900) - anio;
    if (fechaActual.tm_mon + 1 < mes || (fechaActual.tm_mon + 1 == mes && fechaActual.tm_mday < dia)) {
        edad--;
    }

    return edad;
}


///FUNCIONES GENERALES PARA VENDEDODES
void nuevoVendedor(){
    ArchivoVendedores archivoVendedores;
    Vendedor vendedor;

    vendedor.Cargar();
    if(vendedor.getLegajoVendedor() == -1){
        return;
    }

    if(archivoVendedores.GrabarRegistro(vendedor)){
        cout << endl << "SE REGISTRO EXITOSAMENTE AL VENDEDOR" << endl << endl;
        system("pause");
    } else {
        cout << endl << "ERROR AL REGISTRAR AL VENDEDOR" << endl << endl;
        system("pause");
    }
}

void bajaVendedor(){
    ArchivoVendedores archivoVendedores;
    archivoVendedores.BajaRegistro();
}

void modificarVendedor(){
    ArchivoVendedores archivoVendedores;
    archivoVendedores.ModificarRegistro();
}


///LISTADO VENDESORES:
void listarSinOrdenamientoVendedores(){
    ArchivoVendedores archivoVendedor;
    int cantidadRegistros;

    cantidadRegistros = archivoVendedor.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    } else {
        cout << "LISTADO DE VENDEDORES REGISTRADOS SIN ORDENAMIENTO" << endl << endl;
        archivoVendedor.ListarRegistros(ACTIVOS);
    }
}

void listarPorApellidoAscendentementeVendedores(){
    ArchivoVendedores archivoVendedor;
    Vendedor vendedorAux;
    int posMin, cantidadRegistros;

    cantidadRegistros = archivoVendedor.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    }

    ///CREAMOS VECTOR DE ARCHIVO VENDEDORESA
    Vendedor *pVecVendedor = new Vendedor[cantidadRegistros];
    if (pVecVendedor == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoVendedor.LeerArchivo(cantidadRegistros, pVecVendedor);

    ///ORDENAMOS
    for(int i = 0; i < cantidadRegistros - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if(strcmp(pVecVendedor[j].getApellido(), pVecVendedor[posMin].getApellido()) == -1){
                posMin = j;
            }
        }
        vendedorAux = pVecVendedor[i];
        pVecVendedor[i] = pVecVendedor[posMin];
        pVecVendedor[posMin] = vendedorAux;
    }

    ///MUESTRAMOS
    cout << "LISTADO DE VENDEDORES REGISTRADOS ASCENDENTEMENTE POR APELLIDO" << endl << endl;
    for(int x = 0; x < cantidadRegistros; x++){
        if(pVecVendedor[x].getEstado()){
            pVecVendedor[x].Mostrar();
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}

void listarPorApellidoDescendentementeVendedores(){
    ArchivoVendedores archivoVendedor;
    Vendedor vendedorAux;
    int posMin, cantidadRegistros;

    cantidadRegistros = archivoVendedor.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    }

    ///CREAMOS VECTOR DE ARCHIVO VENDEDORES
    Vendedor *pVecVendedor = new Vendedor[cantidadRegistros];
    if (pVecVendedor == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoVendedor.LeerArchivo(cantidadRegistros, pVecVendedor);

    ///ORDENAMOS
    for(int i = 0; i < cantidadRegistros - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if(strcmp(pVecVendedor[j].getApellido(), pVecVendedor[posMin].getApellido()) == 1){
                posMin = j;
            }
        }
        vendedorAux = pVecVendedor[i];
        pVecVendedor[i] = pVecVendedor[posMin];
        pVecVendedor[posMin] = vendedorAux;
    }

    ///MUESTRAMOS
    cout << "LISTADO DE VENDEDORES REGISTRADOS DESCENDENTEMENTE POR APELLIDO" << endl << endl;
    for(int x = 0; x < cantidadRegistros; x++){
        if(pVecVendedor[x].getEstado()){
            pVecVendedor[x].Mostrar();
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}


///CONSULTAS VENDEDORES:
void consultaVendedorPorLegajo(){
    ArchivoVendedores archivoVendedores;
    Vendedor vendedor;
    int legajo, posicion;

    cout << "INGRESE EL NUMERO DE LEGAJO QUE DESEA CONSULTAR: ";
    cin >> legajo;

    posicion = archivoVendedores.BuscarRegistro(legajo, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || legajo < 1) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return;
        } else{
            cout << endl << "LEGAJO INEXISTENTE" << endl << endl;
            return;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    } else {
        cout << endl << "COINCIDENCIA REGISTRADA CON ESTE LEGAJO DE VENDEDOR" << endl << endl;
        vendedor = archivoVendedores.LeerRegistro(posicion);
        vendedor.Mostrar();
        cout << endl;
        return;
    }
}

void consultaVendedorPorDNI(){
    ArchivoVendedores archivoVendedores;
    Vendedor vendedor;
    int cantidadRegistros, DNI;

    cantidadRegistros = archivoVendedores.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    }

    cout << "INGRESE EL NUMERO DE DNI QUE DESEA CONSULTAR: ";
    cin >> DNI;
    ///Verificar si la entrada es valida
    if (cin.fail() || DNI < 1000000 || DNI > 99999999) {
        cout << endl << "Error: Debe ingresar un numero de DNI valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }

    for(int x = 0; x < cantidadRegistros; x++){
        vendedor = archivoVendedores.LeerRegistro(x);
        if(vendedor.getDNI() == DNI && vendedor.getEstado()){
            cout << endl;
            vendedor.Mostrar();
            cout << endl;
            return;
        }
    }
    cout << endl << "NO SE ENCONTRARON COINCIDENCIAS" << endl << endl;
    return;
}

void consultaVendedorPorGenero(){
    ArchivoVendedores archivoVendedores;
    Vendedor vendedor;
    int cantidadRegistros, genero;
    bool coincidencia = false;

    cantidadRegistros = archivoVendedores.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    }

    cout << "INGRESE EL GENERO DE LOS VENDEDORES QUE DESEA CONSULTAR (1-MASCULINO 2-FEMENINO): ";
    cin >> genero;
    ///Verificar si la entrada es valida
    if (cin.fail() || (genero != 1 && genero != 2)) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }

    cout << endl;
    for(int x = 0; x < cantidadRegistros; x++){
        vendedor = archivoVendedores.LeerRegistro(x);
        if(vendedor.getGenero() == genero && vendedor.getEstado()){
            if(!coincidencia){
                system("cls");
                cout << "COINCIDENCIA/S REGISTRADA/S CON GENERO ";
                if(genero == 1){
                    cout << "MASCULINO" << endl << endl;
                } else if(genero == 2){
                    cout << "FEMENINO" << endl << endl;
                }
                coincidencia = true;
            }
            vendedor.Mostrar();
            cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        }
    }

    if (!coincidencia){
        cout << "NO SE ENCONTRARON COINCIDENCIAS" << endl << endl;
        return;
    }
}

void consultaVendedorPorRangoEdad(){
    ArchivoVendedores archivoVendedores;
    Vendedor vendedorAux;
    int posMin, cantidadRegistros, edadMin, edadMax, dia, mes, anio, edad;
    bool coincidencia = false;

    cantidadRegistros = archivoVendedores.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl << endl;
        return;
    }

    ///CREAMOS VECTOR DE ARCHIVO VENTA CABECERA
    Vendedor *pVecVendedor = new Vendedor[cantidadRegistros];
    if (pVecVendedor == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoVendedores.LeerArchivo(cantidadRegistros, pVecVendedor);

    ///ORDENAMOS PARA DESPUES MOSTRAR ENTRE EL RANGO DE FECHA OTORGADO DE MANERA ASCENDENTE
    for(int i = 0; i < cantidadRegistros - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if (pVecVendedor[j].getFechaNacimiento().getAnio() > pVecVendedor[posMin].getFechaNacimiento().getAnio()) {
                posMin = j;
            } else if (pVecVendedor[j].getFechaNacimiento().getAnio() == pVecVendedor[posMin].getFechaNacimiento().getAnio()) {
                if (pVecVendedor[j].getFechaNacimiento().getMes() > pVecVendedor[posMin].getFechaNacimiento().getMes()) {
                    posMin = j;
                } else if (pVecVendedor[j].getFechaNacimiento().getMes() == pVecVendedor[posMin].getFechaNacimiento().getMes()) {
                    if (pVecVendedor[j].getFechaNacimiento().getDia() > pVecVendedor[posMin].getFechaNacimiento().getDia()) {
                        posMin = j;
                    }
                }
            }
        }
        vendedorAux = pVecVendedor[i];
        pVecVendedor[i] = pVecVendedor[posMin];
        pVecVendedor[posMin] = vendedorAux;
    }

    cout << "INGRESAR EL RANGO DE EDAD DE VENDEDOR/ES QUE DESEA CONSULTAR" << endl;
    cout << setfill((char) 196) << setw(60) << (char) 196 << endl << endl;

    cout << "Edad Minima: ";
    cin >> edadMin;
    ///Verificar si la entrada es valida
    if (cin.fail() || edadMin < 1) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }
    cout << "Edad Maximo: ";
    cin >> edadMax;
    ///Verificar si la entrada es valida
    if (cin.fail() || edadMax < 1) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return;
    }
    cout << endl << setfill((char) 196) << setw(60) << (char) 196 << endl << endl;

    for(int i = 0; i < cantidadRegistros; i++){
        if(pVecVendedor[i].getEstado()){
            dia = pVecVendedor[i].getFechaNacimiento().getDia();
            mes = pVecVendedor[i].getFechaNacimiento().getMes();
            anio = pVecVendedor[i].getFechaNacimiento().getAnio();
            edad = calcularEdadVendedor(dia, mes, anio);
            if(edad >= edadMin && edad <= edadMax){
                if(!coincidencia){
                    system("cls");
                    cout << "COINCIDENCIA/S REGISTRADA/S EN ESTE RANGO DE EDAD" << endl << endl;
                    coincidencia = true;
                }

                pVecVendedor[i].Mostrar();
                cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
            }
        }
    }

    if(!coincidencia){
        cout << "NO SE REGISTRARON VENDEDORES EN ESTE RANGO DE EDAD" << endl << endl;
    }
}
