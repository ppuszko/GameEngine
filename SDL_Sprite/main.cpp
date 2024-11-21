#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "GameObject.h"
#include <vector>
#include "GameActor.h"

const int SCREEN_WIDTH = 576;
const int SCREEN_HEIGHT = 324;


int main(int agrc, char* args[])
{
	
	//Sprite spriteSheet;
	//GameObject slime(10);
	GameActor slime(10, 200, 200,64, 64, 3);
	GameObject pad(0, 200);
	Sprite bg1;
	Sprite bg2;
	Sprite bg3;
	Sprite bg4;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (!init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Failed to initalize\n");
	}
	else
	{
		if (!slime.initSprite(renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/PNG/Slime1/Hurt/Slime1_Hurt_body.png", 5, 4))
		{
			printf("Failed to load Game Actor!\n");
		}
		else
		{
			pad.initSprite(renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Nowy folder/PNG/Pads/Pad_3_3.png");
			loadSpriteSheet(bg1, renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Clouds/Clouds 4/1.png");
			loadSpriteSheet(bg2, renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Clouds/Clouds 4/2.png");
			loadSpriteSheet(bg3, renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Clouds/Clouds 4/3.png");
			loadSpriteSheet(bg4, renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Clouds/Clouds 4/4.png");

			//std::vector<SDL_Rect> clips = clipSpriteSheet(spriteSheet, 5, 4);
			slime.setCollisionBoxSize(64, 64);
			bool quit = false;
			int frame{ 0 };


			SDL_Event e;

			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			Uint8 a = 255;



			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					/*else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							case SDLK_r:
								r += 32;
								break;
							case SDLK_g:
								g += 32;
								break;
							case SDLK_b:
								b += 32;
								break;
							case SDLK_e:
								r -= 32;
								break;
							case SDLK_f:
								g -= 32;
								break;
							case SDLK_v:
								b -= 32;
								break;
							case SDLK_a:
								a += 32;
								break;

						}
					}*/
					slime.handleEvent(e);
				}
				
				
				slime.move(SCREEN_WIDTH, SCREEN_HEIGHT);
				slime.applyGravity();

				//rendering layered background 
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);
				bg1.render(0, 0, renderer);
				bg2.render(0, 0, renderer);
				bg3.render(0, 0, renderer);
				bg4.render(0, 0, renderer);

				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);


				slime.showCollisionBox(renderer);
				slime.renderAnimation(renderer, frame, 2);
				//allows for color and alpha modulation
				/*spriteSheet.setColor(r, g, b);
				spriteSheet.setAlpha(a);*/
				
				//slime.showCollision(renderer);
				//Render current frame
				//spriteSheet.renderAnimation(288, 162, renderer, clips, frame, 4);
				//slime.render(288, 162, renderer, 2, frame);
				pad.render(renderer, 1);
				pad.showCollisionBox(renderer);
				SDL_RenderPresent(renderer);

				//std::cout << GameObject::GMList[0]->collisionBox.w;
				
				SDL_Delay(16);
			}
		}
	}
	
	close(window, renderer);

	//spriteSheet.free();

	return 0;
}