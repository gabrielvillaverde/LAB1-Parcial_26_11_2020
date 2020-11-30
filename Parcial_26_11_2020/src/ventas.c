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
* \brief Funci�n que genera una nueva venta en memoria.
* \return puntero del tipo Venta*.
*/
Venta* venta_new(void)
{
	Venta* newVenta = NULL;
	newVenta = (Venta*) malloc (sizeof(Venta));
	return newVenta;
}


/*
* \brief Funci�n que genera una nueva venta con par�metros.
* \param char* ID de cliente a setear.
* \param char* ID de venta a setear.
* \param char* cantidad de afiches a setear.
* \param char* nombre de archivo a setear.
* \param char* zona a setear.
* \param char* estado de cobrado a setear.
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
			venta_setZonaTxt(pVenta, zona);
			venta_setCobradoTxt(pVenta, cobrado);
		}
	}
	return pVenta;
}

/*
* \brief Funci�n que borra una venta y libera espacio de memoria.
* \param Venta* Puntero a la venta.
*/
void venta_delete(Venta* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/*
* \brief Funci�n que chequea que la venta no est� cobrada (en estado 0).
* \param void* es el puntero al elemento que recibe como par�metro.
* \Retorna 1 si la venta no est� cobrada, retorna 0 si error.
*/
int venta_chequearEstadoNoCobrado(void* pElement)
{
	int retorno = 0;

	int cobrado;

	Venta* pVenta = (Venta*) pElement;

	if(pVenta != NULL)
	{
		venta_getCobrado(pVenta, &cobrado);

		if(cobrado == 0)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/*
* \brief Funci�n que chequea que la venta est� cobrada (en estado 1).
* \param void* es el puntero al elemento que recibe como par�metro.
* \Retorna 1 si la venta est� cobrada, retorna 0 si error.
*/
int venta_chequearEstadoSiCobrado(void* pElement)
{
	int retorno = 0;

	int cobrado;

	Venta* pVenta = (Venta*) pElement;

	if(pVenta != NULL)
	{
		venta_getCobrado(pVenta, &cobrado);

		if(cobrado == 1)
		{
			retorno = 1;
		}
	}
	return retorno;
}

/*
* \brief Funci�n que chequea el ID del cliente.
* \param void* es el puntero al ID que recibe como par�metro.
* \Retorna 1 si el ID coincide, 0 para error.
*/
int venta_chequearId(void* pElement, void* pId)
{
	int retorno = 0;

	int idCliente;

	Venta* pVenta = (Venta*) pElement;

	int* pIdAuxiliar = (int*) pId; // Casteo como puntero a entero y lo guardo en un puntero auxiliar a entero.

	if(pVenta != NULL)
	{
		venta_getIdCliente(pVenta, &idCliente); // Obtengo el ID del cliente.

		if(idCliente == *pIdAuxiliar) // Comparo el ID del cliente con el puntero a entero del ID del cliente que recibo como par�metro.
		{
			retorno = 1;
		}
	}
	return retorno;
}

/*
* \brief Funci�n que chequea el ID del cliente y el estado de la cobranza.
* \param void* es el puntero al ID que recibe como par�metro.
* \param void* es el puntero al estado que recibe como par�metro.
* \Retorna 1 si el ID y el estado de la cobranza coinciden, 0 para error.
*/
int venta_chequearIdYEstadoCobranza(void* pElement, void* pId, void* pEstado)
{
	int retorno = 0;

	int cobrado;
	int idCliente;

	Venta* pVenta = (Venta*) pElement;

	int* pIdAuxiliar = (int*) pId; // Casteo como puntero a entero y lo guardo en un puntero auxiliar a entero.
	int* pEstadoAuxiliar = (int*) pEstado; // Casteo como puntero a entero y lo guardo en un puntero auxiliar a entero.

	if(pVenta != NULL)
	{
		venta_getCobrado(pVenta, &cobrado); // Obtengo el valor cobrado.
		venta_getIdCliente(pVenta, &idCliente); // Obtengo el ID del cliente.

		if(cobrado == *pEstadoAuxiliar && idCliente == *pIdAuxiliar) // Comparo el ID del cliente con el puntero a entero del ID del cliente que recibo como par�metro.
		{
			retorno = 1;
		}
	}
	return retorno;
}

/*
* \brief Funci�n que chequea el ID del cliente y la cantidad de afiches que tiene.
* \param void* es el puntero al elemento que recibe como par�metro.
* \param void* es el puntero al ID que recibe como par�metro.
* \Retorna la cantidad de afiches del cliente, retorna 0 si da alg�n error.
*/
int venta_chequearIdYCalcularCantidadAfiches(void* pElement, void* pId)
{
	int retorno = 0;

	int cantidadAfiches;
	int idCliente;

	Venta* pVenta = (Venta*) pElement;

	int* pIdAuxiliar = (int*) pId;

	if(pVenta != NULL)
	{
		venta_getIdCliente(pVenta, &idCliente);
		venta_getCantidadAfiches(pVenta, &cantidadAfiches);

		if(idCliente == *pIdAuxiliar) // Comparo el ID del cliente con el puntero a entero del ID del cliente que recibo como par�metro.
		{
			retorno = cantidadAfiches;
		}
	}
	return retorno;
}

/*
* \brief Funci�n que retorna la cantidad de afiches.
* \param void* es el puntero al elemento que recibe como par�metro.
* \Retorna la cantidad de afiches, retorna 0 si da alg�n error.
*/
int venta_calcularCantidadAfiches(void* pElement)
{
	int retorno = 0;

	int cantidadAfiches;

	Venta* pVenta = (Venta*) pElement;

	if(pVenta != NULL)
	{
		venta_getCantidadAfiches(pVenta, &cantidadAfiches);
		retorno = cantidadAfiches;
	}
	return retorno;
}

/*
* \brief Funci�n que busca una venta por el ID que recibe como par�metro.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \param int, es el ID que recibe como par�metro.
* \Retorna -1 si no encontr� el ID de la venta, o retorna el �ndice de la venta si encontr� el ID.
*/
int venta_findVentaById(LinkedList* pArrayListaVentas, int id)
{
    int retorno = -1;

    int idVenta;

    Venta* pVenta;

    if(pArrayListaVentas != NULL && id > 0)
    {
        for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
        {
        	pVenta = ll_get(pArrayListaVentas, i);

        	if(pVenta != NULL)
        	{
            	venta_getIdVenta(pVenta, &idVenta);

                if(idVenta == id)
                {
                    retorno = i;
                    break;
                }
        	}
        }
    }
    return retorno;
}

/*
* \brief Funci�n que busca una venta por el ID que recibe como par�metro.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \param int, es el ID que recibe como par�metro.
* \param int, es el estado que recibe como par�metro.
* \Retorna -1 si no encontr� el ID de la venta o el estado de cobranza no coincide con el pasado como par�metro, o retorna el �ndice de la venta si encontr� el ID y el estado de cobranza coincide.
*/
int venta_findVentaByIdAndCheckEstadoCobranza(LinkedList* pArrayListaVentas, int id, int estado)
{
    int retorno = -1;

    int idVenta;
    int estadoCobranza;

    Venta* pVenta;

    if(pArrayListaVentas != NULL && id > 0)
    {
        for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
        {
        	pVenta = ll_get(pArrayListaVentas, i);

        	if(pVenta != NULL)
        	{
            	venta_getIdVenta(pVenta, &idVenta);
            	venta_getCobrado(pVenta, &estadoCobranza);

                if(idVenta == id && estadoCobranza == estado)
                {
                    retorno = i;
                    break;
                }
            }
        	}
    }
    return retorno;
}

/*
* \brief Funci�n que setea el ID como texto.
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
* \brief Funci�n que obtiene el ID como texto.
* \param Cliente* puntero al cliente.
* \param char* puntero al espacio donde guardar� el ID.
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
* \brief Funci�n que setea el ID como int.
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
* \brief Funci�n que obtiene el ID como int.
* \param Cliente* puntero a cliente.
* \param int* puntero al espacio donde guardar� el ID.
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
* \brief Funci�n que setea el ID como texto.
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
* \brief Funci�n que obtiene el ID como texto.
* \param Venta* puntero al venta.
* \param char* puntero al espacio donde guardar� el ID.
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
* \brief Funci�n que setea el ID como int.
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
* \brief Funci�n que obtiene el ID como int.
* \param Venta* puntero a venta.
* \param int* puntero al espacio donde guardar� el ID.
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

/*
* \brief Funci�n que setea la cantidad de afiches como int.
* \param Venta* puntero a venta.
* \param int cantidad de afiches a cargar.
* \return (-1) Error (0) todo OK
*/
int venta_setCantidadAfiches(Venta* this, int cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches >= 0)
	{
		retorno = 0;
		this->cantidadAfiches = cantidadAfiches;
	}
	return retorno;
}

/*
* \brief Funci�n que obtiene la cantidad de afiches como int.
* \param Venta* puntero a venta.
* \param int* puntero al espacio donde guardar� la cantidad de afiches.
* \return (-1) Error (0) todo OK
*/
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
* \brief Funci�n que setea la cantidad de afiches como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde se guardar� la cantidad de afiches.
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
* \brief Funci�n que obtiene la cantidad de afiches como texto.
* \param Venta* puntero a venta.
* \param int* puntero al espacio donde guardar� la cantidad de afiches.
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
* \brief Funci�n que setea el nombre del archivo.
* \param Venta* puntero a venta.
* \param char* nombre de archivo a cargar.
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
* \brief Funci�n que obtiene el nombre como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde guardar� el nombre.
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
* \brief Funci�n que setea la zona como int.
* \param Venta* puntero a venta.
* \param int zona a seteaer
* \return (-1) Error (0) todo OK
*/
int venta_setZona(Venta* this, int zona)
{
	int retorno = -1;
	if(this != NULL && (zona == 0 || zona == 1 || zona == 2))
	{
		retorno = 0;
		this->zona = zona;
	}
	return retorno;
}

/*
* \brief Funci�n que obtiene zona como int.
* \param Venta* puntero a venta.
* \param int* puntero al espacio donde guardar� la zona.
* \return (-1) Error (0) todo OK
*/
int venta_getZona(Venta* this, int* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		retorno = 0;
		*zona = this->zona;
	}
	return retorno;
}

/*
* \brief Funci�n que setea la zona como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde guardar� la zona.
* \return (-1) Error (0) todo OK
*/
int venta_setZonaTxt(Venta* this, char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		if(utn_isNumeric(zona))
		{
			retorno = 0;
			this->zona = atoi(zona);
		}
	}
	return retorno;
}

