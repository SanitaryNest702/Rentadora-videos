#ifndef PELICULAS_H
#define PELICULAS_H
#define MAX_PELICULAS 100
#define MAX_CATEGORIAS 20
/*
* Pelicula (Struct)
* Descripcion: Sirve de molde para todas las películas que se vayan a crear, incluye id, titulo, año, copias totales de la película, copias disponibles
* de la película, a que categoría está relacionada y si se encuentra rentada o no
*/
struct Pelicula{
	int id;
	char titulo[100];
	int anio;
	int copiasTotales;
	int copiasDisponibles;
	int idCategoria;
	int activo;
};

/*
* Categoria (Struct)
* Descripcion: Sirve de molde para todas las categorías que se vayan a crear, cada una con id, nombre y si se encuentra en activo o no
*/
struct Categoria{
	int id;
	char nombre[50];
	int activo;
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
