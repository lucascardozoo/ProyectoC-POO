#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Fecha.h"
#include "Direccion.h"
#include "Persona.h"
#include "Vendedor.h"
#include "Cliente.h"
#include "constantes.h"
#include "ArchivoVendedores.h"
#include "ArchivoClientes.h"

using namespace std;

///Asigna el nombre y el tamaño del vector
ArchivoClientes::ArchivoClientes(const char *nombreArchivo){
    int tam = strlen(nombreArchivo) + 1;
    _nombreArchivo = new char[tam];
    if(_nombreArchivo == nullptr){
        exit(1);
    }
    strcpy(_nombreArchivo, nombreArchivo);
    _tamanioRegistro = sizeof(Cliente);
}

char* ArchivoClientes::getNombreArchivo(){
    return _nombreArchivo;
}

int ArchivoClientes::getTamanioRegistro(){
    return _tamanioRegistro;
}

bool ArchivoClientes::CrearDeCero(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

int ArchivoClientes::BuscarRegistro(int numeroCliente, bool activosOtodos){
    FILE *pArchivo;
    Cliente registro;
    int posicion = 0;
    pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -2;
    }
    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getNumeroCliente() == numeroCliente && registro.getEstado()){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getNumeroCliente() == numeroCliente){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    }
    fclose(pArchivo);
    return -1;
}

Cliente ArchivoClientes::LeerRegistro(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return Cliente();
    }
    Cliente registro;
    fseek(pArchivo, _tamanioRegistro * posicion, SEEK_SET);
    fread(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return registro;
}

void ArchivoClientes::LeerArchivo(int cantidadRegistros, Cliente *vector){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], _tamanioRegistro, 1, pArchivo);
    }
    fclose(pArchivo);
}

bool ArchivoClientes::ListarRegistros(bool activosOtodos){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    Cliente registro;
    if(pArchivo == NULL){
        return 0;
    }

    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getEstado()){
                registro.Mostrar();
                cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
            }
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            registro.Mostrar();
            cout << endl << setfill((char) 220) << setw(42) << (char) 220 << endl << endl;
        }
    }

    fclose(pArchivo);
    return true;
}

int ArchivoClientes::ContarRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Cliente);
    fclose(pArchivo);
    return cantidadRegistros;
}

bool ArchivoClientes::GrabarRegistro(Cliente registro){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;

}

