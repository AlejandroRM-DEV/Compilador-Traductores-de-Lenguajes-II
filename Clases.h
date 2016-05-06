#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>

#include "TablaSimbolos.h"

TablaSimbolos* TablaSimbolos::instancia = nullptr;

unsigned long long int contador;

using namespace std;

class Nodo {
	public:
		string simbolo;
		Nodo() {}
		virtual ~Nodo() {}
		virtual TipoDato analizarTipo() = 0;
		virtual string generarCodigo() = 0;
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

		TipoDato analizarTipo() = 0;

		virtual ~Expresion() {
			if ( izquierda != nullptr ) {
				delete izquierda;
			};
			if ( derecha != nullptr ) {
				delete derecha;
			};
		}

		string toString() = 0;
		string generarCodigo() = 0;
};

class Identificador: public Expresion {
	public:
		Identificador ( string simbolo ) {
			this->simbolo = simbolo;
		}

		~Identificador() {}

		TipoDato analizarTipo() {
			return TablaSimbolos::instance()->tipoSim ( simbolo );
		}

		string generarCodigo() {
			stringstream ss;
			ss << "\tpush " << simbolo << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<ID>" << simbolo << "</ID>" << endl;
			return ss.str();
		}
};

class Entero: public Expresion {
	public:
		Entero ( string simbolo ) {
			this->simbolo = simbolo;
		}

		~Entero() {}

		TipoDato analizarTipo() {
			return T_INT;
		}
		string generarCodigo() {
			stringstream ss;
			ss << "\tpush " << simbolo << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<ENTERO>" << simbolo << "</ENTERO>" << endl;
			return ss.str();
		}
};

class Real: public Expresion {
	public:
		Real ( string simbolo ) {
			this->simbolo = simbolo;
		}

		~Real() {}

		TipoDato analizarTipo() {
			return T_FLOAT;
		}
		string generarCodigo() {
			stringstream ss;
			ss << "" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<REAL>" << simbolo << "</REAL>" << endl;
			return ss.str();
		}
};

