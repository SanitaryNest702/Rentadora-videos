
/*
* ==========================================================
* Archivo : multas.h
* Autor :  Hiram Dzul
* Fecha : 03/07/2026
* Descripción : Define la estructura Multa, su variable
* global y los prototipos de las funciones necesarias para
* generar multas, consultar multas pendientes y registrar
* pagos de multas.
* Versión : 1.0
* ==========================================================
*/

#ifndef MULTAS_H
#define MULTAS_H
#define MAX_MULTAS 100


/*
* Multa (Struct)
* Descripción: Sirve de molde para almacenar la información
* de las multas generadas por retraso en la devolución o por
* pérdida de una película. Incluye información de la renta,
* cliente, monto, pagos realizados y estado de la multa.
*/

struct Multa{
	int id;
	int idRenta;
	int idCliente;
	float monto;
	float montoPagado;
	int tipo;/*1=retraso 2=perdida*/
	int saldada; /*1=pagada 0=pendiente */
	int activo;/*1=existe 0=eliminada*/
};

extern struct Multa multas[MAX_MULTAS];
extern int totalMultas;
void generarMultaRetraso(int idRenta, int idCliente, int diasRetraso);
void generarMultaPerdida(int idRenta, int idCliente, float valorPelicula);
void consultarMultaCliente(int idCliente);
void menuMultas();
void registrarPagoMulta();

#endif
