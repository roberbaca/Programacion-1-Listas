#include "juego.h"


juego::juego(Vector2i resolucion, string titulo)
{
	fps = 60.f; // para que corra a 60 frames por segundo
	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	// coordenadas en el eje Y de cada riel
	h0 = 177.5;
	h1 = 250.5;
	h2 = 346;
	h3 = 437;
	h4 = 566.5;
	
	// ubicacion random en el eje X de los 4 vagones a colisionar del juego
	x1 = rand() % 600 + 100;
	x2 = rand() % 600 + 100;
	x3 = rand() % 600 + 100;
	x4 = rand() % 400 + 100;

	// banderas:
	es_colision = false;
	input = false;
	insert = false;
	destroy = false;
	victory = true;
	gameOver = false;

	colision1, colision2, colision3, colision4 = false;

	cargar_imagenes();

	evento1 = new Event;

	// incializamos los relojes:
	reloj1 = new Clock;
	tiempo1 = new Time;
	alarm = false;

	// cronometro
	tiempoInicio = 5.f;
	tiempoFin = 0.f;
	seconds = 5;

	// numeros random para la operacion a resolver
	n1 = rand() % 9;
	n2 = rand() % 9;
	n3 = rand() % 9;
	respuesta = -1;
	solucion = -1;
	playerInput = "";
	
	// incializamos el tren
	train1 = new Tren();
	
	// para reproducir la musica del juego (con loop)
	if (!musica.openFromFile("resources/music/western.wav"))
	{
		// error		
	}
	musica.setLoop(true);
	musica.setVolume(50);
	musica.play();


	// SONIDOS

	if (!buffer_whistle.loadFromFile("resources/sounds/silbato.wav"))
	{
		// Error...
	}
	snd_whistle.setBuffer(buffer_whistle);

	if (!buffer_victory.loadFromFile("resources/sounds/victory.ogg"))
	{
		// Error...
	}
	snd_victory.setBuffer(buffer_victory);

	if (!buffer_gameOver.loadFromFile("resources/sounds/gameover.wav"))
	{
		// Error...
	}
	snd_gameOver.setBuffer(buffer_gameOver);

	if (!buffer_explosion.loadFromFile("resources/sounds/explosion.ogg"))
	{
		// Error...
	}
	snd_explosion.setBuffer(buffer_explosion);


	// loop principal del juego
	game_loop();

}


void juego::cargar_imagenes()
{
	ventana1->setMouseCursorVisible(false); // oculatmos el cursor del mouse

	// cargamos las texturas del background
	txt_fondo = new Texture;
	txt_fondo->loadFromFile("resources/images/fondo.png");
	spr_fondo = new Sprite(*txt_fondo);
	spr_fondo->setScale(0.5, 0.5);

	// cargamos texturas del text box donde se muestra el calculo a resolver
	txt_textBox = new Texture;
	txt_textBox->loadFromFile("resources/images/text_box.png");
	spr_textBox = new Sprite(*txt_textBox);
	spr_textBox->setScale(0.4, 0.4);
	spr_textBox->setOrigin(321, 143.5); 
	spr_textBox->setPosition(470, 65);

	// cargamos texturas del los vagones a colisionar
	txt_vagonDummy = new Texture;
	txt_vagonDummy->loadFromFile("resources/images/vagon.png");
	
	// sprites de los vagones Dummy
	spr_vagonDummy1 = new Sprite(*txt_vagonDummy);
	spr_vagonDummy1->setScale(0.8, 0.8);
	spr_vagonDummy1->setOrigin(31.5, 61);
	spr_vagonDummy1->setPosition(x1, h1);

	spr_vagonDummy2 = new Sprite(*txt_vagonDummy);
	spr_vagonDummy2->setScale(0.8, 0.8);
	spr_vagonDummy2->setOrigin(31.5, 61); 
	spr_vagonDummy2->setPosition(x2, h2);

	spr_vagonDummy3 = new Sprite(*txt_vagonDummy);
	spr_vagonDummy3->setScale(0.8, 0.8);
	spr_vagonDummy3->setOrigin(31.5, 61); 
	spr_vagonDummy3->setPosition(x3, h3);

	spr_vagonDummy4 = new Sprite(*txt_vagonDummy);
	spr_vagonDummy4->setScale(0.8, 0.8);
	spr_vagonDummy4->setOrigin(31.5, 61); 
	spr_vagonDummy4->setPosition(x4, h4);
	
	// fuente para los textos en pantalla
	if (!fuente.loadFromFile("resources/fonts/Square.ttf"))
	{
		//error
	}

	// cronometro
	textoContador.setFont(fuente);
	textoContador.setPosition(600, 30);
	textoContador.setCharacterSize(36);
	textoContador.setFillColor(Color::White);

	// operacion a resolver
	textoCalculo.setFont(fuente);
	textoCalculo.setPosition(400, 65);
	textoCalculo.setCharacterSize(30);

	// player input
	textoRespuesta.setFont(fuente);
	textoRespuesta.setPosition(540, 65);
	textoRespuesta.setCharacterSize(30);
}



