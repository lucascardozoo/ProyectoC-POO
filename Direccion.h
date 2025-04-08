#pragma once

class Direccion
{
    private:        char _nombreCalle[50];
        char _nombreCiudad [50];
        char _provinciaDireccion[50];
        int _alturaCalle, _codigoPostal;

    public:
        Direccion();
        const char* getNombreCalle();
        int getAlturaCalle();
        const char* getNombreCuidad();
        int getCodigoPostal();
        const char* getProvinciaDireccion();

        void setNombreCalle(const char* nombreCalle);
        void setAlturaCalle(int alturaCalle);
        void setNombreCiudad(const char* nombreCiudad);
        void setCodigoPostal(int codigoPostal);
        void setProvinciaDireccion(const char* estadoDireccion);

        void Cargar();
        void Mostrar();

};
