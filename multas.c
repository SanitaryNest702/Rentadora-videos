/*
* ==========================================================
* Archivo     : multas.c
* Autor       : Hiram Dzul
* Fecha       : 03/07/2026
* Descripción : Permite generar multas por entrega tardía o
*               pérdida de película, consultar multas pendientes
*               de un cliente y registrar pagos de multas.
* Versión     : 1.0
* ==========================================================
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "multas.h"
#include "clientes.h"
/* Arreglo de multas y contador total */
struct Multa multas[MAX_MULTAS];
int totalMultas=0;

/*
* ----------------------------------------------------------
* Función    : generarMultaRetraso
* Descripción: Genera una multa por entrega tardía calculando
*              el monto según los días de retraso y una tarifa
*              diaria fija de $10.00.
* Parámetros :
*   idRenta     (int) — ID de la renta asociada
*   idCliente   (int) — ID del cliente que generó el retraso
*   diasRetraso (int) — Número de días de retraso
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void generarMultaRetraso(int idRenta, int idCliente, int diasRetraso){
	if(totalMultas>=MAX_MULTAS){
		printf("No se pueden registrar mas multas\n");
		return;
	}
	if(diasRetraso<=0){
		printf("Los dias de retraso deben ser mayores a 0\n"); 
		return;
	}
	float tarifaDiaria=10.0;
	struct Multa nueva;
	nueva.id=totalMultas+1;
	nueva.idRenta=idRenta;
	nueva.idCliente=idCliente;
	nueva.monto=diasRetraso*tarifaDiaria;
	nueva.montoPagado=0;
	nueva.tipo=1;
	nueva.saldada=0;
	nueva.activo=1;
	multas[totalMultas]=nueva;
	totalMultas++;

	printf("Multa generada correctamene\n");
	printf("Dias de retraso: %d\n", diasRetraso);
	printf("Monto a pagar: %.2f\n", nueva.monto);
}

/*
* ----------------------------------------------------------
* Función    : generarMultaPerdida
* Descripción: Genera una multa por pérdida de película cuyo
*              monto equivale al valor de reposición indicado.
* Parámetros :
*   idRenta       (int)   — ID de la renta asociada
*   idCliente     (int)   — ID del cliente responsable
*   valorPelicula (float) — Valor de reposición de la película
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void generarMultaPerdida(int idRenta, int idCliente, float valorPelicula){
	if(totalMultas>=MAX_MULTAS){
		printf("No se pueden registrar mÃ¡s multas\n");
		return;
	}
	if(valorPelicula<=0){
		printf("El valor de la pelicula tiene que ser mayor a 0\n");
		return;
	}
	struct Multa nueva;
	nueva.id=totalMultas+1;
	nueva.idRenta=idRenta;
	nueva.idCliente=idCliente;
	nueva.monto=valorPelicula;
	nueva.montoPagado=0;
	nueva.tipo=2;/*2=Multa perdida*/
	nueva.saldada=0;
	nueva.activo=1;/*1=Existe*/

	multas[totalMultas]=nueva;
	totalMultas++;

	printf("Multa por perdida generada correctamente.\n");
	printf("Valor de la perdida: %.2f\n", nueva.monto); 
  
}

/*
* ----------------------------------------------------------
* Función    : consultarMultaCliente
* Descripción: Lista todas las multas pendientes (no saldadas)
*              asociadas a un cliente específico, mostrando
*              tipo, monto total, pagado y saldo pendiente.
* Parámetros :
*   idCliente (int) — ID del cliente a consultar
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void consultarMultaCliente(int idCliente){
	int encontrado=0;
	printf("===MULTAS PENDIENTES===\n");
	for(int i=0;i<totalMultas;i++){
		if(multas[i].activo==1 && multas[i].idCliente==idCliente && multas[i].saldada==0){
			encontrado=1;
			printf("\n ID Multa: %d\n", multas[i].id);
			printf("\nID renta: %d\n", multas[i].idRenta);
			printf("\nTipo: %s\n", multas[i].tipo==1? "Retraso": "Perdida de pelicula");
			printf("Monto total: %.2f\n", multas[i].monto);
			printf("Monto pagado: %.2f\n", multas[i].montoPagado);
			printf("Saldo pendiente: %.2f\n", multas[i].monto-multas[i].montoPagado);/*Calcula el saldo pendiente en caso de pagos parciales*/
		}
	}
	
	if(encontrado==0){
		printf("\nSin multas pendientes\n");
	}
}

