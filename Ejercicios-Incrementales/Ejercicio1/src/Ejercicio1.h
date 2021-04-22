typedef struct libros{
	char* Nombre;
	char* ISBN;
	int Precio;
	int Stock;
} t_libros;



int CargarLibro (char* nombre, t_list* libreria);
void ListarLibros(t_list* libreria);
int CargarLibroCompleto(t_libros* libro, t_list* otralibreria);
void ListarLibrosConEstructura(t_list* libreria);
void AumentarStock(char* nombre,int cantidad,t_list* libreria);
void QuitarLibro(char* nombre,t_list* libreria);


