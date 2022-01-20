#include <iostream>
#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;
	
	//game loop
	while (game.running())
	{		
		game.condition();
		//Render and update
		//Draw your game	
	}
}