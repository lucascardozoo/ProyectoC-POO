#include <iostream>
#include <iomanip>
#include <limits>//Para std::numeric_limits

#include "Fecha.h"

using namespace std;

Fecha::Fecha(){
    _dia = 0;
    _mes = 0;
    _anio = 0;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::setDia(int dia){
    _dia = dia;
}

void Fecha::setMes(int mes){
    _mes = mes;
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

void Fecha::Cargar(){
    cout << "Ingrese dia: ";
    cin >> _dia;
    if (cin.fail()) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _anio = -1;
        return;
    } else if(_dia < 1 || _dia > 31){
        cout << endl << "DIA INVALIDO" << endl;
        _anio = -1;
        return;
    }

    cout << "Ingrese mes: ";
    cin >> _mes;
    if (cin.fail()) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _anio = -1;
        return;
    } else if(_mes < 1 || _mes > 12){
        cout << endl << "MES INVALIDO" << endl;
        _anio = -1;
        return;
    }

    cout << "Ingrese anio: ";
    cin >> _anio;
    if (cin.fail()) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _anio = -1;
        return;
    } else if(_anio < 1900){
        cout << endl << "ANIO INVALIDO (PERMITIDO DESDE 1900)" << endl;
        _anio = -1;
        return;
    }
}

void Fecha::Mostrar(){
    cout << right << setfill('0') << setw(2) << _dia << "/" << setw(2) << _mes << "/" << setw(4) << _anio << setfill(' ') << endl;
}