bool ArchivoClientes::EditarRegistro(Cliente registro, int posicion){
    FILE *pArchivo;
    pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return false;
    }
    fseek(pArchivo, posicion * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

Cliente ArchivoClientes::MenuModificarRegistro(Cliente registro){
    ArchivoVendedores archivoVendedores;
    Vendedor registroVendedor;
    Cliente registroCliente;
    bool coincidenciaVendedor, coincidenciaCliente, continuar, arroba = false, punto =  false;
    int opcion, DNI, genero, cantidadRegistros, tam, caracteresPosArroba = 0, caracteresPosPunto = 0, anioActualMayorDeEdad, anioActual, mesActual, diaActual, anioNacimiento, mesNacimiento, diaNacimiento;
    char nombre[50], apellido[50], correo[50], telefono[20];
    Fecha fechaNacimiento;
    Direccion direccion;

    ///OBTENGO FECHA ACTUAL Y FECHA PARA SER MAYOR DE EDAD
    time_t segDesde1970 = time(0);
    tm *pFechaActual = localtime(&segDesde1970);
    tm fechaActual = *pFechaActual;
    anioActualMayorDeEdad = (fechaActual.tm_year + 1900) - 18;
    anioActual = (fechaActual.tm_year + 1900);
    mesActual = fechaActual.tm_mon + 1;
    diaActual = fechaActual.tm_mday;

    system("cls");
    cout << "¿Que desea modificar?" << endl << endl;
    cout << "1- Numero de DNI" << endl;
    cout << "2- Nombre del cliente" << endl;
    cout << "3- Apellido del cliente" << endl;
    cout << "4- Genero del cliente" << endl;
    cout << "5- Correo del cliente" << endl;
    cout << "6- Telefono del cliente" << endl;
    cout << "7- Fecha de nacimiento del cliente" << endl;
    cout << "8- Direccion del cliente" << endl;
    cout << "0- Salir" << endl;

    cout << endl << "OPCION: ";
    cin >> opcion;
    ///Verificar si la entrada es valida
    if (cin.fail()) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        registro.setNumeroCliente(-1);
        return registro;
    }

    switch(opcion){
        case 1:
            system("cls");
            cout << "Ingrese numero de DNI: ";
            cin >> DNI;
            ///Verificar si la entrada es valida
            if (cin.fail() || DNI < 1000000 || DNI > 99999999) {
                cout << endl << "Error: Debe ingresar un numero de DNI valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroCliente(-1);
                break;
            }
            ///VERIFICACION DE SI EL DNI DEL CLIENTE YA EXISTE EN EL ARCHIVO DE VENDEDORES
            coincidenciaVendedor = false;
            cantidadRegistros = archivoVendedores.ContarRegistros();
            for(int i = 0; i < cantidadRegistros; i++){
                registroVendedor = archivoVendedores.LeerRegistro(i);
                if(registroVendedor.getDNI() == DNI){
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
                    registro.setNumeroCliente(-1);
                    break;
                }

                if(!continuar){
                    registro.setNumeroCliente(-1);
                    break;
                }
            }
            ///VERIFICACION DE SI EL DNI DEL CLIENTE YA EXISTE EN EL ARCHIVO DE CLIENTES
            coincidenciaCliente = false;
            cantidadRegistros = ContarRegistros();
            for(int i = 0; i < cantidadRegistros; i++){
                registroCliente = LeerRegistro(i);
                if(registroCliente.getDNI() == DNI){
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
                    registro.setNumeroCliente(-1);
                    break;
                }

                if(!continuar){
                    registro.setNumeroCliente(-1);
                    break;
                }
            }

            registro.setDNI(DNI);
            break;
        case 2:
            system("cls");
            cout << "Ingrese nombre del cliente (50 caracteres maximo): ";
            cin.ignore();
            cin.getline(nombre, 50);

            ///VERIFICACION DEL NOMBRE
            tam = strlen(nombre);
            if(tam < 2){
                cout << endl << "ERROR: EL NOMBRE DEBE TENER AL MENOS 2 CARACTERES" << endl;
                registro.setNumeroCliente(-1);
                break;
            }

            registro.setNombre(nombre);
            break;
        case 3:
            system("cls");
            cout << "Ingrese apellido del cliente (50 caracteres maximo): ";
            cin.ignore();
            cin.getline(apellido, 50);

            ///VERIFICACION DEL APELLIDO
            tam = strlen(apellido);
            if(tam < 2){
                cout << endl << "ERROR: EL APELLIDO DEBE TENER AL MENOS 2 CARACTERES" << endl;
                registro.setNumeroCliente(-1);
                break;
            }

            registro.setApellido(apellido);
            break;
        case 4:
            system("cls");
            cout << "Ingrese el genero (1-Masculino 2-Femenino): ";
            cin >> genero;

            ///Verificar si la entrada es valida
            if (cin.fail() || (genero != 1 && genero != 2)) {
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setNumeroCliente(-1);
                break;
            }

            registro.setGenero(genero);
            break;
        case 5:
            system("cls");
            cout << "Ingrese correo del cliente: ";
            cin.ignore();
            cin.getline(correo, 50);

            ///VERIFICACION DEL CORREO
            if(correo[0] == '@'){
                cout << endl << "ERROR: DEBEN HABER TEXTO ANTES DEL ARROBA (@)" << endl;
                registro.setNumeroCliente(-1);
                break;
            }
            tam = strlen(correo);
            for(int i = 0; i < tam; i++){
                if(correo[i] == ' '){
                    cout << endl << "ERROR: EL CORREO NO PUEDE TENER ESPACIOS" << endl;
                    registro.setNumeroCliente(-1);
                    return registro;
                }
                if(correo[i] == '@'){
                    arroba = true;
                }
                if(arroba && correo[i] == '.'){
                    punto = true;
                }
                if(arroba && !punto && correo[i] != '@'){
                    caracteresPosArroba++;
                }
                if(arroba && punto && correo[i] != '.'){
                    caracteresPosPunto++;
                }
            }
            if(!arroba){
                cout << endl << "ERROR: EL CORREO NO POSSEE UN ARROBA (@)" << endl;
                registro.setNumeroCliente(-1);
                break;
            }
            if(caracteresPosArroba < 1){
                cout << endl << "ERROR: DEBEN HABER TEXTO DESPUES DEL ARROBA Y ANTES DEL PUNTO" << endl;
                registro.setNumeroCliente(-1);
                break;
            }
            if(!punto){
                cout << endl << "ERROR: DEBE HABER UN PUNTO (.) DESPUES DEL ARROBA" << endl;
                registro.setNumeroCliente(-1);
                break;
            }
            if(caracteresPosPunto < 2){
                cout << endl << "ERROR: DEBEN HABER TEXTO DESPUES DEL PUNTO QUE SIGUE DEL ARROBA (MINIMO 2 CARACTERES)" << endl;
                registro.setNumeroCliente(-1);
                break;
            }

            registro.setCorreo(correo);
            break;
        case 6:
            system("cls");
            cout << "Ingrese telefono del cliente: ";
            cin.ignore();
            cin.getline(telefono, 20);

            ///VERIFICACION DEL TELEFONO
            tam = strlen(telefono);
            if(tam < 7){
                cout << endl << "ERROR: EL NUMERO DEBE TENER AL MENOS 7 DIGITOS" << endl;
                registro.setNumeroCliente(-1);
                break;
            }

            registro.setTelefono(telefono);
            break;
        case 7:
            system("cls");
            cout << "Ingrese fecha de nacimiento del cliente: " << endl;
            fechaNacimiento.Cargar();
            if(fechaNacimiento.getAnio() == -1){
                registro.setNumeroCliente(-1);
                break;
            }

            anioNacimiento = fechaNacimiento.getAnio();
            mesNacimiento = fechaNacimiento.getMes();
            diaNacimiento = fechaNacimiento.getDia();

            ///Verificamos fecha que no sea mayor a la actual
            if (anioNacimiento > anioActual || (anioNacimiento == anioActual && mesNacimiento > mesActual) || (anioNacimiento == anioActual && mesNacimiento == mesActual && diaNacimiento > diaActual)) {
                cout << endl << "LA FECHA NO PUEDE SER MAYOR A LA ACTUAL" << endl;
                registro.setNumeroCliente(-1);
                break;
            }

            ///Verificamos fecha actual para ser mayor de edad
            if (anioNacimiento > anioActualMayorDeEdad || (anioNacimiento == anioActualMayorDeEdad && mesNacimiento > mesActual) || (anioNacimiento == anioActualMayorDeEdad && mesNacimiento == mesActual && diaNacimiento > diaActual)) {
                cout << endl << "EL CLIENTE NO ES MAYOR DE EDAD" << endl << endl;
                cout << "DESEA CONTINUAR? 1-SI 0-NO: ";
                cin >> continuar;
                ///Verificar si la entrada es valida
                if (cin.fail() || (continuar != 0 && continuar != 1)) {
                    cout << endl << "Error: Debe ingresar un valor valido." << endl;
                    cin.clear();//Limpia el estado de error
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                    registro.setNumeroCliente(-1);
                    break;
                }

                if(!continuar){
                    registro.setNumeroCliente(-1);
                    break;
                }
            }

            registro.setFechaNacimiento(fechaNacimiento);
            break;
        case 8:
            system("cls");
            cout << "Ingrese direccion del cliente: " << endl;
            cin.ignore();
            direccion.Cargar();

            if(direccion.getCodigoPostal() == -1){
                registro.setNumeroCliente(-1);
                cout << endl;
                break;
            }

            registro.setDireccion(direccion);
            break;
        case 0:
            registro.setNumeroCliente(-1);
            break;
        default:
            cout << endl << "Opcion no valida." << endl;
            registro.setNumeroCliente(-1);
            break;
    }

    return registro;
}

