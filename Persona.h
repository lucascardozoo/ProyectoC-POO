#pragma once

class Persona
{
    protected:
        int _DNI, _genero;
        char _nombre[50], _apellido[50], _correo[50], _telefono[20];
        Fecha _fechaNacimiento;
        Direccion _direccion;
    public:
        Persona();

        int getDNI();
        const char* getNombre();
        const char* getApellido();
        int getGenero();
        Fecha getFechaNacimiento();
        Direccion getDireccion();
        const char* getTelefono();
        const char* getCorreo();

        void setDNI(int DNI);
        void setNombre(const char* nombre);
        void setApellido(const char* apellido);
        void setGenero(int genero);
        void setFechaNacimiento(Fecha fechaNacimiento);
        void setDireccion(Direccion direccion);
        void setTelefono(const char* telefono);
        void setCorreo(const char* correo);
        void Cargar();
        void Mostrar();
};
