/*
 * cliente.c
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "cliente.h"
#include "ventas.h"
#include "utn.h"

/*
* \brief Función que genera un nuevo cliente en memoria.
* \return puntero del tipo Cliente*.
*/
Cliente* cliente_new(void)
{
	Cliente* newCliente = NULL;
	newCliente = (Cliente*)malloc(sizeof(Cliente));
	return newCliente;
}

/*
* \brief Función que genera un nuevo cliente con parámetros.
* \param char* ID a setear.
* \param char* nombre a setear.
* \param char* apellido a setear.
* \param char* cuit a setear.
* \return puntero del tipo Cliente*.
*/
Cliente* cliente_newParametros(char* idCliente, char* nombre, char* apellido, char* cuit)
{
	Cliente* pCliente = NULL;

	if(idCliente != NULL && nombre != NULL && apellido != NULL && cuit != NULL)
	{
		pCliente = cliente_new();
		if (pCliente != NULL)
		{
			cliente_setIdClienteTxt(pCliente, idCliente);
			cliente_setNombre(pCliente, nombre);
			cliente_setApellido(pCliente, apellido);
			cliente_setCuit(pCliente, cuit);
		}
	}
	return pCliente;
}

void cliente_delete(Cliente* this)
{
	free(this);
}

int cliente_findClienteById(LinkedList* pArrayListaClientes, int id)
{
    int retorno = -1;

    int idCliente;

    Cliente* pCliente;

    for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
    {
    	pCliente = ll_get(pArrayListaClientes, i);
        if(cliente_getIdCliente(pCliente, &idCliente) == 0 && idCliente == id)
        {
            retorno = i;
        }
    }
    return retorno;
}

int cliente_findClienteByIdAndImprimir(LinkedList* pArrayListaClientes, int id)
{
	int retorno = -1;

    int idCliente;
    char nombre[10000];
	char apellido[10000];
    char cuit[10000];

    Cliente* pCliente;

    for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
    {
    	pCliente = ll_get(pArrayListaClientes, i);
    	if(cliente_getIdCliente(pCliente, &idCliente) == 0 &&
    	   cliente_getNombre(pCliente, nombre) == 0 &&
    	   cliente_getApellido(pCliente, apellido) == 0 &&
		   cliente_getCuit(pCliente, cuit) == 0 &&
		   idCliente == id)
    	{
    		printf("ID de cliente: %d - Nombre: %s - Apellido: %s - CUIT: %s\n", idCliente, nombre, apellido, cuit);
    		retorno = 0;
    	}
    }
	return retorno;
}

/* Retorna 0 si no es repetido, 1 si es repetido.*/
int cliente_esCuitRepetido(LinkedList* pArrayListaClientes, char* pCuit)
{
	int retorno = 0;

	Cliente* pCliente;

	char cuit[SIZE_CUIT];

	if(pArrayListaClientes != NULL && pCuit != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			if(pCliente != NULL)
			{
				cliente_getCuit(pCliente, cuit);
				if(strncmp(cuit, pCuit, SIZE_CUIT) == 0)
				{
					printf("\nEl CUIT ya existe, por favor ingrese otro.\n");
					retorno = 1;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Función que setea el ID como texto.
* \param Cliente* puntero a cliente.
* \param char* ID a cargar.
* \return (-1) Error (0) todo OK
*/
int cliente_setIdClienteTxt(Cliente* this, char* idClienteACargar)
{
	int retorno = -1;
	if(this != NULL && idClienteACargar != NULL)
	{
		if(utn_isNumeric(idClienteACargar))
		{
			retorno = 0;
			this->idCliente = atoi(idClienteACargar);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene el ID como texto.
* \param Cliente* puntero al cliente.
* \param char* puntero al espacio donde guardará el ID.
* \return (-1) Error (0) todo OK
*/
int cliente_getIdClienteTxt(Cliente* this, char* idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente != NULL)
	{
		retorno = 0;
		sprintf(idCliente,"%d",this->idCliente);
	}
	return retorno;
}

/*
* \brief Función que setea el ID como int
* \param Cliente* puntero a cliente.
* \param int ID a cargar.
* \return (-1) Error (0) todo OK
*/
int cliente_setIdCliente(Cliente* this, int idClienteACargar)
{
	int retorno = -1;
	if(this != NULL && idClienteACargar >= 0)
	{
		retorno = 0;
		this->idCliente = idClienteACargar;
	}
	return retorno;
}

/*
* \brief Función que obtiene el ID como int.
* \param Cliente* puntero a cliente.
* \param int* puntero al espacio donde guardará el ID.
* \return (-1) Error (0) todo OK
*/
int cliente_getIdCliente(Cliente* this, int* idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente != NULL)
	{
		retorno = 0;
		*idCliente = this->idCliente;
	}
	return retorno;
}

/*
* \brief Función que setea el nombre.
* \param Cliente* puntero a cliente.
* \param char* nombre a cargar.
* \return (-1) Error (0) todo OK
*/
int cliente_setNombre(Cliente* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(utn_isAlphabetic(nombre))
		{
			retorno = 0;
			strncpy(this->nombre, nombre, SIZE_NOMBRE);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene el nombre como texto.
* \param Cliente* puntero a cliente.
* \param char* puntero al espacio donde guardará el nombre.
* \return (-1) Error (0) todo OK
*/
int cliente_getNombre(Cliente* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre, this->nombre, SIZE_NOMBRE);
	}
	return retorno;
}

/*
* \brief Función que setea el apellido.
* \param Cliente* puntero a cliente.
* \param char* apellido a cargar.
* \return (-1) Error (0) todo OK
*/
int cliente_setApellido(Cliente* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		if(utn_isAlphabetic(apellido))
		{
			retorno = 0;
			strncpy(this->apellido, apellido, SIZE_APELLIDO);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene el apellido como texto.
* \param Cliente* puntero a cliente.
* \param char* puntero al espacio donde guardará el apellido.
* \return (-1) Error (0) todo OK
*/
int cliente_getApellido(Cliente* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		retorno = 0;
		strncpy(apellido, this->apellido, SIZE_APELLIDO);
	}
	return retorno;
}

/*
* \brief Función que setea el CUIT.
* \param Cliente* puntero a cliente.
* \param char* CUIT a cargar.
* \return (-1) Error (0) todo OK
*/
int cliente_setCuit(Cliente* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL && cuit != NULL)
	{
		if(utn_isCuit(cuit, SIZE_CUIT))
		{
			retorno = 0;
			strncpy(this->cuit, cuit, SIZE_CUIT);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene el CUIT como texto.
* \param Cliente* puntero a cliente.
* \param char* puntero al espacio donde guardará el CUIT.
* \return (-1) Error (0) todo OK
*/
int cliente_getCuit(Cliente* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL && cuit != NULL)
	{
		retorno = 0;
		strncpy(cuit, this->cuit, SIZE_CUIT);
	}
	return retorno;
}
