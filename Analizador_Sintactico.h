#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H
#include "Analizador_Lexico.h"  // para TipoSG

#define MAX_PROD 6

// ----------------- Producción ------------------
typedef struct {
    TipoSG elem[MAX_PROD];
    int cant;
} TProduccion;

// ----------------- Árbol -----------------------
typedef struct TNodoArbol TNodoArbol;  // forward declaration
typedef TNodoArbol* TApuntNodo;

typedef struct {
    TApuntNodo elem[MAX_PROD];
    int cant;
} TipoHijos;

struct TNodoArbol {
    TipoSG Simbolo;
    char lexema[256];  // o char* si lo vas a manejar con malloc/strdup
    TipoHijos Hijos;
};

// ----------------- Pila ------------------------
typedef struct {
    TipoSG Simbolo;
    TApuntNodo NodoArbol;
} TipoElemPila;

typedef struct T_NODO_PILA T_NODO_PILA;
typedef T_NODO_PILA* T_PUNT_PILA;

struct T_NODO_PILA {
    TipoElemPila INFO;
    T_PUNT_PILA SIG;
};

typedef struct {
    T_PUNT_PILA TOPE;
    unsigned short TAM;
} TipoPila;

// ----------------- Prototipo --------------------
void Analizador_Predictivo(const char* archivo, TApuntNodo* arbol, bool* estado);

#endif