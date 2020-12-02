/*
 * informes.c
 *
 *  Created on: 25 nov. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "controller.h"
#include "ventas.h"
#include "cliente.h"

#define FALSE 0
#define TRUE 1

/*
* \brief Función que imprime el cliente con más afiches vendidos
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int informes_imprimirClienteConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	Cliente* pCliente = NULL;

	LinkedList* pListaFiltrada;

	int idCliente;
	int idClienteConMasAfiches;
	int cantidadAfiches;
	int cantidadAfichesMaxima;

	int estado = 1;

	int flag = FALSE;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdCliente(pCliente, &idCliente);

			pListaFiltrada = ll_filter3(pArrayListaVentas, venta_chequearIdYEstadoCobranza, &idCliente, &estado);

			if(pListaFiltrada != NULL && ll_len(pListaFiltrada) > 0)
			{
				cantidadAfiches = ll_count(pListaFiltrada, venta_retornarCantidadAfiches);

				if(cantidadAfiches != 0)
				{
					if(flag == FALSE)
					{
						cantidadAfichesMaxima = cantidadAfiches;
						idClienteConMasAfiches = idCliente;
						flag = TRUE;
					}
					else if(cantidadAfiches > cantidadAfichesMaxima)
					{
						cantidadAfichesMaxima = cantidadAfiches;
						idClienteConMasAfiches = idCliente;
					}
				}
			}
		}
		printf("\nEl cliente al que se le vendieron más afiches fue:\n");
		cliente_findClienteByIdAndImprimir(pArrayListaClientes, idClienteConMasAfiches);
		printf("\nCon una cantidad total de: %d\n", cantidadAfichesMaxima);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Función que imprime el cliente con menos afiches vendidos
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int informes_imprimirClienteConMenosAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	Cliente* pCliente = NULL;

	LinkedList* pListaFiltrada;

	int idCliente;
	int idClienteConMenosAfiches;
	int cantidadAfiches;
	int cantidadAfichesMinima;

	int estado = 1;

	int flag = FALSE;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes); i++)
		{
			pCliente = ll_get(pArrayListaClientes, i); // Obtengo el cliente pasándole el índice.
			cliente_getIdCliente(pCliente, &idCliente);

			pListaFiltrada = ll_filter3(pArrayListaVentas, venta_chequearIdYEstadoCobranza, &idCliente, &estado);

			if(pListaFiltrada != NULL && ll_len(pListaFiltrada) > 0) // Para que no reciba lista de ventas vacías, ya que puede haber clientes sin ventas cobradas y su lista filtrada va a tener 0 elementos.
			{
				cantidadAfiches = ll_count(pListaFiltrada, venta_retornarCantidadAfiches);

				if(cantidadAfiches != 0)
				{
					if(flag == FALSE)
					{
						cantidadAfichesMinima = cantidadAfiches;
						idClienteConMenosAfiches = idCliente;
						flag = TRUE;
					}
					else if(cantidadAfiches < cantidadAfichesMinima)
					{
						cantidadAfichesMinima = cantidadAfiches;
						idClienteConMenosAfiches = idCliente;
					}
				}
			}
		}
		printf("\nEl cliente al que se le vendieron menos afiches fue:\n");
		cliente_findClienteByIdAndImprimir(pArrayListaClientes, idClienteConMenosAfiches);
		printf("\nCon una cantidad total de: %d\n", cantidadAfichesMinima);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Función que imprime la venta con más afiches vendidos.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int informes_imprimirVentaConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	LinkedList* pListaFiltrada = NULL;

	Venta* pVenta;

	int cantidadAfiches;
	int cantidadAfichesMaxima;

	int idVenta;
	int idCliente;

	int flag = FALSE;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		pListaFiltrada = ll_filter(pArrayListaVentas, venta_chequearEstadoSiCobrado);

		for(int i = 0 ; i < ll_len(pListaFiltrada) ; i++)
		{
			if(pListaFiltrada != NULL)
			{
				pVenta = ll_get(pListaFiltrada, i);
				venta_getCantidadAfiches(pVenta, &cantidadAfiches);
				if(flag == FALSE)
				{
					cantidadAfichesMaxima = cantidadAfiches;
					venta_getIdVenta(pVenta, &idVenta);
					venta_getIdCliente(pVenta, &idCliente);
					flag = TRUE;
				}
				else if(cantidadAfiches > cantidadAfichesMaxima)
				{
					cantidadAfichesMaxima = cantidadAfiches;
					venta_getIdVenta(pVenta, &idVenta);
					venta_getIdCliente(pVenta, &idCliente);
				}
			}
		}
		printf("\nEl ID de la venta con más afiches vendidos es: %d\n", idVenta);
		printf("\nLos datos del cliente al que corresponde esta venta son los siguientes:\n");
		cliente_findClienteByIdAndImprimir(pArrayListaClientes, idCliente);
		printf("\nCon una cantidad total de: %d\n", cantidadAfichesMaxima);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Función que imprime el cliente con más ventas cobradas
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int informes_imprimirClienteConMasVentasCobradas(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	int idCliente;
	int idClienteConMasVentasCobradas;

	int estado = 1;

	int cantidadVentasCobradas;
	int cantidadVentasCobradasMaxima;

	int flag = FALSE;

	Cliente* pCliente;

	LinkedList* pListaFiltrada;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes); i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdCliente(pCliente, &idCliente);

			pListaFiltrada = ll_filter3(pArrayListaVentas, venta_chequearIdYEstadoCobranza, &idCliente, &estado);

			if(pListaFiltrada != NULL && ll_len(pListaFiltrada) > 0)
			{
				cantidadVentasCobradas = ll_len(pListaFiltrada);

				if(cantidadVentasCobradas != 0)
				{
					if(flag == FALSE)
					{
						cantidadVentasCobradasMaxima = cantidadVentasCobradas;
						idClienteConMasVentasCobradas = idCliente;
						flag = TRUE;
					}
					else if(cantidadVentasCobradas > cantidadVentasCobradasMaxima)
					{
						cantidadVentasCobradasMaxima = cantidadVentasCobradas;
						idClienteConMasVentasCobradas = idCliente;
					}
				}
			}
		}
		printf("\nEl cliente con más ventas cobradas es:\n");
		cliente_findClienteByIdAndImprimir(pArrayListaClientes, idClienteConMasVentasCobradas);
		printf("\nCon una cantidad total de: %d\n", cantidadVentasCobradasMaxima);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Función que imprime el cliente con menos ventas cobradas
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int informes_imprimirClienteConMenosVentasCobradas(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	int idCliente;
	int idClienteConMenosVentasCobradas;

	int estado = 1;

	int cantidadVentasCobradas;
	int cantidadVentasCobradasMinima;

	int flag = FALSE;

	Cliente* pCliente;

	LinkedList* pListaFiltrada;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes); i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdCliente(pCliente, &idCliente);

			pListaFiltrada = ll_filter3(pArrayListaVentas, venta_chequearIdYEstadoCobranza, &idCliente, &estado);

			if(pListaFiltrada != NULL && ll_len(pListaFiltrada) > 0)
			{
				cantidadVentasCobradas = ll_len(pListaFiltrada);

				if(cantidadVentasCobradas != 0)
				{
					if(flag == FALSE)
					{
						cantidadVentasCobradasMinima = cantidadVentasCobradas;
						idClienteConMenosVentasCobradas = idCliente;
						flag = TRUE;
					}
					else if(cantidadVentasCobradas < cantidadVentasCobradasMinima)
					{
						cantidadVentasCobradasMinima = cantidadVentasCobradas;
						idClienteConMenosVentasCobradas = idCliente;
					}
				}
			}
		}
		printf("\nEl cliente con más ventas cobradas es:\n");
		cliente_findClienteByIdAndImprimir(pArrayListaClientes, idClienteConMenosVentasCobradas);
		printf("\nCon una cantidad total de: %d\n", cantidadVentasCobradasMinima);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Función que imprime la zona que más ventas posee.
* \param pArrayListaVentas LinkedList* puntero al array de ventas
* \return (-1) Error (0) todo OK
*/
int informes_imprimirZonaConMasVentas(LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	Venta* pVenta;
	LinkedList* pListaFiltrada;

	int zona;
	int zonaConMasVentas;
	int cantidadVentas;
	int cantidadVentasMaxima;

	char zonaConMasVentasString[10000];

	int flag = FALSE;

	if(pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
		{
			pVenta = ll_get(pArrayListaVentas, i);
			venta_getZona(pVenta, &zona);

			pListaFiltrada = ll_filter2(pArrayListaVentas, venta_obtenerZona, &zona);

			if(pListaFiltrada != NULL)
			{
				cantidadVentas = ll_len(pListaFiltrada);

				if(flag == FALSE)
				{
					cantidadVentasMaxima = cantidadVentas;
					zonaConMasVentas = zona;
					flag = TRUE;
				}
				else if(cantidadVentas > cantidadVentasMaxima)
				{
					cantidadVentasMaxima = cantidadVentas;
					zonaConMasVentas = zona;
				}
			}
		}

		if(zonaConMasVentas == 0)
		{
			sprintf(zonaConMasVentasString, "CABA");
		}
		else
		if(zonaConMasVentas == 1)
		{
			sprintf(zonaConMasVentasString, "Zona sur");
		}
		else
		if(zonaConMasVentas == 2)
		{
			sprintf(zonaConMasVentasString, "Zona oeste");
		}

		printf("\n%s es la que mayor cantidad de ventas tiene, con un total de: %d\n", zonaConMasVentasString, cantidadVentasMaxima);
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Función que imprime la zona que más ventas posee.
* \param pArrayListaVentas LinkedList* puntero al array de ventas
* \return (-1) Error (0) todo OK
*/
int informes_imprimirZonaConMasVentas2(LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	LinkedList* pListaFiltrada;

	int zonaConMasVentas;
	int cantidadVentas;
	int cantidadVentasMaxima;

	char zonaConMasVentasString[10000];

	int flag = FALSE;

	if(pArrayListaVentas != NULL)
	{
		for(int zona = 0 ; zona < 2 ; zona++)
		{
			pListaFiltrada = ll_filter2(pArrayListaVentas, venta_obtenerZona, &zona);
			cantidadVentas = ll_len(pListaFiltrada);

			if(pListaFiltrada != NULL)
			{
				if(flag == FALSE)
				{
					cantidadVentasMaxima = cantidadVentas;
					zonaConMasVentas = zona;
					flag = TRUE;
				}
				else if(cantidadVentas > cantidadVentasMaxima)
				{
					cantidadVentasMaxima = cantidadVentas;
					zonaConMasVentas = zona;
				}
			}
		}
		if(zonaConMasVentas == 0)
		{
			sprintf(zonaConMasVentasString, "CABA");
		}
		else
		if(zonaConMasVentas == 1)
		{
			sprintf(zonaConMasVentasString, "Zona sur");
		}
		else
		if(zonaConMasVentas == 2)
		{
			sprintf(zonaConMasVentasString, "Zona oeste");
		}

		printf("\n%s es la que mayor cantidad de ventas tiene, con un total de: %d\n", zonaConMasVentasString, cantidadVentasMaxima);
		retorno = 0;
	}
	return retorno;
}

/* De un cliente en particular, filtrar sus ventas por una zona en particular, de un estado en particular,
informar las que tienen mas de 50 afiches vendidos. */

/* De una zona en particular, informar la venta con menos afiches vendidos. */
