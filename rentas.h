#ifndef RENTAS_H
#define RENTAS_H
#define MAX_RENTAS 100

struct Renta{
	int id;
	int idCliente;
	int idPelicula;
	int diasRenta;
	float montoRenta;
	int devuelto;/*0=pendiente 1=devuelta*/
	int vencida;/*0=no vencida 1=vencida*/
	int activo;/*1=existe 0=eliminada*/
};

extern struct Renta rentas[MAX_RENTAS];
extern int totalRentas;

void registrarRenta();
void registrarDevolucion();
void consultarRentasActivas();
void menuRentas();

#endif
