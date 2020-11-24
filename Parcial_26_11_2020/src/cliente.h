/*
 * cliente.h
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#define SIZE_NOMBRE 10000
#define SIZE_APELLIDO 10000
#define SIZE_CUIT 10000

typedef struct
{
	char nombre[SIZE_NOMBRE];
	char apellido[SIZE_APELLIDO];
	char cuit[SIZE_CUIT];
	int idCliente;

}Cliente;

Cliente* cliente_new(void);
Cliente* cliente_newParametros(char* idCliente, char* nombre, char* apellido, char* cuit);
void cliente_delete(Cliente* this);
int cliente_findClienteById(LinkedList* pArrayListaClientes, int id);
int cliente_findClienteByIdAndImprimir(LinkedList* pArrayListaClientes, int id);
int cliente_CalcularCantidadVentasCobradas(void* pElement);
int cliente_esCuitRepetido(LinkedList* pArrayListaClientes, char* pCuit);

int cliente_setIdClienteTxt(Cliente* this, char* idClienteACargar);
int cliente_getIdClienteTxt(Cliente* this, char* idCliente);

int cliente_setIdCliente(Cliente* this, int idClienteACargar);
int cliente_getIdCliente(Cliente* this, int* idCliente);

int cliente_setNombre(Cliente* this, char* nombre);
int cliente_getNombre(Cliente* this, char* nombre);

int cliente_setApellido(Cliente* this, char* apellido);
int cliente_getApellido(Cliente* this, char* apellido);

int cliente_setCuit(Cliente* this, char* cuit);
int cliente_getCuit(Cliente* this, char* cuit);

#endif /* CLIENTE_H_ */
