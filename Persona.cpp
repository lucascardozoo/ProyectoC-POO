#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Cliente.h"
#include "Vendedor.h"
#include "constantes.h"
#include "ArchivoVendedores.h"
#include "ArchivoClientes.h"

using namespace std;

Persona::Persona(){
    _DNI = 0;
    _genero = 0;
    strcpy(_telefono, "Sin telefono");
    strcpy(_nombre, "Sin nombre");
    strcpy(_apellido, "Sin apellido");
    strcpy(_correo, "Sin correo");
}

int Persona::getDNI(){
    return _DNI;
}

const char* Persona::getNombre(){
    return _nombre;
}

const char* Persona::getApellido(){
    return _apellido;
}

int Persona::getGenero(){
    return _genero;
}

Fecha Persona::getFechaNacimiento(){
    return _fechaNacimiento;
}

Direccion Persona::getDireccion(){
    return _direccion;
}

const char* Persona::getTelefono(){
    return _telefono;
}

const char* Persona::getCorreo(){
    return _correo;
}

void Persona::setDNI(int DNI){
    _DNI = DNI;
}

void Persona::setNombre(const char* nombre){
    strcpy(_nombre, nombre);
}

void Persona::setApellido(const char* apellido){
    strcpy(_apellido, apellido);
}

void Persona::setGenero(int genero){
    _genero = genero;
}

void Persona::setFechaNacimiento(Fecha fechaNacimiento){
    _fechaNacimiento = fechaNacimiento;
}

void Persona::setDireccion(Direccion direccion){
    _direccion = direccion;
}

void Persona::setTelefono(const char* telefono){
    strcpy(_telefono, telefono);
}

void Persona::setCorreo(const char* correo){
    strcpy(_correo, correo);
}

