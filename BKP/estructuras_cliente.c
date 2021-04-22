/*
 * estructuras_cliente.c
 *
 *  Created on: 23 oct. 2020
 *      Author: utnso
 */

#include "estructuras_cliente.h"

void* escuchar(){
	//t_respuesta_obtener_restaurante* respuesta_restaurante;
	char* mensaje;
	while(1){
		int cod_op = recibir_operacion(conexion);
		switch(cod_op){/*
			case RESPUESTA_CONSULTAR_RESTAURANTES:
				break;
			case RESPUESTA_SELECCIONAR_RESTAURANTE:
				break;*/
			case RESPUESTA_OBTENER_RESTAURANTE:;
				t_respuesta_obtener_restaurante* respuesta_restaurante;
				respuesta_restaurante = recibir_respuesta_obtener_restaurante(conexion);
				//ver que onda este msj
				mensaje = string_from_format("Recibi las afinidades: %s, posX: %d, posY: %d, recetas: %s, precios: %s, cantidad hornos: %d, cantidad pedidos: %d", respuesta_restaurante->afinidades, respuesta_restaurante->posX, respuesta_restaurante->posY, respuesta_restaurante->recetas, respuesta_restaurante->precios, respuesta_restaurante->cant_hornos, respuesta_restaurante->cant_pedidos);
				log_info(logger, mensaje);
				free(respuesta_restaurante);
				break;
			case RESPUESTA_CONSULTAR_PLATOS:;
				t_restaurante* respuesta_platos;
				respuesta_platos = recibir_respuesta_consultar_platos(conexion);
				mensaje = string_from_format("Recibi los platos: %s", respuesta_platos->nombre_restaurante);
				log_info(logger, mensaje);
				free (respuesta_platos);
				break;
			case RESPUESTA_CREAR_PEDIDO:;
				int* id_pedido;
				id_pedido = recibir_respuesta_crear_pedido(conexion);
				//SEMAFORO DE CONTADOR HILOS
				int err = pthread_create(&hilos_pedidos[(*id_pedido)-1], NULL, pedido_hilo, *id_pedido);
				if (err!=0){
					printf("\nHubo un error en la creacion del hilo\n");
					//return err;
				}
				//contador_hilos=contador_hilos+1;
				//SEMAFORO DE CONTADOR HILOS
				printf("enviado msj de crear pedido\n");
				free(id_pedido);
				break;/*
			case RESPUESTA_GUARDAR_PEDIDO:
				break;*/
			case RESPUESTA_ANIADIR_PLATO:;
				t_plato_listo* a_aniadir;
				a_aniadir=recibir_respuesta_aniadir_platoV2(conexion);
				if(strcmp(a_aniadir->nombre_restaurante, "Ok")){
					accion_a_realizar = ANIADIR;
					plato_a_aniadir=a_aniadir->nombre_comida;
					sem_post(&sem_pedidos[(a_aniadir->id_pedido)-1]);
				}
				else{
					//loguear error
					printf("Fail en la adicion de plato");
				}
				break;/*
			case RESPUESTA_GUARDAR_PLATO:
				break;*/
			case RESPUESTA_CONFIRMAR_PEDIDO:;
				t_pedido_nombre* confirmacion;
				confirmacion = recibir_respuesta_confirmar_pedido(conexion);
				if(strcmp(confirmacion->nombre, "Ok")){
					accion_a_realizar = CONFIRMAR;
					sem_post(&sem_pedidos[(confirmacion->id_pedido)-1]);
					//pthread_join(hilos_pedidos[(confirmacion->id_pedido)-1],NULL);
				}
				else{
					//loguear error
					printf("Fail en la confirmacion de pedido");
				}
				break;/*
			case RESPUESTA_PLATO_LISTO:
				break;
			case RESPUESTA_CONSULTAR_PEDIDO:
				break;*/
			case RESPUESTA_OBTENER_PEDIDO:;
				t_plato_listo* respuesta;
				mensaje = string_from_format("PEDIDO ID: %d, {&s, %s}", respuesta->id_pedido, respuesta->nombre_restaurante, respuesta->nombre_comida);
				break;
			case RESPUESTA_FINALIZAR_PEDIDO:;
				t_pedido_nombre* finalizacion;
				//semaforo accion a realizar
				finalizacion = recibir_respuesta_finalizar_pedido(conexion);
				if(strcmp(finalizacion->nombre, "Ok")){
					//accion_a_realizar = FINALIZAR;
					//sem_post(&sem_pedidos[(finalizacion->id_pedido)-1]);
					//pthread_join(hilos_pedidos[(finalizacion->id_pedido)-1],NULL);
					mensaje = string_from_format("Finalizo el pedido %d", finalizacion->id_pedido);
					log_info(logger, mensaje);
				}
				else{
					//loguear error
					printf("Fail en la finalizacion de pedido");
				}
				//contador_hilos
				//post accion a realizar
				break;/*
			case RESPUESTA_TERMINAR_PEDIDO:
				break;
			case RESPUESTA_OBTENER_RECETA:
				break;*/
		}
	}
}

void* pedido_hilo(int id_pedido){
	t_pedido_en_cliente* miPedido = malloc(sizeof(t_pedido_en_cliente));
	miPedido->id_pedido=id_pedido;
	miPedido->platos="";
	char* modificacion;
	while(miPedido->estado!=FINALIZADO){
		sem_wait(&sem_pedidos[(miPedido->id_pedido)-1]);
		switch(accion_a_realizar){
			case FINALIZAR:;
				miPedido->estado = FINALIZADO;
				break;
			case ANIADIR:;
				if(strcmp(miPedido->platos, "")){
					miPedido->platos=plato_a_aniadir;
				}else{
					modificacion= string_from_format("%s, %s", miPedido->platos, plato_a_aniadir);//probar
					miPedido->platos=modificacion;
				}
				break;
			case CONFIRMAR:;
				miPedido->estado = CONFIRMAR;
				break;
		}
		sem_post(&sem_pedidos[(miPedido->id_pedido)-1]);
	}
	return NULL;
}

/*ANTIGUO CASE----------------------------------------------------------------
			case RESPUESTA_FINALIZAR_PEDIDO:;
				t_pedido_nombre* finalizacion;
				//semaforo accion a realizar
				finalizacion = recibir_respuesta_finalizar_pedido(conexion);
				if(strcmp(finalizacion->nombre, "Ok")){
					accion_a_realizar = FINALIZAR;
					sem_post(&sem_pedidos[(finalizacion->id_pedido)-1]);
					pthread_join(hilos_pedidos[(finalizacion->id_pedido)-1],NULL);
				}
				else{
					//loguear error
					printf("Fail en la finalizacion de pedido");
				}
				//contador_hilos
				//post accion a realizar
				break;/*
----------------------------------------------------------*/
