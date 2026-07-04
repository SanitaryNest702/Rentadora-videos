/*
* ==========================================================
* Archivo : peliculas.c
* Autor : José Ontiveros
* Fecha : 03/07/2026
* Descripción : Permite agregar películas, eliminarlas, buscar películas y hace lo mismo con las categorías.
* Versión : 1.0
* ==========================================================
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "peliculas.h"
#include "rentas.h"

/* */
struct Pelicula peliculas[MAX_PELICULAS];
int totalPeliculas=0;

/* */
struct Categoria categorias[MAX_CATEGORIAS];
int totalCategorias=0;

/*
* ----------------------------------------------------------
* Función: obtenerNombreCategoria
* Descripción: Obtiene el nombre de la categoría correspondiente a un ID dado y lo copia en la variable destino. Si el ID es 0 o la categoria
	no se encuentra, asigna el texto "Sin categoria".
* Parámetros :
* 	idCategoria (int) — ID de la categoria a buscar
* 	destino (char*) — cadena donde se almacena el nombre encontrado
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/
void obtenerNombreCategoria(int idCategoria, char *destino){
	if( idCategoria == 0){
		strcpy(destino, "Sin categoria");
		return; 
	}
	for (int i=0; i<totalCategorias; i++){
		if (categorias[i].id == idCategoria){
			strcpy(destino, categorias[i].nombre);
			return;
		}
	}
	strcpy(destino, "Sin categoria");
}

/*
* ----------------------------------------------------------
* Función: agregarPelicula
* Descripción: Registra una nueva pelicula solicitando al usuario titulo, año, copias disponibles y categoria. Verifica que no se exceda 
	el limite de peliculas y que no exista ya una pelicula con el mismo titulo.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void agregarPelicula(){
	if (totalPeliculas >= MAX_PELICULAS){
		printf("No se pueden registrar mas peliculas, limite alcanzado\n");
		return;
	}
	struct Pelicula nueva;
		nueva.id = totalPeliculas+1;
		nueva.activo = 1;
		printf("Titulo: ");
		scanf(" %[^\n]", nueva.titulo);
		printf("Año: ");
		scanf("%d", &nueva.anio);
		printf("Copias disponibles: ");
		scanf("%d", &nueva.copiasDisponibles);
		nueva.copiasTotales=nueva.copiasDisponibles;
		
	if (totalCategorias == 0){
		printf("No hay categorias registradas todavia, la pelicula quedara sin categoria\n");
		nueva.idCategoria=0;
	}
	else{
		listarCategorias();
		printf("Ingrese el ID de la categoria de la pelicula, o 0 para dejarla sin categoria: \n");
		int idCategoria;
		scanf("%d", &idCategoria);
		
		if (idCategoria == 0){
			nueva.idCategoria = 0;
		}
		else{
			int categoriaEncontrada = 0;
			for(int i=0; i<totalCategorias; i++){
				if (categorias[i].activo == 1 && categorias[i].id == idCategoria){
					categoriaEncontrada = 1;
					break;
				}
			}
			if (categoriaEncontrada == 0){
				printf("Categoria no encontrada, la pelicula quedara sin categoria\n");
				nueva.idCategoria=0;
			}
			else{
				nueva.idCategoria=idCategoria;
			}
		}
	}

	/*Verificar que ya existe una pelicula con ese titulo*/
	for (int i=0; i<totalPeliculas; i++){
		if (peliculas[i].activo == 1 && strcmp(peliculas[i].titulo, nueva.titulo) == 0){
			printf("La pelicula ya esta registrada\n");
			return;
		}
	}

	peliculas[totalPeliculas]=nueva;
	totalPeliculas++;
	printf("Pelicula registrada con exito con ID %d.\n", totalPeliculas);
}