bool ArchivoClientes::ModificarRegistro(){
    Cliente registro;
    int numeroCliente;
    cout << "INGRESAR NUMERO DE CLIENTE A MODIFICAR: ";
    cin >> numeroCliente;
    int posicion = BuscarRegistro(numeroCliente, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || numeroCliente < 1) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NUMERO DE CLIENTE INEXISTENTE" << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE CLIENTES" << endl;
        return false;
    }

    registro = LeerRegistro(posicion);

    registro = MenuModificarRegistro(registro);
    if(registro.getNumeroCliente() == -1){
        return true;
    }

    if(EditarRegistro(registro, posicion)){
        cout << endl << "SE MODIFICO EXITOSAMENTE EL REGISTRO DEL CLIENTE" << endl;
        return true;
    } else {
        cout << endl << "ERROR AL MODIFICAR EL REGISTRO DEL CLIENTE" << endl;
        return false;
    }
}

bool ArchivoClientes::AltaRegistro(){
    Cliente registro;
    int numeroCliente;
    cout << "INGRESAR NUMERO DE CLIENTE A DAR DE ALTA: ";
    cin >> numeroCliente;
    int posicion = BuscarRegistro(numeroCliente, ACTIVOS);
    if(posicion >= 0){
        cout << "YA EXISTE UN CLIENTE CON ESTE NUMERO DE CLIENTE, NO PODES DAR DE ALTA UN CLIENTE CON NUMERO DE CLIENTE EXISTENTE" << endl;
        return false;
    }
    registro.Cargar();
    if(GrabarRegistro(registro)){
        cout << "SE DIO DE ALTA EL REGISTRO" << endl;
        return true;
    } else {
        cout << "NO SE DIO DE ALTA EL REGISTRO" << endl;
        return false;
    }
}

bool ArchivoClientes::BajaRegistro(){
    Cliente registro;
    int numeroCliente;
    cout << "INGRESAR NUMERO DE CLIENTE A DAR DE BAJA: ";
    cin >> numeroCliente;
    if (cin.fail() || numeroCliente < 1) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        return false;
    }

    int posicion = BuscarRegistro(numeroCliente, ACTIVOS);
    if(posicion == -1){
        cout << endl << "NUMERO DE CLIENTE INEXISTENTE" << endl << endl;
        return false;
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO CLIENTES" << endl << endl;
        return false;
    }
    registro = LeerRegistro(posicion);
    registro.setEstado(false);
    if(EditarRegistro(registro, posicion)){
        cout << endl << "BAJA DE CLIENTE EXITOSA" << endl << endl;
        return true;
    } else {
        cout << endl << "ERROR AL DAR DE BAJA EL CLIENTE" << endl << endl;
        return false;
    }
}

ArchivoClientes::~ArchivoClientes(){
    delete []_nombreArchivo;
}
