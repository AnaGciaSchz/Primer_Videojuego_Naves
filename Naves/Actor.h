#pragma once
#include "Game.h" //porque tiene el render

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game); //game es quien lo pinta
	~Actor();
	virtual void draw();
	bool isInRender();
	bool isOverlap(Actor* actor);

	SDL_Texture* texture; //cosas de SDL, no importante
	int x; //pos, como no se inicializa, su valor es aleatorio (lo que haya en ese momento en memoria
	int y; //pos
	float vx; //velocidad en x
	float vy; //velocidad y
	int width;
	int height;
	int fileWidth; //tama�o imagen
	int fileHeight; //tama�o imagen
	Game* game;
};

