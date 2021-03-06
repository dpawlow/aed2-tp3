#ifndef MAPA_CPP
#define MAPA_CPP

#include "Mapa.h"
#include "Cola.cpp"

Mapa::Mapa(): _ancho(0), _alto(0), _relacionCoordenadas(NULL){
	_coordenadas = Conj<Coordenada>();
}

Mapa::Mapa(const Conj<Coordenada>& coordenadas): _ancho(0), _alto(0), _relacionCoordenadas(NULL), _coordenadas(coordenadas) {
	Conj<Coordenada>::const_Iterador it = coordenadas.CrearIt();
	while (it.HaySiguiente()) {
		Coordenada c = it.Siguiente();
		if ((c.longitud+1) > _ancho) { //Actualizo el ancho y alto del mapa
			_ancho = c.longitud+1; // este uno es porque hay que tener en cuenta la posicion 0
		}
		if ((c.latitud+1) > _alto) {
			_alto = c.latitud+1; // este uno es porque hay que tener en cuenta la posicion 0
		}
		it.Avanzar();
	}
	it = coordenadas.CrearIt();
	if (it.HaySiguiente()) {
		AgregarCoordenada(it.Siguiente());
	}
}

Mapa::Mapa(const Mapa& otro): _ancho(otro._ancho), _alto(otro._alto), _relacionCoordenadas(NULL) {
	Conj<Coordenada>::const_Iterador it = otro._coordenadas.CrearIt();

	while (it.HaySiguiente()) {
		_coordenadas.Agregar(it.Siguiente());
		it.Avanzar();
	}

	int tamanioArreglo = _ancho*_alto;
	_relacionCoordenadas = new bool*[tamanioArreglo];
	for (int i = 0; i < tamanioArreglo; i++) {
		_relacionCoordenadas[i] = new bool[tamanioArreglo];
		for (int j = 0; j < tamanioArreglo; j++) {
			_relacionCoordenadas[i][j] = otro._relacionCoordenadas[i][j];
		}
	}
}

Mapa& Mapa::operator=(const Mapa& otro) {
    if(this != &otro) {
			_ancho = otro._ancho;
			_alto = otro._ancho;
			_coordenadas = Conj<Coordenada>(otro._coordenadas);

			int tamanioArreglo = _ancho*_alto;

			_relacionCoordenadas = new bool*[tamanioArreglo];
			for (int i = 0; i < tamanioArreglo; i++) {
				_relacionCoordenadas[i] = new bool[tamanioArreglo];
				for (int j = 0; j < tamanioArreglo; j++) {
					_relacionCoordenadas[i][j] = otro._relacionCoordenadas[i][j];
				}
			}
    }
    return *this;
}

Mapa::~Mapa() {
	for (Nat i = 0; i < _ancho*_alto; i++) {
		if (_relacionCoordenadas[i] != NULL) {
			delete [] _relacionCoordenadas[i];
			_relacionCoordenadas[i] = NULL;
		}
	}
	delete [] _relacionCoordenadas;
	_relacionCoordenadas = NULL;
}

bool Mapa::HayCamino(const Coordenada& c1, const Coordenada& c2) {
	int pos1 = calcularPosicion(c1);
	int pos2 = calcularPosicion(c2);
	return _relacionCoordenadas[pos1][pos2];
}


Conj<Coordenada>& Mapa::Coordenadas(){
	return _coordenadas;
}

bool Mapa::PosExistente(const Coordenada& c) {
	if (c.latitud < _alto && c.longitud < _ancho) {
		int pos = calcularPosicion(c);
		return _relacionCoordenadas[pos][pos];
	}
	return false;
}

Conj<Coordenada> Mapa::CoordenadasConectadasA(Coordenada& c1) const {
	Conj<Coordenada> visitadas;
	Cola<Coordenada> aVisitar;
	aVisitar.Encolar(c1);
	Conj<Coordenada> coordenadas;
	coordenadas.Agregar(c1);

	while (aVisitar.EsVacia() == false) {
		Coordenada coor = aVisitar.Proximo();
		aVisitar.Desencolar();

		visitadas.Agregar(coor);

		if (coor.latitud > 0) {
			Coordenada coorAbajo = coordenadaAbajo(coor);
			if (!visitadas.Pertenece(coorAbajo) && _coordenadas.Pertenece(coorAbajo)) {
				coordenadas.Agregar(coorAbajo);
				aVisitar.Encolar(coorAbajo);
			}
		}

		if (coor.longitud > 0) {
			Coordenada coorIzq = coordenadaIzquierda(coor);
			if (!visitadas.Pertenece(coorIzq) && _coordenadas.Pertenece(coorIzq)) {
				coordenadas.Agregar(coorIzq);
				aVisitar.Encolar(coorIzq);
			}
		}

		Coordenada coorDer = coordenadaDerecha(coor);
		if (!visitadas.Pertenece(coorDer) && _coordenadas.Pertenece(coorDer)) {
			coordenadas.Agregar(coorDer);
			aVisitar.Encolar(coorDer);
		}

		Coordenada coorArriba = coordenadaDerecha(coor);
		if (!visitadas.Pertenece(coorArriba) && _coordenadas.Pertenece(coorArriba)) {
			coordenadas.Agregar(coorArriba);
			aVisitar.Encolar(coorArriba);
		}
	}
	return coordenadas;
}


void Mapa::AgregarCoordenada(const Coordenada& c){
	if (_relacionCoordenadas != NULL) {
		for (Nat i = 0; i < _ancho*_alto; i++) {
			delete [] _relacionCoordenadas[i];
			_relacionCoordenadas[i] = NULL;
		}
		delete [] _relacionCoordenadas;
		_relacionCoordenadas = NULL;
	}

	if ((c.longitud+1) > _ancho) { //Actualizo el ancho y alto del mapa
		_ancho = c.longitud+1; // este uno es porque hay que tener en cuenta la posicion 0
	}
	if ((c.latitud+1) > _alto) {
		_alto = c.latitud+1; // este uno es porque hay que tener en cuenta la posicion 0
	}

	Nat tamanioArreglo = _ancho*_alto;
	_relacionCoordenadas = new bool*[tamanioArreglo];
	for (Nat i = 0; i < tamanioArreglo; i++) {
		_relacionCoordenadas[i] = new bool[tamanioArreglo];
		for (Nat j = 0; j < tamanioArreglo; j++) {
			_relacionCoordenadas[i][j] = false;
		}
	}

	_coordenadas.Agregar(c);

	Conj<Coordenada>::Iterador iter = _coordenadas.CrearIt();
	while (iter.HaySiguiente()) {
		Coordenada coor = iter.Siguiente();
		iter.Avanzar();

		Conj<Coordenada> conectadas = CoordenadasConectadasA(coor);
		Conj<Coordenada>::Iterador iterConectadas = conectadas.CrearIt();
		while (iterConectadas.HaySiguiente()) {
			Coordenada coor2 = iterConectadas.Siguiente();
			iterConectadas.Avanzar();
			int pos1 = calcularPosicion(coor);
			int pos2 = calcularPosicion(coor2);
			_relacionCoordenadas[pos1][pos2] = true;
			_relacionCoordenadas[pos2][pos1] = true;
		}
	}
}

Nat Mapa::calcularPosicion(const Coordenada& c) {
	return _ancho * c.latitud + c.longitud;
}

#endif
