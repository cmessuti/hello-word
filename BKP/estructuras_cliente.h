/*
 * estructuras_cliente.h
 *
 *  Created on: 23 oct. 2020
 *      Author: utnso
 */

#ifndef MODULO_CLIENTE_SRC_ESTRUCTURAS_CLIENTE_H_
#define MODULO_CLIENTE_SRC_ESTRUCTURAS_CLIENTE_H_

#include "../../Conexion-Serializacion/serializacion.h"
#include "../../Conexion-Serializacion/utils.h"

typedef enum{
	FINALIZADO
}estado_pedido;

typedef struct{
	int id_pedido;
	char* platos;
	estado_pedido estado;
}t_pedido_en_cliente;

typedef enum{
	FINALIZAR,
	ANIADIR,
	CONFIRMAR
}accion_pedido;

void* escuchar();
void* pedido_hilo(int);

//int contador_hilos=0;
pthread_t hilos_pedidos[4];
pthread_t escucha;
t_log* logger;
int conexion;
sem_t sem_pedidos[4];
char* plato_a_aniadir;

accion_pedido accion_a_realizar;

#endif /* MODULO_CLIENTE_SRC_ESTRUCTURAS_CLIENTE_H_ */
