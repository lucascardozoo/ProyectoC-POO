#pragma once

class Cliente:public Persona
{
    private:
        int _numeroCliente;
        bool _estado;
    public:
        Cliente();

        int getNumeroCliente();
        bool getEstado();

        void setNumeroCliente(int numeroCliente);
        void setEstado(bool estado);

        void asignacionNumeroCliente();
        void Cargar();
        void Mostrar();
};
