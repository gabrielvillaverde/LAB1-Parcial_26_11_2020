/*
 * ventas.h
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#ifndef VENTAS_H_
#define VENTAS_H_
#define SIZE_NOMBRE_ARCHIVO 100
#define SIZE_ZONA 100

#define CABA 0
#define ZONA_SUR 1
#define ZONA_OESTE 2

typedef struct
{
	int idCliente;
	int idVenta;
	int cantidadAfiches;
	char nombreArchivo[SIZE_NOMBRE_ARCHIVO];
	char zona[SIZE_ZONA];
	int cobrado;
}Venta;

Venta* venta_new(void);
Venta* venta_newParametros(char* idCliente, char* idVenta, char* cantidadAfiches, char* nombreArchivo, char* zona, char* cobrado);
void venta_delete(Venta* this);
int venta_chequearEstadoNoCobrado(void* pElement);
int venta_chequearEstadoCobrado(void* pElement);
int venta_chequearIdYEstadoCobranza(void* pElement, void* pId, void* pEstado);
int venta_chequearIdYCalcularCantidadAfiches(void* pElement, void* pId);
int venta_contarClienteConMasAfichesVendidos(void* pElement);
int venta_findVentaById(LinkedList* pArrayListaVentas, int id);

int venta_setIdClienteTxt(Venta* this, char* idClienteACargar);
int venta_getIdClienteTxt(Venta* this, char* idCliente);
int venta_setIdCliente(Venta* this, int idClienteACargar);
int venta_getIdCliente(Venta* this, int* idCliente);

int venta_setIdVentaTxt(Venta* this, char* idVentaACargar);
int venta_getIdVentaTxt(Venta* this, char* idVenta);

int venta_setIdVenta(Venta* this, int idVentaACargar);
int venta_getIdVenta(Venta* this, int* idVenta);

int venta_setCantidadAfiches(Venta* this, int cantidadAfiches);
int venta_getCantidadAfiches(Venta* this, int* cantidadAfiches);

int venta_setCantidadAfichesTxt(Venta* this, char* cantidadAfiches);
int venta_getCantidadAfichesTxt(Venta* this, char* cantidadAfiches);

int venta_setNombreArchivo(Venta* this, char* nombreArchivo);
int venta_getNombreArchivo(Venta* this, char* nombreArchivo);

int venta_setZona(Venta* this, char* zona);
int venta_getZona(Venta* this, char* zona);

int venta_setCobrado(Venta* this, int cobrado);
int venta_getCobrado(Venta* this, int* cobrado);

int venta_setCobradoTxt(Venta* this, char* cobrado);
int venta_getCobradoTxt(Venta* this, char* cobrado);

#endif /* VENTAS_H_ */
