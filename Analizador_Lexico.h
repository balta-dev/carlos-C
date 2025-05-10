#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include <stdio.h>

#define MAX_SIM 200
#define MAX_LEX 256
#define FIN_ARCH '\0'

typedef enum {
    Tprogram, Tid, TCreal, Tcad, Twhile, Tif, Tdef, Ttitle, Tpycom, Tcoma,
    Tarray, Tmenos, Tmas, Tasig, Tnot, Tand, Tor, Tmultip, Tdiv, TParen_ab,
    TParen_cer, TCorr_ab, TCorr_cer, TLlav_ab, TLlav_cer, Tpot, Troot, Telse,
    Tread, Tprint, TRelacional, pesos, ErrorLexico, VLenguaje, VL_2, VL_3,
    VTitulo, VDefiniciones, VD_2, VD_3, VCuerpo, VC2, VSent, VAsig, VAsig_2,
    VAsig_3, VElem_V, VElem_V2, VopArit, VSOA, VOA2, VSOA2, VOA3, Varreglo,
    VPotencia, VNum_p, VCondi, VOtro, Vvalor_B, VSOL, VOL2, VSOL2, VOL3, VLeer,
    VImprimir, VMostrar, VSM, VSM2, VCiclo
} TipoSG;

typedef struct {
    TipoSG compLex;
    char lexema[MAX_LEX];  // o char* si lo vas a manejar dinámicamente
} TElemTS;

typedef struct {
    TElemTS elem[MAX_SIM];
    int cant;
} TablaDeSimbolos;

void InicializarTS(TablaDeSimbolos* TS);
bool agregarTS(TablaDeSimbolos* TS, const char* palabra, int CompLex);
void CompletarTS(TablaDeSimbolos* TS);
void LeerCar(FILE* fuente, long* control, char* car);
bool EsId(FILE* fuente, long* control, char* lexema);
bool EsConstanteReal(FILE* fuente, long* control, char* lexema);
bool EsCadena(FILE* fuente, long* control, char* lexema);
bool EsSimboloEspecial(FILE* fuente, long* control, char* lexema, TipoSG* CompLex);
void ObtenerSiguienteCompLex(FILE* fuente, long* control, TipoSG* CompLex, char* lexema, TablaDeSimbolos* TS);

#endif
