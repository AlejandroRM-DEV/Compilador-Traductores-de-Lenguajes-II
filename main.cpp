#include <iostream>
#include <fstream>
#include "Sintactico.h"

using namespace std;

int main() {
    Sintactico sin;
    ofstream salida;

    sin.analiza();

    salida.open( "salida.txt" );
    if( !sin.hayError() ) {
        cout << "Aceptado" << endl;
        salida << 1;
    } else {
        cout << "Rechazado" << endl;
        salida << 0;
    }
    salida.close();

    return 0;
}