class OR: public Expresion {
	public:
		OR ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "||";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~OR() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << "" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"||\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class AND: public Expresion {
	public:
		AND ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "&&";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~AND() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << "" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&amp;&amp;\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class Igual: public Expresion {
	public:
		Igual ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "==";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Igual() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss, verdadero, fin;
			verdadero << "VERDADERO" << ( ++contador );
			fin << "FIN" << ( contador );

			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, ebx" << endl;
			ss << "\tje " << verdadero.str()  << endl;
			ss << "\tpush 0" << endl;
			ss << "\tjmp " << fin.str() << endl;
			ss << verdadero.str() << ":" << endl;
			ss << "\tpush 1" << endl;
			ss << fin.str() << ":" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&lt;\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class Diferente: public Expresion {
	public:
		Diferente ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "!=";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Diferente() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss, verdadero, fin;
			verdadero << "VERDADERO" << ( ++contador );
			fin << "FIN" << ( contador );
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, ebx" << endl;
			ss << "\tjne " << verdadero.str()  << endl;
			ss << "\tpush 0" << endl;
			ss << "\tjmp " << fin.str() << endl;
			ss << verdadero.str() << ":" << endl;
			ss << "\tpush 1" << endl;
			ss << fin.str() << ":" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&lt;\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class Menor: public Expresion {
	public:
		Menor ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "<";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Menor() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss, verdadero, fin;
			verdadero << "VERDADERO" << ( ++contador );
			fin << "FIN" << ( contador );
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, ebx" << endl;
			ss << "\tjl " << verdadero.str()  << endl;
			ss << "\tpush 0" << endl;
			ss << "\tjmp " << fin.str() << endl;
			ss << verdadero.str() << ":" << endl;
			ss << "\tpush 1" << endl;
			ss << fin.str() << ":" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&lt;\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class MenorIgual: public Expresion {
	public:
		MenorIgual ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "<=";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~MenorIgual() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss, verdadero, fin;
			verdadero << "VERDADERO" << ( ++contador );
			fin << "FIN" << ( contador );
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, ebx" << endl;
			ss << "\tjle " << verdadero.str()  << endl;
			ss << "\tpush 0" << endl;
			ss << "\tjmp " << fin.str() << endl;
			ss << verdadero.str() << ":" << endl;
			ss << "\tpush 1" << endl;
			ss << fin.str() << ":" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&lt;\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class Mayor: public Expresion {
	public:
		Mayor ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = ">";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Mayor() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss, verdadero, fin;
			verdadero << "VERDADERO" << ( ++contador );
			fin << "FIN" << ( contador );
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, ebx" << endl;
			ss << "\tjg " << verdadero.str()  << endl;
			ss << "\tpush 0" << endl;
			ss << "\tjmp " << fin.str() << endl;
			ss << verdadero.str() << ":" << endl;
			ss << "\tpush 1" << endl;
			ss << fin.str() << ":" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&lt;=\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class MayorIgual: public Expresion {
	public:
		MayorIgual ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = ">=";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~MayorIgual() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss, verdadero, fin;
			verdadero << "VERDADERO" << ( ++contador );
			fin << "FIN" << ( contador );
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, ebx" << endl;
			ss << "\tjge " << verdadero.str()  << endl;
			ss << "\tpush 0" << endl;
			ss << "\tjmp " << fin.str() << endl;
			ss << verdadero.str() << ":" << endl;
			ss << "\tpush 1" << endl;
			ss << fin.str() << ":" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<EXPRESION value=\"&lt;\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</EXPRESION>" << endl;
			return ss.str();
		}
};

class Suma: public Expresion {
	public:
		Suma ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "+";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Suma() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tadd eax, ebx" << endl;
			ss << "\tpush eax" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<SUMA value=\"+\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</SUMA>" << endl;
			return ss.str();
		}
};

class Resta: public Expresion {
	public:
		Resta ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "-";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Resta() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\tsub eax, ebx" << endl;
			ss << "\tpush eax" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<SUMA value=\"-\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</SUMA>" << endl;
			return ss.str();
		}
};

class Multiplicacion: public Expresion {
	public:
		Multiplicacion ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "*";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Multiplicacion() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\txor edx, edx" << endl;
			ss << "\timul ebx" << endl;
			ss << "\tpush eax" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<MULT value=\"*\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</MULT>" << endl;
			return ss.str();
		}
};

class Division: public Expresion {
	public:
		Division ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "/";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Division() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\txor edx, edx" << endl;
			ss << "\tdiv ebx" << endl;
			ss << "\tpush eax" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<MULT value=\"/\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
				ss << derecha->toString( );
			}
			ss << "</MULT>" << endl;
			return ss.str();
		}
};

class Modulo: public Expresion {
	public:
		Modulo ( Expresion* izquierda, Expresion* derecha ) {
			simbolo = "%";
			this->izquierda = izquierda;
			this->derecha = derecha;
		}

		~Modulo() {}

