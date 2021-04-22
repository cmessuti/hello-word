#include "../../Conexion-Serializacion/serializacion.h"
#include "../../Conexion-Serializacion/utils.h"
#include "Modulo-Comanda.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <commons/config.h>
#include <commons/collections/list.h>

/* Creo Lista de Restaurantes */
t_list* lista_resto;


int main(void)
{
	lista_resto = list_create();
	logger = log_create("Comanda.log", "Comanda", 1, LOG_LEVEL_DEBUG);
	t_config* config;
	config = leer_config_comanda();

	/* Inicialización de las memorias */
	int tamanio;
	tamanio = config_get_int_value(config,TAMANIO_MEMORIA);
    char* ram = malloc(tamanio);
	tamanio = config_get_int_value(config,TAMANIO_SWAP);
	char* swap = malloc(tamanio);

	int tamanio_lista_resto;
	int server_fd = iniciar_servidor();
	int cliente_fd;
	int cantidad_consultas = config_get_int_value(config,CANTIDAD_CONSULTAS);
	pthread_t hilo_nueva_consulta[cantidad_consultas];
	int i = 0;

	while(1)
	{
	  cliente_fd = esperar_cliente(server_fd);

	  if(pthread_create(&hilo_nueva_consulta[i], NULL, (void *)Escuchar_Cliente, cliente_fd) != 0) return -1;
	  i++;
	}
 	free(ram);
	free(swap);
	tamanio_lista_resto = list_size(lista_resto);
	for(int x=0;x<tamanio_lista_resto;x+=1)
    {
      list_remove(lista_resto,x);
    };
	list_destroy(lista_resto);

	return EXIT_SUCCESS;

}

t_config* leer_config_comanda(void){
	return config_create("Configs-Logs/Comanda.config");
}


void Escuchar_Cliente(int cliente_fd) {

    int cod_op = recibir_operacion(cliente_fd);
	switch(cod_op)
	{
	case GUARDAR_PEDIDO:;
		pthread_t hilo;
		t_pedido_nombre* pedido;
		char* respuesta;
		pedido = recibir_guardar_pedido(cliente_fd);
		respuesta = GuardarPedido_Comanda(&pedido);
		responder_guardar_pedido(respuesta, pedido->id_pedido, cliente_fd)
		pthread_join(hilo, NULL);
		break;
	case FINALIZAR_PEDIDO:;
		pthread_t hilo;
		t_pedido_nombre* pedido;
		char* respuesta;
		pedido = recibir_finalizar_pedido(cliente_fd);
		respuesta = FinalizarPedido_Comanda(&pedido);
		responder_finalizar_pedido(respuesta, pedido->id_pedido, cliente_fd)
		pthread_join(hilo, NULL);
		break;
    case -1:
		log_error(logger, "el cliente se desconecto. Terminando servidor");
		return EXIT_FAILURE;
	default:
		log_warning(logger, "Operacion desconocida. No quieras meter la pata");
		break;
	}
}


t_config* leer_config(void){
	return config_create("Configs-Logs/Comanda.config");
}



void* GuardarPedido_Comanda(void* pedido) {
    char* NombreDeRes;
	int IdPedido;
	char* estado;

	NombreDeRes = pedido->nombre_largo;
	IdPedido = pedido->id_pedido;

	if (verificaRestaurante(NombreDeRes, IdPedido))

		return "Pedido guardado correctamente";

	return "No se pudo guardar el pedido";
}


void* FinalizarPedido_Comanda(void* pedido) {
    char* NombreDeRes;
	int IdPedido;
	char* estado;

	NombreDeRes = pedido->nombre_largo;
	IdPedido = pedido->id_pedido;

	if (verificaRestauranteYPedido(NombreDeRes, IdPedido))

		return "Pedido finalizado correctamente";

	return "No se pudo finalizar el pedido";
}


int verificaRestaurante(char* NombreDeRes, int IdPedido) {

    if (existeRestaurante(NombreDeRes)) {
	 t_list* lista_platos;
     lista_platos = list_create();
	 t_restos* miElemento = list_buscar_elemento_resto(lista_resto,NombreDeRes);
	 return list_add(miElemento->ListaPedidos,agrego_pedido(IdPedido,lista_platos));
    }
	else {
		    return 0;
    }

}


int existeRestaurante(char* NombreDeRes){
	t_restos* miElemento = list_buscar_elemento_resto(lista_resto,NombreDeRes);
    if (miElemento->NombreResto == NombreDeRes) {
    	return 1;
    }
	else {
		t_list* lista_pedidos;
		lista_pedidos = list_create();
		return list_add(lista_resto,agrego_restaurante(NombreDeRes,lista_pedidos));
    }
}

t_restos *list_buscar_elemento_resto(t_list* lista,char* resto){
    bool encontrar_elemento(t_restos* estructura){
    return string_equals_ignore_case(resto, estructura->NombreResto);
    };
    t_restos* miEstructura = list_find(lista, (void*) encontrar_elemento);
    return miEstructura;
}


t_restos *agrego_restaurante(char resto, t_list* lista){
    t_restos *new = malloc(sizeof(t_restos));
    new->NombreResto = strdup(resto);
    new->ListaPedidos = lista;
    return new;
}

t_pedidos *agrego_pedido(int pedido, t_list* lista){
    t_pedidos *new = malloc(sizeof(t_pedidos));
    new->IdPedido = pedido;
    new->ListaPlatos = lista;
    return new;
}

int verificaRestauranteYPedido(char* NombreDeRes, int IdPedido) {
    if (eliminaPedidoYPlatos(NombreDeRes, IdPedido)) {
	 return 1;
    }
	else {
	 return 0;
    }
}

int eliminaPedidoYPlatos(char* NombreDeRes, int IdPedido){
	int tamanio_lista_pedidos;
	t_pedidos* PedidoAEliminar;
    t_restos* miElementoResto = list_buscar_elemento_resto(lista_resto,NombreDeRes);
    if (miElementoResto->NombreResto == NombreDeRes ) {
    	t_pedidos* miElementoPedido = list_buscar_elemento_pedido(miElementoResto->ListaPedidos,IdPedido);
        if (miElementoPedido->IdPedido == IdPedido ) {
        	list_destroy(miElementoPedido->ListaPlatos);
        	tamanio_lista_pedidos = list_size(miElementoResto->ListaPedidos);
        	for(int x=0;x<tamanio_lista_pedidos;x+=1)
        	            {
        				PedidoAEliminar = list_get(miElementoResto->ListaPedidos, x);
        				 if (PedidoAEliminar->IdPedido == IdPedido ){
        	              list_remove(miElementoResto->ListaPedidos,x);
        				  }
        	            };
        	return 1;
        }
    	else {
    		return 0;
        }
    }
	else {
		return 0;
    }
}

t_pedidos *list_buscar_elemento_pedido(t_list* lista,int pedido){
    bool encontrar_elemento(t_pedidos* estructura){
        if (pedido == estructura->IdPedido) {
        	return 1;
        }
    	else {
    		return 0;
        }
    };
    t_pedidos* miEstructura = list_find(lista, (void*) encontrar_elemento);
    return miEstructura;
}


