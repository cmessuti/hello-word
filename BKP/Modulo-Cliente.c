/*
 ============================================================================
 Name        : Cliente.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<commons/collections/list.h>

#include "../../Conexion-Serializacion/serializacion.h"
#include "../../Conexion-Serializacion/utils.h"

#include "estructuras_cliente.h"

t_log* iniciar_logger(void);
t_config* leer_config(void);
void limpiar (char *cadena);//

void terminar_programa(int, t_log*, t_config*);



int main(void) {
	char* cadena=malloc(125);
	char* comando=malloc(25);
	char* argumento1=malloc(25);
	char* argumento2=malloc(25);
	char* argumento3=malloc(25);
	char* argumento4=malloc(25);
	int salida=1;
	char eleccion;
	char* basura=malloc(1);
	int id_pedido;



//------------------------------CONEXION y LOG----------------------
	//int conexion;
	char* ip;
	char* puerto;
	//char* valor;


	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"
	log_info(logger,"Soy un log");

	config = leer_config();

	ip= config_get_string_value(config,"IP");
	puerto= config_get_string_value(config, "PUERTO");

	char* id_cliente = config_get_string_value(config, "ID_CLIENTE");
	int posicion_x= config_get_int_value(config, "POSICION_X");
	int posicion_y= config_get_int_value(config, "POSICION_Y");

	conexion = crear_conexion(ip, puerto);
	if (conexion==-1){
		return 0;
	}

//-------------------------------HANDSHAKE-------------------------
	/*enviar_handshake_cliente(id_cliente, posicion_x, posicion_y, conexion);
	int cod_op = recibir_operacion(conexion);
	switch(cod_op){
		case HANDSHAKE_APP:
		log_info(logger,"Conexion con el modulo APP exitoso");
		break;
		case HANDSHAKE_RESTAURANTE:
		log_info(logger,"Conexion con el modulo Restaurante exitoso");
		break;
		case HANDSHAKE_SINDICATO:
		log_info(logger,"Conexion con el modulo Sindicato exitoso");
		break;
		case HANDSHAKE_COMANDA:
		log_info(logger,"Conexion con el modulo Comanda exitoso");
		break;
	}*/

//-------------------------------CrearHilo Escucha-----------------------
	int err;
	err = pthread_create(&escucha, NULL, escuchar, NULL);
	if (err!=0){
		printf("\nHubo un error en la creacion del hilo\n");
		return err;
	}

