#include <iostream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Cliente.h"
#include "constantes.h"
#include "ArchivoClientes.h"
#include "funcionesClientes.h"

using namespace std;

///FUNCION PARA CALCULAR EDAD DE CLIENTES
int calcularEdadCliente(int dia, int mes, int anio){
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;

    int edad = (fechaActual.tm_year + 1900) - anio;
    if (fechaActual.tm_mon + 1 < mes || (fechaActual.tm_mon + 1 == mes && fechaActual.tm_mday < dia)) {
        edad--;
    }

    return edad;
}


///FUNCIONES GENERALES PARA CLIENTES
void nuevoCliente(){
    ArchivoClientes archivoClientes;
    Cliente cliente;

    cliente.Cargar();
    if(cliente.getNumeroCliente() == -1){
        return;
    }

    if(archivoClientes.GrabarRegistro(cliente)){
        cout << endl << "SE REGISTRO EXITOSAMENTE AL CLIENTE" << endl << endl;
        system("pause");
    } else {
        cout << endl << "ERROR AL REGISTRAR AL CLIENTE" << endl << endl;
        system("pause");
    }
}

void bajaCliente(){
    ArchivoClientes archivoClientes;
    archivoClientes.BajaRegistro();
}

void modificarCliente(){
    ArchivoClientes archivosClientes;
    archivosClientes.ModificarRegistro();
}


///LISTADO CLIENTES:
void listarSinOrdenamientoClientes(){
    ArchivoClientes archivoClientes;
    int cantidadRegistros;

    cantidadRegistros = archivoClientes.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
        return;
    } else {
        cout << "LISTADO DE CLIENTES REGISTRADOS SIN ORDENAMIENTO" << endl << endl;
        archivoClientes.ListarRegistros(ACTIVOS);
    }
}

void listarPorApellidoAscendentementeClientes(){
    ArchivoClientes archivoClientes;
    Cliente clienteAux;
    int posMin, cantidadRegistros;

    cantidadRegistros = archivoClientes.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
        return;
    }

    ///CREAMOS VECTOR DE ARCHIVO CLIENTES
    Cliente *pVecClientes = new Cliente[cantidadRegistros];
    if (pVecClientes == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoClientes.LeerArchivo(cantidadRegistros, pVecClientes);

    ///ORDENAMOS
    for(int i = 0; i < cantidadRegistros - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if(strcmp(pVecClientes[j].getApellido(), pVecClientes[posMin].getApellido()) == -1){
                posMin = j;
            }
        }
        clienteAux = pVecClientes[i];
        pVecClientes[i] = pVecClientes[posMin];
        pVecClientes[posMin] = clienteAux;
    }

    ///MUESTRAMOS
    cout << "LISTADO DE CLIENTES REGISTRADOS ASCENDENTEMENTE POR APELLIDO" << endl << endl;
    for(int x = 0; x < cantidadRegistros; x++){
        if (pVecClientes[x].getEstado()){
            pVecClientes[x].Mostrar();
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}

void listarPorApellidoDescendentementeClientes(){
    ArchivoClientes archivoClientes;
    Cliente clienteAux;
    int posMin, cantidadRegistros;

    cantidadRegistros = archivoClientes.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
        return;
    }

    ///CREAMOS VECTOR DE ARCHIVO CLIENTES
    Cliente *pVecClientes = new Cliente[cantidadRegistros];
    if (pVecClientes == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoClientes.LeerArchivo(cantidadRegistros, pVecClientes);

    ///ORDENAMOS
    for(int i = 0; i < cantidadRegistros - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if(strcmp(pVecClientes[j].getApellido(), pVecClientes[posMin].getApellido()) == 1){
                posMin = j;
            }
        }
        clienteAux = pVecClientes[i];
        pVecClientes[i] = pVecClientes[posMin];
        pVecClientes[posMin] = clienteAux;
    }

    ///MUESTRAMOS
    cout << "LISTADO DE CLIENTES REGISTRADOS DESCENDENTEMENTE POR APELLIDO" << endl << endl;
    for(int x = 0; x < cantidadRegistros; x++){
        if (pVecClientes[x].getEstado()){
            pVecClientes[x].Mostrar();
            cout << endl << setfill((char) 220) << setw(110) << (char) 220 << endl << endl;
        }
    }
}


