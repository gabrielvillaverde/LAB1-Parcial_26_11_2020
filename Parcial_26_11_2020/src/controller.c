/*
 * controller.c
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "cliente.h"
#include "ventas.h"
#include "controller.h"
#include "parser.h"
#include "utn.h"

#define FALSE 0
#define TRUE 1

static int generarNuevoId(LinkedList* pArrayListaClientes);
static int encontrarMaximoId(LinkedList* pArrayListaClientes);
static int generarNuevoIdVentas(LinkedList* pArrayListaVentas);
static int encontrarMaximoIdVentas(LinkedList* pArrayListaVentas);

/*
* \brief Función que carga los datos de los clientes desde el archivo clientes.csv (modo texto).
* \param path char* es la ruta del archivo.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_loadListaClientesFromText(char* path, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	FILE* pFile;

	if(path != NULL && pArrayListaClientes != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			if(parser_leerListaClientesFromText(pFile, pArrayListaClientes) == 0)
			{
				retorno = 0;
			}
			else
			{
 				printf("\nNo se pudo parsear el archivo.\n");
			}
		}
		fclose(pFile);
	}
    return retorno;
}

int controller_loadListaVentasFromText(char* path, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	FILE* pFile;

	if(path != NULL && pArrayListaVentas != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			if(parser_leerListaVentasFromText(pFile, pArrayListaVentas) == 0)
			{
				retorno = 0;
			}
			else
			{
 				printf("\nNo se pudo parsear el archivo.\n");
			}
		}
		fclose(pFile);
	}
    return retorno;
}

/*
* \brief Función que guarda los datos de los clientes en el archivo clientes.csv (modo texto).
* \param path char* es la ruta del archivo.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_saveClienteAsText(char* path, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	FILE* pFile;
	Cliente* pCliente;

	char idCliente[10000];
	char nombre[10000];
	char apellido[10000];
	char cuit[10000];

	if(path != NULL && pArrayListaClientes != NULL)
	{
		pFile = fopen(path, "w");
		if(pFile != NULL)
		{
			for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
			{
				pCliente = ll_get(pArrayListaClientes, i);
				if(pCliente != NULL)
				{
					if(cliente_getIdClienteTxt(pCliente, idCliente) == 0 &&
					   cliente_getNombre(pCliente, nombre) == 0 &&
					   cliente_getApellido(pCliente, apellido) == 0 &&
					   cliente_getCuit(pCliente, cuit) == 0)
					{
						fprintf(pFile, "%s,%s,%s,%s\n", idCliente, nombre, apellido, cuit);
						retorno = 0;
					}
				}
			}
			fclose(pFile);
		}
	}
    return retorno;
}

/*
* \brief Función que guarda los datos de las ventas en el archivo ventas.csv (modo texto).
* \param path char* es la ruta del archivo.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int controller_saveVentasAsText(char* path, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	FILE* pFile;
	Venta* pVenta;

	char idCliente[10000];
	char idVenta[10000];
	char cantidadAfiches[10000];
	char nombreArchivo[10000];
	char zona[10000];
	char cobrado[10000];

	if(path != NULL && pArrayListaVentas != NULL)
	{
		pFile = fopen(path, "w");
		if(pFile != NULL)
		{
			for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
			{
				pVenta = ll_get(pArrayListaVentas, i);
				if(pVenta != NULL)
				{
					if(venta_getIdClienteTxt(pVenta, idCliente) == 0 &&
					   venta_getIdVentaTxt(pVenta, idVenta) == 0 &&
					   venta_getCantidadAfichesTxt(pVenta, cantidadAfiches) == 0 &&
					   venta_getNombreArchivo(pVenta, nombreArchivo) == 0 &&
					   venta_getZona(pVenta, zona) == 0 &&
					   venta_getCobradoTxt(pVenta, cobrado) == 0)
					{
						fprintf(pFile, "%s,%s,%s,%s,%s,%s\n", idCliente, idVenta, cantidadAfiches, nombreArchivo, zona, cobrado);
						retorno = 0;
					}
				}
			}
			fclose(pFile);
		}
	}
    return retorno;
}

/*
* \brief Función que se encarga de dar de alta un cliente y lo añade al array de clientes.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/

int controller_addCliente(LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	Cliente* pCliente;
	Cliente auxiliarCliente;

	if(pArrayListaClientes != NULL)
	{
		pCliente = cliente_new();
		if(pCliente != NULL &&
				utn_getString("\nIngrese el nombre:\n", "\nError, ingrese un nombre válido.\n", auxiliarCliente.nombre, SIZE_NOMBRE, 3) == 0 &&
				utn_getString("\nIngrese el apellido:\n", "\nError, ingrese un apellido válido.\n", auxiliarCliente.apellido, SIZE_APELLIDO, 3) == 0 &&
				utn_getStringWithNumbersAndSymbols("\nIngrese el CUIT:\n", "\nError, ingrese un CUIT válido.\n", auxiliarCliente.cuit, SIZE_CUIT, 3) == 0 &&
				cliente_esCuitRepetido(pArrayListaClientes, auxiliarCliente.cuit) == 0)
		{
			auxiliarCliente.idCliente = generarNuevoId(pArrayListaClientes);
			if(auxiliarCliente.idCliente > 0 &&
			cliente_setNombre(pCliente, auxiliarCliente.nombre) == 0 &&
			cliente_setApellido(pCliente, auxiliarCliente.apellido) == 0 &&
			cliente_setCuit(pCliente, auxiliarCliente.cuit) == 0 &&
			cliente_setIdCliente(pCliente, auxiliarCliente.idCliente) == 0)
			{
				if(ll_add(pArrayListaClientes, pCliente) == 0)
				{
					printf("\nID del cliente generado es: %d", auxiliarCliente.idCliente);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

int controller_addVenta(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	Venta* pVenta;

	char idCliente[10000];
	char cantidadAfiches[10000];
	char nombreArchivo[10000];
	char zona[10000];


	if(pArrayListaVentas != NULL && pArrayListaClientes != NULL)
	{
		pVenta = venta_new();
		if(
			utn_getStringWithOnlyNumbers("\nIngrese el ID del cliente:\n", "\nError, ingrese un ID válido.\n", idCliente, 1000, 3) == 0 &&
			utn_getStringWithOnlyNumbers("\nIngrese la cantidad de afiches que quiere vender:\n", "\nError, ingrese una cantidad válida.\n", cantidadAfiches, 1000, 3) == 0 &&
			utn_getStringWithNumbersAndSymbols("\nIngrese el nombre del archivo con la imagen del afiche:\n", "\nError, ingrese una cantidad válida.\n", nombreArchivo, SIZE_NOMBRE_ARCHIVO, 3) == 0 &&
			utn_getStringWithOnlyNumbers("\nIngrese la zona: [0] CABA - [1] ZONA SUR  - [2] ZONA OESTE\n" , "\nError, ingrese una zona válida.\n", zona, 10000, 3) == 0)
		{
			if(
			venta_setIdClienteTxt(pVenta, idCliente) == 0 &&
			venta_setIdVenta(pVenta, generarNuevoIdVentas(pArrayListaVentas)) == 0 &&
			venta_setCantidadAfichesTxt(pVenta, cantidadAfiches) == 0 &&
			venta_setNombreArchivo(pVenta, nombreArchivo) == 0 &&
			venta_setZona(pVenta, zona) == 0 &&
			venta_setCobrado(pVenta, 0) == 0)
			{
				if(ll_add(pArrayListaVentas, pVenta) == 0)
				{
					printf("\nID de la venta generada: %d", pVenta->idVenta);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Función que imprime los clientes
* \param pArrayListCliente LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_imprimirClientes(LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	char idCliente[10000];
	char nombre[10000];
	char apellido[10000];
	char cuit[10000];

	Cliente* pCliente;

	if(pArrayListaClientes != NULL)
	{
		printf("\nLista de clientes:\n");

		for(int i ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdClienteTxt(pCliente, idCliente);
			cliente_getNombre(pCliente, nombre);
			cliente_getApellido(pCliente, apellido);
			cliente_getCuit(pCliente, cuit);
			printf("ID de cliente: %s - Nombre: %s - Apellido: %s - CUIT: %s\n", idCliente, nombre, apellido, cuit);
			retorno = 0;
		}
	}
    return retorno;
}

int controller_imprimirVentas(LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	char idCliente[10000];
	char idVenta[10000];
	char cantidadAfiches[10000];
	char nombreArchivo[10000];
	char zona[10000];
	char cobrado[10000];

	Venta* pVenta;

	if(pArrayListaVentas != NULL)
	{
		retorno = 0;
		printf("\nLista de ventas:\n");

		for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
		{
			pVenta = ll_get(pArrayListaVentas, i);
			venta_getIdClienteTxt(pVenta, idCliente);
			venta_getIdVentaTxt(pVenta, idVenta);
			venta_getCantidadAfichesTxt(pVenta, cantidadAfiches);
			venta_getNombreArchivo(pVenta, nombreArchivo);
			venta_getZona(pVenta, zona);
			venta_getCobradoTxt(pVenta, cobrado);
			printf("ID de cliente: %s - ID de venta: %s - Cantidad de afiches: %s - Nombre de archivo: %s - ZONA: %s - Estado de cobranza: %s\n", idCliente, idVenta, cantidadAfiches, nombreArchivo, zona, cobrado);
		}
	}
    return retorno;
}

int controller_modificarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	LinkedList* pListaFiltrada;
	Venta* pVenta = NULL;
	Cliente* pCliente = NULL;

	int idVenta;
	int indiceVenta;
	int indiceCliente;

	int opcion;

	char cantidadAfiches[10000];
	char nombreArchivo[10000];
	char zona[10000];

	if(pArrayListaVentas != NULL)
	{
		pListaFiltrada = ll_filter(pArrayListaVentas, venta_chequearEstadoNoCobrado);

		if(pListaFiltrada != NULL)
		{
			printf("\nEstas son las ventas que aún no se han cobrado:\n");
			if(controller_imprimirVentas(pListaFiltrada) == 0)
			{
				if(utn_getInt("\nIngrese el ID de la venta:\n", "\nError, ingrese un ID válido.\n", &idVenta, 3) == 0)
				{
					indiceVenta = venta_findVentaById(pArrayListaVentas, idVenta);
					pVenta = ll_get(pArrayListaVentas, indiceVenta);

					indiceCliente = cliente_findClienteById(pArrayListaClientes, pVenta->idCliente);
					pCliente = ll_get(pArrayListaClientes, indiceCliente);

					printf("\nEl cliente al que pertenece la venta es %s %s y su CUIT es %s", pCliente->nombre, pCliente->apellido, pCliente->cuit);
					do
					{
						if(utn_getInt("\nElija un campo a modificar: [1] Cantidad de afiches - [2] Nombre del archivo - [3] Zona - [4] Salir\n", "\nError, ingrese un número válido.\n", &opcion, 3) == 0)
						{
							switch(opcion)
							{
							case 1:
								if(utn_getStringWithOnlyNumbers("\nIngrese la nueva cantidad de afiches:\n", "\nError, ingrese una cantidad válida.\n", cantidadAfiches, 1000, 3) == 0)
								{
									if(venta_setCantidadAfichesTxt(pVenta, cantidadAfiches) == 0)
									{
										printf("\nLa cantidad de afiches fue modificada correctamente.\n");
									}
								}
								break;
							case 2:
								if(utn_getStringWithNumbersAndSymbols("\nIngrese el nombre del nuevo archivo con la imagen del afiche:\n", "\nError, ingrese un nombre válido.\n", nombreArchivo, SIZE_NOMBRE_ARCHIVO, 3) == 0)
								{
									if(venta_setNombreArchivo(pVenta, nombreArchivo) == 0)
									{
										printf("\nEl nombre del archivo fue modificado correctamente.\n");
									}
								}
								break;
							case 3:
								if(utn_getStringWithOnlyNumbers("\nIngrese la nueva: [0] CABA - [1] ZONA SUR  - [2] ZONA OESTE\n" , "\nError, ingrese una zona válida.\n", zona, 10000, 3) == 0)
								{
									if(venta_setZona(pVenta, zona) == 0)
									{
										printf("\nLa zona modificada correctamente.\n");
									}
								}
								break;
							}
						}
					}while(opcion != 4);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

int controller_cobrarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	LinkedList* pListaFiltrada;
	Venta* pVenta = NULL;
	Cliente* pCliente = NULL;

	int idVenta;
	int indiceVenta;
	int indiceCliente;

	int opcion;

	if(pArrayListaVentas != NULL && pArrayListaClientes != NULL)
	{
		pListaFiltrada = ll_filter(pArrayListaVentas, venta_chequearEstadoNoCobrado);

		if(pListaFiltrada != NULL)
		{
			printf("\nEstas son las ventas que aún no se han cobrado:\n");
			if(controller_imprimirVentas(pListaFiltrada) == 0)
			{
				if(utn_getInt("\nIngrese el ID de la venta:\n", "\nError, ingrese un ID válido.\n", &idVenta, 3) == 0)
				{
					indiceVenta = venta_findVentaById(pArrayListaVentas, idVenta);
					pVenta = ll_get(pArrayListaVentas, indiceVenta);

					indiceCliente = cliente_findClienteById(pArrayListaClientes, pVenta->idCliente);
					pCliente = ll_get(pArrayListaClientes, indiceCliente);

					printf("\nEl cliente al que pertenece la venta es %s %s y su CUIT es %s", pCliente->nombre, pCliente->apellido, pCliente->cuit);
					do
					{
						if(utn_getInt("\n¿Desea cobrar la venta?: [1] SI - [2] NO\n", "\nError, ingrese una opción válida.\n", &opcion, 3) == 0)
						{
							if(opcion == 1 && venta_setCobrado(pVenta, 1) == 0)
							{
								retorno = 0;
							}
							break;
						}
					}while(opcion != 1);
				}
			}
		}
	}
	return retorno;
}

int controller_generarInformeDeCobros(char* path, LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas, int estado)
{
	int retorno = -1;

	Cliente* pCliente = NULL;
	LinkedList* pListaFiltrada = NULL;
	FILE* pFile;

	int idCliente;
	int cantidadVentas;

	pFile = fopen(path, "w");
	if(pFile != NULL)
	{
		if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
		{
			for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
			{
				pCliente = ll_get(pArrayListaClientes, i);
				if(pCliente != NULL)
				{
					cliente_getIdCliente(pCliente, &idCliente);
					pListaFiltrada = ll_filter3(pArrayListaVentas, venta_chequearIdYEstadoCobranza, &idCliente, &estado);
					cantidadVentas = ll_len(pListaFiltrada);
					controller_saveClienteConCantidadDeVentasAsText(pFile, pCliente, cantidadVentas);
					retorno = 0;
				}
			}
		}
	}
	fclose(pFile);
	return retorno;
}

int controller_saveClienteConCantidadDeVentasAsText(FILE* pFile, void* pCliente, int cantidadVentas)
{
	int retorno = -1;

	char idCliente[10000];
	char nombre[10000];
	char apellido[10000];
	char cuit[10000];

	if(pCliente != NULL && cantidadVentas >= 0)
	{
		if(pFile != NULL)
		{
			if(cliente_getIdClienteTxt(pCliente, idCliente) == 0 &&
			   cliente_getNombre(pCliente, nombre) == 0 &&
			   cliente_getApellido(pCliente, apellido) == 0 &&
			   cliente_getCuit(pCliente, cuit) == 0)
			{
				fprintf(pFile, "%s,%s,%s,%s,%d\n", idCliente, nombre, apellido, cuit, cantidadVentas);
				retorno = 0;
			}
		}
	}
	return retorno;
}


int controller_imprimirClienteConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	Cliente* pCliente = NULL;

	int idCliente;
	int idClienteConMasAfiches;
	int cantidadAfiches;
	int cantidadAfichesMaxima;

	if(pArrayListaClientes != NULL && pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes); i++)
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

int controller_imprimirClienteConMenosAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
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

int controller_imprimirVentaConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
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

/**
 * \brief Genera un nuevo ID para un nuevo cliente
 * 		  Se inicializa a partir del último ID encontrado como máximo, si es que hay datos cargados de un archivo.
 * 		  Solo busca el máximo una vez, y luego sigue otorgando ID a partir del último que dió.
 * \param pArrayListaClientes LinkedList* puntero al array de clientes
 * \return int Return (-1) Si el puntero a LinkedList es NULL o si no hay datos cargados
 * 					  o el valor del nuevo ID generado.
 */