/*
* ----------------------------------------------------------
* Función: eliminarPelicula
* Descripción: Elimina logicamente una pelicula segun el ID capturado. Antes de eliminar valida que la pelicula no tenga rentas activas 
	sin devolver, y pide confirmacion al usuario (SI/NO).
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/		
void eliminarPelicula(){
	int id, encontrado = 0;
	printf("Ingrese el ID de la pelicula a eliminar: ");
	scanf("%d", &id);
	for(int i = 0; i<totalPeliculas; i++){
		if(peliculas[i].activo == 1 && peliculas[i].id == id){
			encontrado = 1;
			
		  /*Verificar que la pelicula no tenga rentas activas*/
			for(int j=0; j<totalRentas; j++){
				if(rentas[j].activo == 1 && rentas[j].idPelicula == id && rentas[j].devuelto == 0){
					printf("No se puede eliminar, pelicula en renta\n");
					return;
				}
			}
			
			printf("\n==Pelicula encontrada==\n");
			printf("ID: %d\n", peliculas[i].id);
			printf("Titulo: %s\n", peliculas[i].titulo);
			
			char confirmacion[3];
			printf("Esta seguro que desea eliminar la pelicula? (SI/NO): ");
			scanf("%s", confirmacion);
			for (int k=0; k<strlen(confirmacion); k++){
				confirmacion[k]=toupper(confirmacion[k]);
			}
			
			if (strcmp(confirmacion, "SI")==0){
				peliculas[i].activo=0;
				printf("Pelicula eliminada correctamente\n");
			}
			else{
				printf("Operacion cancelada\n");
			}
			
			break;
		}
	}
	
	if (encontrado==0){
		printf("Pelicula no encontrada\n");
	}
}
	