///CONSULTAS CLIENTES:
void consultaClientesPorNumeroCliente(){
    ArchivoClientes archivoClientes;
    Cliente cliente;
    int numCliente, posicion;

    cout << "INGRESE EL NUMERO DE CLIENTE QUE DESEA CONSULTAR: ";
    cin >> numCliente;

    posicion = archivoClientes.BuscarRegistro(numCliente, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numCliente < 1) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return;
        } else {
            cout << endl << "NO SE REGISTRARON CLIENTES CON ESTE NUMERO" << endl << endl;
            return;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
        return;
    } else {
        cout << endl << "COINCIDENCIA REGISTRADA CON ESTE NUMERO DE CLIENTE" << endl << endl;
        cliente = archivoClientes.LeerRegistro(posicion);
        cliente.Mostrar();
        cout << endl;
        return;
    }
}

void consultaaClientesPorDNI(){
    ArchivoClientes archivoClientes;
    Cliente cliente;
    int cantidadRegistros, DNI;

    cantidadRegistros = archivoClientes.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
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
        cliente = archivoClientes.LeerRegistro(x);
        if(cliente.getDNI() == DNI && cliente.getEstado()){
            cout << endl;
            cliente.Mostrar();
            cout << endl;
            return;
        }
    }
    cout << endl << "NO SE ENCONTRARON COINCIDENCIAS" << endl << endl;
    return;
}

void consultaaClientesPorGenero(){
    ArchivoClientes archivoClientes;
    Cliente cliente;
    int cantidadRegistros, genero;
    bool coincidencia = false;

    cantidadRegistros = archivoClientes.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
        return;
    }

    cout << "INGRESE EL GENERO DE LOS CLIENTES QUE DESEA CONSULTAR (1-MASCULINO 2-FEMENINO): ";
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
        cliente = archivoClientes.LeerRegistro(x);
        if(cliente.getGenero() == genero && cliente.getEstado()){
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
            cliente.Mostrar();
            cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        }
    }

    if (!coincidencia){
        cout << "NO SE ENCONTRARON COINCIDENCIAS" << endl << endl;
        return;
    }

}

void consultaClientesPorRangoEdad(){
    ArchivoClientes archivoClientes;
    Cliente clienteAux;
    int posMin, cantidadRegistros, edadMin, edadMax, dia, mes, anio, edad;
    bool coincidencia = false;

    cantidadRegistros = archivoClientes.ContarRegistros();
    if(cantidadRegistros == 0){
        cout << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl << endl;
        return;
    }

    ///CREAMOS VECTOR DE ARCHIVO VENTA CABECERA
    Cliente *pVecClientes = new Cliente[cantidadRegistros];
    if (pVecClientes == nullptr) {
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA" << endl;
    }
    archivoClientes.LeerArchivo(cantidadRegistros, pVecClientes);

    ///ORDENAMOS PARA DESPUES MOSTRAR ENTRE EL RANGO DE FECHA OTORGADO DE MANERA ASCENDENTE
    for(int i = 0; i < cantidadRegistros - 1; i++){
        posMin = i;
        for(int j = i + 1; j < cantidadRegistros; j++){
            if (pVecClientes[j].getFechaNacimiento().getAnio() > pVecClientes[posMin].getFechaNacimiento().getAnio()) {
                posMin = j;
            } else if (pVecClientes[j].getFechaNacimiento().getAnio() == pVecClientes[posMin].getFechaNacimiento().getAnio()) {
                if (pVecClientes[j].getFechaNacimiento().getMes() > pVecClientes[posMin].getFechaNacimiento().getMes()) {
                    posMin = j;
                } else if (pVecClientes[j].getFechaNacimiento().getMes() == pVecClientes[posMin].getFechaNacimiento().getMes()) {
                    if (pVecClientes[j].getFechaNacimiento().getDia() > pVecClientes[posMin].getFechaNacimiento().getDia()) {
                        posMin = j;
                    }
                }
            }
        }
        clienteAux = pVecClientes[i];
        pVecClientes[i] = pVecClientes[posMin];
        pVecClientes[posMin] = clienteAux;
    }

    cout << "INGRESAR EL RANGO DE EDAD DE CLIENTE/S QUE DESEA CONSULTAR" << endl;
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
        if(pVecClientes[i].getEstado()){
            dia = pVecClientes[i].getFechaNacimiento().getDia();
            mes = pVecClientes[i].getFechaNacimiento().getMes();
            anio = pVecClientes[i].getFechaNacimiento().getAnio();
            edad = calcularEdadCliente(dia, mes, anio);
            if(edad >= edadMin && edad <= edadMax){
                if(!coincidencia){
                    system("cls");
                    cout << "COINCIDENCIA/S REGISTRADA/S EN ESTE RANGO DE EDAD" << endl << endl;
                    coincidencia = true;
                }

                pVecClientes[i].Mostrar();
                cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
            }
        }
    }

    if(!coincidencia){
        cout << "NO SE REGISTRARON CLIENTES EN ESTE RANGO DE EDAD" << endl << endl;
    }
}
