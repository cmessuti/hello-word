/*
 * Modulo-Comanda.h
 *
 *  Created on: 23 oct. 2020
 *      Author: utnso
 */

#ifndef MODULO_COMANDA_H_
#define MODULO_COMANDA_H_

typedef struct datos{
	char* campo1;
	t_list* campo2;
} t_datos;

t_datos *agrego_restaurante(char* cadena, t_list* lista);
t_datos *list_buscar_elemento(t_list* lista,char* resto);



#endif /* MODULO_COMANDA_H_ */
