#ifndef MULTAS_H
#define MULTAS_H
#define MAX_MULTAS 100

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

extern struct Multa multas[MAX_MMULTAS];
extern int totalMultas;
void generarMultas(int idRenta, int idCliente, int diasRetraso);
void generarMultaPerdida(int idRenta, int idCliente, float valorPelicula);
void consultarMultaCliente(int idCliente);
void registrarPelicula();
void menuMultas();

#endif
