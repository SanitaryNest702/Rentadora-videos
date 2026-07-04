/*
* ==========================================================
* Archivo : rentas.h
* Autor : José Ontiveros
* Fecha : 03/07/2026
* Descripción : Define la estructura Renta, su variable global y los prototipos de las funciones para registrar rentas y 
devoluciones, y consultar las rentas activas.
* Versión : 1.0
* ==========================================================
*/

#ifndef RENTAS_H
#define RENTAS_H
#define MAX_RENTAS 100
/*
* Renta (Struct)
* Descripcion: Sirve de molde para todas las rentas que se vayan a crear, cuenta con id, id del cliente para asociarlo a la renta, id de la peliculas
* para saber que pelicula se rentó, dias rentados, monto de la renta, si ya fue devuelta, si ya venció la renta o si se encuentra en activo
*/
struct Renta{
	int id;
	int idCliente;
	int idPelicula;
	int diasRenta;
	float montoRenta;
	int devuelto;
	int vencida;
	int activo;
};

extern struct Renta rentas[MAX_RENTAS];
extern int totalRentas;

void registrarRenta();
void registrarDevolucion();
void consultarRentasActivas();
void menuRentas();

#endif
