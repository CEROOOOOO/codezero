#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
constexpr int h = 600;
constexpr int w = 800;
SDL_Window* window = nullptr;
SDL_Renderer* board = nullptr;
bool init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << " errror 1";
	}
	else {
		if (!SDL_CreateWindowAndRenderer("hiiii", w, h, NULL, &window, &board)) {
			std::cout << "error in creationg window amd rendiorerr";
		}
		else {
			return true; 
		}
	}



		
		return true;
}
class loading {
private :
	SDL_Texture* pen = nullptr;
public :
	bool loadmedia(const char* path) {
		pen = IMG_LoadTexture(board, path);
		if (pen == nullptr) {
			std::cout << "error 3";
		}
		else {
			return true;
		}
		return true;
	}
	bool render() {
		SDL_RenderTexture(board, pen, NULL, NULL);
		return true;
	}
	void close() {
		SDL_DestroyTexture(pen);
		pen = nullptr;
		SDL_DestroyRenderer(board);
		board = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	
};
int main() {
	loading l0 , l1, l2, l3, l4;
	if (init() == false) {
		std::cout << "errorz1";
	}
	if (l0.loadmedia("C:\\users\\cero3\\source\\repos\\SDL3\\sdl3\\mine0.png") == false) {
		std::cout << "errorz1";
	}
	if (l1.loadmedia("C:\\Users\\cero3\\source\\repos\\SDL3\\sdl3\\mine.png") == false) {
		std::cout << "errorrz2";
	}
	if (l2.loadmedia("C:\\Users\\cero3\\source\\repos\\SDL3\\sdl3\\mine1.png") == false) {
		std::cout << "errorz22";
	}
	if (l3.loadmedia("C:\\Users\\cero3\\source\\repos\\SDL3\\sdl3\\mine2.png") == false) {
		std::cout << "errorz3";
	}
	if (l4.loadmedia("C:\\Users\\cero3\\source\\repos\\SDL3\\sdl3\\mine3.png") == false) {
		std::cout << "errorz4";
	}
	else {
		bool quit = false;
		SDL_Event e;
		SDL_zero(e);
		while (quit == false) {
		    SDL_SetRenderDrawColor(board,0,0,0,255);
			SDL_RenderClear(board);
			l0.render();
			SDL_RenderPresent(board);
			while (SDL_PollEvent(&e) == true) {
				if (e.type == SDL_EVENT_QUIT) {
					quit = true;
				}
				else if (e.type == SDL_EVENT_KEY_DOWN) {
					if (e.key.key == SDLK_UP) {
						l1.render();
					}
					if (e.key.key == SDLK_DOWN) {
						l2.render();
					}
					if (e.key.key == SDLK_RIGHT) {
						l3.render();
					}
					if (e.key.key == SDLK_LEFT) {
						l4.render();
					}       
				}
			}
		}
	}

}  