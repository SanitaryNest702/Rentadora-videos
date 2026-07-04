

/*
* ==========================================================
* Archivo : clientes.h
* Autor : Hiram Dzul
* Fecha : 03/07/2026
* Descripción : Define la estructura Cliente, su variable
* global y los prototipos de las funciones necesarias para
* registrar, buscar, actualizar y eliminar clientes dentro
* del sistema.
* Versión : 1.0
* ==========================================================
*/


#ifndef CLIENTES_H
#define CLIENTES_H
#define MAX_CLIENTES 100


/*
* Cliente (Struct)
* Descripción: Sirve de molde para almacenar la información
* de cada cliente registrado en el sistema. Cuenta con un ID
* único, nombre, teléfono, dirección y un indicador que
* determina si el cliente sigue activo en el sistema.
*/

struct Cliente{
	int id;
	char nombre[50];
	char telefono[50];
	char direccion[100];
	int activo;
};

extern struct Cliente clientes[MAX_CLIENTES];
extern int totalClientes;
void registrarClientes();
void buscarCliente();
void actualizarCliente();
void eliminarCliente();
void menuClientes();
void pausar();
#endif
