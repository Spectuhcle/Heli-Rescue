#include "Menu.h"
#include <iostream>

Menu::Menu() {
}

Menu::~Menu() {
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

Menu::Menu(int initState){
	state = initState;
}

void Menu::render(SDL_Renderer* renderer) {
	TTF_Init();
	if (state == 1) {
		mainMenuRender(renderer);
	} else if (state == 2) {
		exitMenuRender(renderer);
	}
}

void Menu::mainMenuRender(SDL_Renderer* renderer) {
	//SDL_RenderClear(renderer);
	//std::cout << "In mainMenu" << std::endl;

	textDisplay("Welcome to Heli-Rescue!", 240, 40, 100, 0, 85, 255, renderer,font);
	textDisplay("Start Game [G]", 400, 160, 72, 255, 230, 0, renderer,font);
	textDisplay("Quit Game [Q]", 400, 260, 72, 50, 255, 0, renderer,font);

	//std::cout << "Everything displayed on screen" << std::endl;
}

void Menu::exitMenuRender(SDL_Renderer* renderer) {
	SDL_RenderClear(renderer);
	textDisplay("Are you sure you want to quit? [Y/N]", 40, 360, 72, 255, 25, 0, renderer,font);
	std::cout << "sure you want to quit?";
}

void Menu::handleEvent(SDL_Event e, bool& isRunning, bool& isStart) {

	while (SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT) {
			isStart = false;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_g:
				isStart = false;
				isRunning = true;
				break;
			case SDLK_q:
				isStart = false;
				isRunning = false;
				break;
			}
		}	
	}
}


void Menu::setState(int state) {
	this->state = state;
}
int Menu::getState() {
	return state;
}

void Menu::textDisplay(std::string text, int x, int y, int size, int r, int g, int b, SDL_Renderer* renderer,TTF_Font* font) {
	SDL_Color color = { r, g, b };

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	int w = 0;
	int h = 0;
	SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
	SDL_Rect textRect = { x, y, w, h };

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}
void Menu::loadFont(int size) {

	font = TTF_OpenFont("assets/vevey.ttf", size);

}