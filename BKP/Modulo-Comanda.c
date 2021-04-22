#include "../../Conexion-Serializacion/serializacion.h"
#include "../../Conexion-Serializacion/utils.h"
#include "Modulo-Comanda.h"
#include <string.h>


int main(void)
{

/*int var;
int var2;
int indice;
int result;
int var4;
int tamanioLista;

char* var3;
var3 = "Soy String";
char* result3;
char* variable1;
char* variable2;
char* variable3;
char* variablevalor;
int contador;
variable1 = "hola";
variable2 = "que";
variable3 = "tal";

var = 26;
var2 = 10;
printf("Imprimo el numero: %d\n", var);
printf("Imprimo el numero: %d\n", var2);*/
t_list* lista;
lista = list_create();
/*tamanioLista = list_size(lista);
printf("tamanio inicial: %d\n", tamanioLista);
indice = list_add(lista,var);
printf("Me retorno: %d\n", indice);
indice = list_add(lista,var2);
printf("y ahora me retorno: %d\n", indice);
result = list_get(lista,1);
printf("recupero el segundo: %d\n", result);
result = list_get(lista,0);
printf("recupero el primero: %d\n", result);
list_add_in_index(lista,1,2610);
result = list_get(lista,1);
printf("recupero el cambio: %d\n", result);

indice = list_add(lista,var3);
result3 = list_get(lista,18);
printf("Imprimo mi cadena: %s\n", result3);

var4 = list_size(lista);
printf("Mostrame var4: %d\n", var4);

list_clean(lista);
tamanioLista = list_size(lista);
printf("Borre, mi tamanio es: %d\n", tamanioLista);
list_add(lista,variable1);
list_add(lista,variable2);
list_add(lista,variable3);
tamanioLista = list_size(lista);
printf("Ahora meti: %d\n", tamanioLista);
contador = 0;
   while(contador < list_size(lista)){
	   variablevalor = list_get(lista,contador);
	   if(variablevalor=="que"){
	   printf("Estoy imprimiendo: %s\n", variablevalor);
	   }
	   contador++;
   }
valores.campo1 = 26;
valores.campo2 = "deldiez";
printf("Imprimo campo1: %d\n", valores.campo1);
printf("Imprimo campo2: %s\n", valores.campo2);*/
int tamanio = list_size(lista);
printf("Imprimo tamanio lista: %d\n", tamanio);
list_add(lista,valores_create(26,"deldiez"));
tamanio = list_size(lista);
printf("Imprimo tamanio nuevo de lista: %d\n", tamanio);



free(lista);

return EXIT_SUCCESS;
}

t_datos *valores_create(int numero, char *cadena){
	t_datos *new = malloc(sizeof(t_datos));
	new->campo1 = numero;
	new->campo2 = strdup(cadena);
	return new;
}


