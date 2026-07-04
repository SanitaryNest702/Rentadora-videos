/*
* ==========================================================
* Archivo     : reportes.c
* Autor       : Hiram Dzul
* Fecha       : 03/07/2026
* Descripción : Genera reportes y estadísticas del sistema,
*               incluyendo películas más rentadas, clientes
*               frecuentes, promedios, ingresos y rentas vencidas.
* Versión     : 1.0
* ==========================================================
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "reportes.h"
#include "rentas.h"
#include "multas.h"
#include "peliculas.h"
#include "clientes.h"

/*
* ----------------------------------------------------------
* Función    : listarPeliculasMasRentadas
* Descripción: Cuenta las rentas por película y las muestra
*              ordenadas de mayor a menor usando ordenamiento
*              de burbuja.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void listarPeliculasMasRentadas(){
	if(totalRentas==0){
		printf("No hay rentas registradas\n");
		return;
	}
	int conteo[MAX_PELICULAS]={0};
	for(int i=0;i<totalRentas;i++){
		if(rentas[i].activo==1){
			int idPel= rentas[i].idPelicula; /*Cuenta cuantas veces fue rentada cada pelicula usando el ID*/
			conteo[idPel-1]++;
		}
	}
	/*Ordenar de mayor a menor (Por burbuja)*/
	int orden[MAX_PELICULAS];
	for(int i=0;i<totalPeliculas;i++){
		orden[i]=i;
	}
	for(int i=0;i<totalPeliculas-1;i++){
		for(int j=0;j<totalPeliculas-i-1;j++){
			if(conteo[orden[j]]<conteo[orden[j+1]]){
				int temp=orden[j];
				orden[j]=orden[j+1];
				orden[j+1]=temp;
			}
		}
	}

	printf("\n===PELICULAS MAS RENTADAS===\n");
	for(int i=0;i<totalPeliculas;i++){
		int idx=orden[i];
		if(peliculas[idx].activo==1){
			printf("%d. %s- Rentas: %d\n", i+1, peliculas[idx].titulo, conteo[idx]);
		}
	}
}

/*
* ----------------------------------------------------------
* Función    : listarClientesConMasRentas
* Descripción: Cuenta las rentas por cliente y las muestra
*              ordenadas de mayor a menor usando ordenamiento
*              de burbuja.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void listarClientesConMasRentas(){
	if(totalClientes==0){
		printf("No hay clientes registrados\n");
		return;
	}
	if(totalRentas==0){
		printf("No hay rentas registradas\n");
		return;
	}	
	/*Contar rentas por clientes*/


	int conteo[MAX_CLIENTES]={0};
	for(int i=0;i<totalRentas;i++){
		if(rentas[i].activo==1){
			int idCli=rentas[i].idCliente;
			conteo[idCli-1]++;
		}
	}

	/*Ordenar de mayor a menor (Con burbuja)*/

	int orden[MAX_CLIENTES];
	for(int i=0;i<totalClientes;i++){
		orden[i]=i;
		for(int i=0;i<totalClientes-1;i++){
			for(int j=0;j<totalClientes-i-1;j++){
				if(conteo[orden[j]]<conteo[orden[j+1]]){
					int temp=orden[j];
					orden[j]=orden[j+1]; 
					orden[j+1]=temp;
				}
			}
		}
		printf("\n===CLIENTES CON MAS RENTAS===\n");
		for(int i=0;i<totalClientes;i++){
			int idx=orden[i];
			if(clientes[idx].activo==1){
				printf("%d. %s - Rentas: %d\n", i+1, clientes[idx].nombre, conteo[idx]);
			}
		}
	}
}

