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
				cantidadAfiches = ll_count(pListaFiltrada, venta_calcularCantidadAfiches);

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
				cantidadAfiches = ll_count(pListaFiltrada, venta_calcularCantidadAfiches);

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
