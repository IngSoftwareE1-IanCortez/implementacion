#include "clases.hpp"


int main(){
	Juego* juego = new Juego();
	int estrategia;

	while(!juego->validarJugadores()){
		std::cout << "Asignar un jugador a estrategia: ";
		std::cin >> estrategia;

		juego->agregarEstrategia(estrategia);
	}

	juego->iniciarJuego();


	delete juego;

	return 0;
}