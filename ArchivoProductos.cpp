#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Producto.h"
#include "constantes.h"
#include "ArchivoProductos.h"

using namespace std;

///Asigna el nombre y el tamaño del vector
ArchivoProductos::ArchivoProductos(const char *nombreArchivo){
    int tam = strlen(nombreArchivo) + 1;
    _nombreArchivo = new char[tam];
    if(_nombreArchivo == nullptr){
        exit(1);
    }
    strcpy(_nombreArchivo, nombreArchivo);
    _tamanioRegistro = sizeof(Producto);
}

char* ArchivoProductos::getNombreArchivo(){
    return _nombreArchivo;
}

int ArchivoProductos::getTamanioRegistro(){
    return _tamanioRegistro;
}

bool ArchivoProductos::CrearDeCero(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

int ArchivoProductos::BuscarRegistro(int idProducto, bool activosOtodos){
    FILE *pArchivo;
    Producto registro;
    int posicion = 0;
    pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -2;
    }
    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getIdProducto() == idProducto && registro.getEstado()){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getIdProducto() == idProducto){
                fclose(pArchivo);
                return posicion;
            }
            posicion++;
        }
    }
    fclose(pArchivo);
    return -1;
}

Producto ArchivoProductos::LeerRegistro(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        cout << "NO SE PUDO ABRIR EL ARCHIVO" << endl;
        return Producto();
    }
    Producto registro;
    fseek(pArchivo, _tamanioRegistro * posicion, SEEK_SET);
    fread(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return registro;
}

void ArchivoProductos::LeerArchivo(int cantidadRegistros, Producto *vector){
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

bool ArchivoProductos::ListarRegistros(bool activosOtodos){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    Producto registro;
    if(pArchivo == NULL){
        cout << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS" << endl << endl;
        return 0;
    }

    if(activosOtodos){
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            if(registro.getEstado()){
                registro.Mostrar();
                cout << endl << setfill((char) 220) << setw(100) << (char) 220 << endl << endl;
            }
        }
    } else {
        while(fread(&registro, _tamanioRegistro, 1, pArchivo) == 1){
            registro.Mostrar();
            cout << endl << setfill((char) 220) << setw(100) << (char) 220 << endl << endl;
        }
    }

    fclose(pArchivo);
    return true;
}

int ArchivoProductos::ContarRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Producto);
    fclose(pArchivo);
    return cantidadRegistros;
}

bool ArchivoProductos::GrabarRegistro(Producto registro){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;

}

bool ArchivoProductos::EditarRegistro(Producto registro, int posicion){
    FILE *pArchivo;
    pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        cout << "ERROR AL ABRIR EL ARCHIVO PRODUCTOS" << endl << endl;
        return false;
    }
    fseek(pArchivo, posicion * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&registro, _tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

Producto ArchivoProductos::MenuModificarRegistro(Producto registro){
    int opcion, cantidad, categoria, tam;
    float precio;
    char descripcion[100], nombre[50];

    system("cls");
    cout << "¿Que desea hacer?" << endl << endl;
    cout << "1- Aumetar Stock del producto" << endl;
    cout << "2- Disminuir Stock del producto" << endl;
    cout << "3- Modificar Stock del producto" << endl;
    cout << "4- Modificar la categoria del producto" << endl;
    cout << "5- Modificar el nombre del producto" << endl;
    cout << "6- Modificar la descripcion del producto" << endl;
    cout << "7- Modificar el precio del producto" << endl;
    cout << "0- Salir" << endl;

    cout << endl << "OPCION: ";
    cin >> opcion;
    ///Verificar si la entrada es valida
    if (cin.fail()) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl;
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        registro.setIdProducto(-1);
        return registro;
    }

    switch(opcion){
        case 1:
            system("cls");
            cout << "Ingrese la cantidad que desea aumetar del stock: ";
            cin >> cantidad;
            ///Verificar si la entrada es valida
            if (cin.fail() || cantidad < 1) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setIdProducto(-1);
                break;
            }

            registro += cantidad;
            break;
        case 2:
            system("cls");
            cout << "Ingrese la cantidad que desea disminuir del stock: ";
            cin >> cantidad;
            ///Verificar si la entrada es valida
            if (cin.fail() || cantidad < 1) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setIdProducto(-1);
                break;
            }

            registro -= cantidad;
            break;
        case 3:
            system("cls");
            cout << "Ingrese la nueva cantidad total del stock: ";
            cin >> cantidad;
            ///Verificar si la entrada es valida
            if (cin.fail() || cantidad < 0) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setIdProducto(-1);
                break;
            }

            registro.setStockProducto(cantidad);
            break;
        case 4:
            system("cls");
            cout << "Elija una categoria" << endl << endl;
            cout << "1- Zapatillas" << endl;
            cout << "2- Remeras" << endl;
            cout << "3- Buzos" << endl;
            cout << "4- Shorts" << endl;

            cout << endl << "OPCION: ";
            cin >> categoria;
            ///Verificar si la entrada es valida
            if (cin.fail() || (categoria != 1 && categoria != 2 && categoria != 3 && categoria != 4)) {
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setIdProducto(-1);
                break;
            }

            registro.setCategoriaProducto(categoria);
            break;
        case 5:
            system("cls");
            cout << "Ingrese el nuevo nombre del producto (50 caracteres maximo): ";
            cin.ignore();
            cin.getline(nombre, 50);
            ///VERIFICACION DEL NOMBRE
            tam = strlen(nombre);
            if(tam < 2){
                cout << endl << "ERROR: EL NOMBRE DEBE TENER AL MENOS 2 CARACTERES" << endl;
                registro.setIdProducto(-1);
                break;
            }

            registro.setNombreProducto(nombre);
            break;
        case 6:
            system("cls");
            cout << "Ingrese la nueva descripcion del producto (100 caracteres maximo): ";
            cin.ignore();
            cin.getline(descripcion, 100);
            ///VERIFICACION DEL NOMBRE
            tam = strlen(descripcion);
            if(tam < 2){
                cout << endl << "ERROR: LA DESCRIPCION DEBE TENER AL MENOS 2 CARACTERES" << endl;
                registro.setIdProducto(-1);
                break;
            }

            registro.setDescripcionProducto(descripcion);
            break;
        case 7:
            system("cls");
            cout << "Ingrese el nuevo precio del producto: ";
            cin >> precio;
            ///VERIFICACION DEL PRECIO
            if (cin.fail() || precio < 0) {//Verificar si la entrada es válida
                cout << endl << "Error: Debe ingresar un valor valido." << endl;
                cin.clear();//Limpia el estado de error
                cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
                registro.setIdProducto(-1);
                break;
            }

            registro.setPrecioProducto(precio);
            break;
        case 0:
            registro.setIdProducto(-1);
            break;
        default:
            cout << endl << "Opcion no valida." << endl;
            registro.setIdProducto(-1);
            break;
    }

    return registro;
}

