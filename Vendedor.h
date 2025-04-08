#pragma once

class Vendedor:public Persona
{
    private:
        int _legajoVendedor;
        Fecha _fechaIngreso;
        float _sueldo;
        bool _estado;
    public:
        Vendedor();

        int getLegajoVendedor();
        Fecha getFechaIngreso();
        float getSueldo();
        bool getEstado();

        void setLegajoVendedor(int legajoVendedor);
        void setFechaIngreso(Fecha fechaIngreso);
        void setSueldo(float sueldo);
        void setEstado(bool estado);

        void asignacionLegajoVendedor();
        void Cargar();
        void Mostrar();
};
