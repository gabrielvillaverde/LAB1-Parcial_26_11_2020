/*
 * parser.c
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "cliente.h"
#include "ventas.h"

/*
* \brief Parsea los datos los datos de los clientes desde el archivo clientes.csv (modo texto).
* \param FILE* puntero al archivo.
* \param pArrayListaClientes LinkedList* puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int parser_leerListaClientesFromText(FILE* pFile, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	Cliente* pCliente;

	char idClienteAuxiliar[10000];
	char nombreAuxiliar[SIZE_NOMBRE];
	char apellidoAuxiliar[SIZE_APELLIDO];
	char cuitAuxiliar[SIZE_CUIT];

	if(pFile != NULL && pArrayListaClientes != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", idClienteAuxiliar, nombreAuxiliar, apellidoAuxiliar, cuitAuxiliar) == 4)
			{
				pCliente = cliente_newParametros(idClienteAuxiliar, nombreAuxiliar, apellidoAuxiliar, cuitAuxiliar);
				if(pCliente != NULL)
				{
					// DEBUG:
					printf("ID de cliente: %s - Nombre: %s - Apellido: %s - CUIT: %s\n", idClienteAuxiliar, nombreAuxiliar, apellidoAuxiliar, cuitAuxiliar);
					ll_add(pArrayListaClientes, pCliente); // Agrego el puntero a Cliente* en la lista enlazada.
					retorno = 0;
				}
			}
		}while(feof(pFile) == 0); // Leo mientras la función feof no haya llegado al final del archivo.
	}
	return retorno;
}

/*
* \brief Parsea los datos los datos de las ventas desde el archivo ventas.csv (modo texto).
* \param FILE* puntero al archivo.
* \param pArrayListaVentas LinkedList* puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/

int parser_leerListaVentasFromText(FILE* pFile, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	Venta* pVenta;

	char idClienteAuxiliar[10000];
	char idVentaAuxiliar[10000];
	char cantidadAfichesAuxiliar[10000];
	char nombreArchivoAuxiliar[SIZE_NOMBRE_ARCHIVO];
	char zonaAuxiliar[10000];
	char cobradoAuxiliar[10000];

	if(pFile != NULL && pArrayListaVentas != NULL)
	{
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idClienteAuxiliar, idVentaAuxiliar, cantidadAfichesAuxiliar, nombreArchivoAuxiliar, zonaAuxiliar, cobradoAuxiliar) == 6)
			{
				pVenta = venta_newParametros(idClienteAuxiliar, idVentaAuxiliar, cantidadAfichesAuxiliar, nombreArchivoAuxiliar, zonaAuxiliar, cobradoAuxiliar);
				if(pVenta != NULL)
				{
					// DEBUG:
					printf("ID de cliente: %s - ID de venta: %s - Cantidad de afiches: %s - Nombre de archivo: %s - Zona: %s - Cobrado: %s\n", idClienteAuxiliar, idVentaAuxiliar, cantidadAfichesAuxiliar, nombreArchivoAuxiliar, zonaAuxiliar, cobradoAuxiliar);
					ll_add(pArrayListaVentas, pVenta); // Agrego el puntero a Cliente* en la lista enlazada.
					retorno = 0;
				}
			}
		}while(feof(pFile) == 0); // Leo mientras la función feof no haya llegado al final del archivo.
	}
	return retorno;
}
