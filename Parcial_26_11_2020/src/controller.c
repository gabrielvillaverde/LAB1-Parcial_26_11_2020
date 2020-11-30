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
* \brief Función que carga los datos de los clientes desde el archivo pasado como parámetro (modo texto).
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

/*
* \brief Función que carga los datos de las ventas desde el archivo pasado como parámetro (modo texto).
* \param path char* es la ruta del archivo.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
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
* \brief Función que guarda los datos de los clientes en el archivo pasado como parámetro (modo texto).
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
* \brief Función que guarda los datos de las ventas en el archivo pasado como parámetro (modo texto).
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
					   venta_getZonaTxt(pVenta, zona) == 0 &&
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

	char nombre[SIZE_NOMBRE];
	char apellido[SIZE_APELLIDO];
	char cuit[SIZE_CUIT];

	if(pArrayListaClientes != NULL)
	{
		pCliente = cliente_new();
		if( pCliente != NULL &&
			utn_getString("\nIngrese el nombre:\n", "\nError, ingrese un nombre válido.\n", nombre, SIZE_NOMBRE, 3) == 0 &&
			utn_getString("\nIngrese el apellido:\n", "\nError, ingrese un apellido válido.\n", apellido, SIZE_APELLIDO, 3) == 0 &&
			utn_getStringWithNumbersAndSymbols("\nIngrese el CUIT:\n", "\nError, ingrese un CUIT válido.\n", cuit, SIZE_CUIT, 3) == 0 &&
			cliente_esCuitRepetido(pArrayListaClientes, cuit) == 0)
		{
			cliente_setIdCliente(pCliente, generarNuevoId(pArrayListaClientes));

			if(pCliente->idCliente > 0 &&
				cliente_setNombre(pCliente, nombre) == 0 &&
				cliente_setApellido(pCliente, apellido) == 0 &&
				cliente_setCuit(pCliente, cuit) == 0)
			{
				if(ll_add(pArrayListaClientes, pCliente) == 0)
				{
					printf("\nID del cliente generado es: %d", pCliente->idCliente);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Función que da de baja al cliente.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_removeCliente(LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	Cliente* pCliente;

	int idCliente;
	int indiceClienteEliminar;
	int opcion;

	if(pArrayListaClientes != NULL)
	{
		controller_imprimirClientes(pArrayListaClientes);
		if( utn_getInt("\nIngrese el ID del cliente a borrar:\n", "\nError, ingrese un ID válido.\n", &idCliente, 3) == 0 &&
			cliente_findClienteById(pArrayListaClientes, idCliente) != -1)
		{
			printf("\nLos datos del cliente al que corresponde ese ID son los siguientes:\n");
			cliente_findClienteByIdAndImprimir(pArrayListaClientes, idCliente);

			indiceClienteEliminar = cliente_findClienteById(pArrayListaClientes, idCliente);
			pCliente = ll_get(pArrayListaClientes, indiceClienteEliminar);

			if(pCliente != NULL)
			{
				if(utn_getIntConMinMax("\n¿Desea eliminar el cliente? [1] SI - [0] NO\n", "\nError, ingrese [1] SI - [0] NO\n", &opcion, 0, 1, 3) == 0)
				{
					if(opcion)
					{
						cliente_delete(pCliente); // Libero el espacio de memoria que ocupaba ese cliente.
						ll_remove(pArrayListaClientes, indiceClienteEliminar); // Elimino el nodo de la LinkedList que correspondía a ese cliente.
						retorno = 0;
					}
					else
					{
						printf("\nEl cliente no ha sido dado de baja.\n");
					}
				}
			}
		}
		else
		{
			printf("\nEl ID del cliente no existe.\n");
		}
	}

	return retorno;
}

/*
* \brief Función que da de baja al cliente junto con todas sus ventas.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* * \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
int controller_removeClienteConTodasSusVentas(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas)
{
	int retorno = -1;

	Cliente* pCliente;
	Venta* pVenta;

	int idCliente;
	int idClienteAuxiliar;
	//int idVentaAuxiliar;
	int indiceClienteEliminar;
	int opcion;

	if(pArrayListaVentas != NULL && pArrayListaClientes != NULL)
	{
		printf("\nA continuación se listan los ID de clientes que tienen ventas registradas en el sistema:\n");
		controller_imprimirVentas(pArrayListaVentas);

		if( utn_getInt("\nIngrese el ID del cliente a borrar:\n", "\nError, ingrese un ID válido.\n", &idCliente, 3) == 0 &&
					cliente_findClienteById(pArrayListaClientes, idCliente) != -1)
		{
			printf("\nLos datos del cliente al que corresponde ese ID son los siguientes:\n");
			cliente_findClienteByIdAndImprimir(pArrayListaClientes, idCliente);

			indiceClienteEliminar = cliente_findClienteById(pArrayListaClientes, idCliente);
			pCliente = ll_get(pArrayListaClientes, indiceClienteEliminar);

			if(utn_getIntConMinMax("\n¿Desea eliminar el cliente junto con todas sus ventas? [1] SI - [0] NO\n", "\nError, ingrese [1] SI - [0] NO\n", &opcion, 0, 1, 3) == 0)
			{
				if(opcion == 1)
				{
					cliente_delete(pCliente);
					ll_remove(pArrayListaClientes, indiceClienteEliminar);

					for(int i = 0 ; i < ll_len(pArrayListaVentas) ; i++)
					{
						pVenta = ll_get(pArrayListaVentas, i);

						venta_getIdCliente(pVenta, &idClienteAuxiliar);
						//venta_getIdVenta(pVenta, &idVentaAuxiliar);

						if(idClienteAuxiliar == idCliente)
						{
							venta_delete(pVenta);
							ll_remove(pArrayListaVentas, i);
						}
					}
					retorno = 0;
				}
			}
			printf("\nLa lista quedó así:\n");
			controller_imprimirVentas(pArrayListaVentas);
		}
		else
		{
			printf("\nEl ID es inexistente.\n");
		}
	}
	return retorno;
}

/*
* \brief Función que se encarga de dar de alta una venta asociada a un ID de cliente existente y la añade al array de ventas.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_addVenta(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	Venta* pVenta;
	Cliente* pCliente;

	int idCliente;
	int indiceCliente;
	char cantidadAfiches[10000];
	char nombreArchivo[10000];
	char zona[10000];


	if(pArrayListaVentas != NULL && pArrayListaClientes != NULL)
	{
		pVenta = venta_new();
		if(	utn_getInt("\nIngrese el ID del cliente al cuál se le añadirá una venta:\n", "\nError, ingrese un ID válido.\n", &idCliente, 3) == 0 &&
			cliente_findClienteById(pArrayListaClientes, idCliente) != -1 &&
			utn_getStringWithOnlyNumbers("\nIngrese la cantidad de afiches que quiere vender:\n", "\nError, ingrese una cantidad válida.\n", cantidadAfiches, 10000, 3) == 0 &&
			utn_getStringWithNumbersAndSymbols("\nIngrese el nombre del archivo con la imagen del afiche:\n", "\nError, ingrese una cantidad válida.\n", nombreArchivo, 10000, 3) == 0 &&
			utn_getStringWithOnlyNumbers("\nIngrese la zona: [0] CABA - [1] ZONA SUR  - [2] ZONA OESTE\n" , "\nError, ingrese una zona válida.\n", zona, 10000, 3) == 0)
		{
			if(	venta_setIdCliente(pVenta, idCliente) == 0 &&
				venta_setIdVenta(pVenta, generarNuevoIdVentas(pArrayListaVentas)) == 0 &&
				venta_setCantidadAfichesTxt(pVenta, cantidadAfiches) == 0 &&
				venta_setNombreArchivo(pVenta, nombreArchivo) == 0 &&
				venta_setZonaTxt(pVenta, zona) == 0 &&
				venta_setCobrado(pVenta, 0) == 0)
			{
				if(ll_add(pArrayListaVentas, pVenta) == 0)
				{
					indiceCliente = cliente_findClienteById(pArrayListaClientes, pVenta->idCliente);
					pCliente = ll_get(pArrayListaClientes, indiceCliente);
					printf("\nEl ID de la venta generada es: %d. El cliente al que pertenece la venta generada es %s %s y su CUIT es %s", pVenta->idVenta, pCliente->nombre, pCliente->apellido, pCliente->cuit);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("\nEl ID del cliente no existe.\n");
		}
	}
	return retorno;
}

/*
* \brief Función que se encarga de modificar una venta.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_modificarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	LinkedList* pListaFiltrada;

	Venta* pVenta = NULL;
	Cliente* pCliente = NULL;

	int idVentaModificar;
	int indiceVentaModificar;
	int indiceCliente;

	int opcion;

	char cantidadAfiches[10000];
	char nombreArchivo[10000];
	char zona[10000];

	if(pArrayListaVentas != NULL && pArrayListaClientes != NULL)
	{
		pListaFiltrada = ll_filter(pArrayListaVentas, venta_chequearEstadoNoCobrado);

		if(pListaFiltrada != NULL)
		{
			printf("\nEstas son las ventas que aún no se han cobrado:\n");

			if(controller_imprimirVentas(pListaFiltrada) == 0)
			{
				if( utn_getInt("\nIngrese el ID de la venta a modificar:\n", "\nError, ingrese un ID válido.\n", &idVentaModificar, 3) == 0 &&
					venta_findVentaByIdAndCheckEstadoCobranza(pArrayListaVentas, idVentaModificar, 0) != -1)
				{
					indiceVentaModificar = venta_findVentaById(pArrayListaVentas, idVentaModificar);
					pVenta = ll_get(pArrayListaVentas, indiceVentaModificar);

					indiceCliente = cliente_findClienteById(pArrayListaClientes, pVenta->idCliente);
					pCliente = ll_get(pArrayListaClientes, indiceCliente);
					printf("\nEl cliente al que pertenece la venta es %s %s y su CUIT es %s", pCliente->nombre, pCliente->apellido, pCliente->cuit);

					do
					{
						if(utn_getIntConMinMax("\nElija un campo a modificar: [1] Cantidad de afiches - [2] Nombre del archivo - [3] Zona - [4] Salir\n", "\nError, ingrese un número válido.\n", &opcion, 1, 4, 3) == 0)
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
									if(venta_setZonaTxt(pVenta, zona) == 0)
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
				else
				{
					printf("\nEl ID de la venta no existe o la venta ya está cobrada y por lo tanto no se puede modificar.\n");
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Función que se encarga de cobrar una venta.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_cobrarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	LinkedList* pListaFiltrada;
	Venta* pVenta = NULL;
	Cliente* pCliente = NULL;

	int idVentaCobrar;
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
				if( utn_getInt("\nIngrese el ID de la venta que quiere cobrar:\n", "\nError, ingrese un ID válido.\n", &idVentaCobrar, 3) == 0 &&
					venta_findVentaByIdAndCheckEstadoCobranza(pArrayListaVentas, idVentaCobrar, 0) != -1)
				{
					indiceVenta = venta_findVentaById(pArrayListaVentas, idVentaCobrar);
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
				else
				{
					printf("\nEl ID de la venta no existe o la venta ya está cobrada y por lo tanto no se puede cobrar.\n");
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

		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i);

			if(pCliente != NULL)
			{
				cliente_getIdClienteTxt(pCliente, idCliente);
				cliente_getNombre(pCliente, nombre);
				cliente_getApellido(pCliente, apellido);
				cliente_getCuit(pCliente, cuit);
				printf("ID de cliente: %s - Nombre: %s - Apellido: %s - CUIT: %s\n", idCliente, nombre, apellido, cuit);
				retorno = 0;
			}
		}
	}
    return retorno;
}

/*
* \brief Función que imprime las ventas
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \return (-1) Error (0) todo OK
*/
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

			if(pVenta != NULL)
			{
				venta_getIdClienteTxt(pVenta, idCliente);
				venta_getIdVentaTxt(pVenta, idVenta);
				venta_getCantidadAfichesTxt(pVenta, cantidadAfiches);
				venta_getNombreArchivo(pVenta, nombreArchivo);
				venta_getZonaTxt(pVenta, zona);
				venta_getCobradoTxt(pVenta, cobrado);
				printf("ID de cliente: %s - ID de venta: %s - Cantidad de afiches: %s - Nombre de archivo: %s - ZONA: %s - Estado de cobranza: %s\n", idCliente, idVenta, cantidadAfiches, nombreArchivo, zona, cobrado);
			}
		}
	}
    return retorno;
}

