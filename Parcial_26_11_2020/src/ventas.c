/*
 * ventas.c
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "ventas.h"
#include "utn.h"

/*
* \brief Función que genera una nueva venta en memoria.
* \return puntero del tipo Venta*.
*/
Venta* venta_new(void)
{
	Venta* newVenta = NULL;
	newVenta = (Venta*)malloc(sizeof(Venta));
	return newVenta;
}


/*
* \brief Función que genera una nueva venta con parámetros.
* \param
* \param
* \param
* \param
* \return
*/
Venta* venta_newParametros(char* idCliente, char* idVenta, char* cantidadAfiches, char* nombreArchivo, char* zona, char* cobrado)
{
	Venta* pVenta = NULL;

	if(idCliente != NULL && idVenta != NULL && cantidadAfiches != NULL && nombreArchivo != NULL && zona != NULL)
	{
		pVenta = venta_new();
		if(pVenta != NULL)
		{
			venta_setIdClienteTxt(pVenta, idCliente);
			venta_setIdVentaTxt(pVenta, idVenta);
			venta_setCantidadAfichesTxt(pVenta, cantidadAfiches);
			venta_setNombreArchivo(pVenta, nombreArchivo);
			venta_setZona(pVenta, zona);
			venta_setCobradoTxt(pVenta, cobrado);
		}
	}
	return pVenta;
}

void venta_delete(Venta* this)
{
	free(this);
}

/*
 * Retorna 1 si OK, 0 ERROR.
 */