static int generarNuevoId(LinkedList* pArrayListaClientes)
{
    static int id = -1;
    static int esLaPrimeraVez = TRUE;

    if(pArrayListaClientes != NULL)
    {
    	if(ll_isEmpty(pArrayListaClientes) == 0 && esLaPrimeraVez == TRUE)
    	{
    		id = encontrarMaximoId(pArrayListaClientes);
    		esLaPrimeraVez = FALSE;
    	}
    	id++;
    }
    return id;
}

/**
 * \brief Busca en el array el máximo ID ya cargado.
 * \param pArrayListaClientes LinkedList* puntero al array de clientes
 * \return int Return (-1) Si el puntero a LinkedList es NULL
 * 					   o el máximo ID encontrado en el archivo
 */
static int encontrarMaximoId(LinkedList* pArrayListaClientes)
{
	Cliente* pCliente;

	int maximo;

	int id = -1;

	if(pArrayListaClientes != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);
			cliente_getIdCliente(pCliente, &id);
			if(i == 0 || id > maximo)
			{
				maximo = id;
			}
		}
		id = maximo;
	}
	return id;
}

static int generarNuevoIdVentas(LinkedList* pArrayListaVentas)
{
    static int id = -1;
    static int esLaPrimeraVez = TRUE;

    if(pArrayListaVentas != NULL)
    {
    	if(ll_isEmpty(pArrayListaVentas) == 0 && esLaPrimeraVez == TRUE)
    	{
    		id = encontrarMaximoIdVentas(pArrayListaVentas);
    		esLaPrimeraVez = FALSE;
    	}
    	id++;
    }
    return id;
}

static int encontrarMaximoIdVentas(LinkedList* pArrayListaVentas)
{
	Venta* pVenta;

	int maximo;

	int id = -1;

	if(pArrayListaVentas != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
		{
			pVenta = ll_get(pArrayListaVentas, i);
			venta_getIdVenta(pVenta, &id);
			if(i == 0 || id > maximo)
			{
				maximo = id;
			}
		}
		id = maximo;
	}
	return id;
}
