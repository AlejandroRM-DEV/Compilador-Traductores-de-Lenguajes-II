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
        //cout << "Aceptado" << endl;
        salida << nodo->toString();
    } else {
        //cout << "Rechazado" << endl;
        salida << 0;
    }
    salida.close();

    return 0;
}
