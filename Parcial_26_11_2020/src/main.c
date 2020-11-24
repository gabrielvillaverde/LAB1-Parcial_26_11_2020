/*
 ============================================================================
 Name        : Clase_25_PARCIAL_2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "controller.h"
#include "ventas.h"

#define FALSE 0
#define TRUE 1

/* ERRORES:
 * 1) Al vender un afiche, si ingreso un ID de cliente que no existe, lo toma igual.
 * 2) Al ingresar un ID inexistente a la hora de modificar y cobrar la venta, explota el programa.
 * 3) Cuando hago una venta, y elijo la zona, a la hora de imprimir en vez de la zona me muestra el número.
 * 4) Cambié en controller_cobrarVentas y le agregué que pArrayClientes != NULL, chequear si sigue andando.
 * 5)
 */

int main(void)
{
	setbuf(stdout,NULL);

	int opcion;
	int opcionSubMenu;

	LinkedList* listaClientes = ll_newLinkedList(); // Creo una LinkedList de clientes.
	LinkedList* listaVentas = ll_newLinkedList(); // Creo una LinkedList de ventas.

	if(controller_loadListaClientesFromText("clientes.csv", listaClientes) == 0)
	{
		printf("\nArchivo de clientes cargado correctamente.\n\n");
	}

	if(controller_loadListaVentasFromText("ventas.csv", listaVentas) == 0)
	{
		printf("\nArchivo de ventas cargado correctamente.\n");
	}

	do
	{
    	if(utn_getIntConMinMax("\nBienvenido al sistema, elija una opción: \n\n"
    			"1  -  Agregar cliente.\n"
    			"2  -  Vender afiches.\n"
    			"3  -  Modificar venta.\n"
    			"4  -  Cobrar venta.\n"
    			"5  -  Generar informe de cobros.\n"
    			"6  -  Generar informe de deudas.\n"
    			"7  -  Generar estadísticas.\n"
    			"8  -  Imprimir clientes.\n"
    			"9  -  Imprimir ventas.\n"
    			"10  - Guardar los datos de los clientes en clientes.csv.\n"
    			"11  - Guardar los datos de las ventas en ventas.csv.\n"
    			"12  -  Salir\n", "\nError, ingrese una opción entre 1 y 10.\n", &opcion, 1, 12, 3) == 0)
    	{
    		switch(opcion)
    		{
    		case 1:
    			if(controller_addCliente(listaClientes) == 0)
    			{
    				printf("\nCliente dado de alta correctamente.\n");
    			}
    			break;
    		case 2:
    			if(controller_addVenta(listaVentas, listaClientes) == 0)
    			{
    				printf("\nVenta concretada.\n");
    			}
    			break;
    		case 3:
    			if(controller_modificarVentas(listaVentas, listaClientes) == 0)
    			{
    				printf("\nModificación concretada.\n");
    			}
    			break;
    		case 4:
    			if(controller_cobrarVentas(listaVentas, listaClientes) == 0)
    			{
    				printf("\nLa venta fue cobrada correctamente.\n");
    			}
    			break;
    		case 5:
    			if(controller_generarInformeDeCobros("ventasCobradas.csv", listaClientes, listaVentas, 1) == 0)
    			{
    				printf("\nEl archivo de la lista de clientes junto con la cantidad de ventas cobradas que posee cada uno fue creado correctamente.\n");
    			}
    			else
    			{
    				printf("\nNo se pudo crear el archivo.\n");
    			}
    			break;
    		case 6:
    			if(controller_generarInformeDeCobros("ventasNoCobradas.csv", listaClientes, listaVentas, 0) == 0)
    			{
    				printf("\nEl archivo de la lista de clientes junto con la cantidad de ventas a cobrar que posee cada uno fue creado correctamente.\n");
    			}
    			else
    			{
    				printf("\nNo se pudo crear el archivo.\n");
    			}
    			break;
    		case 7:
    			do
    			{
    				if(utn_getIntConMinMax("\nBienvenido al sistema de informes, elija una opción: \n\n"
    				    			"1  -  Cliente al que se le vendió más afiches.\n"
    				    			"2  -  Cliente al que se le vendió menos afiches.\n"
    				    			"3  -  Venta con más afiches vendidos.\n"
									"4 -   Salir.","\nError, ingrese una opción entre 1 y 10.\n", &opcionSubMenu, 1, 4, 3) == 0)
    				{
    					switch(opcionSubMenu)
    					{
    					case 1:
    		    			if(controller_imprimirClienteConMasAfichesVendidos(listaClientes, listaVentas) == 0)
    		    			{
    		    				printf("\El cliente con más afiches vendidos fue impreso correctamente.\n");
    		    			}
    		    			else
    		    			{
    		    				printf("\nNo se pudo imprimir el cliente con más afiches vendidos.\n");
    		    			}
    						break;
    					case 2:
    		    			if(controller_imprimirClienteConMenosAfichesVendidos(listaClientes, listaVentas) == 0)
    		    			{
    		    				printf("\El cliente con menos afiches vendidos fue impreso correctamente.\n");
    		    			}
    		    			else
    		    			{
    		    				printf("\nNo se pudo imprimir el cliente con menos afiches vendidos.\n");
    		    			}
    						break;
    					case 3:
    		    			if(controller_imprimirVentaConMasAfichesVendidos(listaClientes, listaVentas) == 0)
    		    			{
    		    				printf("\nVenta con más afiches vendidos impresa correctamente.\n");
    		    			}
    		    			else
    		    			{
    		    				printf("\nNo se pudo imprimir la venta con más afiches vendidos.\n");
    		    			}
    						break;
    					}
    				}
    			}while(opcionSubMenu != 4);
    			break;
    		case 8:
    			if(controller_imprimirClientes(listaClientes) == 0)
    			{
    				printf("\nClientes impresos correctamente.\n");
    			}
    			break;
    		case 9:
    			if(controller_imprimirVentas(listaVentas) == 0)
    			{
    				printf("\nVentas impresas correctamente.\n");
    			}
    			break;
    		case 10:
    			if(controller_saveClienteAsText("clientes.csv", listaClientes) == 0)
    			{
    				printf("\nArchivo de clientes actualizado.\n");
    			}
    			break;
    		case 11:
    			if(controller_saveVentasAsText("ventas.csv", listaVentas) == 0)
    			{
    				printf("\nArchivo de ventas actualizado.\n");
    			}
    			break;
    		}
    	}
	}while(opcion != 12);

	return EXIT_SUCCESS;
}
