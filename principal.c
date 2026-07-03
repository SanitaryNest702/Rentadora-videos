#include <stdio.h>
#include "peliculas.h"
#include "clientes.h"
#include "rentas.h"
#include "multas.h"
#include "reportes.h"

void mostrarMenuPrincipal();
void dirigirFlujo(int opcion);

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

int main(){
	int opcion;
	
	do{
		mostrarMenuPrincipal();
		scanf("%d", &opcion);
		dirigirFlujo(opcion);
	}while(opcion!=0);

	return 0;
}
