#pragma once

class ArchivoVentaCabecera
{
    private:
        char *_nombreArchivo;
        int _tamanioRegistro;
    public:
        ArchivoVentaCabecera(const char *nombreArchivo = "ArchivoVentaCabecera.dat");

        char* getNombreArchivo();
        int getTamanioRegistro();

        bool CrearDeCero();
        int BuscarRegistro(int numeroFactura, bool activosOtodos);
        VentaCabecera LeerRegistro(int posicion);
        void LeerArchivo(int cantidadRegistros, VentaCabecera *vector);
        bool ListarRegistros(bool activosOtodos);
        int ContarRegistros();
        bool GrabarRegistro(VentaCabecera registro);
        bool EditarRegistro(VentaCabecera registro, int posicion);
        VentaCabecera MenuModificarRegistro(VentaCabecera registro);
        bool ModificarRegistro();
        bool AltaRegistro();
        bool BajaRegistro();

        ~ArchivoVentaCabecera();
};
