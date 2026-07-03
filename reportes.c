#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "reportes.h"
#include "rentas.h"
#include "multas.h"
#include "peliculas.h"
#include "clientes.h"

int contadorReportes[6]={0, 0, 0, 0, 0, 0};

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
  contadorReportes[0]++;
}


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
  for(int i=0;i<totalClientes;i++)
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
    contadorReportes[1]++;
}

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
  contadorReportes[3]++;
}

/*Calcular ingreso total por rentas*/

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


/*Listar Rentas proximas a vencer o ya vencidas*/

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
  contadorReportes[5]++;
}

void exportarReporte() {
    int opcion;
    printf("\n=== EXPORTAR REPORTE ===\n");
    printf("1. Peliculas mas rentadas\n");
    printf("2. Clientes con mas rentas\n");
    printf("3. Promedio de dias de renta\n");
    printf("4. Total recaudado por multas\n");
    printf("5. Ingreso total por rentas\n");
    printf("6. Rentas proximas a vencer o vencidas\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1: 
          listarPeliculasMasRentadas();
          break;
        case 2: listarClientesConMasRentas();
          break;
        case 3: calcularPromedioDiasRenta();
          break;
        case 4: calcularTotalMultas();
          break;
        case 5: calcularIngresoTotalRentas();
          break;
        case 6: listarRentasVencidas();
          break;
        default: 
          printf("Opcion invalida.\n"); 
          break;
    }
    printf("\nReporte generado correctamente.\n");
}

void limpiarHistorial() {
    char confirmacion[10];
    printf("Esta seguro que desea limpiar el historial? (SI/NO): ");
    scanf("%s", confirmacion);

    for (int i = 0; i < strlen(confirmacion); i++) {
        confirmacion[i] = toupper(confirmacion[i]);
    }
    if (strcmp(confirmacion, "SI") == 0 || strcmp(confirmacion, "SÍ") == 0) {
        for (int i = 0; i < 6; i++) {
            contadorReportes[i] = 0;
        }
        printf("Historial limpiado correctamente.\n");
    } else {
        printf("Operacion cancelada.\n");
    }
}
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
        printf("0. Regresar al menu principal\n");
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
            case 7:
              exportarReporte();
              break;
            case 8:
              limpiarHistorial();
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
