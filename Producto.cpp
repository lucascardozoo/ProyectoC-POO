#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>//Para numeric_limits

#include "Producto.h"
#include "constantes.h"
#include "ArchivoProductos.h"

using namespace std;

Producto::Producto(){
    _idProducto = 0;
    _stockProducto = 0;
    _categoriaProducto = 0;
    strcpy(_nombreProducto, "Sin nombre");
    strcpy(_descripcionProducto, "Sin descripcion");
    _precioProducto = 0.0;
    _estado = false;
}

int Producto::getIdProducto(){
    return _idProducto;
}

int Producto::getCategoriaProducto(){
    return _categoriaProducto;
}

const char* Producto::getNombreProducto(){
    return _nombreProducto;
}

const char* Producto::getDescripcionProducto(){
    return _descripcionProducto;
}

float Producto::getPrecioProducto(){
    return _precioProducto;
}

int Producto::getStockProducto(){
    return _stockProducto;
}

bool Producto::getEstado(){
    return _estado;
}

void Producto::setIdProducto(int idProducto){
    _idProducto = idProducto;
}

void Producto::setCategoriaProducto(int categoriaProducto){
    _categoriaProducto = categoriaProducto;
}

void Producto::setNombreProducto(const char* nombreProducto){
    strcpy(_nombreProducto, nombreProducto);
}

void Producto::setDescripcionProducto(const char* descripcionProducto){
    strcpy(_descripcionProducto, descripcionProducto);
}

void Producto::setPrecioProducto(float precioProducto){
    _precioProducto = precioProducto;
}

void Producto::setStockProducto(int stockProducto){
    _stockProducto = stockProducto;
}

void Producto::setEstado(bool estado){
    _estado = estado;
}

void Producto::asignacionIDProducto(){
    ArchivoProductos archivoProductos;
    int cantidadRegistros = archivoProductos.ContarRegistros();
    _idProducto = cantidadRegistros + 1;
}

void Producto::Cargar(){
    asignacionIDProducto();

    cout << "1- Zapatillas" << endl;
    cout << "2- Remeras" << endl;
    cout << "3- Buzos" << endl;
    cout << "4- Shorts" << endl << endl;
    cout << "Ingrese una categoria para el producto: ";
    cin >> _categoriaProducto;
    ///Verificar si la entrada es valida
    if (cin.fail() || (_categoriaProducto != 1 && _categoriaProducto != 2 && _categoriaProducto != 3 && _categoriaProducto != 4)) {
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        system("pause");
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _idProducto = -1;
        return;
    }

    cout << "Ingrese el nombre del producto (50 caracteres maximo): ";
    cin.ignore();
    cin.getline(_nombreProducto, 50);
    ///VERIFICACION DEL NOMBRE
    int tam = strlen(_nombreProducto);
    if(tam < 2){
        cout << endl << "ERROR: EL NOMBRE DEBE TENER AL MENOS 2 CARACTERES" << endl << endl;
        system("pause");
        _idProducto = -1;
        return;
    }

    cout << "Ingrese la descripcion del producto (100 caracteres maximo): ";
    cin.getline(_descripcionProducto, 100);
    ///VERIFICACION DEL DESCRIPCION
    tam = strlen(_descripcionProducto);
    if(tam < 2){
        cout << endl << "ERROR: LA DESCRIPCION DEBE TENER AL MENOS 2 CARACTERES" << endl << endl;
        system("pause");
        _idProducto = -1;
        return;
    }

    cout << "Ingrese el precio del producto: ";
    cin >> _precioProducto;
    ///VERIFICACION DEL PRECIO
    if (cin.fail() || _precioProducto < 0) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        system("pause");
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _idProducto = -1;
        return;
    }

    cout << "Ingrese el stock del producto: ";
    cin >> _stockProducto;
    ///VERIFICACION DEL STOCK
    if (cin.fail() || _stockProducto < 0) {//Verificar si la entrada es válida
        cout << endl << "Error: Debe ingresar un valor valido." << endl << endl;
        system("pause");
        cin.clear();//Limpia el estado de error
        cin.ignore(numeric_limits <streamsize>::max(), '\n');//Ignora el resto de la entrada para evitar bucles infinitos
        _idProducto = -1;
        return;
    }

    _estado = true;
}

void Producto::Mostrar(){
    cout << "ID del producto: " << _idProducto << endl;
    cout << "Categoria del producto: ";
    switch(_categoriaProducto){
        case 1:
            cout << "Zapatillas" << endl;
            break;
        case 2:
            cout << "Remeras" << endl;
            break;
        case 3:
            cout << "Buzos" << endl;
            break;
        case 4:
            cout << "Shorts" << endl;
            break;
        default:
            cout << "Valor invalido" << endl;
            break;
    }
    cout << "Nombre del producto: " << _nombreProducto << endl;
    cout << "Descripcion del producto: " << _descripcionProducto << endl;
    cout << fixed << setprecision(2) << "Precio del producto: $" << _precioProducto << endl;
    cout << "Stock del producto: " << _stockProducto << endl;
    if (_estado){
        cout << "Estado del producto: Activo" << endl;
    } else {
        cout << "Estado del producto: Desactivo" << endl;
    }
}

void Producto::operator+=(int cantidadStock){
    _stockProducto += cantidadStock;
}

void Producto::operator-=(int cantidadStock){
    _stockProducto -= cantidadStock;
}
