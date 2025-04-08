#pragma once

///FUNCIONES UTILES:
void showItem(const char *text, int posX, int posY, bool seleccionado);

///MENU:
void menu();

/// MENU VENTAS
void subMenuVentas();
void subMenuModificarVenta();void subMenuListadoVentas();
void subMenuConsultaVentas();
void subMenuInformesVentas();

///MENU CLIENTES:
void subMenuClientes();
void subMenuListadoClientes();
void subMenuConsultaClientes();

///MENU VENDEDORES:
void subMenuVendedores();
void subMenuListadoVededores();
void subMenuConsultaVendedores();

///MENU PRODUCTOS:
void subMenuProductos();
void subMenuListadoProductos();
void subMenuConsultaProductos();
