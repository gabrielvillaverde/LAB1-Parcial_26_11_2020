/*
 * parser.h
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_leerListaClientesFromText(FILE* pFile, LinkedList* pArrayListaClientes);
int parser_leerListaVentasFromText(FILE* pFile, LinkedList* pArrayListaVentas);

#endif /* PARSER_H_ */
