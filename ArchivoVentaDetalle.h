#pragma once

class ArchivoVentaDetalle
{
    private:
        char *_nombreArchivo;
        int _tamanioRegistro;
    public:
        ArchivoVentaDetalle(const char *nombreArchivo = "ArchivoVentaDetalle.dat");

        char* getNombreArchivo();
        int getTamanioRegistro();

        bool CrearDeCero();
        int BuscarRegistro(int numeroFactura, bool activosOtodos);
        int BuscarRegistro(int numeroFactura, int idProducto, bool activosOtodos);
        VentaDetalle LeerRegistro(int posicion);
        void LeerArchivo(int cantidadRegistros, VentaDetalle *vector);
        bool ListarRegistros(bool activosOtodos);
        int ContarRegistros();
        bool GrabarRegistro(VentaDetalle registro);
        bool EditarRegistro(VentaDetalle registro, int posicion);
        VentaDetalle MenuModificarRegistro(VentaDetalle registro);
        bool ModificarRegistro();
        bool AltaRegistro();
        bool BajaRegistro();

        ~ArchivoVentaDetalle();
};
