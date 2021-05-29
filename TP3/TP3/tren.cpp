#include "tren.h"


Tren::Tren() // constructor
{
	h0 = 177.5;
	h1 = 250.5;
	h2 = 346;
	h3 = 437;
	h4 = 566.5;
	
	primero = ultimo = NULL; // la lista empieza vacia
	posLista = 250.f; // coordenada en eje X (posicion en la formacion)
		
	loadLista(); // cargamos lista con locomotora y los vagones
	
	cout << "cantidad de vagones: "<<obtenerCantidadVagones() << endl; // para debug
	cout << "ultimo vagon: " << get_ultimo() << endl; // para debug
	
	cargar_graficos();
}


void Tren::loadLista()
{
	for (int i = 0; i < 2; i++) // agrego 2 vagones a la lista
	{
		nro = rand() % 9; // numero random que paso por parametro a la funcion insertar
		cout << "vagon N"<<i<<": " <<nro << endl; // para debug
		insertar(nro);
	}
}



void Tren::cargar_graficos()
{
	// dibujamos el tren
	txt_tren = new Texture;
	txt_tren->loadFromFile("resources/images/tren.png");
	spr_tren = new Sprite(*txt_tren);
	spr_tren->setTexture(*txt_tren);
	spr_tren->setOrigin(44, 82); 
	spr_tren->setScale(0.8f, 0.8f);
	spr_tren->setPosition(166,h0); 
}


void Tren::insertar(int v)
{
	// agregamos nuevos nodos a la lista
	vagon *anterior;

	// Si la lista está vacía, o si el nro que tiene el vagon es mayor al del nuevo nodo, agregamos un nuevo nodo a la cabecera
	if ((primero == NULL) || (primero->nroEnVagon > v))
	{
		primero = new vagon(v, primero);
	}
	else // si la lista no esta vacía
	{
		anterior = primero;
		
		// Avanzamos hasta el último elemento o hasta que el siguiente tenga un valor mayor que v
		while (anterior->siguiente && anterior->siguiente->nroEnVagon <= v)
		{
			anterior = anterior->siguiente;
		}

		// Creamos un nuevo nodo después del nodo anterior, y cuyo siguiente es el siguiente del anterior
		anterior->siguiente = new vagon(v, anterior->siguiente);
	}
}






void Tren::borrar(int v) // destruye un vagon
{
	vagon *anteriorNodo, *aux;
	aux = primero;
	anteriorNodo = NULL;

	while (aux && aux->nroEnVagon < v)
	{
		anteriorNodo = aux;
		aux = aux->siguiente;
	}
	if (!aux || aux->nroEnVagon != v)
	{
		return;
	}
	else
	{
		if (!anteriorNodo)
		{
			primero = aux->siguiente;
		}
		else
		{
			anteriorNodo->siguiente = aux->siguiente;
		}
		delete aux;
	}
}


void Tren::dibujar(RenderWindow& ventana)
{
	// simplemente recorro la lista para dibujar sus nodos
	// los vagones de la lista siguen el movimiento de la locomotora

	ultimo = primero;
	int ind = 1; // auxiliar para llevar un indice de la cantidad de vagones

	if (primero)
	{

		while (ultimo->siguiente)
		{
			if (ultimo)
			{
				ind++;
				ultimo = ultimo->siguiente;
				ultimo->set_position({ spr_tren->getPosition().x - 55.f * ind, spr_tren->getPosition().y });
				ultimo->dibujar(ventana);
			}
			
		}
		primero->set_position({ spr_tren->getPosition().x -55.f, spr_tren->getPosition().y });
		primero->dibujar(ventana);
	}
}


float Tren::get_positionX()
{
	return spr_tren->getPosition().x;
}

float Tren::get_positionY()
{
	return spr_tren->getPosition().y;
}



void Tren::mover(int velocidad)
{
	// movimiento del tren. 
	//Cuando llega la borde de la pantalla, continua avanzando por el carril inferior

	float x, y;

	y = spr_tren->getPosition().y;
	x = spr_tren->getPosition().x;

	spr_tren->setPosition(x + velocidad, y);
		
	if ((x > 800 + spr_tren->getGlobalBounds().width) && (y == h0))
	{
		spr_tren->setPosition(-spr_tren->getGlobalBounds().width, h1);
	}

	if ((x > 800 + spr_tren->getGlobalBounds().width) && (y == h1))
	{
		spr_tren->setPosition(-spr_tren->getGlobalBounds().width, h2);
	}

	if ((x > 800 + spr_tren->getGlobalBounds().width) && (y == h2))
	{
		spr_tren->setPosition(-spr_tren->getGlobalBounds().width, h3);
	}

	if ((x > 800 + spr_tren->getGlobalBounds().width) && (y == h3))
	{
		spr_tren->setPosition(-spr_tren->getGlobalBounds().width, h4);
	}
}



Sprite Tren::get_sprite()
{
	return *spr_tren;
}


int Tren::obtenerCantidadVagones()
{
	{
		if (primero == NULL)
		{
			return 0;
		}

		int retorno = 0;
		ultimo = primero;

		while (ultimo != NULL)
		{
			if (ultimo)
			{
				ultimo = ultimo->siguiente;
			}
			retorno++;
		}
		return retorno;
	}
}


int Tren::get_ultimo()
{
	ultimo = primero;

	if (primero != NULL)
	{
		while (ultimo->siguiente)
		{
			if (ultimo)
			{
				ultimo = ultimo->siguiente;
			}
		}
	}
	
	return ultimo->nroEnVagon;
}