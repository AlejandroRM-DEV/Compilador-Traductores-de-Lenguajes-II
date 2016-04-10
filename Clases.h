#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Nodo {
public:
    string simbolo;
    Nodo() {}
    virtual ~Nodo() {}
    virtual string toString() = 0;
};

class Expresion: public Nodo {
public:
    Expresion* izquierda;
    Expresion* derecha;

    Expresion() {
        izquierda = nullptr;
        derecha = nullptr;
    }

    virtual ~Expresion() {
        if( izquierda != nullptr ) {
            delete izquierda;
        };
        if( derecha != nullptr ) {
            delete derecha;
        };
    }

    string toString() = 0;
};

class Identificador: public Expresion {
public:
    Identificador( string simbolo ) {
        this->simbolo = simbolo;
    }

    ~Identificador() {}

    string toString() {
        stringstream ss;
        ss << "<ID>" << simbolo << "</ID>" << endl;
        return ss.str();
    }
};

class Entero: public Expresion {
public:
    Entero( string simbolo ) {
        this->simbolo = simbolo;
    }

    ~Entero() {}

    string toString() {
        stringstream ss;
        ss << "<ENTERO>" << simbolo << "</ENTERO>" << endl;
        return ss.str();
    }
};

class Real: public Expresion {
public:
    Real( string simbolo ) {
        this->simbolo = simbolo;
    }

    ~Real() {}

    string toString() {
        stringstream ss;
        ss << "<REAL>" << simbolo << "</REAL>" << endl;
        return ss.str();
    }
};