/*
* ----------------------------------------------------------
* Función    : calcularPromedioDiasRenta
* Descripción: Calcula y muestra el promedio de días de duración
*              de todas las rentas activas registradas en el sistema.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void calcularPromedioDiasRenta(){
	if(totalRentas==0){
		printf("No hay datos suficientes para calcular\n");
		return;
	}

	int totalDias=0;
	int rentasContadas=0;
	for(int i=0;i<totalRentas;i++){
		if(rentas[i].activo==1){
			totalDias+=rentas[i].diasRenta;
			rentasContadas++;
		}
	}
	
	if(rentasContadas==0){
		printf("No hay rentas activas para calcular\n");
		return;
	}
	float promedio=(float)totalDias/ rentasContadas;
    printf("\n=== PROMEDIO DE DIAS DE RENTA ===\n");
    printf("Total de rentas analizadas: %d\n", rentasContadas);
    printf("Total de dias rentados: %d\n", totalDias);
    printf("Promedio de dias por renta: %.2f dias\n", promedio);

    contadorReportes[2]++;
}

/*
* ----------------------------------------------------------
* Función    : calcularTotalMultas
* Descripción: Calcula y muestra el total recaudado por multas
*              y el monto pendiente por cobrar de todas las
*              multas activas en el sistema.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void calcularTotalMultas(){
	if(totalMultas==0){
		printf("No se han registrado multas\n");
		return;
	}

	float totalRecaudado=0;
	float totalPendiente=0;
	int multasContadas=0;
	for(int i =0;i<totalMultas;i++){
		if(multas[i].activo==1){
			totalRecaudado+=multas[i].montoPagado;
			totalPendiente+=multas[i].monto-multas[i].montoPagado;
			multasContadas++;
		}
	}
	printf("\n=== TOTAL RECAUDADO POR MULTAS ===\n");
	printf("Total de multas registradas: %d\n", multasContadas);
	printf("Total recaudado: $%.2f\n", totalRecaudado);
	printf("Total pendiente por cobrar: $%.2f\n", totalPendiente);
}

/*
* ----------------------------------------------------------
* Función    : calcularIngresoTotalRentas
* Descripción: Calcula y muestra el ingreso total estimado
*              generado por todas las rentas activas registradas.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/

void calcularIngresoTotalRentas(){
	if(totalRentas==0){
		printf("No hay rentas registradas\n");
		return;
	}
	float totalIngreso=0;
	int rentasContadas=0;

	for(int i=0;i<totalRentas;i++){
		if(rentas[i].activo==1){
			totalIngreso+=rentas[i].montoRenta;
			rentasContadas++;
		}
	}
	
	printf("\n=== INGRESO TOTAL POR RENTAS ===\n");
	printf("Total de rentas analizadas: %d\n", rentasContadas);
	printf("Ingreso total estimado: $%.2f\n", totalIngreso);
	contadorReportes[4]++;
}


/*
* ----------------------------------------------------------
* Función    : listarRentasVencidas
* Descripción: Lista todas las rentas activas que no han sido
*              devueltas, mostrando su estado como VENCIDA o
*              Proxima a vencer según el campo vencida del struct.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/

void listarRentasVencidas(){
	if(totalRentas==0){
		printf("No hay rentas activas\n");
		return;
	}
	int encontrado=0;

	printf("\n===RENTAS PROXIMAS A VENCER O VENCIDAS===\n" );
	for(int i=0;i<totalRentas;i++){
		if(rentas[i].activo==1 && rentas[i].devuelto==0){
			encontrado = 1;
			printf("\nID Renta: %d\n", rentas[i].id);
			printf("ID Cliente: %d\n", rentas[i].idCliente);
			printf("ID Pelicula: %d\n", rentas[i].idPelicula);printf("Dias de renta: %d\n", rentas[i].diasRenta);
			printf("Estado: %s\n", rentas[i].vencida == 1 ? "VENCIDA" : "Proxima a vencer");
		}
	}
	if(encontrado==0){
		printf("No hay rentas proximas a vencer o vencidas\n"); 
	}
}

/*
* ----------------------------------------------------------
* Función    : menuReportes
* Descripción: Muestra el menú del módulo de reportes y dirige
*              al usuario a la función correspondiente según
*              la opción elegida. Se repite hasta que el usuario
*              elija regresar al menú principal.
* Parámetros : Ninguno
* Retorna    : No retorna valor alguno
* ----------------------------------------------------------
*/
void menuReportes() {
    int opcion;
    do {
        printf("\n=== MODULO DE REPORTES Y ESTADISTICAS ===\n");
        printf("1. Peliculas mas rentadas\n");
        printf("2. Clientes con mas rentas\n");
        printf("3. Promedio de dias de renta\n");
        printf("4. Total recaudado por multas\n");
        printf("5. Ingreso total por rentas\n");
        printf("6. Rentas proximas a vencer o vencidas\n");
        printf("7. Exportar reporte\n");
        printf("8. Limpiar historial\n");
        printf("0. Regresar al menu principal: ");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: 
              listarPeliculasMasRentadas();
              break;
            case 2:
              listarClientesConMasRentas();
              break;
            case 3:
              calcularPromedioDiasRenta();
              break;
            case 4:
              calcularTotalMultas();
              break;
            case 5: 
              calcularIngresoTotalRentas();
              break;
            case 6:
              listarRentasVencidas();
              break;
            case 0:
              printf("Regresando al menu principal...\n");
              break;
            default:
              printf("Opcion invalida.\n");
        }
      if(opcion!=0){
        pausar();
      }
    } while(opcion != 0);
}