void juego::procesar_eventos()
{
	while (ventana1->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
		case Event::Closed:
			exit(1);
			break;

		case Event::TextEntered: 

			if ((es_colision) && (!gameOver) && (seconds > 0))
			{
				if ((evento1->text.unicode >= 48) && (evento1->text.unicode <= 57)) // permito ingresar solo numeros
				{
					//cout << "caracter ASCII tipeado: " << static_cast<char>(evento1->text.unicode) << endl; // para debug
					playerInput += evento1->text.unicode;
				}
								
				else if (Keyboard::isKeyPressed(Keyboard::Enter)) // para confirmar respuesta chequeo si se ingreso algun numero
				{
					if (playerInput.empty())
					{
						respuesta = 0;
						input = true;
					}
					
					else
					{
						cout << "respuesta: " << playerInput << endl; // para debug
						respuesta = stoi(playerInput); // lo transformo en integer
						input = true;
					}
				}
			}
			
			break;

		case Event::KeyPressed:
			
			if (Keyboard::isKeyPressed(Keyboard::Escape)) // para cerrar el juego presionando la tecla ESC
			{
				exit(1);
			}
			break;
		}
	}
}


void juego::dibujar()
{
	// dibujamos el background y la locomotora y los vagones
	ventana1->draw(*spr_fondo);
	
	if (!gameOver)
	{
		ventana1->draw(train1->get_sprite());
	}

	else if ((gameOver) && (victory))
	{
		ventana1->draw(train1->get_sprite());
		textoContador.setFillColor(Color::Green);
		ventana1->draw(textoContador);
	}
	
	// dibujo los vagones
	train1->dibujar(*ventana1);

	// estos son los vagones ubicados en posiciones random para colisionar
	ventana1->draw(*spr_vagonDummy1);
	ventana1->draw(*spr_vagonDummy2);
	ventana1->draw(*spr_vagonDummy3);
	ventana1->draw(*spr_vagonDummy4);
	
	// si hay colision con un vagon, muestra el cuadro de texto con el calculo a resolver y el cronometro
	if ((es_colision) && (!gameOver))
	{
		ventana1->draw(*spr_textBox);
		ventana1->draw(textoCalculo);
		ventana1->draw(textoRespuesta);
	}

	if (es_colision)
	{
		ventana1->draw(textoContador);
	}
}



void juego::game_loop()
{
	// bucle del juego
	while (ventana1->isOpen())
	{
		*tiempo1 = reloj1->getElapsedTime();

		if (tiempo2 + tiempoFrame < tiempo1->asSeconds()) // para que transcurra 1 fps entre ciclos
		{
			tiempo2 = tiempo1->asSeconds();

			actualizarContador(); // cronometro en reversa 

			ventana1->clear(); // limpiar la ventana

			procesar_eventos(); // cerrar la ventana y player input

			mover_tren(); // controla el movimiento del tren

			chequear_colisiones(); // chequeo si el tren colisiona con algun vagon. 

			generar_random(); // genero numeros random para la operacion aritmetica

			fin_juego(); // chequeo condicion de victoria o derrota

			dibujar(); // dubujo los sprites en pantalla

			ventana1->display(); // mostrar la ventana 
		}
	}
}


