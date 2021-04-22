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
#include "Ejercitacion.h"

int main(void) {
	puts("Hola");
	int a=1;
	int b;
	b = funcionTest(a);
	return EXIT_SUCCESS;
}

int funcionTest (int a){
	return a;
}
