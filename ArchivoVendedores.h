#pragma once

class ArchivoVendedores
{
    private:
        char *_nombreArchivo;
        int _tamanioRegistro;
    public:
        ArchivoVendedores(const char *nombreArchivo = "ArchivoVendedores.dat");

        char* getNombreArchivo();
        int getTamanioRegistro();

        bool CrearDeCero();
        int BuscarRegistro(int legajoVendedor,bool activosOtodos);
        Vendedor LeerRegistro(int posicion);
        void LeerArchivo(int cantidadRegistros, Vendedor *vector);
        bool ListarRegistros(bool activosOtodos);
        int ContarRegistros();
        bool GrabarRegistro(Vendedor registro);
        bool EditarRegistro(Vendedor registro, int posicion);
        Vendedor MenuModificarRegistro(Vendedor registro);
        bool ModificarRegistro();
        bool AltaRegistro();
        bool BajaRegistro();

        ~ArchivoVendedores();
};
