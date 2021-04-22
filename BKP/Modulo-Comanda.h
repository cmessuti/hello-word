/*
 * Modulo-Comanda.h
 *
 *  Created on: 23 oct. 2020
 *      Author: utnso
 */

#ifndef MODULO_COMANDA_H_
#define MODULO_COMANDA_H_

typedef struct datos{
	int campo1;
	char* campo2;
} t_datos;

t_datos *valores_create(int numero, char *cadena);


/*void* GuardarPedido_Comanda(void*);
void* ObtenerPedido_Comanda(void* pedido);
void* ConfirmarPedido_Comanda(void* pedido);
void* FinalizarPedido_Comanda(void* pedido);


char* verificaRestaurante(char*);
char* existeRestaurante(char*);
char* existePedido(char*, int);
char* obtenerDatosPedido(char*, int);
char* obtenerEstadoPedido(char*, int);
char* actualizarEstadoPedido(char*, int, char*);
char* eliminarPlatosyPedido(char*, int);*/

#endif /* MODULO_COMANDA_H_ */
