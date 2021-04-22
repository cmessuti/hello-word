/*
 * Modulo-Comanda.h
 *
 *  Created on: 23 oct. 2020
 *      Author: utnso
 */

#ifndef MODULO_COMANDA_H_
#define MODULO_COMANDA_H_

t_config* leer_config(void);

typedef struct restos{
    char NombreResto;
    t_list* ListaPedidos;
} t_restos;

typedef struct pedidos{
    int IdPedido;
    t_list* ListaPlatos;
} t_pedidos;

typedef struct Platos {
    char* Plato;
    int Frame;  /* número de frame de la memoria */
	int FrameSwap;  /* número de frame swap de la memoria */
	char Presencia;  /* indica si la página está o no en ram */
	int antiguedad;  /* se usara para algoritmo de reemplazo LRU */
	char uso;  /* se usará para algoritmo de reemplazo clock mejorado */
	char modificado;  /* se usará para algoritmo de reemplazo clock mejorado y para saber si se debe actualizar swap */
} t_platos;


void Escuchar_Cliente(int cliente_fd);
void* GuardarPedido_Comanda(void* pedido);
void* FinalizarPedido_Comanda(void* pedido);

/*--------------------------------*/
t_restos *agrego_restaurante(char resto, t_list* lista);
t_restos *list_buscar_elemento_resto(t_list* lista,char* resto);
t_pedidos *list_buscar_elemento_pedido(t_list* lista,int pedido);
t_pedidos *agrego_pedido(int pedido, t_list* lista);
int verificaRestaurante(char*);
int existeRestaurante(char*);
int verificaRestauranteYPedido(char* NombreDeRes, int IdPedido);
int eliminaPedidoYPlatos(char* NombreDeRes, int IdPedido);


#endif /* MODULO_COMANDA_H_ */
