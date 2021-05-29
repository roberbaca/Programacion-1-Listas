#include "vagon.h"
#include <iostream>


typedef vagon* pnodo;

class Tren
{

private:

	//Punteros de la lista
	vagon *primero;
	vagon *ultimo;

	// sprite y textura del tren
	Sprite *spr_tren;
	Texture *txt_tren;

	float h0, h1, h2, h3, h4; // rieles
	float posLista; // posicion de los vagones en la formacion
	
	int nro; // numero aleatorio para los 2 primeros vagones
		

public:

	Tren();

	Sprite get_sprite();

	float get_positionX(); // devuelve la coordenada en X del tren
	float get_positionY(); // devuelve la coordenada en Y del tren
	
	void loadLista(); // carga la lista inicial

	void mover(int velocidad); // movimiento del tren

	void cargar_graficos();

	void dibujar(RenderWindow& ventana);

	//Devuelve el valor del último nodo
	int get_ultimo();

	//Inserta en la lista
	void insertar(int v);

	//Borra de la lista
	void borrar(int v);

	//Devuelve la cantidad de nodos de la lista
	int obtenerCantidadVagones();

	~Tren();
};