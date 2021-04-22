#include "../../Conexion-Serializacion/serializacion.h"
#include "../../Conexion-Serializacion/utils.h"
#include "Modulo-Comanda.h"
#include <string.h>
#include <stdbool.h>

int main(void)
{

t_list* lista_resto;
lista_resto = list_create();

t_list* lista_pedidos;
lista_pedidos = list_create();

int tamanio = list_size(lista_resto);
printf("Imprimo tamanio lista: %d\n", tamanio);
list_add(lista_resto,agrego_restaurante("Mc Donald",lista_pedidos));
tamanio = list_size(lista_resto);
printf("Imprimo tamanio nuevo de lista: %d\n", tamanio);
list_add(lista_resto,agrego_restaurante("Martinez",lista_pedidos));
tamanio = list_size(lista_resto);
printf("Imprimo tamanio nuevo de lista: %d\n", tamanio);
list_add(lista_resto,agrego_restaurante("Alicia",lista_pedidos));
tamanio = list_size(lista_resto);
printf("Imprimo tamanio nuevo de lista: %d\n", tamanio);
list_remove(lista_resto,1);
tamanio = list_size(lista_resto);
printf("Imprimo tamanio nuevo de lista: %d\n", tamanio);
t_datos* miElemento = list_buscar_elemento(lista_resto,"Mc Donald");
printf("Imprimo mi valor encontrado %s\n",miElemento->campo1);


free(lista_resto);
free(lista_pedidos);

return EXIT_SUCCESS;
}

t_datos *agrego_restaurante(char* cadena, t_list* lista){
	t_datos *new = malloc(sizeof(t_datos));
	new->campo1 = strdup(cadena);
	new->campo2 = lista;
	return new;
}

t_datos *list_buscar_elemento(t_list* lista,char* resto){
	bool  encontrar_elemento(t_datos* estructura){
	return	string_equals_ignore_case(resto, estructura->campo1);
	};
	t_datos* miEstructura =	list_find(lista, (void*) encontrar_elemento);
	return miEstructura;
}




