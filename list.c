/*+++
Este código se actualizó de forma manual (igual que en el Lab 1) porque el classic token de Github no lo actualiza automáticamente desde replit,
retorna el mismo error que ya me había encontrado en el Lab anterior -> funciona la primera vez, pero por alguna razón deja de actualizar el
repositorio después independientemente de si pego el token correctamente, dejando este error en específico:
Token: 
Token vacío. Abortando.
---
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    List *nuevaLista = malloc(sizeof(List));
    nuevaLista->current = nuevaLista->head = nuevaLista->tail = NULL;
    return nuevaLista;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.

void * firstList(List * list) {
    if(list->head) {
        list->current = list->head;
        return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if(list->current && list->current->next) {
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {
    if(list->tail) {
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if(list->current && list->current->prev) {
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * list, void * data) {
    Node *tmpNode = createNode(data);
    if(list->head) {
        tmpNode->next = list->head;
        list->head->prev = tmpNode;
        list->head = tmpNode;
    }
    else {
        list->head = tmpNode;
        list->tail = tmpNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * list, void * data) {

    /*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Función original -> La versión que le sigue está mejor optimizada y es más robusta
    
    Node *newNode = createNode(data);
    
    if(list->current) {
        newNode->next = list->current->next;
        newNode->prev = list->current;
        if(list->current->next != NULL) list->current->next->prev = newNode;
        else list->tail = newNode;
        list->current->next = newNode;
        list->current = newNode;
    }
    // Caso donde la lista está completamente vacía
    else {
        if(list->head==NULL) list->head = list->tail = list->current = newNode;
    }
    ---------------------------------------------------------------------------
    */

    if(!list) return;
    
    if(list->current) {
        Node *newNode = createNode(data);
        newNode->next = list->current->next;
        newNode->prev = list->current;

        if(list->current->next != NULL)list->current->next->prev = newNode;
        else list->tail = newNode;

        list->current->next = newNode;
        list->current = newNode;
    }
    else if(list->head == NULL) {
        Node *newNode = createNode(data);
        list->head = list->tail = list->current = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {

    /*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Versión original de la función -> Ignorar, le sigue una versión mejor optimizada.
    
    Node *tmpNode = list->current;
    void *dato = NULL;
    if(tmpNode) {
        dato = tmpNode->data;
        if(tmpNode == list->head) {
            
            if(tmpNode->next != NULL) {
                list->head = list->current = tmpNode->next;
                list->current->prev = list->head->prev = NULL;
                free(tmpNode);
            }
            else list->head = list->current = list->tail = NULL;
        }
        else if(tmpNode == list->tail) {
            list->tail = tmpNode->prev;
            list->tail->next = NULL;
            list->current = NULL;
            free(tmpNode);
        }
        else if(tmpNode->next != NULL) {
            tmpNode->next->prev = tmpNode->prev;
            tmpNode->prev->next = tmpNode->next;
            list->current = tmpNode->next;
            free(tmpNode);
        }
    }
    ------------------------------------------------------------------------------
    */

    /*
    +++ 
    En vez de comenzar a preguntar sobre cada caso posible de uno en uno, esta función pregunta por cada vínculo posible
    que el nodo a eliminar, current, podría llegar a tener, comenzando a barrer list dependiendo de dichos vínculos que
    puedan o no existir para comenzar a ajustar la eliminación del nodo actual(current).
    
    La lógica iría de esta forma:
    1. list o el nodo current existen? Si no, finalizar la función de inmediato
    2. Inicializar variables tmpNode->a eliminar su data que debemos imprimir.
    3. Existe un nodo previo al actual? En caso de que sí, lo ajustamos para desenlazarlo del nodo actual. En caso
        contrario, eso significaría que el nodo actual era el head, por ende hay que actualizar el head.
    4. Existe un nodo siguiente al actual? En caso de que sí, lo ajustamos al nodo previo al actual; en caso contrario,
        eso significaría que el nodo actual era el tail, por ende el nodo tail de list debe ser ajustado.
    5. Liberar nodo actual(tmpNode) del heap.
    ---
    */
    
    // Descartar casos donde la lista o current no existan por seguridad
    if(!list || !list->current) return NULL;
    
    Node *tmpNode = list->current;
    void *dato = tmpNode->data;
    
    if(tmpNode->prev) tmpNode->prev->next = tmpNode->next;
    else list->head = tmpNode->next;

    if(tmpNode->next) {
        tmpNode->next->prev = tmpNode->prev;
        list->current = tmpNode->next; // Enlazar current al nodo siguiente de current
    }
    
    else {
        list->tail = tmpNode->prev; // nodo tail actualizado
        list->current = NULL; // No hay nodo siguiente
    }
    free(tmpNode); // Liberar nodo a borrar del heap
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
