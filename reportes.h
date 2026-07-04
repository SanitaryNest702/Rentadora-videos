
/*
* ==========================================================
* Archivo : reportes.h
* Autor : Hiram Dzul
* Fecha : 03/07/2026
* Descripción : Contiene los prototipos de las funciones
* utilizadas para generar reportes y estadísticas sobre
* las películas, clientes, rentas y multas registradas
* en el sistema.
* Versión : 1.0
* ==========================================================
*/
#ifndef REPORTES_H
#define REPORTES_H
/*
* Lista las películas ordenadas de acuerdo con la cantidad
* de veces que han sido rentadas.
*/
void listarPeliculasMasRentadas();
/*
* Lista los clientes ordenados según la cantidad de rentas
* realizadas dentro del sistema.
*/
void listarClientesConMasRentas();
/*
* Calcula el promedio de días registrados en las rentas.
*/
void calcularPromedioDiasRenta();
/*
* Calcula el total recaudado y pendiente por concepto de
* multas registradas.
*/
void calcularTotalMultas();
/*
* Calcula el ingreso total generado por las rentas.
*/
void calcularIngresoTotalRentas();
/*
* Muestra las rentas activas indicando su estado actual.
*/
void listarRentasVencidas();
/*
* Despliega el menú principal del módulo de reportes y
* estadísticas.
*/
void menuReportes();

#endif
