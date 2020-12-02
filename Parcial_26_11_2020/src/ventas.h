/*
 * ventas.h
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#ifndef VENTAS_H_
#define VENTAS_H_

#define SIZE_NOMBRE_ARCHIVO 10000

typedef struct
{
	int idCliente;
	int idVenta;
	int cantidadAfiches;
	char nombreArchivo[SIZE_NOMBRE_ARCHIVO];
	int zona;
	int cobrado;
}Venta;

Venta* venta_new(void);
Venta* venta_newParametros(char* idCliente, char* idVenta, char* cantidadAfiches, char* nombreArchivo, char* zona, char* cobrado);
void venta_delete(Venta* this);

int venta_chequearEstadoSiCobrado(void* pElement);
int venta_chequearEstadoNoCobrado(void* pElement);
int venta_chequearId(void* pElement, void* pId);
int venta_chequearIdYEstadoCobranza(void* pElement, void* pId, void* pEstado);
int venta_chequearIdYCalcularCantidadAfiches(void* pElement, void* pId);
int venta_retornarCantidadAfiches(void* argumento);
int venta_contarClienteConMasAfichesVendidos(void* pElement);
int venta_findVentaById(LinkedList* pArrayListaVentas, int id);
int venta_findVentaByIdAndCheckEstadoCobranza(LinkedList* pArrayListaVentas, int id, int estado);

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

int venta_getZona(Venta* this, int* zona);
int venta_setZona(Venta* this, int zona);
int venta_setZonaTxt(Venta* this, char* zona);
int venta_getZonaTxt(Venta* this, char* zona);

int venta_setCobrado(Venta* this, int cobrado);
int venta_getCobrado(Venta* this, int* cobrado);
int venta_setCobradoTxt(Venta* this, char* cobrado);
int venta_getCobradoTxt(Venta* this, char* cobrado);

/*
int venta_setZona(Venta* this, int zona);
int venta_getZona(Venta* this, int* zona);
*/

int venta_calculo20PorCientoSobreCantidadAfiches(void* pElement);
int venta_obtenerZonaCaba(void* pElement);
int venta_obtenerZonaSur(void* pElement);
int venta_obtenerZonaOeste(void* pElement);
int venta_obtenerZona(void* pElement, void* pZona);
int venta_retornarZona(void* pElement);

#endif /* VENTAS_H_ */
