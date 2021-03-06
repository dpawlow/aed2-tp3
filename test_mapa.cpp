#include <iostream>
#include <fstream>
#include "mini_test.h"
#include "Mapa.h"

using namespace std;
using namespace aed2;

void HayCamino(Mapa& m, int lat1, int long1, int lat2, int long2, bool expected) {
    Coordenada uno(lat1, long1);
    Coordenada dos(lat2, long2);
    ASSERT(m.HayCamino(uno, dos) == expected);
}


void test_crearmapa() {
    Mapa m;
    ASSERT(m.Ancho() == 0);
    ASSERT(m.Alto() == 0);
}

void test_mapa_4x4() {
    Mapa m;
    Coordenada c(3,3);
    m.AgregarCoordenada(c);
    Coordenada c1(2, 3);
    m.AgregarCoordenada(c1);
    Coordenada c2(3, 2);
    m.AgregarCoordenada(c2);

    Coordenada c3(1, 1);
    m.AgregarCoordenada(c3);

    ASSERT(m.Ancho() == 4);
    ASSERT(m.Alto() == 4);
}

void test_mapa_4x4_creciendo() {
    Mapa m;
    Coordenada c(1,1);
    m.AgregarCoordenada(c);

    ASSERT(m.Ancho() == 2);
    ASSERT(m.Alto() == 2);
    ASSERT(m.Coordenadas().Cardinal() == 1);
    HayCamino(m, 1, 1, 1, 1, true);

    Coordenada c1(3, 2);
    m.AgregarCoordenada(c1);
    ASSERT(m.Coordenadas().Cardinal() == 2);
    HayCamino(m, 3, 2, 1, 1, false);

    Coordenada c2(2, 3);
    m.AgregarCoordenada(c2);
    ASSERT(m.Coordenadas().Cardinal() == 3);
    HayCamino(m, 3, 2, 2, 3, false);

    Coordenada c3(3, 3);
    m.AgregarCoordenada(c3);
    HayCamino(m, 3, 2, 2, 3, true);
    HayCamino(m, 3, 2, 3, 2, true);
    HayCamino(m, 3, 2, 3, 3, true);
    HayCamino(m, 2, 3, 3, 2, true);
    HayCamino(m, 2, 3, 2, 3, true);
    HayCamino(m, 2, 3, 3, 3, true);
    HayCamino(m, 3, 3, 2, 3, true);
    HayCamino(m, 3, 3, 3, 2, true);
    HayCamino(m, 3, 3, 3, 3, true);

    HayCamino(m, 2, 3, 1, 1, false);
    HayCamino(m, 3, 2, 1, 1, false);
    HayCamino(m, 3, 3, 1, 1, false);

    HayCamino(m, 1, 1, 2, 3, false);
    HayCamino(m, 1, 1, 3, 2, false);
    HayCamino(m, 1, 1, 3, 3, false);

    ASSERT(m.Ancho() == 4);
    ASSERT(m.Alto() == 4);
    ASSERT(m.Coordenadas().Cardinal() == 4);

    ASSERT(m.Coordenadas().Pertenece(Coordenada(1,1)));
    ASSERT(m.Coordenadas().Pertenece(Coordenada(2,3)));
    ASSERT(m.Coordenadas().Pertenece(Coordenada(3,2)));
    ASSERT(m.Coordenadas().Pertenece(Coordenada(3,3)));
}

void test_CrearCopia(){
    Mapa m;
    Coordenada c(1,1);
    Coordenada c1(0,1);
    Coordenada c2(1,0);
    Coordenada c3(0,0);

    m.AgregarCoordenada(c);
    m.AgregarCoordenada(c1);
    m.AgregarCoordenada(c2);
    m.AgregarCoordenada(c3);

    ASSERT(m.Coordenadas().Cardinal()== 4);
    ASSERT(m.Coordenadas().Pertenece(c));
    ASSERT(m.Coordenadas().Pertenece(c1));
    ASSERT(m.Coordenadas().Pertenece(c2));
    ASSERT(m.Coordenadas().Pertenece(c3));
    ASSERT(m.HayCamino(c, c1));
    ASSERT(m.HayCamino(c, c2));
    ASSERT(m.HayCamino(c, c3));
    ASSERT(m.HayCamino(c1, c2));
    ASSERT(m.HayCamino(c1, c3));
    ASSERT(m.HayCamino(c2, c3));
    ASSERT(m.PosExistente(c));
    ASSERT(m.PosExistente(c1));
    ASSERT(m.PosExistente(c2));
    ASSERT(m.PosExistente(c3));


}

void test_free(){
    Mapa m;
    Mapa m2;
    Mapa m3;
    Coordenada c(1,1);
    m.AgregarCoordenada(c);
    m2.AgregarCoordenada(c);
    m3.AgregarCoordenada(c);
}

void test_copias_locas(){
    Mapa m;
    Mapa m2(m);
    Mapa m3(m2);
    Coordenada c(1,5);
    m3.AgregarCoordenada(c);
}

void test_tonto() {
  Mapa m;
  Coordenada c1 = Coordenada(0,0);
  Coordenada c2 = Coordenada(0,1);
  Coordenada c3 = Coordenada(0,10);
  m.AgregarCoordenada(c1);
  m.AgregarCoordenada(c2);
  m.AgregarCoordenada(c3);
}

void test_enorme() {
  Mapa m;
  for (int i=0; i < 20; i++) {
    if (i%4 != 0) {
      for (int j=0; j < 20; j++) {
        if (j%4 != 0) {
          m.AgregarCoordenada(Coordenada(i, j));
        }
      }
    }
  }
  ASSERT(m.Ancho() == 20);
  ASSERT(m.Alto() == 20);
}

int test_mapa() {
	RUN_TEST(test_crearmapa);
	RUN_TEST(test_mapa_4x4);
	RUN_TEST(test_mapa_4x4_creciendo);
    RUN_TEST(test_CrearCopia);
    RUN_TEST(test_free);
    RUN_TEST(test_copias_locas);
    RUN_TEST(test_enorme);
    return 0;
}

int main() {
	return test_mapa();
}