int venta_chequearEstadoNoCobrado(void* pElement)
{
	int retorno = 0;
	int cobrado;

	if(pElement != NULL)
	{
		venta_getCobrado((Venta*)pElement, &cobrado);
		if(cobrado == 0)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * Retorna 1 si OK, 0 ERROR.
 */
int venta_chequearEstadoCobrado(void* pElement)
{
	int retorno = 0;
	int cobrado;

	if(pElement != NULL)
	{
		venta_getCobrado((Venta*)pElement, &cobrado);
		if(cobrado == 1)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/*
 * Retorna 1 si OK, 0 ERROR.
 */
int venta_chequearIdYEstadoCobranza(void* pElement, void* pId, void* pEstado)
{
	int retorno = 0;

	int cobrado;
	int idCliente;

	int* pIdAuxiliar = (int*) pId; // Casteo como puntero a entero y lo guardo en un puntero auxiliar a entero.
	int* pEstadoAuxiliar = (int*) pEstado; // Casteo como puntero a entero y lo guardo en un puntero auxiliar a entero.

	if(pElement != NULL)
	{
		venta_getCobrado((Venta*)pElement, &cobrado); // Obtengo el valor cobrado.
		venta_getIdCliente((Venta*)pElement, &idCliente); // Obtengo el ID del cliente.
		if(cobrado == *pEstadoAuxiliar && idCliente == *pIdAuxiliar) // Comparo el ID del cliente con el puntero a entero del ID del cliente que recibo como parámetro.
		{
			retorno = 1;
		}
	}
	return retorno;
}

/* Retorna la cantidad de afiches. */
int venta_chequearIdYCalcularCantidadAfiches(void* pElement, void* pId)
{
	int retorno = 0;

	int idCliente;
	int cantidadAfiches;

	Venta* pVenta = (Venta*) pElement;

	int* pIdAuxiliar = (int*) pId;

	if(pVenta != NULL)
	{
		venta_getIdCliente(pVenta, &idCliente);
		venta_getCantidadAfiches(pVenta, &cantidadAfiches);
		if(idCliente == *pIdAuxiliar) // Comparo el ID del cliente con el puntero a entero del ID del cliente que recibo como parámetro.
		{
			retorno = cantidadAfiches;
		}
	}
	return retorno;
}

int venta_findVentaById(LinkedList* pArrayListaVentas, int id)
{
    int retorno = -1;
    int idAux;

    Venta* pVenta;

    for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
    {
    	pVenta = ll_get(pArrayListaVentas, i);
        if(venta_getIdVenta(pVenta, &idAux) == 0 && idAux == id)
        {
            retorno = i;
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
int venta_setIdClienteTxt(Venta* this, char* idClienteACargar)
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
int venta_getIdClienteTxt(Venta* this, char* idCliente)
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
int venta_setIdCliente(Venta* this, int idClienteACargar)
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
int venta_getIdCliente(Venta* this, int* idCliente)
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
* \brief Función que setea el ID como texto.
* \param Venta* puntero a venta.
* \param char* ID a cargar.
* \return (-1) Error (0) todo OK
*/
int venta_setIdVentaTxt(Venta* this, char* idVentaACargar)
{
	int retorno = -1;
	if(this != NULL && idVentaACargar != NULL)
	{
		if(utn_isNumeric(idVentaACargar))
		{
			retorno = 0;
			this->idVenta = atoi(idVentaACargar);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene el ID como texto.
* \param Venta* puntero al venta.
* \param char* puntero al espacio donde guardará el ID.
* \return (-1) Error (0) todo OK
*/
int venta_getIdVentaTxt(Venta* this, char* idVenta)
{
	int retorno = -1;
	if(this != NULL && idVenta != NULL)
	{
		retorno = 0;
		sprintf(idVenta,"%d",this->idVenta);
	}
	return retorno;
}

/*
* \brief Función que setea el ID como int
* \param Venta* puntero a venta.
* \param int ID a cargar.
* \return (-1) Error (0) todo OK
*/
int venta_setIdVenta(Venta* this, int idVentaACargar)
{
	int retorno = -1;
	if(this != NULL && idVentaACargar >= 0)
	{
		retorno = 0;
		this->idVenta = idVentaACargar;
	}
	return retorno;
}

/*
* \brief Función que obtiene el ID como int.
* \param Venta* puntero a venta.
* \param int* puntero al espacio donde guardará el ID.
* \return (-1) Error (0) todo OK
*/
int venta_getIdVenta(Venta* this, int* idVenta)
{
	int retorno = -1;
	if(this != NULL && idVenta != NULL)
	{
		retorno = 0;
		*idVenta = this->idVenta;
	}
	return retorno;
}

int venta_setCantidadAfiches(Venta* this, int cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches >= 0)
	{
		retorno = 0;
		this->idVenta = cantidadAfiches;
	}
	return retorno;
}

int venta_getCantidadAfiches(Venta* this, int* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches != NULL)
	{
		retorno = 0;
		*cantidadAfiches = this->cantidadAfiches;
	}
	return retorno;
}

/*
* \brief Función que setea
* \param Cliente* puntero a cliente.
* \param char*
* \return (-1) Error (0) todo OK
*/
int venta_setCantidadAfichesTxt(Venta* this, char* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches != NULL)
	{
		if(utn_isNumeric(cantidadAfiches))
		{
			retorno = 0;
			this->cantidadAfiches = atoi(cantidadAfiches);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene
* \param Cliente* puntero al cliente.
* \param char* puntero al espacio
* \return (-1) Error (0) todo OK
*/
int venta_getCantidadAfichesTxt(Venta* this, char* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches != NULL)
	{
		retorno = 0;
		sprintf(cantidadAfiches,"%d",this->cantidadAfiches);
	}
	return retorno;
}

/*
* \brief Función que setea el nombre.
* \param Venta* puntero a venta.
* \param char* nombre a cargar.
* \return (-1) Error (0) todo OK
*/
int venta_setNombreArchivo(Venta* this, char* nombreArchivo)
{
	int retorno = -1;
	if(this != NULL && nombreArchivo != NULL)
	{
		if(utn_isAlphaNumericWithSymbols(nombreArchivo))
		{
			retorno = 0;
			strncpy(this->nombreArchivo, nombreArchivo, SIZE_NOMBRE_ARCHIVO);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene el nombre como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde guardará el nombre.
* \return (-1) Error (0) todo OK
*/
int venta_getNombreArchivo(Venta* this, char* nombreArchivo)
{
	int retorno = -1;
	if(this != NULL && nombreArchivo != NULL)
	{
		retorno = 0;
		strncpy(nombreArchivo, this->nombreArchivo, SIZE_NOMBRE_ARCHIVO);
	}
	return retorno;
}

/*
* \brief Función que
* \param Venta* puntero a venta.
* \param char*
* \return (-1) Error (0) todo OK
*/
int venta_setZona(Venta* this, char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		if(utn_isAlphaNumericWithSymbols(zona))
		{
			retorno = 0;
			strncpy(this->zona, zona, SIZE_ZONA);
		}
	}
	return retorno;
}

/*
* \brief Función que obtiene
* \param Venta* puntero a venta.
* \param char*
* \return (-1) Error (0) todo OK
*/
int venta_getZona(Venta* this, char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		retorno = 0;
		strncpy(zona, this->zona, SIZE_ZONA);
	}
	return retorno;
}

int venta_setCobrado(Venta* this, int cobrado)
{
	int retorno = -1;
	if(this != NULL && cobrado >= 0)
	{
		retorno = 0;
		this->cobrado = cobrado;
	}
	return retorno;
}

int venta_getCobrado(Venta* this, int* cobrado)
{
	int retorno = -1;
	if(this != NULL && cobrado != NULL)
	{
		retorno = 0;
		*cobrado = this->cobrado;
	}
	return retorno;
}

int venta_setCobradoTxt(Venta* this, char* cobrado)
{
	int retorno = -1;
	if(this != NULL && cobrado != NULL)
	{
		if(utn_isNumeric(cobrado))
		{
			retorno = 0;
			this->cobrado = atoi(cobrado);
		}
	}
	return retorno;
}

int venta_getCobradoTxt(Venta* this, char* cobrado)
{
	int retorno = -1;
	if(this != NULL && cobrado != NULL)
	{
		retorno = 0;
		sprintf(cobrado,"%d",this->cobrado);
	}
	return retorno;
}
