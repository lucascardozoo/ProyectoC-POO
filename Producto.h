#pragma once

class Producto{
    private:
        int _idProducto, _stockProducto, _categoriaProducto;
        char _nombreProducto[50], _descripcionProducto[100];
        float _precioProducto;
        bool _estado;

    public:
        Producto();

        int getIdProducto();
        int getCategoriaProducto();
        const char* getNombreProducto();
        const char* getDescripcionProducto();
        float getPrecioProducto();
        int getStockProducto();
        bool getEstado();

        void setIdProducto(int idProducto);
        void setCategoriaProducto(int categoriaProducto);
        void setNombreProducto(const char* nombreProducto);
        void setDescripcionProducto(const char* descripcionProducto);
        void setPrecioProducto(float precioProducto);
        void setStockProducto(int stockProducto);
        void setEstado(bool estado);

        void asignacionIDProducto();
        void Cargar();
        void Mostrar();

        void operator+=(int cantidadStock);
        void operator-=(int cantidadStock);
};