void juego::mover_tren()
{
	int velocidad = 3;

	// movimiento del tren y los vagones
	if (!gameOver)
	{
		// no ingrese respuesta pero hay colision
		if ((!input) && (es_colision))
		{
			if (seconds > 0) // hay tiempo disponible todavía, el tren no se mueve
			{
				train1->mover(0);
			}
			else if ((seconds < 0)) // se acabo el tiempo, el tren avanza
			{
				train1->mover(velocidad);
			}
		}

		// ingrese respuesta y aun hay colision
		if ((input) && (es_colision))
		{
			train1->mover(velocidad);
		}

		// no ingrese respuesta y no hay colision
		if ((!input) && (!es_colision))
		{
			train1->mover(velocidad);
		}
	}

	else // cuando se acaba el juego, el tren NO avanza
	{
		train1->mover(0);
	}
}



void juego::chequear_colisiones()
{
	//colisiones con los vagones random
	if ((train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy1->getGlobalBounds())) ||
	   (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy2->getGlobalBounds())) ||
	   (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy3->getGlobalBounds())) ||
	   (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy4->getGlobalBounds())))
	{
		es_colision = true;
		mostrar_calculo();
	}
	
	else
	{
		es_colision = false;
		input = false;
		insert = false; // desactivo bandera para insertar vagon
		destroy = false; // desactivo bandera para borrar vagon
		playerInput = "";
	}
	

	// desaparezco el vagon Dummy despues de una colision (lo vuelvo transparente)
	if (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy1->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spr_vagonDummy1->setColor(Color::Transparent);
		}
	}

	if (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy2->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spr_vagonDummy2->setColor(Color::Transparent);
		}
	}
		
	if (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy3->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spr_vagonDummy3->setColor(Color::Transparent);
		}
	}

	if (train1->get_sprite().getGlobalBounds().intersects(spr_vagonDummy4->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spr_vagonDummy4->setColor(Color::Transparent);
		}
	}
}



