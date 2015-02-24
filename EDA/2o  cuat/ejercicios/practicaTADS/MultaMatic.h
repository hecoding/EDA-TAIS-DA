// Héctor Laria - 2º A IS
#ifndef MULTAMATIC_H
#define MULTAMATIC_H

#include "TablaHash.h"
#include "Hash.h"
#include "Lista.h"
#include <string>
#include "Excepciones.h"
#include "Tramo.h"
#include "Matricula.h"

// Excepciones

class ECamaraRepetida : public ExcepcionTAD {
	public :
	ECamaraRepetida () {};
	ECamaraRepetida(const std :: string &msg) : ExcepcionTAD(msg) {}
};

class ETramoRepetido : public ExcepcionTAD {
	public :
	ETramoRepetido () {};
	ETramoRepetido(const std :: string &msg) : ExcepcionTAD(msg) {}
};

class ECamaraInexistente : public ExcepcionTAD {
	public :
	ECamaraInexistente () {};
	ECamaraInexistente(const std :: string &msg) : ExcepcionTAD(msg) {}
};

class ETramoInexistente : public ExcepcionTAD {
	public :
	ETramoInexistente () {};
	ETramoInexistente(const std :: string &msg) : ExcepcionTAD(msg) {}
};


// Implementación

class MultaMatic {
private:
	Tabla<string, Tramo> _tablaTramos;
	Tabla<string, string> _tablaCamaras;
	Tabla<string, Matricula> _tablaMatriculas;
	
public:
	MultaMatic() : _tablaTramos(Tabla<string, Tramo>()), _tablaCamaras(Tabla<string, string>()), _tablaMatriculas(Tabla<string, Matricula>()) {}

	void insertaTramo (string tramo, string camara_inicial, string camara_final, unsigned int t_minimo) {
		// no se puede repetir tramo
		if (_tablaTramos.esta(tramo)) throw ETramoRepetido();
		// inserta la cámara inicial
		if (_tablaCamaras.esta(camara_inicial)) throw ECamaraRepetida();
		else _tablaCamaras.inserta(camara_inicial, tramo);
		// inserta la cámara final
		if (_tablaCamaras.esta(camara_final)) throw ECamaraRepetida();
		else _tablaCamaras.inserta(camara_final, tramo);

		Tramo tr;
		tr.camaraInicial = camara_inicial;
		tr.camaraFinal = camara_final;
		tr.tiempo_min = t_minimo;
		tr.multados = Lista<string>();

		_tablaTramos.inserta(tramo, tr);
	}

	void fotoEntrada (string camara, string matricula, unsigned int tiempo_actual) {
		if (!_tablaCamaras.esta(camara)) throw ECamaraInexistente();
		// si es un coche nuevo, lo guarda
		if (!_tablaMatriculas.esta(matricula)) _tablaMatriculas.inserta(matricula, Matricula());

		Matricula mat;
		mat.multas = _tablaMatriculas.consulta(matricula).multas;
		mat.t_ini = tiempo_actual;
		mat.t_fin = 0;
		_tablaMatriculas.inserta(matricula, mat);
	}

	void fotoSalida (string camara, string matricula, unsigned int tiempo_actual) {
		if (!_tablaCamaras.esta(camara)) throw ECamaraInexistente();

		Tramo tramo = _tablaTramos.consulta(_tablaCamaras.consulta(camara));
		Matricula infractor = _tablaMatriculas.consulta(matricula);
		unsigned int tiempo_transcurrido = tiempo_actual - infractor.t_ini;
		unsigned int tiempo_min_tramo = tramo.tiempo_min;

		if (tiempo_transcurrido < tiempo_min_tramo) {
			// se crea el nuevo valor a insertar para actualizar las multas de una matrícula
			Matricula matricula_actualizada;
			matricula_actualizada.multas = tramo.multados;
			matricula_actualizada.t_ini = 0;
			matricula_actualizada.t_fin = 0;
			matricula_actualizada.multas.ponDr(tiempo_transcurrido + " seg de un mínimo de " + tiempo_min_tramo);

			_tablaMatriculas.inserta(matricula, matricula_actualizada);

			// se crea el nuevo valor a insertar para actualizar los multados en un tramo
			Tramo tramo_actualizado;
			tramo_actualizado.camaraInicial = tramo.camaraInicial;
			tramo_actualizado.camaraFinal = tramo.camaraFinal;
			tramo_actualizado.tiempo_min = tramo.tiempo_min;
			tramo_actualizado.multados = tramo.multados;
			tramo_actualizado.multados.ponDr(matricula);

			_tablaTramos.inserta(_tablaCamaras.consulta(camara), tramo_actualizado);
		}
	}

	const Lista<string> multasPorMatricula (string matricula) {
		return _tablaMatriculas.consulta(matricula).multas;
	}

	const Lista<string> multasPorTramos (string id_tramo) {
		if (!_tablaTramos.esta(id_tramo)) throw ETramoInexistente();
		
		return _tablaTramos.consulta(id_tramo).multados;
	}

};

#endif