/*
* ----------------------------------------------------------
* Función: buscarPelicula
* Descripción: Busca una pelicula activa por titulo o por ID, segun la opcion elegida por el usuario, y muestra en pantalla sus datos 
	junto con el nombre de su categoria.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void buscarPelicula(){
	int opcion, encontrado=0;
	char titulo[100];
	
	printf("Buscar por:\n1. Titulo\n2. ID\n");
	scanf("%d", &opcion);

	if (opcion==1){
		
		printf("Ingrese el titulo de la pelicula a buscar: ");
		scanf(" %[^\n]", titulo);
		
		for (int i=0; i<totalPeliculas; i++){
			if (peliculas[i].activo==1 && strcmp(peliculas[i].titulo, titulo)==0){
				encontrado=1;
				char nombreCategoria[50];
				obtenerNombreCategoria(peliculas[i].idCategoria, nombreCategoria);
				printf("Pelicula encontrada\n\n");
				printf("ID: %d, Titulo: %s, Categoria: %s, Año: %d, Copias disponibles: %d\n", peliculas[i].id, peliculas[i].titulo, nombreCategoria, peliculas[i].anio, peliculas[i].copiasDisponibles);
				break;
			}
		}
	}
	else if (opcion==2){
		int id;
		
		printf("Ingrese el ID de la pelicula a buscar: ");
		scanf("%d", &id);
		
		for (int i=0;i<totalPeliculas;i++){
			if (peliculas[i].activo==1 && peliculas[i].id==id){
				encontrado=1;
				char nombreCategoria[50];
				obtenerNombreCategoria(peliculas[i].idCategoria, nombreCategoria);
				printf("Pelicula encontrada\n\n");
				printf("ID: %d, Titulo: %s, Categoria: %s, Año: %d, Copias disponibles: %d\n", peliculas[i].id, peliculas[i].titulo, nombreCategoria, peliculas[i].anio, peliculas[i].copiasDisponibles);
				break;
			}
		}
	}
	else{
		printf("Opcion invalida\n");
		return;
	}

	if (encontrado==0){
		printf("Pelicula no encontrada\n");
	}
}
	
/*
* ----------------------------------------------------------
* Función: listarPeliculasDisponibles
* Descripción: Recorre el arreglo de peliculas y muestra en pantalla unicamente aquellas activas que tienen al menos una copia disponible.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void listarPeliculasDisponibles(){
	int encontrado=0;
	printf("\n===Peliculas Disponibles===\n");
	
	for (int i=0; i<totalPeliculas; i++){
		if (peliculas[i].activo==1 && peliculas[i].copiasDisponibles>0){
			encontrado=1;
			char nombreCategoria[50];
			obtenerNombreCategoria(peliculas[i].idCategoria, nombreCategoria);
			printf("ID: %d - %s (%s, %d) - Copias disponibles: %d\n", peliculas[i].id, peliculas[i].titulo, nombreCategoria, peliculas[i].anio, peliculas[i].copiasDisponibles);
		}
	}
	
	if (encontrado==0){
		printf("No hay peliculas disponibles\n");
	}
}
	
/*
* ----------------------------------------------------------
* Función: agregarCategoria
* Descripción: Registra una nueva categoria solicitando su nombre al usuario. Verifica que no se exceda el limite de categorias y que 
	no exista ya una categoria activa con el mismo nombre.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void agregarCategoria(){
	struct Categoria nueva;
	
	if (totalCategorias>=MAX_CATEGORIAS){
		printf("No se pueden registrar mas categorias, limite alcanzado\n");
		return;
	}
	
	nueva.id=totalCategorias+1;
	nueva.activo=1;
	printf("Nombre de la categoria: ");
	scanf(" %[^\n]", nueva.nombre);

	for (int i=0;i<totalCategorias;i++){
		if (categorias[i].activo==1 && strcmp(categorias[i].nombre, nueva.nombre)==0){
			printf("La categoria ya existe\n");
			return;
		}
	}

	categorias[totalCategorias] = nueva;
	totalCategorias++;
	printf("Categoria registrada con ID %d.\n", totalCategorias);
}

/*
* ----------------------------------------------------------
* Función: eliminarCategoria
* Descripción: Elimina logicamente una categoria segun el ID capturado, validando primero que ninguna pelicula activa este usando dicha 
	categoria antes de proceder con la eliminacion.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void eliminarCategoria(){
	int id, encontrado=0;
	printf("Ingrese el ID de la categoria a eliminar: ");
	scanf("%d", &id);
	
	for (int i=0; i<totalCategorias; i++){
		if (categorias[i].activo==1 && categorias[i].id==id){
			encontrado=1;
			
			/*Verificar que ninguna pelicula activa use esta categoria*/
			for (int j=0; j<totalPeliculas; j++){
				if (peliculas[j].activo==1 && peliculas[j].idCategoria==id){
					printf("No se puede eliminar, hay peliculas registradas con esta categoria\n");
					return;
				}
			}
			
			categorias[i].activo=0;
			printf("Categoria eliminada\n");
			break;
		}
	}
	
	if(encontrado==0){
		printf("No encontrada\n");
	}
}

