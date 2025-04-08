#pragma once

class VentaDetalle
{
    private:
        int _numeroFactura, _idProducto, _cantidadProducto;
        float _precioProducto, _totalPorProducto;
        bool _estado;

    public:
        VentaDetalle();

        /// getter
        int getNumeroFactura();
        int getIdProducto();
        float getPrecioProducto();
        int getCantidadProducto();
        float getTotalPorProducto();
        bool getEstado();

        /// setter
        void setNumeroFactura(int numeroFactura);
        void setIdProducto(int idProducto);
        void setPrecioProducto(float precioProducto);
        void setCantidadProducto(int cantidadProducto);
        void setTotalPorProducto(float totalPorProducto);
        void setEstado(bool estado);

        void Cargar();
        void Mostrar(bool encabezado);

        void operator+=(int cantidadProducto);
        void operator-=(int cantidadProducto);
};
