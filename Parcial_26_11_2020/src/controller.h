/*
 * controller.h
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadListaClientesFromText(char* path, LinkedList* pArrayListaClientes);
int controller_loadListaVentasFromText(char* path, LinkedList* pArrayListaVentas);
int controller_saveClienteAsText(char* path, LinkedList* pArrayListaClientes);
int controller_saveVentasAsText(char* path, LinkedList* pArrayListaVentas);
int controller_addCliente(LinkedList* pArrayListaClientes);
int controller_removeCliente(LinkedList* pArrayListaClientes);
int controller_removeClienteConTodasSusVentas(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);
int controller_addVenta(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes);
int controller_modificarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes);
int controller_imprimirClientes(LinkedList* pArrayListaClientes);
int controller_imprimirVentas(LinkedList* pArrayListaVentas);
int controller_cobrarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes);
int controller_generarInformeDeCobros(char* path, LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas, int estado);
int controller_saveClienteConCantidadDeVentasAsText(FILE* pFile, void* pCliente, int cantidadVentas);
int controller_sortClientes(LinkedList* pArrayListaClientes);

int controller_generarListaVentasConAfichesQueSePudieronImprimir(LinkedList* pArrayListaVentas);
int controller_obtenerVentasZonaSur(LinkedList* pArrayListaVentas);
int controller_obtenerVentasZona(LinkedList* pArrayListaVentas, int zona);
int controller_cantidadAfichesPromedioPorTodasLasVentas(LinkedList* pArrayListaVentas);

#endif /* CONTROLLER_H_ */
