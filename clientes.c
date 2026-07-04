/*
* ==========================================================
* Archivo     : clientes.c
* Autor       :Hiram Dzul
* Fecha       : 03/07/2026
* Descripción : Permite registrar, buscar, actualizar y eliminar
*               clientes del sistema de la rentadora de videos.
* Versión     : 1.0
* ==========================================================
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "clientes.h"
#ifdef _WIN32
    #include <windows.h>
    #define LIMPIAR_PANTALLA() system("cls")
#else
    #include <unistd.h>
    #define LIMPIAR_PANTALLA() system("clear")
#endif

void pausar(){
	printf("\nPresione ENTER para continuar...");
    while(getchar() != '\n');
    getchar();
    LIMPIAR_PANTALLA();
}
/* Arreglo de clientes y contador total */
struct Cliente clientes[MAX_CLIENTES];
int totalClientes=0;

/*
* ----------------------------------------------------------
* Función    : registrarClientes
* Descripción: Registra un nuevo cliente en el sistema solicitando
*              nombre, teléfono y dirección. Verifica que el cliente
*              no esté duplicado antes de registrarlo.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void registrarClientes(){
	if(totalClientes>=MAX_CLIENTES){
		printf("No se pueden registrar mas clientes, limite alcanzado\n");
		return;
	}
	struct Cliente nuevo;
	nuevo.id=totalClientes+1;
	nuevo.activo=1;
	printf("Nombre: ");
	scanf(" %[^\n]", nuevo.nombre);
	printf("Telefono: ");
	scanf(" %[^\n]", nuevo.telefono);
	printf("Direccion: ");
	scanf(" %[^\n]", nuevo.direccion);
	/*Verificar que ya existe un cliente con ese nombre*/
	for(int i=0;i<totalClientes;i++){
		if(clientes[i].activo==1 && strcmp(clientes[i].nombre, nuevo.nombre)==0){
			printf("El cliente ya existe en el sistema\n");
			return;
		}
	}

	clientes[totalClientes]=nuevo;
	totalClientes++;
	printf("Cliente registrado con exito\n");
    printf("ID asignado: %d\n", nuevo.id);
}

