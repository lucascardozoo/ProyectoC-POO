#include <iostream>

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Cliente.h"
#include "constantes.h"
#include "ArchivoClientes.h"

using namespace std;

Cliente::Cliente(){
    _numeroCliente = 0;
    _estado =  false;
}

int Cliente::getNumeroCliente(){
    return _numeroCliente;
}

bool Cliente::getEstado(){
    return _estado;
}

void Cliente::setNumeroCliente(int numeroCliente){
    _numeroCliente = numeroCliente;
}

void Cliente::setEstado(bool estado){
    _estado = estado;
}

void Cliente::asignacionNumeroCliente(){
    ArchivoClientes archivoClientes;
    int cantidadRegistros = archivoClientes.ContarRegistros();
    _numeroCliente = cantidadRegistros + 1;
}

void Cliente::Cargar(){
    Persona::Cargar();
    if (Persona::getDNI() == -1){
        _numeroCliente = -1;
        return;
    } else {
        asignacionNumeroCliente();
        _estado = true;
        return;
    }
}

void Cliente::Mostrar(){
    cout << "Numero de cliente: " << _numeroCliente << endl;
    if (_estado){
        cout << "Estado del cliente: Activo" << endl << endl;
    } else {
        cout << "Estado del cliente: Desactivo" << endl << endl;
    }
    Persona::Mostrar();
}
