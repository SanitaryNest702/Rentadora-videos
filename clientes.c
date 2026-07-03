#include<stdio.h>
#include<string.h>
#include<ctype.h>
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

struct Cliente clientes[MAX_CLIENTES];
int totalClientes=0;

void registrarClientes(){
if(totalClientes>=MAX_CLIENTES){
printf("No se pueden registrar mas clientes, limite alcanzado\n");
  return;
}
struct Cliente nuevo;
  nuevo.id=totalClientes+1;
  nuevo.activo=1;
  printf("Nombre: \n");
  scanf(" %[^\n]", nuevo.nombre);
  printf("Telefono: \n");
  scanf(" %[^\n]", nuevo.telefono);
  printf("Direccion: \n");
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
}

void buscarCliente(){
char nombre[50];
printf("Ingrese el nombre del cliente a buscar\n");
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

void actualizarCliente(){
  int id;
  printf("Ingrese el ID del cliente a actualizar\n");
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
      printf("Que desea actualizar?\n");
      printf("1. Nombre\n");
      printf("2.Telefono\n");
      printf("3. Direccion\n");
      scanf("%d", & opcion);
      switch(opcion){
        case 1:
          printf("Ingrese nuevo nombre: \n");
          scanf(" %[^\n]", clientes[i].nombre);
          printf("Nombre actualizado correctamente\n");
        break;

        case 2:
          printf("Nuevo telefono:\n");
          scanf(" %[^\n]", clientes[i].telefono);
          printf("Telefono actualizado correctamente\n");
        break;

        case 3:
          printf("Nueva direccion:\n");
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


void eliminarCliente(){
  int id;
  printf("Ingrese el ID del cliente a eliminar:\n");
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

      char confirmacion[3];
      printf("Esta seguro que desea eliminar al cliente?\n");
      scanf("%s", confirmacion);
      for(int j=0;j<strlen(confirmacion);j++){
        confirmacion[i]=toupper(confirmacion[i]);
      }
      if(strcmp(confirmacion, "SÍ")==0|| strcmp(confirmacion, "SI")==0){
        clientes[i].activo=0;
        printf("Cliente eliminado correctamente\n");
    }else{
        printf("Operacion cancelada\n");
}
      break;
    }
  }
    if(encontrado==0){
    printf("Cliente no encontrado\n");
    }
}

void menuClientes(){
int opcion;
do{
 printf("\n===MODULO DE CLIENTES===\n");
  printf("1.Registrar Cliente\n"); 
  printf("2.Buscar Cliente\n");
  printf("3.Actualizar Cliente\n");
  printf("4.Eliminar Cliente\n");
  printf("0.Regresar al menu principal\n");

  printf("Elija una opcion\n");
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
