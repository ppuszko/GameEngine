#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "GameObject.h"
#include <vector>
#include "GameActor.h"
//676x324, pad: 418x113

const int SCREEN_WIDTH = 576;
const int SCREEN_HEIGHT = 324;


int main(int agrc, char* args[])
{
	
	//Sprite spriteSheet;
	//GameObject slime(10);
	GameActor slime(150, 200, 200,64, 64, 10);
	//GameObject pad1(0, 300);
	GameObject pad2(0, 300);
	GameObject pad3(400, 230);
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
			//pad1.initSprite(renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Nowy folder/PNG/Pads/Pad_3_3.png");
			pad2.initSprite(renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Nowy folder/PNG/Pads/Pad_3_3.png");
			pad3.initSprite(renderer, "C:/Users/ppusz/Desktop/SDLImagebmp/Nowy folder/PNG/Pads/Pad_3_3.png");
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
				
				pad2.render(renderer, 1);
				pad3.render(renderer, 1);
				
				pad2.showCollisionBox(renderer);
				pad3.showCollisionBox(renderer);
				SDL_RenderPresent(renderer);

				
				
				SDL_Delay(16);
			}
		}
	}
	
	close(window, renderer);

	//spriteSheet.free();

	return 0;
}