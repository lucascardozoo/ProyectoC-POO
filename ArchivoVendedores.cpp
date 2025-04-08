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
#include "ArchivoClientes.h"
#include "ArchivoVendedores.h"

using namespace std;

///Asigna el nombre y el tamaño del vector
ArchivoVendedores::ArchivoVendedores(const char *nombreArchivo){
    int tam = strlen(nombreArchivo) + 1;
    _nombreArchivo = new char[tam];
    if(_nombreArchivo == nullptr){
        exit(1);
    }
    strcpy(_nombreArchivo, nombreArchivo);
    _tamanioRegistro = sizeof(Vendedor);
}

char* ArchivoVendedores::getNombreArchivo(){
    return _nombreArchivo;
}

int ArchivoVendedores::getTamanioRegistro(){
    return _tamanioRegistro;
}

bool ArchivoVendedores::CrearDeCero(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

int ArchivoVendedores::BuscarRegistro(int legajoVendedor, bool activosOtodos){
    FILE *pArchivo;
    Vendedor registro;
    int posicion = 0;
    pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -2;
    }
    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getLegajoVendedor() == legajoVendedor && registro.getEstado()){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getLegajoVendedor() == legajoVendedor){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    }
    fclose(pArchivo);
    return -1;
}

Vendedor ArchivoVendedores::LeerRegistro(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return Vendedor();
    }
    Vendedor registro;
    fseek(pArchivo, _tamanioRegistro * posicion, SEEK_SET);
    fread(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return registro;
}