/*
* ----------------------------------------------------------
* Función    : buscarCliente
* Descripción: Busca un cliente activo por nombre e imprime
*              sus datos si es encontrado.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void buscarCliente(){
	char nombre[50];
	printf("Ingrese el nombre del cliente a buscar: ");
	scanf(" %[^\n]", nombre);
	int encontrado=0;
	for(int i=0;i<totalClientes;i++){
		if(clientes[i].activo==1 && strcmp(clientes[i].nombre, nombre)==0){
			printf("Cliente encontrado\n");
			printf("ID:%d\n", clientes[i].id);
			printf("Nombre: %s\n", clientes[i].nombre);
			printf("Telefono: %s\n", clientes[i].telefono);
			printf("Direccion: %s\n", clientes[i].direccion);
			encontrado=1;
			break;
		}
	}
	
    if(encontrado==0){
		printf("Cliente no encontrado\n");
	}
}
	
	/*
* ----------------------------------------------------------
* Función    : listaarClientes
* Descripción: Lista los clientes ingresados mostrando su Id y nombre
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void listarClientes(){
	if(totalClientes==0){
		printf("No hay clientes registrados\n");
		return;
	}
	printf("\n=== LISTA DE CLIENTES ===\n");
	for(int i=0;i<totalClientes;i++){
		if(clientes[i].activo==1){
			printf("ID: %d - %s\n", clientes[i].id, clientes[i].nombre);
		}
	}
}

/*
* ----------------------------------------------------------
* Función    : actualizarCliente
* Descripción: Busca un cliente por ID y permite modificar
*              uno de sus campos: nombre, teléfono o dirección,
*              según la opción elegida por el usuario.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
	
void actualizarCliente(){
	int id;
	listarClientes();
	printf("Ingrese el ID del cliente a actualizar: ");
	scanf("%d", &id);
	int encontrado=0;
	for(int i=0;i<totalClientes;i++){
		if(clientes[i].activo==1 && clientes[i].id==id){
			encontrado=1;
			printf("\n==Cliente encontrado==\n");
			printf("Nombre actual: %s\n", clientes[i].nombre);
			printf("Telefono actual: %s\n", clientes[i].telefono);
			printf("Direccion actual: %s\n", clientes[i].direccion);
			
			int opcion;
			printf("¿Que desea actualizar?\n");
			printf("1. Nombre\n");
			printf("2.Telefono\n");
			printf("3. Direccion\n");
			scanf("%d", & opcion);
			switch(opcion){
				case 1:
				printf("Ingrese nuevo nombre: ");
				scanf(" %[^\n]", clientes[i].nombre);
				printf("Nombre actualizado correctamente\n");
				break;
				
				case 2:
				printf("Nuevo telefono: ");
				scanf(" %[^\n]", clientes[i].telefono);
				printf("Telefono actualizado correctamente\n");
				break;
				
				case 3:
				printf("Nueva direccion: ");
				scanf(" %[^\n]", clientes[i].direccion);
				printf("Direccion actualizada correctamente\n");
				break;
				
				default:
				printf("Opcion invalida\n");
			}
		}
	}
	
	if(encontrado==0){
		printf("Cliente no encontrado\n");
	}
}

/*
* ----------------------------------------------------------
* Función    : eliminarCliente
* Descripción: Busca un cliente por ID, muestra sus datos y
*              solicita confirmación antes de marcarlo como
*              inactivo en el sistema.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void eliminarCliente(){
	int id;
    listarClientes();
	printf("Ingrese el ID del cliente a eliminar: ");
	scanf("%d", &id);
	int encontrado=0;
	for(int i=0;i<totalClientes;i++){
		if(clientes[i].activo==1 && clientes[i].id==id){
			encontrado=1;
			printf("\n==Cliente encontrado==\n");
			printf("ID: %d\n", clientes[i].id);
			printf("Nombre: %s\n", clientes[i].nombre);
			printf("Telefono: %s\n", clientes[i].telefono);
			printf("Direccion: %s\n", clientes[i].direccion);
			
			char confirmacion[10];
			printf("¿Esta seguro que desea eliminar al cliente?: ");
			scanf("%s", confirmacion);
			for(int j=0;j<strlen(confirmacion);j++){
				confirmacion[j]=toupper(confirmacion[j]);
			}
			if(strcmp(confirmacion, "SI")==0){
				clientes[i].activo=0;
				printf("Cliente eliminado correctamente\n");
			}
			else{
				printf("Operacion cancelada\n");
			}
			break;
		}
	}
    if(encontrado==0){
		printf("Cliente no encontrado\n");
    }
}

/*
* ----------------------------------------------------------
* Función    : menuClientes
* Descripción: Muestra el menú del módulo de clientes y dirige
*              al usuario a la función correspondiente según
*              la opción elegida. Se repite hasta que el usuario
*              elija regresar al menú principal.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void menuClientes(){
int opcion;
do{
	printf("\n===MODULO DE CLIENTES===\n");
	printf("1.Registrar Cliente\n"); 
	printf("2.Buscar Cliente\n");
	printf("3.Actualizar Cliente\n");
	printf("4.Eliminar Cliente\n");
	printf("0.Regresar al menu principal\n");

	printf("Elija una opcion: ");
	scanf("%d", &opcion);
	switch(opcion){
		case 1:
		registrarClientes();
		break;
		
		case 2:
		buscarCliente();
		break;
		
		case 3:
		actualizarCliente();
		break;
		
		case 4:
		eliminarCliente(); 
		break;
		case 0:
		printf("Regresando al menu principal...\n");
		break;
		
		default:
		printf("Opcion invalida\n"); 
	}
	
	if(opcion != 0){
		pausar();
	}
  }while(opcion!=0);
}
