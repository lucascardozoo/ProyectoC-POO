#pragma once

class VentaCabecera
{
    private:
        int _numeroFactura, _numeroCliente, _legajoVendedor;
        Fecha _fechaVenta;
        float _totalVenta;
        bool _estado;

    public:
        VentaCabecera();

        /// getter
        int getNumeroFactura();
        Fecha getFechaVenta();
        int getNumeroCliente();
        int getLegajoVendedor();
        float getTotalVenta();
        bool getEstado();

        /// setter
        void setNumeroFactura(int numeroFactura);
        void setFechaVenta(Fecha fechaVenta);
        void setNumeroCliente(int numeroCliente);
        void setLegajoVendedor(int legajoVendedor);
        void setTotalVenta(float totalVenta);
        void setEstado(bool estado);

        void asignacionNumeroFactura();
        void Cargar();
        void Mostrar();

        void operator+=(float totalPorProducto);
        void operator-=(float totalPorProducto);
};
