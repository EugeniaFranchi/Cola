#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CANT_ENCOLAR_VOLUMEN 500
#define CANT_ENCOLAR_DESENCOLADA 20

void pruebas_crear_destruir(){
	printf("\n--CREAR/DESTRUIR--\n");
	void* nulo = NULL;
	cola_t* col = cola_crear();
	print_test("Se creo una cola", col!=NULL);
	cola_destruir(col, nulo);
	print_test("Se destruyo la cola", true);	
}

void pruebas_destruir(){
	printf("\n--DESTRUIR DATOS--\n");
	char* dato = malloc(sizeof(char));
	if (!dato){
		return;
	}
	char* dato1 = malloc(sizeof(char));
	if (!dato1){
		return;
	}
	char* dato2 = malloc(sizeof(char));
	if (!dato2){
		return;
	}
	char* dato3 = malloc(sizeof(char));
	if (!dato3){
		return;
	}
	
	/*Pruebas de 1 elemento*/
	cola_t* col = cola_crear();
	print_test("Creo una cola", col!=NULL);
	print_test("Encolo un dato", cola_encolar(col, dato) == true);
	cola_destruir(col, free);
	print_test("Destruyo la cola y su dato", true);
	
	/*Pruebas de varios elementos*/
	col = cola_crear();
	print_test("Creo una cola", col!=NULL);
	print_test("Encolo dato1", cola_encolar(col, dato1) == true);
	print_test("Encolo dato2", cola_encolar(col, dato2) == true);
	print_test("Encolo dato3", cola_encolar(col, dato3) == true);
	cola_destruir(col, free);
	print_test("Destruyo la cola y sus datos", true);
}

void pruebas_cola_vacia(){
	printf("\n--VACIA--\n");
	void* vacio = cola_crear();
	
    print_test("Esta vacia", cola_esta_vacia(vacio) == true);
    print_test("No puedo desencolar", cola_desencolar(vacio) == NULL);
    print_test("No hay primero", cola_ver_primero(vacio) == NULL);
    
    cola_destruir(vacio, NULL);
}

void pruebas_desencolar_encolar(){
	printf("\n--ENCOLAR/DESENCOLAR--\n");
	int valor1[] = {0};
	int valor2[] = {489};
	int valor3[] = {68};
	void* nulo = NULL;
	cola_t* cola1 = cola_crear();
	
	/*Pruebas de 1 elemento*/
	print_test("Encolo valor1",cola_encolar(cola1, valor1) == true);
	print_test("No esta vacia", cola_esta_vacia(cola1) == false);
	print_test("Desencolar valor1", cola_desencolar(cola1) == valor1);
	print_test("Esta vacia", cola_esta_vacia(cola1) == true);
	
	/*Pruebas de varios elementos*/
	print_test("Encolo valor2",cola_encolar(cola1, valor2) == true);
	print_test("No esta vacia", cola_esta_vacia(cola1) == false);
	print_test("Encolo valor3",cola_encolar(cola1, valor3) == true);
	print_test("No esta vacia", cola_esta_vacia(cola1) == false);
	print_test("Desencolar valor2", cola_desencolar(cola1) == valor2);
	print_test("No esta vacia", cola_esta_vacia(cola1) == false);
	print_test("Desencolar valor3", cola_desencolar(cola1) == valor3);
	print_test("Esta vacia", cola_esta_vacia(cola1) == true);
	
	/*Pruebas con NULL*/
	print_test("Encolo NULL",cola_encolar(cola1, nulo) == true);
	print_test("No esta vacia", cola_esta_vacia(cola1) == false);
	print_test("Desencolo NULL", cola_desencolar(cola1) == nulo);
	print_test("Esta vacia", cola_esta_vacia(cola1) == true);

	cola_destruir(cola1, NULL);
}

void pruebas_ver_primero(){
	printf("\n--VER PRIMERO--\n");
	cola_t* cola2 = cola_crear();
	int valor1[] = {45};
	int valor2[] = {765};
	void* nulo = NULL;
	
	/*Pruebas con elementos*/
	print_test("Encolo valor1",cola_encolar(cola2, valor1) == true);
	print_test("El primero es valor1",cola_ver_primero(cola2) == valor1);
	print_test("Encolo valor2",cola_encolar(cola2, valor2) == true);
	print_test("El primero es valor1",cola_ver_primero(cola2) == valor1);
	print_test("Desencolo valor1", cola_desencolar(cola2) == valor1);
	print_test("El primero es valor2",cola_ver_primero(cola2) == valor2);
	print_test("Desencolo valor2", cola_desencolar(cola2) == valor2);
	print_test("No tiene primero.",cola_ver_primero(cola2) == NULL);
	
	/*Pruebas con NULL*/
	print_test("Encolo NULL",cola_encolar(cola2, nulo) == true);
	print_test("El primero es NULL",cola_ver_primero(cola2) == nulo);
	print_test("Desencolo NULL", cola_desencolar(cola2) == nulo);
	print_test("No tiene primero.",cola_ver_primero(cola2) == NULL);
	
	cola_destruir(cola2, NULL);
}

void pruebas_volumen(){
	printf("\n--VOLUMEN--\n");
	cola_t* cola3 = cola_crear();
	int valor[] = {23};
	
	/*Pruebas encolando*/
	for (int i = 0; i < CANT_ENCOLAR_VOLUMEN; i++){
		cola_encolar(cola3, valor);
	}
	print_test("Puede encolar 500 elementos", true);
	
	/*Pruebas desencolando*/
	for (int i = 0; i < CANT_ENCOLAR_VOLUMEN; i++){
		cola_desencolar(cola3);
	}
	print_test("Puede desencolar 500 elementos", true);
	
	cola_destruir(cola3, NULL);
}

void pruebas_desencolada(){
	printf("\n--DESENCOLADA--\n");
	cola_t* cola4 = cola_crear();
	int valor[] = {89};
	
	/*Apilo*/
	for (int i = 0; i < CANT_ENCOLAR_DESENCOLADA; i++){
		cola_encolar(cola4, valor);
	}
	
	/*Desapilo*/
	for (int i = 0; i < CANT_ENCOLAR_DESENCOLADA; i++){
		cola_desencolar(cola4);
	}
	
	/*Compruebo que desencolada por completo se comporta como recien creada*/
    print_test("Esta vacia", cola_esta_vacia(cola4) == true);
	print_test("No puedo desencolar", cola_desencolar(cola4) == NULL);
    print_test("No hay tope", cola_ver_primero(cola4) == NULL);
	
	cola_destruir(cola4, NULL);
}

void pruebas_cola_alumno() {
	pruebas_crear_destruir();
	pruebas_destruir();
    pruebas_cola_vacia();
    pruebas_desencolar_encolar();
    pruebas_ver_primero();
    pruebas_volumen();
    pruebas_desencolada();
}

