#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "Analizador_Lexico.h" 

void InicializarTS(TablaDeSimbolos* TS){
    TS->cant = 0;

}

bool agregarTS(TablaDeSimbolos* TS, const char* palabra, int CompLex) {
    if (TS->cant >= MAX_SIM - 1) {
        fprintf(stderr, "Error: Tabla de símbolos llena.\n");
        return false;
    }

    TS->cant++;
    
    // Usar snprintf que es más seguro (garantiza terminación nula)
    snprintf(TS->elem[TS->cant].lexema, sizeof(TS->elem[TS->cant].lexema), "%s", palabra);
    
    TS->elem[TS->cant].compLex = CompLex;
    return true;
}

void CompletarTS(TablaDeSimbolos* TS) {
    if (TS == NULL) return;

    // Asignar el componente léxico correcto a cada palabra reservada
    agregarTS(TS, "while", Twhile);
    agregarTS(TS, "if", Tif);
    agregarTS(TS, "def", Tdef);
    agregarTS(TS, "program", Tprogram);
    agregarTS(TS, "title", Ttitle);
    agregarTS(TS, "read", Tread);
    agregarTS(TS, "print", Tprint);
    agregarTS(TS, "pot", Tpot);
    agregarTS(TS, "root", Troot);
    agregarTS(TS, "array", Tarray);
    agregarTS(TS, "else", Telse);
}


void instalarEnTs(const char* lexema, TablaDeSimbolos* TS, TipoSG* CompLex) {
    bool pre_ex = false;
    uint8_t i;

    for (i = 0; i < TS->cant; i++) {
        if (strcmp(lexema, TS->elem[i].lexema) == 0) {
            *CompLex = TS->elem[i].compLex;
            pre_ex = true;
            break;
        }
    }

    if (!pre_ex) {
        strcpy(TS->elem[TS->cant].lexema, lexema);  // asegurate de tener espacio
        TS->elem[TS->cant].compLex = Tid;
        *CompLex = Tid;
        TS->cant++;
    }
}


void LeerCar(FILE* fuente, long* control, char* car) {
    fseek(fuente, *control, SEEK_SET);  // Posiciona al inicio del carácter actual
    int c = fgetc(fuente);             // Lee un carácter (fgetc retorna int, no char)
    
    if (c != EOF) {
        *car = (char)c;                // Almacena el carácter leído
    } else {
        *car = EOF;                    // Fin de archivo
    }
}


bool EsId(FILE* fuente, long* control, char* lexema) {
    
    typedef enum { L, D, O } Sigma;
    
    // delta[estado][simbolo que representa]
    // por ejemplo en la def delta[3][3] significa que tiene 3 estados (q1, q2 y q3) y que tiene 3 simbolos posibles (L, D, O)

    int estadoActual = 0;

    int delta[3][3] = {
        {1, 3, 3},  // estado 0 (q0) va a estado 1 (q1) por medio de L, va a estado 3 (q3) por medio de D, va a q3 por medio de O.
        {1, 1, 2},  // q1 va a q1 por medio de L, va a q1 por medio de D, va a q2 por medio de O.
    };

    // en resumen, define el comportamiento del autómata.
    // q2 es el estado final, así que la única forma de llegar es a través de una (o muchas) letra/s y un símbolo. 

    long contLocal = *control;
    char car;
    int len = 0;

    Sigma CarASimb(char c) {    
        if (isalpha(c)) return L;
        else if (isdigit(c)) return D;
        else return O;
    }

    while (estadoActual != 2 && estadoActual != 3) {
        LeerCar(fuente, &contLocal, &car);
        estadoActual = delta[estadoActual][CarASimb(car)];
        contLocal++;
        if (estadoActual == 1) lexema[len++] = car;
    }

    if (estadoActual == 2) {
        lexema[len] = '\0';
        *control = contLocal - 1;
        return true;
    }

    return false;
}

/*

Nota: Estas otras funciones que devuelven booleanos también le faltan autómatas

bool EsConstanteReal(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
bool EsCadena(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
bool EsSimboloEspecial(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
void ObtenerSiguienteCompLex(FILE* fuente, long* control, TipoSG* CompLex, char* lexema, size_t maxLexema, TablaDeSimbolos* TS){

}
*/
