/*
 * informes.h
 *
 *  Created on: 25 nov. 2020
 *      Author: Hzkr
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int informes_imprimirClienteConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);
int informes_imprimirClienteConMenosAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);
int informes_imprimirVentaConMasAfichesVendidos(LinkedList* pArrayListaClientes, LinkedList* pArrayListaVentas);

#endif /* INFORMES_H_ */