/*
* \brief Función que genera un archivo con un informe de cobros, que contiene la lista de clientes junto con la cantidad de ventas cobradas que posee cada uno.
* \param pArrayListaClientes LinkedList* es el puntero al array de clientes.
* \param pArrayListaVentas LinkedList* es el puntero al array de ventas.
* \param int es el estado de cobranza que recibe como parámetro.
* \return (-1) Error (0) todo OK
*/
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

					if(pListaFiltrada != NULL)
					{
						cantidadVentas = ll_len(pListaFiltrada);

						if(controller_saveClienteConCantidadDeVentasAsText(pFile, pCliente, cantidadVentas) == 0)
						{
							retorno = 0;
						}
					}
				}
			}
		}
	}
	fclose(pFile);
	return retorno;
}

/*
* \brief Función que guarda los datos de un cliente en el archivo pasado como parámetro de la función que llama a esta.
* \param void* es el puntero al cliente.
* \param int es la cantidad de ventas recibidas como parámetro.
* \return (-1) Error (0) todo OK
*/
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

/*
* \brief Función que ordena los clientes
* \param pArrayListEmployee LinkedList* es el puntero al array de clientes.
* \return (-1) Error (0) todo OK
*/
int controller_sortClientes(LinkedList* pArrayListaClientes)
{
	int retorno = -1;

	if(pArrayListaClientes != NULL)
	{
		cliente_sortClientes(pArrayListaClientes);
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
    static int id = -1; // Inicializo el ID en -1.

    static int flagPrimeraVez = TRUE;

    if(pArrayListaClientes != NULL)
    {
    	if(ll_isEmpty(pArrayListaClientes) == 0 && flagPrimeraVez == TRUE) // Si la lista no está vacía y es la primera vez...
    	{
    		id = encontrarMaximoId(pArrayListaClientes); // Le asigno a mi variable ID el valor que encuentra la función encontrarMaximoId.
    		flagPrimeraVez = FALSE; // Levanto la flag.
    	}
    	id++; // Aumento el contador del ID.
    }
    return id; // Retorno el ID.
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

	int maximo; // Declaro una variable auxiliar para guardar el máximo.

	int id = -1; // Inicializo el ID en -1.

	if(pArrayListaClientes != NULL)
	{
		for(int i = 0 ; i < ll_len(pArrayListaClientes) ; i++)
		{
			pCliente = ll_get(pArrayListaClientes, i); // Obtengo el índice que quiero del array de clientes y lo guardo en pCliente.
			cliente_getIdCliente(pCliente, &id); // Obtengo el ID de ese cliente.

			if(i == 0 || id > maximo) // Chequeo si el ID que obtuve es mayor al máximo actual.
			{
				maximo = id; // Si es mayor, el nuevo máximo es el ID que le pasé.
			}
		}
		id = maximo; // Al salir del bucle, me guardo en la variable ID el máximo que obtuve.
	}
	return id; // Retorno el ID.
}

static int generarNuevoIdVentas(LinkedList* pArrayListaVentas)
{
    static int id = -1;
    static int flagPrimeraVez = TRUE;

    if(pArrayListaVentas != NULL)
    {
    	if(ll_isEmpty(pArrayListaVentas) == 0 && flagPrimeraVez == TRUE)
    	{
    		id = encontrarMaximoIdVentas(pArrayListaVentas);
    		flagPrimeraVez = FALSE;
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
