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

	int idCliente;
	int idClienteConMasAfiches;
	int cantidadAfiches;
	int cantidadAfichesMaxima;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdCliente(pCliente, &idCliente);
			cantidadAfiches = ll_reduceInt(pArrayListaVentas, venta_chequearIdYCalcularCantidadAfiches, &idCliente);
			if(cantidadAfiches != 0)
			{
				if(i == 0 || cantidadAfiches > cantidadAfichesMaxima)
				{
					cantidadAfichesMaxima = cantidadAfiches;
					idClienteConMasAfiches = idCliente;
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

	int idCliente;
	int idClienteConMenosAfiches;
	int cantidadAfiches;
	int cantidadAfichesMinima;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes); i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdCliente(pCliente, &idCliente);
			cantidadAfiches = ll_reduceInt(pArrayListaVentas, venta_chequearIdYCalcularCantidadAfiches, &idCliente);
			if(cantidadAfiches != 0)
			{
				if(i == 0 || cantidadAfiches < cantidadAfichesMinima)
				{
					cantidadAfichesMinima = cantidadAfiches;
					idClienteConMenosAfiches = idCliente;
				}
			}
		}
		printf("\nEl cliente al que se le vendieron más afiches fue:\n");
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
		for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
		{
			pListaFiltrada = ll_filter(pArrayListaVentas, venta_chequearEstadoCobrado);
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
		retorno = 0;
	}
	return retorno;
}
