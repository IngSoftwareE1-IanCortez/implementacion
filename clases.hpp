#ifndef CLASES_HPP
#define CLASES_HPP


#include <random>
#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <cstdlib>


class Estrategia {
public:
	Estrategia() = default;
	virtual void agregarNumero(int num) = 0;
	virtual bool validarEstrategia() = 0;
};


// Estrategia 1
class CincoPares: public Estrategia {
private:
	std::array<int, 5> arreglo;
	int posArreglo = 0;

public:
	CincoPares() = default;

	void agregarNumero(int num) override{
		arreglo[posArreglo] = num;
		++posArreglo;
		if(posArreglo > 4) posArreglo = 0;
	}

	virtual bool validarEstrategia() override{
		if(posArreglo < 4) return false;
		
		for(int i=0; i<5; ++i){
			if(arreglo[i] % 2 != 0) return false;
		}

		return true;
	}
};


// Estrategia 2
class CincoImpares: public Estrategia {
private:
	std::array<int, 5> arreglo;
	int posArreglo = 0;

public:
	CincoImpares() = default;

	void agregarNumero(int num) override{
		arreglo[posArreglo] = num;
		++posArreglo;
		if(posArreglo > 4) posArreglo = 0;
	}

	virtual bool validarEstrategia() override{
		if(posArreglo < 4) return false;
		
		for(int i=0; i<5; ++i){
			if(arreglo[i] % 2 == 0) return false;
		}

		return true;
	}
};


// Estrategia 3
class NumeroPrimo: public Estrategia {
private:
	int numero{};

public:
	NumeroPrimo() = default;

	void agregarNumero(int num) override{
		numero = num;
	}

	virtual bool validarEstrategia() override {
		if(numero == 1) return false;

		for(int i=2; i<numero; ++i){
			if(numero % i == 0) return false;
		}
		
		return true;
	}
};


// Estrategia 4
class Multiplos10: public Estrategia {
private:
	std::array<int, 3> arreglo;
	int posArreglo = 0;

public:
	Multiplos10() = default;

	void agregarNumero(int num) override {
		arreglo[posArreglo] = num;
		++posArreglo;
		if(posArreglo > 2) posArreglo = 0;
	}

	virtual bool validarEstrategia() override {
		if(posArreglo < 2) return false;
		
		for(int i=0; i<3; ++i){
			if(arreglo[i] % 10 != 0) return false;
		}

		return true;
	}
};


// Estrategia 5
class Multiplos25: public Estrategia {
private:
	std::array<int, 2> arreglo;
	int posArreglo = 0;

public:
	Multiplos25() = default;

	void agregarNumero(int num) override {
		arreglo[posArreglo] = num;

		if(posArreglo == 1) --posArreglo;
		else ++posArreglo;
	}

	virtual bool validarEstrategia() override {
		if(posArreglo == 0) return false;
		
		if(arreglo[0] % 25 != 0) return false;
		if(arreglo[1] % 25 != 0) return false;

		return true;
	}
};


class GeneradorNumerosAleatorios {
private:
	std::vector<int> arreglo;
	int posActual = 0;

public:
	GeneradorNumerosAleatorios() = default;
	GeneradorNumerosAleatorios(int inicio, int fin){
		for(int i=inicio; i<=fin; ++i){
			arreglo.push_back(i);
		}
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(arreglo.begin(), arreglo.end(), std::default_random_engine(seed));
	};

	int devolverNumero(){
		return arreglo[posActual++];
	}
};


class Juego {
private:
	Estrategia* est1 = nullptr;
	Estrategia* est2 = nullptr;
	Estrategia* est3 = nullptr;
	Estrategia* est4 = nullptr;
	Estrategia* est5 = nullptr;
	GeneradorNumerosAleatorios* gen = new GeneradorNumerosAleatorios(1, 100);

public:
	Juego() = default;

	virtual ~Juego() {
		delete est1;
		delete est2;
		delete est3;
		delete est4;
		delete est5;
		delete gen;
	}

	
	void agregarEstrategia(int i){
		switch (i){
		case 1:
			if(est1 != nullptr){
				std::cout << "Estrategia ya tomada" << std::endl;
				break;
			}
			est1 = new CincoPares();
			std::cout << "Asignado a estrategia 1" << std::endl;
			break;

		case 2:
			if(est2 != nullptr){
				std::cout << "Estrategia ya tomada" << std::endl;
				break;
			}
			est2 = new CincoImpares();
			std::cout << "Asignado a estrategia 2" << std::endl;
			break;

		case 3:
			if(est3 != nullptr){
				std::cout << "Estrategia ya tomada" << std::endl;
				break;
			}
			est3 = new NumeroPrimo();
			std::cout << "Asignado a estrategia 3" << std::endl;
			break;

		case 4:
			if(est4 != nullptr){
				std::cout << "Estrategia ya tomada" << std::endl;
				break;
			}
			est4 = new Multiplos10();
			std::cout << "Asignado a estrategia 4" << std::endl;
			break;

		case 5:
			if(est5 != nullptr){
				std::cout << "Estrategia ya tomada" << std::endl;
				break;
			}
			est5 = new Multiplos25();
			std::cout << "Asignado a estrategia 5" << std::endl;
			break;
		
		default:
			std::cout << "Estrategia no valida" << std::endl;
			break;
		}
	}


	void iniciarJuego(){
		while(true){
			int numero = gen->devolverNumero();

			std::cout << "Numero generado: " << numero << std::endl;

			est1->agregarNumero(numero);
			est2->agregarNumero(numero);
			est3->agregarNumero(numero);
			est4->agregarNumero(numero);
			est5->agregarNumero(numero);

			if(est1->validarEstrategia()){
				std::cout << "Ganador jugador con la estrategia \"Cinco numeros pares\"" << std::endl;
				break;
			}

			if(est2->validarEstrategia()){
				std::cout << "Ganador jugador con la estrategia \"Cinco numeros impares\"" << std::endl;
				break;
			}
			
			if(est3->validarEstrategia()){
				std::cout << "Ganador jugador con la estrategia \"Un numero primo\"" << std::endl;
				break;
			}

			if(est4->validarEstrategia()){
				std::cout << "Ganador jugador con la estrategia \"Tres numeros multiplos de 10\"" << std::endl;
				break;
			}

			if(est5->validarEstrategia()){
				std::cout << "Ganador jugador con la estrategia \"Dos numeros multiplos de 25\"" << std::endl;
				break;
			}
		}
	}


	bool validarJugadores(){
		return (est1 != nullptr) && (est2 != nullptr) && (est3 != nullptr) && (est4 != nullptr) && (est5 != nullptr);
	}
};


#endif