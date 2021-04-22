/*
 ============================================================================
 Name        : Ejercicio1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<commons/collections/list.h>
#include "Ejercicio1.h"

int main(void) {
	puts("Voy a crear una lista de libros");
	t_list* libreria;
	t_list* libreria2;
	int retorno;
	int cantidad;
	char* nombreLibro;
	char* nombreParaSubirStock;
	char* nombreParaEliminarElemento;
	t_libros* otroLibro=malloc(sizeof(t_libros));
	t_libros* otroLibro2=malloc(sizeof(t_libros));
	nombreLibro = "Libro1";
	libreria = list_create();
	puts("Voy a agregar un libro llamado Libro1\n");
	retorno = CargarLibro(nombreLibro,libreria);
	if(retorno>=0){
		printf("Libro agregado correctamente\n");
	}
	else{
		printf("El libro no se pudo agregar\n");
	}
	puts("Voy a agregar otro libro llamado Libro2\n");
	nombreLibro = "Libro2";
	retorno = CargarLibro(nombreLibro,libreria);
	if(retorno>=0){
			printf("Libro agregado correctamente\n");
		}
		else{
			printf("El libro no se pudo agregar\n");
		}
	puts("Ahora voy a listar los libros, son los siguientes:\n");
	ListarLibros(libreria);
	puts("Ahora voy a crear otra lista cuyos elementos seran una estructura:\n");
	libreria2 = list_create();
	puts("Voy a agregar un elemento:\n");
	otroLibro->Nombre="Libro3";
	otroLibro->ISBN="1234567890123";
	otroLibro->Precio=1250;
	otroLibro->Stock=3;
	retorno = CargarLibroCompleto(otroLibro,libreria2);
	if(retorno>=0){
			printf("Libro agregado correctamente\n");
		}
		else{
			printf("El libro no se pudo agregar\n");
		}
	puts("Voy a agregar otro elemento:\n");
	otroLibro2->Nombre="Libro4";
	otroLibro2->ISBN="3216549870321";
	otroLibro2->Precio=2250;
	otroLibro2->Stock=5;
	retorno = CargarLibroCompleto(otroLibro2,libreria2);
	if(retorno>=0){
			printf("Libro agregado correctamente\n");
		}
		else{
			printf("El libro no se pudo agregar\n");
		}
	printf("Voy ahora a imprimir los datos del libro ingresado\n");
	ListarLibrosConEstructura(libreria2);
	printf("Voy a modificar el stock de Libro4 y a imprimir de nuevo la lista\n");
	cantidad = 8;
	nombreParaSubirStock="Libro4";
	AumentarStock(nombreParaSubirStock,cantidad,libreria2);
	ListarLibrosConEstructura(libreria2);
	printf("Voy a quitar Libro3 y a imprimir de nuevo la lista\n");
	nombreParaEliminarElemento="Libro3";
	/*QuitarLibro(nombreParaEliminarElemento,libreria2);
	ListarLibrosConEstructura(libreria2);*/
	/*free(otroLibro);*/
	return EXIT_SUCCESS;
}

int CargarLibro (char* nombre, t_list* libreria){
	int retorno;
	retorno = list_add(libreria,nombre);
	return retorno;
}

void ListarLibros(t_list* libreria){
int tamanio;
int i;
char* nombreLibro;
tamanio=list_size(libreria);
if(tamanio>0){
	 for(i=0;i<tamanio;i++){
			nombreLibro=list_get(libreria,i);
			printf("Nombre de libro: %s.\n",nombreLibro);
	 }
	}
else{
	printf("No hay ningun libro\n");
	}
}

int CargarLibroCompleto(t_libros* libro, t_list* otralibreria){
	int retorno;
	retorno = list_add(otralibreria,libro);
	return retorno;
}

void ListarLibrosConEstructura(t_list* libreria){
int tamanio;
int i;
t_libros* nombreLibro=malloc(sizeof(t_libros));
tamanio=list_size(libreria);
if(tamanio>0){
	 for(i=0;i<tamanio;i++){
			nombreLibro=list_get(libreria,i);
			printf("Nombre de libro: %s.\n",nombreLibro->Nombre);
			printf("ISBN de libro: %s.\n",nombreLibro->ISBN);
			printf("Precio de libro: %d.\n",nombreLibro->Precio);
			printf("Cantidad en Stock: %d.\n",nombreLibro->Stock);
	 }
	 	}
else{
	printf("No hay ningun libro\n");
	}
/*free(nombreLibro);*/
}

void AumentarStock(char* nombre,int cantidad,t_list* libreria){
	int tamanio;
	int i;
	t_libros* nombreLibro=malloc(sizeof(t_libros));
	tamanio=list_size(libreria);
	if(tamanio>0){
		 for(i=0;i<tamanio;i++){
				nombreLibro=list_get(libreria,i);
				if(nombreLibro->Nombre==nombre){
					nombreLibro->Stock=nombreLibro->Stock + cantidad;
				 }
		 }
		 	}
	else{
		printf("No hay ningun libro\n");
		}
}


void QuitarLibro(char* nombre,t_list* libreria){
	int tamanio;
	int i;
	t_libros* nombreLibro;
	tamanio=list_size(libreria);
	if(tamanio>0){
		 for(i=0;i<tamanio;i++){
				nombreLibro=list_get(libreria,i);
				if(strcmp(nombreLibro->Nombre,nombre)==0){
					list_remove(libreria,i);
				}
		 }
		 	}
	else{
		printf("No hay ningun libro\n");
		}
}
