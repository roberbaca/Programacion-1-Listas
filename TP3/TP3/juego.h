#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "tren.h"


using namespace std;
using namespace sf;

class juego
{

public:

	juego(Vector2i resolucion, string titulo); // constructor

	void cargar_imagenes();
	void procesar_eventos();
	void game_loop();
	void dibujar();
	void chequear_colisiones();
	void fin_juego();
	void actualizarContador();
	void mover_tren();
	void mostrar_calculo();
	void generar_random();

private:

	RenderWindow* ventana1;
	View* camara1;
	Event* evento1;

	bool gameOver; // bandera para fin del juego

	// variables para controlar el tiempo y los fps
	float fps, tiempoFrame, tiempo2;
	Time* tiempo1;
	Clock* reloj1;
	Clock relojContador;

	// variables para controlar el cronometro en reversa
	float tiempoInicio;
	float tiempoFin;
	int seconds;
	bool alarm;
	
	// texto y fuentes
	Font fuente;

	Text textoContador;
	Text textoCalculo;
	Text textoRespuesta;

	// sonidos
	Sound snd_whistle;
	Sound snd_explosion;
	Sound snd_gameOver;
	Sound snd_victory;

	SoundBuffer buffer_whistle;
	SoundBuffer buffer_explosion;
	SoundBuffer buffer_gameOver;
	SoundBuffer buffer_victory;
	
	// musica del juego
	Music musica;

	// sprite y textura del background
	Sprite* spr_fondo;
	Texture* txt_fondo;

	// sprite y textura de cuadro de texto
	Sprite* spr_textBox;
	Texture* txt_textBox;

	// sprite y textura de los vagones a colisionar (son solo sprites)
	Sprite* spr_vagonDummy1;
	Sprite* spr_vagonDummy2;
	Sprite* spr_vagonDummy3;
	Sprite* spr_vagonDummy4;
	Texture* txt_vagonDummy;

	// creo una instancia del tren
	Tren* train1;

	float x1, x2, x3, x4; // numeros random para indicar coordenada en X de los vagones a colisionar
	float h0, h1, h2, h3, h4; // rieles (coordenada en Y)

	bool es_colision; // bandera para chequear si hubo colision entre tren y vagones
	bool colision1, colision2, colision3, colision4; // bandera para saber cual vagon colisionó


	int n1, n2, n3; // numeros random para el calculo a realizar
	string playerInput; // para registrar respuesta por teclado
	int respuesta; // valor entero de playerInput
	int solucion; // resultado de la operacion de sumar 3 numeros random
	
	bool input; // bandera para chequear si se ingreso una respuesta
	bool insert; // bandera para que se ejecute 1 vez la funcion insertar vagon
	bool destroy; // bandera para que se ejecute 1 vez la funcion borrar vagon
	bool victory; // bandera para chequear si se llego a la meta
};

