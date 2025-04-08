#pragma once

///FUNCION PARA CONSULTAR EDAD DE VENDEDORES
int calcularEdadVendedor(int dia, int mes, int anio);

///FUNCIONES GENERALES PARA VENDEDODES
void nuevoVendedor();
void modificarVendedor();
void bajaVendedor();

///LISTADOS VENDEDORES:
void listarSinOrdenamientoVendedores();
void listarPorApellidoAscendentementeVendedores();
void listarPorApellidoDescendentementeVendedores();

///CONSULTAS VENDEDORES:
void consultaVendedorPorLegajo();
void consultaVendedorPorDNI();
void consultaVendedorPorGenero();
void consultaVendedorPorRangoEdad();
