#pragma once

///FUNCION PARA CONSULTAR EDAD DE CLIENTES
int calcularEdadCliente(int dia, int mes, int anio);

///FUNCIONES GENERALES PARA CLIENTES
void nuevoCliente();
void modificarCliente();
void bajaCliente();

///LISTADOS CLIENTES:
void listarSinOrdenamientoClientes();
void listarPorApellidoAscendentementeClientes();
void listarPorApellidoDescendentementeClientes();

///CONSULTAS CLIENTES:
void consultaClientesPorNumeroCliente();
void consultaaClientesPorDNI();
void consultaaClientesPorGenero();
void consultaClientesPorRangoEdad();
