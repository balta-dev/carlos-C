#include <stdio.h>
#include <string.h>
#include <stdint.h>
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


void LeerCar(FILE* fuente, long* control, char* car){

    fseek(fuente, 0, SEEK_END);
    long filesize = ftell(fuente);

    if (*control < filesize) {
        fseek(fuente, *control, SEEK_SET);
        *car = fgetc(fuente);
    } else {
        *car = EOF;
    }

}

/*
bool EsId(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
bool EsConstanteReal(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
bool EsCadena(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
bool EsSimboloEspecial(FILE* fuente, long* control, char* lexema, size_t maxLexema){

}
void ObtenerSiguienteCompLex(FILE* fuente, long* control, TipoSG* CompLex, char* lexema, size_t maxLexema, TablaDeSimbolos* TS){

}

*/