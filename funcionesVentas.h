#pragma once

///FUNCIONES GENERALES PARA VENTAS
void nuevaVenta();
void darBajaVenta();
void darBajaProductoDeVenta();
void modificarCabecera();
void modificarDetalle();
void agregarProductoAlDetalle();

///LISTADOS VENTAS:
void listarSinOrdenamientoVentas();
void listarPorNumFacturaAscendente();
void listarPorNumFacturaDescendente();
void listarPorFechaDeVentaAscendente();
void listarPorFechaDeVentaDescendente();

///CONSULTAS VENTAS:
void consultaPorNumeroFactura();
void consultaPorFecha();
void consultaPorRangoFecha();

///INFORMES VENTAS:
bool bisiesto(int anio);
void informeRecaudacionDiaria();
void informeRecaudacionSemanal();
void informeRecaudacionMensual();
void informeRecaudacionAnual();
