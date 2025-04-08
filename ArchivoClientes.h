#pragma once

class ArchivoClientes
{
    private:
        char *_nombreArchivo;
        int _tamanioRegistro;
    public:
        ArchivoClientes(const char *nombreArchivo = "ArchivoClientes.dat");

        char* getNombreArchivo();
        int getTamanioRegistro();

        bool CrearDeCero();
        int BuscarRegistro(int numeroCliente,bool activosOtodos);
        Cliente LeerRegistro(int posicion);
        void LeerArchivo(int cantidadRegistros, Cliente *vector);
        bool ListarRegistros(bool activosOtodos);
        int ContarRegistros();
        bool GrabarRegistro(Cliente registro);
        bool EditarRegistro(Cliente registro, int posicion);
        Cliente MenuModificarRegistro(Cliente registro);
        bool ModificarRegistro();
        bool AltaRegistro();
        bool BajaRegistro();

        ~ArchivoClientes();
};

