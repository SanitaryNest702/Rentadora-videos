/*
* ==========================================================
* Archivo : rentas.c
* Autor : José Ontiveros
* Fecha : 03/07/2026
* Descripción : Permite agregar rentas, registrar devolucione de películas y consultar las rentas activas
* Versión : 1.0
* ==========================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rentas.h"
#include "peliculas.h"
#include "clientes.h"
#include "multas.h"

struct Renta rentas[MAX_RENTAS];
int totalRentas=0;

/*
* ----------------------------------------------------------
* Función: registrarRenta
* Descripción: Registra una nueva renta solicitando el ID del cliente y de la pelicula. Valida que el cliente exista, 
	que no tenga multas pendientes, que la pelicula exista y tenga copias disponibles, y que los dias de renta sean validos. 
	Calcula el monto a pagar y resta una copia disponible de la pelicula.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/
void registrarRenta(){
	if(totalRentas>=MAX_RENTAS){
		printf("No se pueden registrar mas rentas, limite alcanzado\n");
		return;
	}
	
	int idCliente, idPelicula, diasRenta;
	printf("ID del cliente: ");
	scanf("%d", &idCliente);
	printf("ID de la pelicula: ");
	scanf("%d", &idPelicula);

	int clienteEncontrado=0;
	for(int i=0; i<totalClientes; i++){
		if(clientes[i].activo==1 && clientes[i].id==idCliente){
			clienteEncontrado=1;
			break;
		}
	}
	
	if(clienteEncontrado==0){
		printf("Cliente no encontrado\n");
		return;
	}

	for(int i=0; i<totalMultas; i++){
		if(multas[i].activo==1 && multas[i].idCliente==idCliente && multas[i].saldada==0){
			printf("Cliente con multas pendientes, no se puede rentar\n");
			return;
		}
	}

	int peliculaIndex=-1;
	for(int i=0; i<totalPeliculas; i++){
		if(peliculas[i].activo==1 && peliculas[i].id==idPelicula){
			peliculaIndex=i;
			break;
		}
	}
	
	if(peliculaIndex==-1){
		printf("Pelicula no encontrada\n");
		return;
	}
	
	if(peliculas[peliculaIndex].copiasDisponibles<=0){
		printf("Sin copias disponibles, no se puede rentar\n");
		return;
	}

	printf("Dias de renta: ");
	scanf("%d", &diasRenta);
	
	if(diasRenta<=0){
		printf("Los dias de renta deben ser mayores a 0\n");
		return;
	}

	float tarifaDiaria=15.0;
	struct Renta nueva;
	nueva.id=totalRentas+1;
	nueva.idCliente=idCliente;
	nueva.idPelicula=idPelicula;
	nueva.diasRenta=diasRenta;
	nueva.montoRenta=diasRenta*tarifaDiaria;
	nueva.devuelto=0;
	nueva.vencida=0;
	nueva.activo=1;

	rentas[totalRentas]=nueva;
	totalRentas++;

	peliculas[peliculaIndex].copiasDisponibles--;

	printf("Renta registrada, fecha de devolucion: %d dias\n", diasRenta);
	printf("Monto de la renta: %.2f\n", nueva.montoRenta);
}

/*
* ----------------------------------------------------------
* Función: registrarDevolucion
* Descripción: Registra la devolucion de una renta segun su ID. Solicita los dias reales que duro la renta, marca la renta como devuelta, 
	regresa la copia al inventario de peliculas y, si la devolucion fue tardia, marca la renta como vencida y genera una multa por retraso.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/
void registrarDevolucion(){
	int id;
	printf("Ingrese el ID de la renta a devolver: ");
	scanf("%d", &id);

	int encontrado=0;
	for(int i=0;i<totalRentas;i++){
		if(rentas[i].activo==1 && rentas[i].id==id){
			encontrado=1;
			
			if(rentas[i].devuelto==1){
				printf("Esta renta ya fue devuelta\n");
				return;
			}
			
			int diasReales;
			printf("Ingrese los dias reales que duro la renta: ");
			scanf("%d", &diasReales);
			
			rentas[i].devuelto=1;
			
			/*Devolver la copia al inventario de peliculas*/
			for(int j=0;j<totalPeliculas;j++){
				if(peliculas[j].id==rentas[i].idPelicula){
					peliculas[j].copiasDisponibles++;
					break;
				}
			}
			
			if(diasReales>rentas[i].diasRenta){
				int diasRetraso=diasReales-rentas[i].diasRenta;
				rentas[i].vencida=1;
				generarMultaRetraso(rentas[i].id, rentas[i].idCliente, diasRetraso);
				printf("Devolucion tardia, se genero multa\n");
			}
			else{
				printf("Devolucion exitosa\n");
			}
			break;
		}
	}
	
	if(encontrado==0){
		printf("Renta no encontrada\n");
	}
}
	
/*
* ----------------------------------------------------------
* Función: consultarRentasActivas
* Descripción: Muestra en pantalla el detalle de todas las rentas activas que aun no han sido devueltas (ID de renta, ID de cliente, 
	ID de pelicula, dias de renta y monto).
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void consultarRentasActivas(){
	int encontrado=0;
	printf("\n===Rentas Activas===\n");
	
	for(int i=0; i<totalRentas; i++){
		if(rentas[i].activo==1 && rentas[i].devuelto==0){
			encontrado=1;
			printf("\nID Renta: %d\n", rentas[i].id);
			printf("ID Cliente: %d\n", rentas[i].idCliente);
			printf("ID Pelicula: %d\n", rentas[i].idPelicula);
			printf("Dias de renta: %d\n", rentas[i].diasRenta);
			printf("Monto: %.2f\n", rentas[i].montoRenta);
		}
	}
	
	if(encontrado==0){
		printf("No hay rentas pendientes de devolucion\n");
	}
}
	
/*
* ----------------------------------------------------------
* Función: menuRentas
* Descripción: Despliega el menu del modulo de rentas y en un ciclo repite la lectura de la opcion elegida por el usuario, invocando 
	la funcion correspondiente hasta que se elija regresar al menu principal (opcion 0).
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void menuRentas(){
	int opcion;
	
	do{
		printf("\n===RENTAS===\n\n");
		printf("1.Registrar Renta\n");
		printf("2.Registrar Devolucion\n");
		printf("3.Consultar Rentas Activas\n");
		printf("0.Regresar al menu principal\n");
		
		printf("Elija una opcion: ");
		scanf("%d", &opcion);
		switch(opcion){
			case 1:
			registrarRenta();
			break;
			
			case 2:
			registrarDevolucion();
			break;
			
			case 3:
			consultarRentasActivas();
			break;
			
			case 0:
			system("cls");
			break;
			
			default:
			printf("Opcion invalida\n");
		}
	}while(opcion!=0);
}
