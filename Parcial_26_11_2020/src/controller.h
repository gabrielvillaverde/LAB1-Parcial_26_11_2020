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
int controller_addCliente(LinkedList* pArrayListaClientes);
int controller_esCuitRepetido(LinkedList* pArrayListaClientes, char* pCuit);
int controller_addVenta(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes);
int controller_saveClienteAsText(char* path, LinkedList* pArrayListaClientes);
int controller_saveVentasAsText(char* path, LinkedList* pArrayListaVentas);
int controller_imprimirClientes(LinkedList* pArrayListaClientes);
int controller_imprimirVentas(LinkedList* pArrayListaVentas);
int controller_modificarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes);
int controller_cobrarVentas(LinkedList* pArrayListaVentas, LinkedList* pArrayListaClientes);
int controller_generarInformeDeCobros(char* path, LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas, int estado);
int controller_saveClienteConCantidadDeVentasAsText(FILE* pFile, void* pCliente, int cantidadVentas);
int controller_imprimirClienteConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);
int controller_imprimirClienteConMenosAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);
int controller_imprimirVentaConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);

#endif /* CONTROLLER_H_ */
