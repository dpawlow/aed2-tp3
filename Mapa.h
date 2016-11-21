#ifndef MAPA_H
#define MAPA_H

#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Conj.h"
#include <iostream>
#include "TiposJuego.h"

using namespace std;
using namespace aed2;

class Mapa {
public:
	Mapa(); //CrearMapa()
	~Mapa();
	Conj<Coordenada> Coordenadas();
	void AgregarCoordenada (const Coordenada&);
	bool HayCamino(const Coordenada&, const Coordenada&);
	bool PosExistente(const Coordenada&);
	Nat Ancho() const { return _ancho; };
	Nat Alto() const { return _alto; };
	void Mostrar();
private:
	Conj<Coordenada> CoordenadasConectadasA(Coordenada&) const;
	Conj<Coordenada> _coordenadas;
	Nat _ancho;
	Nat _alto;
	bool** _relacionCoordenadas;
};

#endif
