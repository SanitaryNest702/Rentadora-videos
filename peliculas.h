#ifndef PELICULAS_H
#define PELICULAS_H
#define MAX_PELICULAS 100
#define MAX_CATEGORIAS 20

struct Pelicula{
	int id;
	char titulo[100];
	int anio;
	int copiasTotales;
	int copiasDisponibles;
	int idCategoria;/*0=sin categoria; la categoria funciona como el genero de la pelicula*/
	int activo;/*1=existe 0=eliminada*/
};

struct Categoria{
	int id;
	char nombre[50];
	int activo;/*1=existe 0=eliminada*/
};

extern struct Pelicula peliculas[MAX_PELICULAS];
extern int totalPeliculas;
extern struct Categoria categorias[MAX_CATEGORIAS];
extern int totalCategorias;

void agregarPelicula();
void eliminarPelicula();
void buscarPelicula();
void listarPeliculasDisponibles();
void agregarCategoria();
void eliminarCategoria();
void asignarCategoria();
void listarCategorias();
void listarPorCategoria();
void menuPeliculas();

#endif
