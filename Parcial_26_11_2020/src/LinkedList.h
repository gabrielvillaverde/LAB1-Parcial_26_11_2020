/*
 * LinkedList.h
 *
 *  Created on: 20 nov. 2020
 *      Author: Hzkr
 */

#ifndef __LINKEDLIST
#define __LINKEDLIST
struct Node
{
    void* pElement;          // Puntero al elemento, es void* así es genérico (persona, empleado, etcétera)
    struct Node* pNextNode;  // Puntero al próximo nodo
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;        // Puntero al primer nodo
    int size;                // Cada vez que agrego o elimino un elemento: size++/--
}typedef LinkedList;
#endif

LinkedList* ll_newLinkedList(void);
int ll_len(LinkedList* this);
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex, void* pElement);
int ll_add(LinkedList* this, void* pElement);
void* ll_get(LinkedList* this, int index);
int ll_set(LinkedList* this, int index, void* pElement);
int ll_remove(LinkedList* this, int index);
int ll_clear(LinkedList* this);
int ll_deleteLinkedList(LinkedList* this);
int ll_indexOf(LinkedList* this, void* pElement);
int ll_isEmpty(LinkedList* this);
int ll_push(LinkedList* this, int index, void* pElement);
void* ll_pop(LinkedList* this, int index);
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this, LinkedList* this2);
LinkedList* ll_subList(LinkedList* this, int from,int to);
LinkedList* ll_clone(LinkedList* this);
int ll_sort(LinkedList* this, int (*pFunc)(void*, void*), int order);
int ll_map(LinkedList* this, int (*pFunc)(void*));
int ll_map2(LinkedList* this, int (*pFunc)(void*, char*), void* argumento);
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*));
LinkedList* ll_filter2(LinkedList* this, int (*pFunc)(void*,void*), void* argumento);
LinkedList* ll_filter3(LinkedList* this, int (*pFunc)(void*, void*, void*), void* argumentoUno, void* argumentoDos);
int ll_reduce(LinkedList* this, int (*pFunc)(void*, int, int));
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*,void*), void* argumento);
float ll_reduceFloat(LinkedList* this, float (*pFunc)(void*));
int ll_count(LinkedList* this, int(*pFunc)(void*));
