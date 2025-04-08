#pragma once

class ArchivoProductos
{
    private:
        char *_nombreArchivo;
        int _tamanioRegistro;
    public:
        ArchivoProductos(const char *nombreArchivo = "ArchivoProductos.dat");

        char* getNombreArchivo();
        int getTamanioRegistro();

        bool CrearDeCero();
        int BuscarRegistro(int idProducto,bool activosOtodos);
        Producto LeerRegistro(int posicion);
        void LeerArchivo(int cantidadRegistros, Producto *vector);
        bool ListarRegistros(bool activosOtodos);
        int ContarRegistros();
        bool GrabarRegistro(Producto registro);
        bool EditarRegistro(Producto registro, int posicion);
        Producto MenuModificarRegistro(Producto registro);
        bool ModificarRegistro();
        bool AltaRegistro();
        bool BajaRegistro();

        ~ArchivoProductos();
};