//---------------------------------------------------------envio de mensaje y comandos-------------------
	while(salida==1){

	printf("Escribe el comando\n");

	fgets(cadena,125,stdin);
	limpiar(cadena); //para eliminar el \n del final

	char** cadenaSeparada = string_split(cadena, " ");

	comando= *cadenaSeparada;

	//prueba de envio de msj, se envia el comando ingresado
	//enviar_mensaje(comando,conexion);

	//Se divide el comportamiento segun el comando ingresado, lo que tiene cada if es simplemente a modo de prueba
	if(strcmp(comando,"ConsultarRestaurantes")==0){
		enviar_consultar_restaurantes(conexion);
		printf("enviada la consulta\n");
	}

	if(strcmp(comando,"SeleccionarRestaurante")==0){
		argumento1= *(cadenaSeparada+1);
		enviar_seleccionar_restaurante(id_cliente, posicion_x, posicion_y, argumento1, conexion);
	}

	if(strcmp(comando,"ObtenerRestaurante")==0){
		argumento1= *(cadenaSeparada+1);
		enviar_obtener_restaurante(argumento1, conexion);
		printf("Datos de %s, enviado el msj\n", argumento1);
	}

	if(strcmp(comando,"ConsultarPlatos")==0){
		argumento1= *(cadenaSeparada+1);
		enviar_consultar_platos(argumento1, conexion);
		printf("platos de %s\n", argumento1);
	}

	if(strcmp(comando,"CrearPedido")==0){
		enviar_crear_pedido(conexion);
		//agregado
		/*err = pthread_create(&pedidos, NULL, pedido, conexion);
		if (err!=0){
			printf("\nHubo un error en la creacion del hilo\n");
			return err;
		}
		printf("enviado msj de crear pedido\n");*/
	}

	if(strcmp(comando,"GuardarPedido")==0){//LISTO
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		id_pedido= atoi(argumento2);
		enviar_guardar_pedido(argumento1, id_pedido, conexion);
	}

	if(strcmp(comando,"AñadirPlato")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		id_pedido=atoi(argumento2);
		enviar_aniadir_plato(argumento1, id_pedido, conexion);
		printf("ok o fail\n");
	}

	if(strcmp(comando,"GuardarPlato")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		argumento3= *(cadenaSeparada+3);
		argumento4= *(cadenaSeparada+4);
		id_pedido= atoi(argumento2);
		int cantidad;
		cantidad=atoi(argumento4);
		enviar_guardar_plato(argumento1, id_pedido, argumento3, cantidad, conexion);
		printf("ok o fail\n");
	}

	if(strcmp(comando,"ConfirmarPedido")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		id_pedido= atoi(argumento2);
		enviar_confirmar_pedido(argumento1, id_pedido, conexion);
		printf("ok o fail pedido: %s\n", argumento1);
	}

	if(strcmp(comando,"PlatoListo")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		argumento3= *(cadenaSeparada+3);
		id_pedido= atoi(argumento2);
		enviar_plato_listo(argumento1, id_pedido, argumento3, conexion);
		printf("ok o fail\n");
	}

	if(strcmp(comando,"ConsultarPedido")==0){
		argumento1= *(cadenaSeparada+1);
		id_pedido= atoi(argumento1);
		enviar_consultar_pedido(id_pedido, conexion);
		printf("datos de pedido: %s\n", argumento1);
	}

	if(strcmp(comando,"ObtenerPedido")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		id_pedido=atoi(argumento2);
		enviar_obtener_pedido(argumento1, id_pedido, conexion);
		printf("datos de pedido: %s\n", argumento2);
	}

	if(strcmp(comando,"FinalizarPedido")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		id_pedido=atoi(argumento2);
		enviar_finalizar_pedido(argumento1, id_pedido, conexion);
		printf("ok o fail\n");
	}

	if(strcmp(comando,"TerminarPedido")==0){
		argumento1= *(cadenaSeparada+1);
		argumento2= *(cadenaSeparada+2);
		id_pedido=atoi(argumento2);
		enviar_terminar_pedido(argumento1, id_pedido, conexion);
		printf("ok o fail\n");
	}
	if(strcmp(comando, "ObtenerReceta")==0){
		argumento1= *(cadenaSeparada+1);
		enviar_obtener_receta(argumento1, conexion);
		printf("enviado plato para obtener receta \n");
	}/*
	if(strcmp(comando, "ResponderObtenerRestaurante")==0){

		responder_obtener_restaurante(afinidades, posX, posY, recetas, precios,cantHornos, cantPedidos, conexion);
		printf("Envie el msj\n");
	}*/
	if(strcmp(comando,"Salir")==0){
		salida=0;
	}
	}

	//se liberan los malloc
	free(comando);
	free(argumento1);
	free(argumento2);
	free(argumento3);
	free(argumento4);
	free(cadena);
	free(basura);

	terminar_programa(conexion, logger, config);
	return 0;
}

t_log* iniciar_logger(void){
	return log_create("Configs-Logs/Cliente.log","Cliente",1,LOG_LEVEL_INFO);
}

t_config* leer_config(void){
	return config_create("Configs-Logs/Cliente.config");
}

void limpiar (char *cadena){
	char *p;
	p= strchr (cadena,'\n');
	if(p){
		*p='\0';
	}
}

void terminar_programa(int conexion, t_log* logger, t_config* config){
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	config_destroy(config);
	close(conexion);
}




