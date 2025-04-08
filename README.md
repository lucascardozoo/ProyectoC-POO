## Sistema de gestión de tienda de ropa

Es un proyecto en equipo, se realizo desde cero para entregar como proyecto final para la facultad.

### Introducción

Elegimos desarrollar un programa que sea un sistema de gestión de inventario para una tienda de ropa, el cual administre los productos, su stock y las ventas.

### Objetivos

Desarrollar un sistema de gestión para una tienda de ropa en C++, utilizando el paradigma de programación orientada a objetos (POO) y manejo de archivos de datos, que permita realizar las siguientes acciones:

- Agregar, editar y eliminar productos.
- Registrar ventas y actualizar automáticamente el inventario.
- Sistema de salida: Consultas, listados e Informes.

### Descripción

Por cada venta, se actualizará automáticamente el stock de los productos correspondientes. Los detalles de cada venta incluyen la fecha, el N.º de factura, el nombre del cliente, el nombre del vendedor, los productos adquiridos, el importe unitario y total.
Se podrán gestionar los productos, agregándolos con sus propiedades, como el nombre, ID, categoría, precio, stock y descripción, o editando alguna o varias de estas propiedades, o eliminando un producto directamente.
El sistema de salida nos permitirá realizar listados de productos, clientes, vendedores y ventas, permitiéndonos, por ejemplo, aplicar un ordenamiento por precio del producto, por apellido del cliente, por apellido del vendedor, o por fecha o N.º de factura de ventas. Además, podremos consultar lo mencionado anteriormente, filtrando, por ejemplo, por categoría de producto, por DNI, rango de edad o género del cliente o vendedor, y por rango de fecha o N.º de factura de ventas. Por último, el sistema tendrá la funcionalidad de generar informes de facturación diaria, semanal, mensual o anual.
la interfaz fue realizada con rlutil.

### Alcance y Funcionalidades Principales

Gestión de productos:
- Agregar nuevos productos con sus propiedades.
- Editar o eliminar productos existentes.
Registro de ventas: 
- Registro de ventas con la fecha.
- Actualización automática del inventario tras cada venta.
Sistema de salida:
- Listado de productos, clientes, vendedores, ventas.
- Consultas de productos, clientes, vendedores, ventas.
- Informe de recaudación diario, semanal, mensual o anual de ventas.

ANEXO I: DIAGRAMA DE CLASES

![image](/assets/diagramaDeClasesTPIntegradorDrawio.png)

### Construido
- C++
- CodeBlocks