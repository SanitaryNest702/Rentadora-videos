#infdef CLIENTES_H
#define CLIENTES_H
#define MAX_CLIENTES 100
struct Cliente{
int id;
char nombre[50];
char telefono[50];
char direccion[100];
int activo;
};
extern struct Cliente cliente[MAX_CLIENTES];
extern int totalClientes;
void registrarClientes();
void buscarCliente();
void actualizarCliente();
void eliminarCliente();
void menuClientes()
#endif;
