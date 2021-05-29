#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class vagon 
{

private:

	//Numero para imprimir en vagon
	int nroEnVagon;

	//Vagon siguiente
	vagon *siguiente;

	//Sprite del vagon
	Sprite* spr_vagon;
	Texture* txt_vagon;

	Vector2f coordenadas;

	// texto y fuentes
	Font fuenteVagon;
	Text textoVagon;


public:

	vagon(int nro, vagon *sig = NULL);

	Sprite get_sprite(); // devuelve el sprite

	void dibujar(RenderWindow& ventana);

	void cargar_graficos();

	void set_position(Vector2f coord);

	float get_positionX();

	//~vagon();

	friend class Tren;
};