/*
* ----------------------------------------------------------
* Función    : registrarPagoMulta
* Descripción: Busca una multa por ID y registra un pago parcial
*              o total. Valida que el monto sea mayor a 0 y no
*              supere el saldo pendiente. Marca la multa como
*              saldada si el pago cubre el total.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void registrarPagoMulta(){
	int id;
	printf("Ingrese el ID de la multa a pagar: ");
	scanf("%d", &id);

	int encontrado=0;
	for(int i=0;i<totalMultas;i++){
		if(multas[i].activo==1 && multas[i].id==id){
			encontrado=1;
			
			if(multas[i].saldada==1){
				printf("Esta multa ya fue saldada\n");
				return;
			}
			float saldoPendiente= multas[i].monto-multas[i].montoPagado;
			printf("\nID multa: %d\n", multas[i].id);
			printf("Monto Total: %.2f\n", multas[i].monto);
			printf("Monto pagado: %.2f\n", multas[i].montoPagado);
			printf("Saldo Pendiente: %.2f\n", multas[i].monto- multas[i].montoPagado);
			
			float pago;
			printf("Ingrese el monto a pagar: $");
			scanf("%f", &pago);
			
			if(pago<=0){
				printf("EL monto debe ser mayor a 0\n"); 
				return;
			}
			if(pago>saldoPendiente){/*Evitar que pague mas de lo que debe*/
				printf("El monto ingresado supera el saldo pendiente\n");
				return;
			}
			multas[i].montoPagado+=pago; /*Acumula pagos parciales*/
			if(multas[i].montoPagado>=multas[i].monto){/*Verifica si ya quedo saldada completamente*/
				multas[i].saldada=1;
				printf("Multa saldada correctamente\n");
			}else{
				printf("Pago parcial registrado\n");
				printf("Saldo pendiente: %.2f\n", multas[i].monto-multas[i].montoPagado);
			}
			break;
		}
	}
	if(encontrado==0){
		printf("Multa no encontrada\n");
	}
}

/*
* ----------------------------------------------------------
* Función    : menuMultas
* Descripción: Muestra el menú del módulo de multas y dirige
*              al usuario a la función correspondiente según
*              la opción elegida. Se repite hasta que el usuario
*              elija regresar al menú principal.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void menuMultas(){
	int opcion;
	do{
		printf("\n===MODULO DE MULTAS===\n"); 
		printf("1.Generar multa por entrega tardÃ­a\n"); 
		printf("2.Generar multa por perdida de pelicula\n");
		printf("3.Consultar multas pendiendes del cliente\n");
		printf("4.Registrar pago de multa\n");
		printf("0.Regresar al menu principal\n");
		printf("Opcion: "); 
		scanf("%d", &opcion);
		switch(opcion){
			case 1:{
				int idRenta, idCliente, diasRetraso;
				printf("ID del renta: ");
				scanf("%d", &idRenta); 
				printf("ID del cliente: ");
				scanf("%d", &idCliente);
				printf("Dias de retraso: ");
				scanf("%d", &diasRetraso);
				generarMultaRetraso(idRenta, idCliente, diasRetraso);
				break;
			}
			case 2:{
				int idRenta, idCliente;
				float valorPelicula;
				printf("ID de la renta: ");
				scanf ("%d", &idRenta);
				printf("ID del cliente: "); 
				scanf("%d", &idCliente);
				printf("Valor de reposicion de pelicula: ");
				scanf("%f", &valorPelicula);
				generarMultaPerdida(idRenta, idCliente, valorPelicula);
				break;
				}
			case 3:{
				int idCliente;
				printf("ID del cliente: ");
				scanf("%d", &idCliente);
				consultarMultaCliente(idCliente);
				break;
			}
			case 4:{
				registrarPagoMulta();
				break;
			}
			case 0:
			printf("Regresando al menu principal...\n");
			break;
			default:
			printf("Opcion invalida\n");
		}
		if(opcion!=0){
			pausar();
		}
	}while(opcion!=0);
}
