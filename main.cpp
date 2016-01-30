#include <iostream>
#include <fstream>
#include "Lexico.h"

using namespace std;

int main() {
    Lexico lex;
    ofstream salida;

    while( !lex.fin() ) {
        lex.sigSimbolo();
    }

    salida.open( "salida.txt" );
    if( !lex.hayError() ) {
        salida << 1;
    } else {
        salida << 0;
    }
    salida.close();

    return 0;
}