bool ArchivoProductos::ModificarRegistro(){
    Producto registro;
    int IDProducto;
    cout << "INGRESAR ID DEL PRODUCTO A MODIFICAR: ";
    cin >> IDProducto;
    int posicion = BuscarRegistro(IDProducto, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || IDProducto < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "ID DE PRODUCTO INEXISTENTE" << endl;
            return false;
        }
    } else if (posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS"<< endl;
        return false;
    }

    registro = LeerRegistro(posicion);

    registro = MenuModificarRegistro(registro);
    if(registro.getIdProducto() == -1){
        return true;
    }

    if(EditarRegistro(registro, posicion)){
        cout << endl << "SE MODIFICO EXITOSAMENTE EL REGISTRO DEL PRODUCTO" << endl;
        return true;
    } else {
        cout << endl << "ERROR AL MODIFICAR EL REGISTRO DEL PRODUCTO" << endl;
        return false;
    }
}

bool ArchivoProductos::AltaRegistro(){
    Producto registro;
    int IDProducto;
    cout << "INGRESAR ID DEL PRODUCTO A DAR DE ALTA: ";
    cin >> IDProducto;
    int posicion = BuscarRegistro(IDProducto, ACTIVOS);
    if(posicion >= 0){
        cout << endl << "YA EXISTE UN PRODUCTO CON ESTE ID, NO PODES DAR DE ALTA UN PRODUCTO CON ID EXISTENTE" << endl << endl;
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

bool ArchivoProductos::BajaRegistro(){
    Producto registro;
    int IDProducto;
    cout << "INGRESAR ID DEL PRODUCTO A DAR DE BAJA: ";
    cin >> IDProducto;
    int posicion = BuscarRegistro(IDProducto, ACTIVOS);
    if(posicion == -1){
        if (cin.fail() || IDProducto < 1) {//Verificar si la entrada es válida
            cout << endl << "Error: Debe ingresar un valor valido." << endl;
            cin.clear();//Limpia el estado de error
            cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
            return false;
        } else {
            cout << endl << "NO EXISTE UN REGISTRO CON ESTE ID DE PRODUCTO" << endl;
            return false;
        }
    } else if(posicion == -2){
        cout << endl << "ERROR AL ABRIR EL ARCHIVO DE PRODUCTO" << endl;
        return false;
    }
    registro = LeerRegistro(posicion);
    registro.setEstado(false);
    if(EditarRegistro(registro, posicion)){
        cout << endl << "BAJA DE PRODUCTO EXITOSA" << endl;
        return true;
    } else {
        cout << endl << "ERROR AL DAR DE BAJA EL REGISTRO DEL PRODUCTO" << endl;
        return false;
    }
}

ArchivoProductos::~ArchivoProductos(){
    delete []_nombreArchivo;
}