class OR: public Expresion {
public:
    OR( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "||";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~OR() {}

    string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"||\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class AND: public Expresion {
public:
    AND( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "&&";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~AND() {}

    string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"&&\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class Igual: public Expresion {
public:
    Igual( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "==";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Igual() {}

    string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"==\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class Diferente: public Expresion {
public:
    Diferente( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "!=";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Diferente() {}

     string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"!=\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class Menor: public Expresion {
public:
    Menor( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "<";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Menor() {}

    string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"&lt;\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class MenorIgual: public Expresion {
public:
    MenorIgual( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "<=";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~MenorIgual() {}

     string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"&lt;=\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class Mayor: public Expresion {
public:
    Mayor( Expresion* izquierda, Expresion* derecha ) {
        simbolo = ">";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Mayor() {}

     string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"&gt;\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class MayorIgual: public Expresion {
public:
    MayorIgual( Expresion* izquierda, Expresion* derecha ) {
        simbolo = ">=";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~MayorIgual() {}

    string toString() {
        stringstream ss;
        ss << "<EXPRESION value=\"&gt;=\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</EXPRESION>" << endl;
        return ss.str();
    }
};

class Suma: public Expresion {
public:
    Suma( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "+";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Suma() {}

        string toString() {
        stringstream ss;
        ss << "<SUMA value=\"+\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</SUMA>" << endl;
        return ss.str();
    }
};

class Resta: public Expresion {
public:
    Resta( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "-";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Resta() {}

    string toString() {
        stringstream ss;
        ss << "<SUMA value=\"-\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</SUMA>" << endl;
        return ss.str();
    }
};

class Multiplicacion: public Expresion {
public:
    Multiplicacion( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "*";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Multiplicacion() {}

    string toString() {
        stringstream ss;
        ss << "<MULT value=\"*\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</MULT>" << endl;
        return ss.str();
    }
};

class Division: public Expresion {
public:
    Division( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "/";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Division() {}

    string toString() {
        stringstream ss;
        ss << "<MULT value=\"/\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</MULT>" << endl;
        return ss.str();
    }
};

class Modulo: public Expresion {
public:
    Modulo( Expresion* izquierda, Expresion* derecha ) {
        simbolo = "%";
        this->izquierda = izquierda;
        this->derecha = derecha;
    }

    ~Modulo() {}

    string toString() {
        stringstream ss;
        ss << "<MULT value=\"%\">" << endl;
        if( izquierda != nullptr ) {
            ss << izquierda->toString( );
        }
        if( derecha != nullptr ) {
            ss << derecha->toString( );
        }
        ss << "</MULT>" << endl;
        return ss.str();
    }
};

class Asignacion: public Expresion {
public:
    Identificador* id;
    Expresion* expresion;

    Asignacion( Identificador* id, Expresion* expresion ) {
        this->id = id;
        this->expresion = expresion;
    }

    ~Asignacion() {
        if( id != nullptr ) {
            delete id;
        };
        if( expresion != nullptr ) {
            delete expresion;
        };
    }

    string toString() {
        stringstream ss;

        ss << "<ASIGNACION>" << endl;
        ss << id->simbolo << endl;

        if( expresion != nullptr ) {
            ss << expresion->toString( );
        }
        ss << "</ASIGNACION>" << endl;

        return ss.str();
    }
};

class UnarioNegativo: public Expresion {
public:
    Expresion* exp;

    UnarioNegativo( Expresion* exp ) {
        this->exp = exp;
    }

    ~UnarioNegativo( ) {
        delete exp;
    }

    string toString() {
        stringstream ss;
        ss << "<SIGNO value=\"-\">" << endl;

        if( exp != nullptr ) {
            ss << exp->toString( );
        }
        ss << "</SIGNO>" << endl;
        return ss.str();
    }
};

class UnarioPositivo: public Expresion {
public:
    Expresion* exp;

    UnarioPositivo( Expresion* exp ) {
        this->exp = exp;
    }

    ~UnarioPositivo( ) {
        delete exp;
    }

    string toString() {
        stringstream ss;
        ss << "<SIGNO value=\"+\">" << endl;

        if( exp != nullptr ) {
            ss << exp->toString( );
        }
        ss << "</SIGNO>" << endl;
        return ss.str();
    }
};

class Proposicion: public Nodo {
public:
    Proposicion() {}
    virtual ~Proposicion() {}
    virtual string toString() = 0;
};

class If: public Proposicion {
public:
    Expresion* exp;
    Nodo* proIf;
    Nodo* proElse;

    If() {
        exp = nullptr;
        proIf = nullptr;
        proElse = nullptr;
    }

    ~If() {
        delete exp;
        if( proIf != nullptr ) {
            delete proIf;
        }
        if( proElse != nullptr ) {
            delete proElse;
        }
    }

    string toString() {
        stringstream ss;
        ss << "<SI>" << endl;
        ss << exp->toString();
        ss << proIf->toString();

        if( proElse != nullptr ) {
            ss << "<OTRO>" << endl;
            ss << proElse->toString( );
            ss << "</OTRO>" << endl;
        }
        ss << "</SI>" << endl;
        return ss.str();
    }
};

class Bloque: public Proposicion {
public:
    vector<Nodo*> cuerpo;

    Bloque( ) {
    }

    ~Bloque() {
        for( Nodo* nodo : cuerpo ) {
            delete nodo;
        }
    }

    string toString() {
        stringstream ss;

        ss << "<BLOQUE>" << endl;
        for( Nodo* n: cuerpo ) {
            ss << n->toString();
        }
        ss << "</BLOQUE>" << endl;
        return ss.str();
    }
};

class Print: public Proposicion {
public:
    Expresion* exp;

    Print() {
        exp = nullptr;
    }

    ~Print() {
        delete exp;
    }

    string toString() {
        stringstream ss;
        ss << "<IMPRIME>" << endl;
        ss << "<EXPRESION>" << endl;
        ss << exp->toString();
        ss << "</EXPRESION>" << endl;
        ss << "</IMPRIME>" << endl;
        return ss.str();
    }
};

class While: public Proposicion {
public:
    Expresion* exp;
    Nodo* proposicion;

    While() {
        exp = nullptr;
        proposicion = nullptr;
    }

    ~While() {
        delete exp;
        delete proposicion;
    }

    string toString() {
        stringstream ss;
        ss << "<MIENTRAS>" << endl;
        ss << exp->toString();
        ss << proposicion->toString( );
        ss << "</MIENTRAS>" << endl;
        return ss.str();
    }
};


class UnidadTraduccion: public Nodo {
public:
    vector<Nodo*> definiciones;

    UnidadTraduccion() {}

    ~UnidadTraduccion() {
        for( Nodo* d : definiciones ) {
            delete d;
        }
    }
    string toString() {
        stringstream ss;
        ss << "<PROGRAMA>" << endl;

        for( Nodo* d : definiciones ) {
            ss << d->toString();
        }
        ss << "</PROGRAMA>" << endl;

        return ss.str();
    }
};
#endif // CLASES_H_INCLUDED
