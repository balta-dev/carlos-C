#ifndef EVALUADOR_H
#define EVALUADOR_H

#include <stdbool.h>  // Para poder usar tipos como bool

// Definimos los valores máximos, igual que en Pascal
#define MaxVar 200
#define MaxReal 200
#define MaxArreglo 100

// Definimos el tipo TTipo como un enumerado
typedef enum {
    Treal,
    Tarreglo
} TTipo;

// Definimos el tipo TElemEstado como una estructura
typedef struct {
    char lexemaId[100];        // Asumimos que el tamaño máximo del lexema es 100
    float ValReal;             // Para valores reales
    TTipo Tipo;                // Tipo (real o arreglo)
    float ValArray[MaxArreglo]; // Arreglo de valores reales
    unsigned char CantArray;   // Cantidad de elementos en el arreglo
} TElemEstado;

// Definimos el tipo TEstado como una estructura
typedef struct {
    TElemEstado elementos[MaxVar]; // Elementos del estado
    unsigned short cant;           // Cantidad de elementos en el estado
} TEstado;

// Funciones declaradas para manejar el estado
void inicializarEstado(TEstado* estado);
bool buscarElemento(const TEstado* estado, const char* lexema, TElemEstado* resultado);
void agregarElemento(TEstado* estado, const TElemEstado* elem);

#endif
