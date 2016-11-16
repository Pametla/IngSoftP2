// Ingenieria de Software 
// Pamela Blacutt
// Practica 1
// 14-11-16

// Controles: p mueve personaje hacia la derecha
// Controles: o mueve personaje hacia la izquierda
// Controles: m dispara hacia la derecha
// Controles: m dispara hacia la izquierda

#include "stdafx.h"

#define ANCHOMUNDO 70
#define FPS 20 //Frames por segundo

//---INICIALIZACION DE FUNCIONES---
void reiniciarJuego();

//---INICIALIZACION DE VARIABLES---

//Variables personaje
int posicionPersonaje = ANCHOMUNDO / 2;
char teclaPulsada;
bool personajeVivo = true;

//Variables bala
int posicionBala = 0;
bool disparar = false;
int contadorPosicionBala = 0;
int direccionBala = 1; //+1 a la derecha -1 a la izquierda

					   //Variables generales
int delay = 1000 / 20;

//Variables enemigo
int contadorPosicionEnemigo = 0;
int direccionEnemigo = 1;
bool enemigoVivo = true;
int posicionEnemigo = 0;
int posicionAleatoria = 0;

int main()
{
	
	while (true)
	{

		//Pone el mundo al medio
		printf("\n\n\n\n\n\n\n\n\n\n\n\n                      ");

		if (_kbhit())//Devuelve 0 si no se ha pulsado una tecla
		{
			teclaPulsada = _getch();

			//---MOVIMIENTO---

			//Movimiento derecha
			if (teclaPulsada=='p') {

				if (posicionPersonaje < ANCHOMUNDO) {//Proteccion para que no se salga del mundo

					posicionPersonaje = posicionPersonaje + 1;
				}
			}

			//Movimiento izquierda
			if (teclaPulsada == 'o') {

				if (posicionPersonaje >=0) { //Proteccion para que no se salga del mundo

					posicionPersonaje = posicionPersonaje - 1;
				}
			}


			//---DISPARO---

			//Disparo hacia la derecha
			if (teclaPulsada == 'm' && !disparar) {

				disparar = true;
				direccionBala = 1;
			}

			//Disparo hacia la izquierda
			else if (teclaPulsada == 'n' && !disparar) {

				disparar = true;
				direccionBala = -1;
			}
		}

		//Se realizó un disparo
		if (disparar && personajeVivo) {

			contadorPosicionBala = contadorPosicionBala + 1;
			posicionBala = posicionPersonaje + (contadorPosicionBala * direccionBala);

			if (contadorPosicionBala >= ANCHOMUNDO || contadorPosicionBala <= 0) { //Fin del mundo

				disparar = false;
				contadorPosicionBala = 0;
			}
		}

		//---ENEMIGO---

		//Crear enemigo
		if (enemigoVivo){


			if (posicionAleatoria == 0) {
				posicionEnemigo = 0;
				direccionEnemigo = 1;
			}
			else {
				posicionEnemigo = ANCHOMUNDO;
				direccionEnemigo = -1;
			}
				
			//Movimiento enemigo
			contadorPosicionEnemigo = contadorPosicionEnemigo + 1;
			posicionEnemigo = posicionEnemigo + (contadorPosicionEnemigo * direccionEnemigo);

			if (contadorPosicionEnemigo >= ANCHOMUNDO || contadorPosicionEnemigo <= 0 ) { //Fin del mundo

				enemigoVivo = false;
				contadorPosicionEnemigo = 0;
			}

			//Matar enemigo
			if (posicionBala == posicionEnemigo || posicionBala == (posicionEnemigo + 1 * direccionEnemigo)) {
			
				enemigoVivo = false;
				contadorPosicionEnemigo = 0;

				disparar = false;
				contadorPosicionBala = 0;

			}

			//Muere el personaje
			if (posicionPersonaje == posicionEnemigo || posicionPersonaje == (posicionEnemigo + 1 * direccionEnemigo)) {
				
				personajeVivo = false;

				disparar = false;
				contadorPosicionBala = 0;

				enemigoVivo = false;
				contadorPosicionEnemigo = 0;

				//Reiniciar el juego
				reiniciarJuego();
				

			}
		}
		
		//---IMPRIMIR MUNDO---

		for (int i = 0; i <= ANCHOMUNDO; i++) {

			if(i== posicionPersonaje && personajeVivo)  printf("%c", '*');		//imprime personaje
			else if (i == posicionBala && disparar)  printf("%c", '.');			//imprime bala
			else if (i == posicionEnemigo && enemigoVivo)  printf("%c", 'I');	//imprime enemigo
			else  printf("%c", '-');											//imprime mundo
		}

		//imprimir score
		printf("\n                       Score: %d", 2);
		
		Sleep(delay);
		system("cls");

		//Crear enemigo nuevo
		if (personajeVivo && !enemigoVivo) {
		
			//Posicion inicial enemigo
			posicionAleatoria = rand() % 2;
			enemigoVivo = true;
		} 
	}

    return 0;
}

void reiniciarJuego() {
	system("cls");
	//Pone el mundo al medio
	printf("\n\n\n\n\n\n\n\n\n\n\n\n                      ");
	printf("GAME OVER");
	Sleep(2000);
	personajeVivo = true;
}