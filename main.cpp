#include "clases.hpp"


int main(){
	Juego juego;
	int estrategia;

	while(!juego.validarJugadores()){
		std::cout << "Asignar un jugador a estrategia: ";
		std::cin >> estrategia;

		juego.agregarEstrategia(estrategia);
	}

	juego.iniciarJuego();
	return 0;
}