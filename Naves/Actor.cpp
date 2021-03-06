#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game) {
	this->game = game;
	texture = game->getTexture(filename);
	this->x = x;
	this->y = y;
	// lo que mide el fichero
	this->fileWidth = width;
	this->fileHeight = height;
	// lo que va a medir en el juego
	this->width = width;
	this->height = height;

}

Actor::~Actor() {
}


void Actor::draw() {
	SDL_Rect source; //dimensiones imagen, no tiene new, se crea en el stack, no en el heap, se construye igualmente
	source.x = 0;
	source.y = 0;
	source.w = fileWidth;
	source.h = fileHeight;

	SDL_Rect destination;
	destination.x = x - width/2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(game->renderer, texture, &source, &destination, 0, NULL, SDL_FLIP_NONE); //referencias porque est�n en el stack, 0 es que no queremos ning�n �ngulo, null porque no queremos m�s punteros
		//null pointer es null de tipo pointer
}

bool Actor::isOverlap(Actor* actor) {
	bool overlap = false;
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2) {

		overlap = true;
	}
	return overlap;
}

bool Actor::isInRender() {
	if (x - width / 2 <= WIDTH && x + width / 2 >= 0 &&
		y - height / 2 <= HEIGHT && y + height / 2 >= 0) {
		return true;
	}
	return false;
}


