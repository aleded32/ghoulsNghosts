#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


RenderWindow app(VideoMode(700, 285), "snakesNtigers");



Texture floorText;
Texture empty;
Texture backgroundText;
Texture playerText;
Texture chestText;





int tileX = 1;
int tileY = 8;

void spawn(Sprite floor, Sprite empty, Texture tile[3],  int tileX, int tileY) 
{

	floor.setTexture(tile[0]);
	floor.setPosition(tileX * 32, tileY * 32);
	empty.setTexture(tile[1]);
	empty.setPosition(tileX * 32, tileY * 32);
	

	app.draw(floor);
	app.draw(empty);

}




int main()
{
	app.setFramerateLimit(60);
	Sprite floor;
	floorText.loadFromFile("floor.png");
	
	
	
	


	Texture tile[2] = { empty, floorText};



	

	Sprite background;
	backgroundText.loadFromFile("background.png");
	background.setTexture(backgroundText);
	background.setPosition(0, 0);
	background.setScale(0.5f, 0.5f);

	Sprite player;
	playerText.loadFromFile("player.png");
	player.setTexture(playerText);
	player.setPosition(1*32, 7*32);
	
	Sprite chest;
	chestText.loadFromFile("chest.png");
	chest.setTexture(chestText);
	chest.setPosition(18 * 32, 7 * 32);


	
	


	Sprite empty;
	empty.setColor(Color::Transparent);


	/* 0 = nothing 
	   1 = platform
	   2 = chest
	   3 = ogre
	   4 = crow
	*/
	int gamefield[9][22] = 
	{
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1
	 
	};



	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j<22; j++)
		{
		
			cout << gamefield[i][j] << " ";
			gamefield[tileY][tileX] = 0;
			gamefield[tileY][tileX] = 1;
			
		
		}
		cout << endl;
	}

	while (app.isOpen()) 
	{
		Event e;
		while (app.pollEvent(e)) 
		{
			if (e.type == Event::Closed) 
			{
			
				app.close();
			}
		
		}

		app.clear();
		
		app.draw(background);
		app.draw(chest);
		app.draw(player);
		
		
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				spawn(floor ,empty, &tile[gamefield[i][j]], j, i);
				

			}
			
		}

		
		app.display();
	}
	return 0;
}