		TipoDato analizarTipo() {
			if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
				return izquierda->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << izquierda->generarCodigo();
			ss << derecha->generarCodigo();
			ss << "\tpop ebx" << endl;
			ss << "\tpop eax" << endl;
			ss << "\txor edx, edx" << endl;
			ss << "\tdiv ebx" << endl;
			ss << "\tpush edx" << endl;
			return ss.str();

		}
		string toString() {
			stringstream ss;
			ss << "<MULT value=\"%\">" << endl;
			if ( izquierda != nullptr ) {
				ss << izquierda->toString( );
			}
			if ( derecha != nullptr ) {
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

		Asignacion ( Identificador* id, Expresion* expresion ) {
			this->id = id;
			this->expresion = expresion;
		}

		~Asignacion() {
			if ( id != nullptr ) {
				delete id;
			};
			if ( expresion != nullptr ) {
				delete expresion;
			};
		}

		TipoDato analizarTipo() {
			TipoDato tipoExp = expresion->analizarTipo();
			if ( tipoExp != T_ERROR ) {
				if ( TablaSimbolos::instance()->existe ( id->simbolo ) ) {
					if ( id->analizarTipo() != tipoExp ) {
						return T_ERROR;
					}
				} else {
					TablaSimbolos::instance()->agregarVariable ( id->simbolo, tipoExp );
				}
				return id->analizarTipo();
			} else {
				return T_ERROR;
			}
		}
		string generarCodigo() {
			stringstream ss;
			ss << expresion->generarCodigo();
			ss << "\tpop " << id->simbolo << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;

			ss << "<ASIGNACION>" << endl;
			ss << id->simbolo << endl;

			if ( expresion != nullptr ) {
				ss << expresion->toString( );
			}
			ss << "</ASIGNACION>" << endl;

			return ss.str();
		}
};

class UnarioNegativo: public Expresion {
	public:
		Expresion* exp;

		UnarioNegativo ( Expresion* exp ) {
			this->exp = exp;
		}

		~UnarioNegativo( ) {
			delete exp;
		}

		TipoDato analizarTipo() {
			return exp->analizarTipo();
		}
		string generarCodigo() {
			stringstream ss;
			ss << exp->generarCodigo();
			ss << "\tpop eax" << endl;
			ss << "\tneg eax" << endl;
			ss << "\tpush eax" << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<SIGNO value=\"-\">" << endl;

			if ( exp != nullptr ) {
				ss << exp->toString( );
			}
			ss << "</SIGNO>" << endl;
			return ss.str();
		}
};

class UnarioPositivo: public Expresion {
	public:
		Expresion* exp;

		UnarioPositivo ( Expresion* exp ) {
			this->exp = exp;
		}

		~UnarioPositivo( ) {
			delete exp;
		}

		TipoDato analizarTipo() {
			return exp->analizarTipo();
		}
		string generarCodigo() {
			stringstream ss;
			ss << exp->generarCodigo();
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<SIGNO value=\"+\">" << endl;

			if ( exp != nullptr ) {
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
		virtual TipoDato analizarTipo() = 0;
		virtual string toString() = 0;
		virtual string generarCodigo() = 0;
};

class Else: public Proposicion {
	public:
		vector<Nodo*> cuerpo;

		Else( ) {
		}

		~Else() {
			for ( Nodo* nodo : cuerpo ) {
				delete nodo;
			}
		}

		TipoDato analizarTipo() {
			for ( Nodo* n : cuerpo ) {
				if ( n->analizarTipo( ) == T_ERROR ) {
					return T_ERROR;
				}
			}
			return T_VACIO;
		}
		string generarCodigo() {
			stringstream ss;
			for ( Nodo* d : cuerpo ) {
				ss << d->generarCodigo();
			}
			return ss.str();
		}
		string toString() {
			stringstream ss;

			ss << "<OTRO>" << endl;
			for ( Nodo* n : cuerpo ) {
				ss << n->toString();
			}
			ss << "</OTRO>" << endl;
			return ss.str();
		}
};

class If: public Proposicion {
	public:
		Expresion* exp;
		Nodo* proIf;
		Else* proElse;

		If() {
			exp = nullptr;
			proIf = nullptr;
			proElse = nullptr;
		}

		~If() {
			delete exp;
			if ( proIf != nullptr ) {
				delete proIf;
			}
			if ( proElse != nullptr ) {
				delete proElse;
			}
		}

		TipoDato analizarTipo() {
			if ( exp->analizarTipo() == T_ERROR ) {
				return T_ERROR;
			}
			if ( proIf != nullptr ) {
				if ( proIf->analizarTipo() == T_ERROR ) {
					return T_ERROR;
				}
			}
			if ( proElse != nullptr ) {
				if ( proElse->analizarTipo() == T_ERROR ) {
					return T_ERROR;
				}
			}
			return T_VACIO;
		}
		string generarCodigo() {
			stringstream ss, ciclo, fin, otro;
			ciclo << "IF_" << ( ++contador );
			fin << "FIN" << ( contador );
			otro << "ELSE_" << ( contador );

			ss << ciclo.str() << ": " << endl;
			ss << exp->generarCodigo();
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, 1" << endl;
			ss << "\tjne " << otro.str() << endl;
			ss << proIf->generarCodigo();
			ss << "\tjmp " << fin.str() << endl;
			ss << otro.str() << ": " << endl;
			if ( proElse != nullptr ) {
				ss << proElse->generarCodigo();
			}
			ss << fin.str() << ": " << endl;
			return ss.str();
		}
		string toString() {
			stringstream ss;
			ss << "<SI>" << endl;
			ss << exp->toString();
			ss << proIf->toString();

			if ( proElse != nullptr ) {
				ss << proElse->toString( );
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
			for ( Nodo* nodo : cuerpo ) {
				delete nodo;
			}
		}
		string generarCodigo() {
			stringstream ss;
			for ( Nodo* d : cuerpo ) {
				ss << d->generarCodigo();
			}
			return ss.str();
		}
		TipoDato analizarTipo() {
			for ( Nodo* n : cuerpo ) {
				if ( n->analizarTipo( ) == T_ERROR ) {
					return T_ERROR;
				}
			}
			return T_VACIO;
		}

		string toString() {
			stringstream ss;

			ss << "<BLOQUE>" << endl;
			for ( Nodo* n : cuerpo ) {
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

		TipoDato analizarTipo() {
			if ( exp->analizarTipo( ) == T_ERROR ) {
				return T_ERROR;
			}
			return T_VACIO;
		}
		string generarCodigo() {
			stringstream ss;
			ss << exp->generarCodigo();
			ss << "\tpop eax" << endl;
			ss << "\tprint str$(eax)" << endl;
			ss << "\tprint chr$(13,10)" << endl;
			return ss.str();
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
		Else* proElse;

		While() {
			exp = nullptr;
			proposicion = nullptr;
			proElse = nullptr;
		}

		~While() {
			delete exp;
			delete proposicion;
			if ( proElse != nullptr ) {
				delete proElse;
			}
		}
		string generarCodigo() {
			stringstream ss, ciclo, fin, otro;
			ciclo << "WHILE" << ( ++contador );
			fin << "FIN" << ( contador );
			otro << "ELSE" << ( contador );

			ss << ciclo.str() << ": " << endl;
			ss << exp->generarCodigo();
			ss << "\tpop eax" << endl;
			ss << "\tcmp eax, 1" << endl;
			ss << "\tjne " << otro.str() << endl;
			ss << proposicion->generarCodigo();
			ss << "\tjmp " << ciclo.str() << endl;
			ss << otro.str() << ": " << endl;
			if ( proElse != nullptr ) {
				ss << proElse->generarCodigo();
			}
			ss << fin.str() << ": " << endl;
			return ss.str();
		}
		TipoDato analizarTipo() {
			if ( exp->analizarTipo() == T_ERROR ) {
				return T_ERROR;
			}
			if ( proposicion->analizarTipo() == T_ERROR ) {
				return T_ERROR;
			}
			if ( proElse != nullptr ) {
				if ( proElse->analizarTipo() == T_ERROR ) {
					return T_ERROR;
				}
			}
			return T_VACIO;
		}

		string toString() {
			stringstream ss;
			ss << "<MIENTRAS>" << endl;
			ss << exp->toString();
			ss << proposicion->toString( );
			if ( proElse != nullptr ) {
				ss << proElse->toString( );
			}
			ss << "</MIENTRAS>" << endl;
			return ss.str();
		}
};

class UnidadTraduccion: public Nodo {
	public:
		vector<Nodo*> definiciones;

		UnidadTraduccion() {}

		~UnidadTraduccion() {
			for ( Nodo* d : definiciones ) {
				delete d;
			}
		}

		TipoDato analizarTipo() {
			for ( Nodo* def : definiciones ) {
				if ( def->analizarTipo( ) == T_ERROR ) {
					return T_ERROR;
				}
			}
			return T_VACIO;
		}
		string generarCodigo() {
			stringstream ss;
			ss << ".386" << endl;
			ss << ".model flat, stdcall" << endl;
			ss << "option casemap:none" << endl;

			ss << "include \\masm32\\macros\\macros.asm" << endl;
			ss << "include \\masm32\\include\\masm32.inc" << endl;
			ss << "include \\masm32\\include\\kernel32.inc" << endl;

			ss << "includelib \\masm32\\lib\\masm32.lib" << endl;
			ss << "includelib \\masm32\\lib\\kernel32.lib" << endl;
			ss << ".data" << endl;

			//Variables
			for ( string sim : TablaSimbolos::instance()->listaSim() ) {
				ss << "\t" << sim << " dword 0" << endl;
			}

			ss << ".code" << endl;
			ss << "start:" << endl;
			for ( Nodo* d : definiciones ) {
				ss << d->generarCodigo();
				ss << endl;
			}
			ss << "exit" << endl;
			ss << "end start" << endl;

			return ss.str();
		}

		string toString() {
			stringstream ss;
			ss << "<PROGRAMA>" << endl;

			for ( Nodo* d : definiciones ) {
				ss << d->toString();
			}
			ss << "</PROGRAMA>" << endl;

			return ss.str();
		}
};
#endif // CLASES_H_INCLUDED
