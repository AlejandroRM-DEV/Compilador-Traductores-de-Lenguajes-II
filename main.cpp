#include <iostream>
#include <fstream>
#include "Sintactico.h"

using namespace std;

int main() {
    Sintactico sin;
    ofstream salida;

    UnidadTraduccion* nodo = sin.analiza();

    salida.open( "salida.txt" );
    if( !sin.hayError() ) {
        if( nodo->analizarTipo() != T_ERROR ) {
            salida << nodo->generarCodigo();
        } else {
            salida << 0;
        }
    } else {
        salida << 0;
    }
    salida.close();

    return 0;
}
