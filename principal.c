#include <stdio.h>
#include "peliculas.h"
#include "clientes.h"
#include "rentas.h"
#include "multas.h"
#include "reportes.h"

void mostrarMenuPrincipal();
void dirigirFlujo(int opcion);

/*
* ----------------------------------------------------------
* Función: mostrarMenuPrincipal
* Descripción: Muestra las opciones que puede escoger el usuario para trabajar
* Parámetros :
* 	No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/
void mostrarMenuPrincipal(){
	printf("===SISTEMA DE RENTADORA DE VIDEOS===\n");
	printf("1.Modulo de Peliculas\n");
	printf("2.Modulo de Clientes\n");
	printf("3.Modulo de Rentas\n");
	printf("4.Modulo de Multas\n");
	printf("5.Modulo de Reportes y Estadisticas\n");
	printf("0.Salir\n\n");
	printf("Elija una opcion: ");
}

/*
* ----------------------------------------------------------
* Función: dirigirFlujo
* Descripción: Permite seleccionar con que módulo se quiere trabajar o si se quiere salir del programa
* Parámetros :
* 	opcion (int): Sirve como identificador para escoger que opción trabajara
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/
void dirigirFlujo(int opcion){
	switch(opcion){
		case 1:
		menuPeliculas();
		break;
		
		case 2:
		menuClientes();
		break;
		
		case 3:
		menuRentas();
		break;
		
		case 4:
		menuMultas();
		break;
		
		case 5:
		menuReportes();
		break;
		
		case 0:
		printf("Saliendo del sistema...\n");
		break;
		
		default:
		printf("Opcion invalida\n");
	}
}

/*
* ----------------------------------------------------------
* Función: main
* Descripción: Llama a las funciones para mostrar el menú y dirigir la opción ingresada por el usuario para ir a un módulo específico o salir del programa
* ----------------------------------------------------------
*/
int main(){
	int opcion;
	
	do{
		mostrarMenuPrincipal();
		scanf("%d", &opcion);
		dirigirFlujo(opcion);
	}while(opcion!=0);

	return 0;
}