void Persona::Cargar(){
    ArchivoVendedores archivoVendedores;
    ArchivoClientes archivoClientes;
    Vendedor registroVendedor;
    Cliente registroCliente;
    int cantidadRegistros, tam, caracteresPosArroba = 0, caracteresPosPunto = 0, anioActualMayorDeEdad, anioActual, mesActual, diaActual, anioNacimiento, mesNacimiento, diaNacimiento;
    bool continuar, coincidenciaVendedor, coincidenciaCliente, arroba = false, punto = false;

    ///OBTENGO FECHA ACTUAL Y FECHA PARA SER MAYOR DE EDAD
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActualMayorDeEdad = (fechaActual.tm_year + 1900) - 18;
    anioActual = (fechaActual.tm_year + 1900);
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    cout << "Ingrese el numero de DNI: ";
    cin >> _DNI;
    ///Verificar si la entrada es valida
    if (cin.fail() || _DNI < 1000000 || _DNI > 99999999) {
        cout << endl << "Error: Debe ingresar un numero de DNI valido." << endl << endl;
        system("pause");
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _DNI = -1;
        return;
    }

    ///VERIFICACION DE SI EL DNI DEL VENDEDOR YA EXISTE EN EL ARCHIVO DE VENDEDORES
    coincidenciaVendedor = false;
    cantidadRegistros = archivoVendedores.ContarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        registroVendedor = archivoVendedores.LeerRegistro(i);
        if(registroVendedor.getDNI() == _DNI){
            coincidenciaVendedor = true;
        }
    }
    if(coincidenciaVendedor){
        cout << endl << "YA EXISTE UN VENDEDOR CON ESTE DNI" << endl << endl;
        cout << "DESEA CONTINUAR? 1-SI 0-NO: ";
        cin >> continuar;
        ///Verificar si la entrada es valida
        if (cin.fail() || (continuar != 0 && continuar != 1)) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            system("pause");
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            _DNI = -1;
            return;
        }

        if(!continuar){
            _DNI = -1;
            return;
        }
        cout << endl;
    }

    ///VERIFICACION DE SI EL DNI DEL CLIENTE YA EXISTE EN EL ARCHIVO DE CLIENTES
    coincidenciaCliente = false;
    cantidadRegistros = archivoClientes.ContarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        registroCliente = archivoClientes.LeerRegistro(i);
        if(registroCliente.getDNI() == _DNI){
            coincidenciaCliente = true;
        }
    }
    if (coincidenciaCliente){
        cout << endl << "YA EXISTE UN CLIENTE CON ESTE DNI" << endl << endl;
        cout << "DESEA CONTINUAR? 1-SI 0-NO: ";
        cin >> continuar;
        ///Verificar si la entrada es valida
        if (cin.fail() || (continuar != 0 && continuar != 1)) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            system("pause");
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            _DNI = -1;
            return;
        }

        if(!continuar){
            _DNI = -1;
            return;
        }
        cout << endl;
    }

    cout << "Ingrese nombre/s (50 caracteres maximo): ";
    cin.ignore();
    cin.getline(_nombre, 50);
    ///VERIFICACION DEL NOMBRE
    tam = strlen(_nombre);
    if(tam < 2){
        cout << endl << "ERROR: EL NOMBRE DEBE TENER AL MENOS 2 CARACTERES" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }

    cout << "Ingrese apellido/s (50 caracteres maximo): ";
    cin.getline(_apellido, 50);
    ///VERIFICACION DEL APELLIDO
    tam = strlen(_apellido);
    if(tam < 2){
        cout << endl << "ERROR: EL APELLIDO DEBE TENER AL MENOS 2 CARACTERES" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }

    cout << "Ingrese el genero (1-Masculino 2-Femenino): ";
    cin >> _genero;
    ///Verificar si la entrada es valida
    if (cin.fail() || (_genero != 1 && _genero != 2)) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        system("pause");
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _DNI = -1;
        return;
    }

    cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA)" << endl;
    _fechaNacimiento.Cargar();
    if(_fechaNacimiento.getAnio() == -1){
        cout << endl;
        system("pause");
        _DNI = -1;
        return;
    }
    anioNacimiento = _fechaNacimiento.getAnio();
    mesNacimiento = _fechaNacimiento.getMes();
    diaNacimiento = _fechaNacimiento.getDia();
    ///Verificamos fecha que no sea mayor a la actual
    if (anioNacimiento > anioActual || (anioNacimiento == anioActual && mesNacimiento > mesActual) || (anioNacimiento == anioActual && mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        cout << endl << "LA FECHA NO PUEDE SER MAYOR A LA ACTUAL" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }
    ///Verificamos fecha actual para ser mayor de edad
    if (anioNacimiento > anioActualMayorDeEdad || (anioNacimiento == anioActualMayorDeEdad && mesNacimiento > mesActual) || (anioNacimiento == anioActualMayorDeEdad && mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        cout << endl << "NO ES MAYOR DE EDAD" << endl << endl;
        cout << "DESEA CONTINUAR? 1-SI 0-NO: ";
        cin >> continuar;
        ///Verificar si la entrada es valida
        if (cin.fail() || (continuar != 0 && continuar != 1)) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            system("pause");
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            _DNI = -1;
            return;
        }
        if(!continuar){
            _DNI = -1;
            return;
        }
        cout << endl;
    }

    cin.ignore();
    _direccion.Cargar();
    if(_direccion.getCodigoPostal() == -1){
        cout << endl;
        system("pause");
        _DNI = -1;
        return;
    }

    cout << "Ingrese el numero del telefono: ";
    cin.ignore();
    cin.getline(_telefono, 20);
    ///VERIFICACION DEL TELEFONO
    tam = strlen(_telefono);
    if(tam < 7){
        cout << endl << "ERROR: EL NUMERO DEBE TENER AL MENOS 7 DIGITOS" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }

    cout << "Ingrese el correo electronico: ";
    cin.getline(_correo, 50);
    ///VERIFICACION DEL CORREO
    if(_correo[0] == '@'){
        cout << endl << "ERROR: DEBEN HABER TEXTO ANTES DEL ARROBA (@)" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }
    tam = strlen(_correo);
    for(int i = 0; i < tam; i++){
        if(_correo[i] == ' '){
            cout << endl << "ERROR: EL CORREO NO PUEDE TENER ESPACIOS" << endl << endl;
            system("pause");
            _DNI = -1;
            return;
        }
        if(_correo[i] == '@'){
            arroba = true;
        }
        if(arroba && _correo[i] == '.'){
            punto = true;
        }
        if(arroba && !punto && _correo[i] != '@'){
            caracteresPosArroba++;
        }
        if(arroba && punto && _correo[i] != '.'){
            caracteresPosPunto++;
        }
    }
    if(!arroba){
        cout << endl << "ERROR: EL CORREO NO POSSEE UN ARROBA (@)" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }
    if(caracteresPosArroba < 1){
        cout << endl << "ERROR: DEBEN HABER TEXTO DESPUES DEL ARROBA Y ANTES DEL PUNTO" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }
    if(!punto){
        cout << endl << "ERROR: DEBE HABER UN PUNTO (.) DESPUES DEL ARROBA" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }
    if(caracteresPosPunto < 2){
        cout << endl << "ERROR: DEBEN HABER TEXTO DESPUES DEL PUNTO QUE SIGUE DEL ARROBA (MINIMO 2 CARACTERES)" << endl << endl;
        system("pause");
        _DNI = -1;
        return;
    }

    return;
}

void Persona::Mostrar(){
    cout << "DNI: " << _DNI << endl;
    cout << "Nombre/s: " << _nombre << endl;
    cout << "Apellido/s: " << _apellido << endl;
    cout << "Genero: ";
    if(_genero == 1){
        cout << "Masculino" << endl;
    } else if(_genero == 2){
        cout << "Femenino" << endl;
    } else {
        cout << "Valor invalido" << endl;
    }
    cout << "Fecha de nacimiento: ";
    _fechaNacimiento.Mostrar();
    cout << "Numero del telefono: " << _telefono << endl;
    cout << "Correo: " << _correo << endl;
    _direccion.Mostrar();
}