void juego::fin_juego()
{
	if ((gameOver) && (!victory))
	{
		if (!alarm)
		{
			snd_gameOver.play(); // sonido de derrota. Perdiste.
			alarm = true;
		}
	}

	/* 
		------------------------- CONDICION DE VICTORIA ---------------------

		Se presenta cuando el jugador logra alcanzar la estacion de llegada.

		----------------------------------------------------------------------
	*/

	if (!gameOver) 
	{
		// Si llegaste al final del recorrido
		if ((train1->get_positionX() > 730) && (train1->get_positionY() == 566.5)) 
		{
			musica.setLoop(false);
			musica.stop();
			snd_victory.play(); // sonido de victoria. Objetivo cumplido. Ganaste el juego.
			victory = true;
			textoContador.setFillColor(Color::Green);
			textoContador.setString("GANASTE !!!");
			snd_victory.play();
			gameOver = true; 
		}
	}

	/*
		------------------------- CONDICION DE DERROTA ---------------------

		Se presenta cuando todos los vagones y la locomotora son destruidos.

		----------------------------------------------------------------------

		Cuando hay una colision con un vagon, se muestra el cuadro de texto con el calculo a resolver.
		A partir de alli pueden darse las siguientes situaciones:

		A - Se responde dentro del tiempo asignado (5 seg.) y:
			A1- La respuesta es CORRECTA: se inserta el vagon a la formacion en forma ordenada. El tren avanza.
			A2- La respuesta es INCORRECTA: - se destruye un vagon (si existe) y el tren avanza. 
											- si NO hay vagones se destruye la locomotora y se acaba el juego. CONDICION DE DERROTA.
		
		B - No se responde dentro del tiempo asignado (se acaba el tiempo) y por lo tanto se destruye un vagon.
			B1- Si existe un vagon, se destruye y se continua el juego. El tren avanza.
			B2- Si NO existen vagones, se destruye la locomotora y se acaba del juego. CONDICION DE DERROTA.
	*/
	
	if ((es_colision) && (!gameOver))
	{
		if (seconds > 0)
		{

			if ((input) & (solucion == respuesta)) // respuesta correcta
			{
				//se inserta un vagon a la formacion en forma ordenada
				textoContador.setFillColor(Color::Green);
				textoContador.setString("CORRECTO !");

				if (!insert)
				{
					train1->insertar(respuesta);
					snd_whistle.play();
					cout << "el nuevo ultimo es: " << train1->get_ultimo() << endl;
					cout << "cantidad de vagones: " << train1->obtenerCantidadVagones() << endl;
					insert = true;
				}

				playerInput = "";
			}

			if ((input) & (solucion != respuesta)) // respuesta incorrecta
			{
				textoContador.setFillColor(Color::Red);
				textoContador.setString("INCORRECTO !");

				// si hay vagones, destruyo el ultimo vagon
				if ((!destroy) && (train1->obtenerCantidadVagones() > 0))
				{
					train1->borrar(train1->get_ultimo());
					snd_explosion.play();
					cout << "cantidad de vagones: " << train1->obtenerCantidadVagones() << endl;
					destroy = true;
				}

				playerInput = "";

				/*
				------ CONDICION DE DERROTA ------
				*/

				// si no hay vagones, voy a Game Over
				if ((!destroy) && (train1->obtenerCantidadVagones() == 0))
				{
					snd_explosion.play();
					cout << "cantidad de vagones: " << train1->obtenerCantidadVagones() << endl;

					musica.setLoop(false);
					musica.stop();
					textoContador.setFillColor(Color::Red);
					textoContador.setString("GAME OVER !");
					victory = false;

					destroy = true;
					gameOver = true;
				}
				playerInput = "";
			}

		}
		// si se acaba el tiempo
		else if (seconds < 0)
		{
			// si hay vagones, destruyo el ultimo vagon
			if ((!destroy) && (train1->obtenerCantidadVagones() > 0))
			{
				train1->borrar(train1->get_ultimo());
				snd_explosion.play();
				cout << "cantidad de vagones: " << train1->obtenerCantidadVagones() << endl;
				destroy = true;
			}

			/*
				------ CONDICION DE DERROTA ------
			*/

			// si no hay vagones, voy a Game Over
			if ((!destroy) && (train1->obtenerCantidadVagones() == 0))
			{
				snd_explosion.play();
				cout << "cantidad de vagones: " << train1->obtenerCantidadVagones() << endl;

				musica.setLoop(false);
				musica.stop();
				textoContador.setFillColor(Color::Red);
				textoContador.setString("GAME OVER !");
				victory = false;

				gameOver = true;
				destroy = true;
			}
		}
	}
}



void juego::actualizarContador()
{
	// reseteo el reloj del cronometro cuand no hay colisiones con los vagones
	if (!es_colision)
	{
		textoContador.setFillColor(Color::White);
		relojContador.restart();
		seconds = 5;
	}
		
	if ((!gameOver) && (es_colision))
	{
		tiempoFin = relojContador.getElapsedTime().asSeconds(); // Asignar a tiempoFin, el tiempo actual en cada framerate
		seconds = (int)(tiempoInicio - tiempoFin);
		
		if (seconds > 0)
		{
			char buffer[20];
			sprintf_s(buffer, "Tiempo: %i", seconds);
			textoContador.setString(buffer);
		}

		if (seconds == 0)
		{
			char buffer[20];
			sprintf_s(buffer, "Tiempo: %i", seconds);
			textoContador.setString(buffer);
			textoContador.setFillColor(Color::Red);
		}
	}
}


void juego::mostrar_calculo()
{
	textoCalculo.setFillColor(Color::Black);
	textoCalculo.setString(to_string(n1) + " + " + to_string(n2) + " + " + to_string(n3) + " = ");
	solucion = n1 + n2 + n3; // resultado de la operacion aritmetica

	textoRespuesta.setFillColor(Color::Blue);
	textoRespuesta.setString(playerInput);
}


void juego::generar_random()
{
	// si no hay colision, voy generando nuevos numeros random
	if (!es_colision)
	{
		n1 = rand() % 9;
		n2 = rand() % 9;
		n3 = rand() % 9;
	}
}