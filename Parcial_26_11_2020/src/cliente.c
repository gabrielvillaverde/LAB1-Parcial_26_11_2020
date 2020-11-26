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
	if(this != NULL)
	{
		free(this);
	}
}

/* Retorna -1 si no encontró el ID, retorna el índice si encontró el ID. */
int cliente_findClienteById(LinkedList* pArrayListaClientes, int id)
{
    int retorno = -1;

    int idCliente;

    Cliente* pCliente;

    if(pArrayListaClientes != NULL && id > 0)
    {
        for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
        {
        	pCliente = ll_get(pArrayListaClientes, i);
            if(cliente_getIdCliente(pCliente, &idCliente) == 0 && idCliente == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/* Retorna -1 si no encontró el ID, retorna el índice si encontró el ID. */
int cliente_findClienteByIdTxt(LinkedList* pArrayListaClientes, char* pId)
{
    int retorno = -1;

    char idCliente[10000];

    Cliente* pCliente;

    if(pArrayListaClientes != NULL && pId != NULL)
    {
        for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
        {
        	pCliente = ll_get(pArrayListaClientes, i);
            if(cliente_getIdClienteTxt(pCliente, idCliente) == 0)
            {
            	if(strncmp(idCliente, pId, 10000) == 0)
            	{
                    retorno = i;
                    break;
            	}
            }
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

/* Retorna 0 si no es repetido, 1 si es repetido.*/
int cliente_esIdRepetido(LinkedList* pArrayListaClientes, char* pId)
{
	int retorno = 0;

	Cliente* pCliente;

	char idCliente[10000];

	if(pArrayListaClientes != NULL && pId != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			if(pCliente != NULL)
			{
				cliente_getIdClienteTxt(pCliente, idCliente);
				if(strncmp(idCliente, pId, 10000) == 0)
				{
					printf("\nEl ID ya existe, por favor ingrese otro.\n");
					retorno = 1;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Función que ordena los clientes
* \param LinkedList* puntero a la lista de clientes.
* \return (-1) Error (0) todo OK
*/
int cliente_sortClientes(LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	int opcion;
	int orden;

	if(pArrayListaClientes != NULL)
	{
		do
		{
		if(utn_getIntConMinMax("\n1 - Ordenar la lista por nombre."
							   "\n2 - Ordenar la lista por apellido."
							   "\n3 - Ordenar la lista por ID."
							   "\n4 - Volver al menú anterior.\n",
							   "\nError, por favor elija una opción entre 1 y 4.\n", &opcion, 1, 4, 3) == 0)
		{
			if(opcion != 4)
			{
				if(utn_getIntConMinMax("\n¿Cómo quiere ordenar la lista? [1 - Ascendente] - [0 - Descendente]\n",
						      "\nError, escoja una opción entre 1 y 2.\n", &orden, 0, 1, 3) == 0)
				{
					switch(opcion)
					{
						case 1:
							printf("\nUsted ordenó la lista por nombre, ahora puede volver al menú anterior.\n");
							ll_sort(pArrayListaClientes, cliente_compareByName, orden);
							break;
						case 2:
							printf("\nUsted ordenó la lista por apellido, ahora puede volver al menú anterior.\n");
							ll_sort(pArrayListaClientes, cliente_compareByApellido, orden);
							break;
						case 3:
							printf("\nUsted ordenó la lista por ID, ahora puede volver al menú anterior.\n");
							ll_sort(pArrayListaClientes, cliente_compareById, orden);
							break;
					}
				}
			}
		}
		}while(opcion != 4);
	}
	return retorno;
}

/*
* \brief Función que compara los nombres
* \param puntero al primer elemento.
* \param puntero al segundo elemento.
* \return (0) si son iguales, (-1) si el primero es menor al segundo, (1) si el primero es mayor al segundo
*/
int cliente_compareByName(void* pFirstElem, void* pSecondElem)
{
	int retorno = 0;

	char firstName[10000];
	char secondName[10000];

	cliente_getNombre(pFirstElem, firstName);
	cliente_getNombre(pSecondElem, secondName);

	if(strncmp(firstName, secondName, 100) > 0)
	{
		retorno = 1;
	}
	else
	if(strncmp(firstName, secondName, 100) < 0)
	{
		retorno = -1;
	}
	return retorno;
}

/*
* \brief Función que compara los apellidos
* \param puntero al primer elemento.
* \param puntero al segundo elemento.
* \return (0) si son iguales, (-1) si el primero es menor al segundo, (1) si el primero es mayor al segundo
*/
int cliente_compareByApellido(void* pFirstElem, void* pSecondElem)
{
	int retorno = 0;

	char firstApellido[10000];
	char secondApellido[10000];

	cliente_getApellido(pFirstElem, firstApellido);
	cliente_getApellido(pSecondElem, secondApellido);

	if(strncmp(firstApellido, secondApellido, 100) > 0)
	{
		retorno = 1;
	}
	else
	if(strncmp(firstApellido, secondApellido, 100) < 0)
	{
		retorno = -1;
	}
	return retorno;
}

/*
* \brief Función que compara los CUIT
* \param puntero al primer elemento.
* \param puntero al segundo elemento.
* \return (0) si son iguales, (-1) si el primero es menor al segundo, (1) si el primero es mayor al segundo
*/
int cliente_compareByCuit(void* pFirstElem, void* pSecondElem)
{
	int retorno = 0;

	char firstCuit[10000];
	char secondCuit[10000];

	cliente_getCuit(pFirstElem, firstCuit);
	cliente_getCuit(pSecondElem, secondCuit);

	if(strncmp(firstCuit, secondCuit, 100) > 0)
	{
		retorno = 1;
	}
	else
	if(strncmp(firstCuit, secondCuit, 100) < 0)
	{
		retorno = -1;
	}
	return retorno;
}

int cliente_compareById(void* pFirstElem, void* pSecondElem)
{
	int retorno = 0;

	int firstId;
	int secondId;

	cliente_getIdCliente(pFirstElem, &firstId);
	cliente_getIdCliente(pSecondElem, &secondId);

	if(firstId > secondId)
	{
		retorno = 1;
	}
	else if(secondId > firstId)
	{
		retorno = -1;
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
