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
            cout << "Aceptado" << endl;
            cout << nodo->generarCodigo();
            salida << nodo->generarCodigo();;
        } else {
            cout << "Rechazado semantico" << endl;
            salida << 0;
        }
    } else {
        cout << "Rechazado sintactico" << endl;
        salida << 0;
    }
    salida.close();

    return 0;
}