void ArchivoVendedores::LeerArchivo(int cantidadRegistros, Vendedor *vector){
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

bool ArchivoVendedores::ListarRegistros(bool activosOtodos){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    Vendedor registro;
    if(pArchivo == NULL){
        return false;
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

int ArchivoVendedores::ContarRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Vendedor);
    fclose(pArchivo);
    return cantidadRegistros;
}

bool ArchivoVendedores::GrabarRegistro(Vendedor registro){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;

}

bool ArchivoVendedores::EditarRegistro(Vendedor registro, int posicion){
    FILE *pArchivo;
    pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        cout << endl << "NO SE PUDO ABRIR EL ARCHIVO" << endl << endl;
        return false;
    }
    fseek(pArchivo, posicion * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

Vendedor ArchivoVendedores::MenuModificarRegistro(Vendedor registro){
    ArchivoClientes archivoClientes;
    Vendedor registroVendedor;
    Cliente registroCliente;
    bool coincidenciaVendedor, coincidenciaCliente, continuar, arroba = false, punto = false;
    int opcion, DNI, genero, cantidadRegistros, tam, caracteresPosArroba = 0, caracteresPosPunto = 0, anioActualMayorDeEdad, anioActual, mesActual, diaActual, anioIngreso, mesIngreso, diaIngreso, anioNacimiento, mesNacimiento, diaNacimiento;
    float sueldo;
    char nombre[50], apellido[50], correo[50], telefono[20];
    Fecha fechaNacimiento, fechaIngreso;
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
    cout << "2- Nombre del vendedor" << endl;
    cout << "3- Apellido del vendedor" << endl;
    cout << "4- Genero del vendedor" << endl;
    cout << "5- Sueldo del vendedor" << endl;
    cout << "6- Correo del vendedor" << endl;
    cout << "7- Telefono del vendedor" << endl;
    cout << "8- Fecha de ingreso del vendedor" << endl;
    cout << "9- Fecha de nacimiento del vendedor" << endl;
    cout << "10- Direccion del vendedor" << endl;
    cout << "0- Salir" << endl;

    cout << endl << "OPCION: ";
    cin >> opcion;
    ///Verificar si la entrada es valida
    if (cin.fail()) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        registro.setLegajoVendedor(-1);
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
                registro.setLegajoVendedor(-1);
                break;
            }
            ///VERIFICACION DE SI EL DNI DEL VENDEDOR YA EXISTE EN EL ARCHIVO DE VENDEDORES
            coincidenciaVendedor = false;
            cantidadRegistros = ContarRegistros();
            for(int i = 0; i < cantidadRegistros; i++){
                registroVendedor = LeerRegistro(i);
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
                    registro.setLegajoVendedor(-1);
                    break;
                }

                if(!continuar){
                    registro.setLegajoVendedor(-1);
                    break;
                }
            }
            ///VERIFICACION DE SI EL DNI DEL VENDEDOR YA EXISTE EN EL ARCHIVO DE CLIENTES
            coincidenciaCliente = false;
            cantidadRegistros = archivoClientes.ContarRegistros();
            for(int i = 0; i < cantidadRegistros; i++){
                registroCliente = archivoClientes.LeerRegistro(i);
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
                    registro.setLegajoVendedor(-1);
                    break;
                }

                if(!continuar){
                    registro.setLegajoVendedor(-1);
                    break;
                }
            }

            registro.setDNI(DNI);
            break;
        case 2:
            system("cls");
            cout << "Ingrese nombre del vendedor (50 caracteres maximo): ";
            cin.ignore();
            cin.getline(nombre, 50);

            ///VERIFICACION DEL NOMBRE
            tam = strlen(nombre);
            if(tam < 2){
                cout << endl << "ERROR: EL NOMBRE DEBE TENER AL MENOS 2 CARACTERES" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setNombre(nombre);
            break;
        case 3:
            system("cls");
            cout << "Ingrese apellido del vendedor (50 caracteres maximo): ";
            cin.ignore();
            cin.getline(apellido, 50);

            ///VERIFICACION DEL APELLIDO
            tam = strlen(apellido);
            if(tam < 2){
                cout << endl << "ERROR: EL APELLIDO DEBE TENER AL MENOS 2 CARACTERES" << endl;
                registro.setLegajoVendedor(-1);
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
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setGenero(genero);
            break;
        case 5:
            system("cls");
            cout << "Ingrese sueldo del vendedor: ";
            cin >> sueldo;

            ///Verificar si la entrada es valida
            if (cin.fail() || sueldo < 0) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setSueldo(sueldo);
            break;
        case 6:
            system("cls");
            cout << "Ingrese correo del vendedor: ";
            cin.ignore();
            cin.getline(correo, 50);

            ///VERIFICACION DEL CORREO
            if(correo[0] == '@'){
                cout << endl << "ERROR: DEBEN HABER TEXTO ANTES DEL ARROBA (@)" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }
            tam = strlen(correo);
            for(int i = 0; i < tam; i++){
                if(correo[i] == ' '){
                    cout << endl << "ERROR: EL CORREO NO PUEDE TENER ESPACIOS" << endl;
                    registro.setLegajoVendedor(-1);
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
                registro.setLegajoVendedor(-1);
                break;
            }
            if(caracteresPosArroba < 1){
                cout << endl << "ERROR: DEBEN HABER TEXTO DESPUES DEL ARROBA Y ANTES DEL PUNTO" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }
            if(!punto){
                cout << endl << "ERROR: DEBE HABER UN PUNTO (.) DESPUES DEL ARROBA" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }
            if(caracteresPosPunto < 2){
                cout << endl << "ERROR: DEBEN HABER TEXTO DESPUES DEL PUNTO QUE SIGUE DEL ARROBA (MINIMO 2 CARACTERES)" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setCorreo(correo);
            break;
        case 7:
            system("cls");
            cout << "Ingrese telefono del vendedor: ";
            cin.ignore();
            cin.getline(telefono, 20);

            ///VERIFICACION DEL TELEFONO
            tam = strlen(telefono);
            if(tam < 7){
                cout << endl << "ERROR: EL NUMERO DEBE TENER AL MENOS 7 DIGITOS" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setTelefono(telefono);
            break;
        case 8:
            system("cls");
            cout << "Ingrese fecha de ingreso del vendedor: " << endl << endl;
            fechaIngreso.Cargar();

            if(fechaIngreso.getAnio() == -1){
                registro.setLegajoVendedor(-1);
                break;
            }
            ///Verificamos fecha que no sea mayor a la actual
            anioIngreso = fechaIngreso.getAnio();
            mesIngreso = fechaIngreso.getMes();
            diaIngreso = fechaIngreso.getDia();
            if (anioIngreso > anioActual || (anioIngreso == anioActual && mesIngreso > mesActual) || (anioIngreso == anioActual && mesIngreso == mesActual && diaIngreso > diaActual)) {
                cout << endl << "LA FECHA NO PUEDE SER MAYOR A LA ACTUAL" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setFechaIngreso(fechaIngreso);
            break;
        case 9:
            system("cls");
            cout << "Ingrese fecha de nacimiento del vendedor: " << endl << endl;
            fechaNacimiento.Cargar();

            if(fechaNacimiento.getAnio() == -1){
                registro.setLegajoVendedor(-1);
                break;
            }

            anioNacimiento = fechaNacimiento.getAnio();
            mesNacimiento = fechaNacimiento.getMes();
            diaNacimiento = fechaNacimiento.getDia();

            ///Verificamos fecha que no sea mayor a la actual
            if (anioNacimiento > anioActual || (anioNacimiento == anioActual && mesNacimiento > mesActual) || (anioNacimiento == anioActual && mesNacimiento == mesActual && diaNacimiento > diaActual)) {
                cout << endl << "LA FECHA NO PUEDE SER MAYOR A LA ACTUAL" << endl;
                registro.setLegajoVendedor(-1);
                break;
            }

            ///Verificamos fecha actual para ser mayor de edad
            if (anioNacimiento > anioActualMayorDeEdad || (anioNacimiento == anioActualMayorDeEdad && mesNacimiento > mesActual) || (anioNacimiento == anioActualMayorDeEdad && mesNacimiento == mesActual && diaNacimiento > diaActual)) {
                cout << endl << "EL VENDEDOR NO ES MAYOR DE EDAD" << endl << endl;
                cout << "DESEA CONTINUAR? 1-SI 0-NO: ";
                cin >> continuar;
                ///Verificar si la entrada es valida
                if (cin.fail() || (continuar != 0 && continuar != 1)) {
                    cout << endl << "Error: Debe ingresar un valor valido." << endl;
                    cin.clear();//Limpia el estado de error
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                    registro.setLegajoVendedor(-1);
                    break;
                }

                if(!continuar){
                    registro.setLegajoVendedor(-1);
                    break;
                }
            }

            registro.setFechaNacimiento(fechaNacimiento);
            break;
        case 10:
            system("cls");
            cout << "Ingrese direccion del vendedor: " << endl << endl;
            cin.ignore();
            direccion.Cargar();

            if(direccion.getCodigoPostal() == -1){
                registro.setLegajoVendedor(-1);
                break;
            }

            registro.setDireccion(direccion);
            break;
        case 0:
            registro.setLegajoVendedor(-1);
            break;
        default:
            cout << endl << "Opcion no valida." << endl;
            registro.setLegajoVendedor(-1);
            break;
    }

    return registro;
}

bool ArchivoVendedores::ModificarRegistro(){
    Vendedor registro;
    int legajoVendedor;

    cout << "INGRESAR LEGAJO DE VENDEDOR A MODIFICAR: ";
    cin >> legajoVendedor;
    int posicion = BuscarRegistro(legajoVendedor, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || legajoVendedor < 1) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else{
            cout << endl << "NO EXISTE UN VENDEDOR REGISTRADO CON ESTE LEGAJO" << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE VENDEDORES" << endl;
        return false;
    }

    registro = LeerRegistro(posicion);

    registro = MenuModificarRegistro(registro);
    if(registro.getLegajoVendedor() == -1){
        return true;
    }

    if(EditarRegistro(registro, posicion)){
        cout << endl << "SE MODIFICO EXITOSAMENTE EL REGISTRO DEL VENDEDOR" << endl;
        return true;
    } else {
        cout << endl << "ERROR AL MODIFICAR EL REGISTRO DEL VENDEDOR" << endl;
        return false;
    }
}

bool ArchivoVendedores::AltaRegistro(){
    Vendedor registro;
    int legajoVendedor;
    cout << "INGRESAR LEGAJO DE VENDEDOR A DAR DE ALTA: ";
    cin >> legajoVendedor;
    int posicion = BuscarRegistro(legajoVendedor, ACTIVOS);
    if(posicion >= 0){
        cout << endl << "YA EXISTE UN VENDEDOR CON ESTE LEGAJO, NO PODES DAR DE ALTA UN VENDEDOR CON LEGAJO EXISTENTE" << endl << endl;
        return false;
    }
    registro.Cargar();
    if(GrabarRegistro(registro)){
        cout << endl << "SE DIO DE ALTA EL REGISTRO" << endl;
        return true;
    } else {
        cout << endl << "NO SE DIO DE ALTA EL REGISTRO" << endl;
        return false;
    }
}

bool ArchivoVendedores::BajaRegistro(){
    Vendedor registro;
    int legajoVendedor;
    cout << "INGRESAR LEGAJO DE VENDEDOR A DAR DE BAJA: ";
    cin >> legajoVendedor;
    int posicion = BuscarRegistro(legajoVendedor, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || legajoVendedor < 1) {
            cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "LEGAJO DE VENDEDOR INEXISTENTE" << endl << endl;
            return false;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO VENDEDOR" << endl << endl;
        return false;
    }
    registro = LeerRegistro(posicion);
    registro.setEstado(false);
    if(EditarRegistro(registro, posicion)){
        cout << endl << "BAJA DE VENDEDOR EXITOSA" << endl << endl;
        return true;
    } else {
        cout << endl << "ERROR AL DAR DE BAJA EL VENDEDOR" << endl << endl;
        return false;
    }
}

ArchivoVendedores::~ArchivoVendedores(){
    delete []_nombreArchivo;
}
