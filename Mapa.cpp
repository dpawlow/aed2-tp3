#include "Mapa.h"

Mapa::Mapa(){
	coordenadas = Conj<Coordenada>();
	ancho = 0;
	alto = 0;
	relacionCoordenadas = new bool*[0];
}

bool Mapa::HayCamino(const Coordenada& c1, const Coordenada& c2) {
	return true;
}

Conj<Coordenada> Mapa::Coordenadas(){
	return coordenadas;
}

bool Mapa::PosExistente(const Coordenada& c) {
	return true;
}

void Mapa::AgregarCoordenada(const Coordenada& c1){
	/*if (Longitud(c) > ancho) { //Actualizo el ancho y alto del mapa
		ancho = c1.;
	}
	if (Latitud(c) > alto) {
		alto = Latitud(c);
	}*/

/*
	coordenadas.Agregar(c1); //Agrego la coordenada nueva a las coordenas del mapa

	relacionCoordenadas = new bool*[ancho*alto]; //Defino el espacio para las relaciones de las coordenadas

	Iterador iter = CrearIt(coordenadas)
	while HaySiguiente(iter) do
	coor ← Siguiente(iter)
	Avanzar(iter)
	conectadas ← iCoordenadasConectadas(coor, m)
	iterConectadas ← CrearIt(conectadas)
	while HaySiguiente(iterConectadas) do
	coor 2 ← Siguiente(iterConectadas)
	Avanzar(iterConectadas)
	pos1 ← m.ancho * Longitud(coor) + m.alto * Altitud(coor)
	pos2 ← m.ancho * Longitud(coor 2 ) + m.alto * Altitud(coor 2 )
	m.relacionCoordenadas[pos1][pos2] ← True
	m.relacionCoordenadas[pos2][pos1] ← True
	end while
	end while
*/
}