/*
* \brief Funci�n que obtiene la zona como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde guardar� la zona.
* \return (-1) Error (0) todo OK
*/
int venta_getZonaTxt(Venta* this, char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		retorno = 0;
		sprintf(zona, "%d", this->zona);
	}
	return retorno;
}

/*
* \brief Funci�n que setea el valor cobrado como int.
* \param Venta* puntero a venta.
* \param int valor cobrado a cargar.
* \return (-1) Error (0) todo OK
*/
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

/*
* \brief Funci�n que obtiene el valor cobrado como int.
* \param Venta* puntero a venta.
* \param int* puntero al espacio donde guardar� el valor cobrado.
* \return (-1) Error (0) todo OK
*/
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

/*
* \brief Funci�n que setea el valor cobrado como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde guardar� el valor cobrado.
* \return (-1) Error (0) todo OK
*/
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

/*
* \brief Funci�n que obtiene el valor cobrado como texto.
* \param Venta* puntero a venta.
* \param char* puntero al espacio donde guardar� el valor cobrado.
* \return (-1) Error (0) todo OK
*/
int venta_getCobradoTxt(Venta* this, char* cobrado)
{
	int retorno = -1;
	if(this != NULL && cobrado != NULL)
	{
		retorno = 0;
		sprintf(cobrado, "%d", this->cobrado);
	}
	return retorno;
}
