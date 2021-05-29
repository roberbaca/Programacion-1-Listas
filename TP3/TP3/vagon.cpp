#include "vagon.h"

vagon::vagon(int nro, vagon* sig)
{
	nroEnVagon = nro;
	siguiente = sig;
	cargar_graficos();
}


void vagon::dibujar(RenderWindow& ventana)
{
	ventana.draw(*spr_vagon);
	ventana.draw(textoVagon);
}

void vagon::cargar_graficos()
{
	txt_vagon = new Texture;
	txt_vagon->loadFromFile("resources/images/vagon.png");
	spr_vagon = new Sprite(*txt_vagon);
	spr_vagon->setTexture(*txt_vagon);
	spr_vagon->setOrigin(31.5, 61); 
	spr_vagon->setScale(0.8f, 0.8f);
	spr_vagon->setPosition(coordenadas);

	// fuente para los textos en pantalla
	if (!fuenteVagon.loadFromFile("resources/fonts/Square.ttf"))
	{
		//error
	}

	textoVagon.setFont(fuenteVagon);
	textoVagon.setPosition(spr_vagon->getPosition().x -10 , spr_vagon->getPosition().y-40);
	textoVagon.setCharacterSize(22);
	textoVagon.setFillColor(Color::Yellow);
	textoVagon.setString(to_string(nroEnVagon));
}


Sprite vagon::get_sprite()
{
	return *spr_vagon;
}


float vagon::get_positionX()
{
	return spr_vagon->getPosition().x;
}


void vagon::set_position(Vector2f coord)
{
	spr_vagon->setPosition(coord);
	textoVagon.setPosition(spr_vagon->getPosition().x -10 , spr_vagon->getPosition().y - 40);
}