/*
* ----------------------------------------------------------
* Función: listarCategorias
* Descripción: Muestra en pantalla el ID y nombre de todas las categorias activas registradas en el sistema.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void listarCategorias(){
	int encontrado=0;
	printf("\n===Categorias===\n");
	
	for (int i=0; i<totalCategorias; i++){
		if (categorias[i].activo==1){
			encontrado=1;
			printf("ID: %d - %s\n", categorias[i].id, categorias[i].nombre);
		}
	}
	
	if (encontrado==0){
		printf("No hay categorias registradas\n");
	}
}

/*
* ----------------------------------------------------------
* Función: asignarCategoria
* Descripción: Asigna una categoria existente a una pelicula existente. Solicita al usuario el ID de la pelicula y el ID de la categoria, 
	validando que ambos existan antes de realizar la asignacion.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/
void asignarCategoria(){
	int idPelicula, idCategoria;
	printf("ID de la pelicula: \n");
	scanf("%d", &idPelicula);
	printf("ID de la categoria: \n");
	scanf("%d", &idCategoria);

	int peliculaEncontrada=0, categoriaEncontrada=0;

	for (int i=0; i<totalCategorias; i++){
		if (categorias[i].activo==1 && categorias[i].id==idCategoria){
			categoriaEncontrada=1;
			break;
		}
	}
	
	if (categoriaEncontrada==0){
		printf("Categoria no encontrada\n");
		return;
	}

	for (int i=0; i<totalPeliculas; i++){
		if (peliculas[i].activo==1 && peliculas[i].id==idPelicula){
			peliculaEncontrada=1;
			peliculas[i].idCategoria=idCategoria;
			printf("Categoria asignada correctamente\n");
			break;
		}
	}
	
	if (peliculaEncontrada==0){
		printf("Pelicula no encontrada\n");
	}
}

/*
* ----------------------------------------------------------
* Función: listarPorCategoria
* Descripción: Solicita al usuario el ID de una categoria y muestra en pantalla todas las peliculas activas que pertenecen a dicha categoria.
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void listarPorCategoria(){
	int idCategoria;
	printf("Ingrese el ID de la categoria: ");
	scanf("%d", &idCategoria);

	int categoriaEncontrada=0;
	char nombreCategoria[50];
	for (int i=0; i<totalCategorias; i++){
		if (categorias[i].activo==1 && categorias[i].id==idCategoria){
			categoriaEncontrada=1;
			strcpy(nombreCategoria, categorias[i].nombre);
			break;
		}
	}
	
	if (categoriaEncontrada==0){
		printf("Categoria no encontrada\n");
		return;
	}

	int encontrado=0;
	printf("\n===Peliculas de la Categoria %s===\n", nombreCategoria);
	
	for (int i=0; i<totalPeliculas; i++){
		if (peliculas[i].activo==1 && peliculas[i].idCategoria==idCategoria){
			encontrado=1;
			printf("ID: %d - %s\n", peliculas[i].id, peliculas[i].titulo);
		}
	}
	
	if (encontrado==0){
		printf("No hay peliculas registradas en esta categoria\n");
	}
}
	
/*
* ----------------------------------------------------------
* Función: menuPeliculas
* Descripción: Despliega el menu del modulo de peliculas y categorias, y en un ciclo repite la lectura de la opcion elegida por el usuario 
	invocando la funcion correspondiente hasta que se elija regresar al menu principal (opcion 0).
* Parámetros : No tiene parámetros
* Retorna: No retorna valor alguno
* ----------------------------------------------------------
*/	
void menuPeliculas(){
	int opcion;
	do{
		printf("\n===PELICULAS===\n");
		printf("1.Agregar Pelicula\n");
		printf("2.Eliminar Pelicula\n");
		printf("3.Buscar Pelicula\n");
		printf("4.Listar Peliculas Disponibles\n");
		printf("5.Agregar Categoria\n");
		printf("6.Eliminar Categoria\n");
		printf("7.Asignar Categoria a Pelicula\n");
		printf("8.Listar Categorias\n");
		printf("9.Listar Peliculas por Categoria\n");
		printf("0.Regresar al menu principal\n");
		
		printf("\nElija una opcion: ");
		scanf("%d", &opcion);
		switch(opcion){
			case 1:
			agregarPelicula();
			break;
			
			case 2:
			eliminarPelicula();
			break;
			
			case 3:
			buscarPelicula();
			break;
			
			case 4:
			listarPeliculasDisponibles();
			break;
			
			case 5:
			agregarCategoria();
			break;
			
			case 6:
			eliminarCategoria();
			break;
			
			case 7:
			asignarCategoria();
			break;
			
			case 8:
			listarCategorias();
			break;
			
			case 9:
			listarPorCategoria();
			break;
			
			case 0:
			system("cls");
			break;
			
			default:
			printf("Opcion invalida\n");
		}
	}while(opcion!=0);
}
