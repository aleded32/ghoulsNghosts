#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "enemy.h"
#include "item.h"


using namespace std;
using namespace sf;





Texture floorText;
Texture empty;
Texture backgroundText;


Texture chestText;
Texture wallT;






int tileX = 1;
int tileY = 8;

void spawn(Sprite floor, Sprite empty, Sprite wall, Texture tile[3],  int tileX, int tileY) 
{

	floor.setTexture(tile[0]);
	floor.setPosition(tileX * 32, tileY * 32);
	empty.setTexture(tile[1]);
	empty.setPosition(tileX * 32, tileY * 32);
	wall.setTexture(tile[2]);
	wall.setPosition(tileX * 32, tileY * 32);

	app.draw(wall);
	app.draw(floor);
	app.draw(empty);

}






int main()
{
	app.setFramerateLimit(60);
	
	

	Sprite floor;
	Sprite wall;
	wall.setColor(Color::Transparent);
	floorText.loadFromFile("floor.png");
	
	
	
	


	Texture tile[3] = { empty, floorText, wallT};

	
	
	Player player;

	snake Snake;



	

	Sprite background;
	backgroundText.loadFromFile("background.png");
	background.setTexture(backgroundText);
	background.setPosition(0, 0);
	background.setScale(0.5f, 0.5f);

	
	
	Sprite chest;
	chestText.loadFromFile("chest.png");
	chest.setTexture(chestText);
	chest.setPosition(18 * 32, 7 * 32);



	
	
	Thread t1(&Player::PlayerView, &player);

	Sprite empty;
	empty.setColor(Color::Transparent);


	int gamefield[9][22] = 
	{
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	 
	};


	//initallizes gamefield
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j<22; j++)
		{
			
			
			gamefield[tileY][tileX] = 2;
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
				
				t1.wait();
				
				app.close();
			}
			
		}
			
			

			//launching viewport of player on a different thread
			t1.launch();
			

		int playerX = int(player.x / 32);
		int playerY = int(player.y / 32);
		int snakeX = int(Snake.x / 32);
		int snakeY = int(Snake.y / 33);

		//collision for player		
		if (gamefield[playerY+1][playerX] == 1) 
		{
			velocity.y = NULL;
			velocity.x = 0;
			isJumping = false;

		}
		else if (gamefield[playerY][playerX] == 0)
		{
			velocity.x = velocity.x + gravity.x;
			velocity.y = velocity.y + gravity.y;

			player.x += velocity.x;
			 player.y += velocity.y;
		}
		if (gamefield[playerY][playerX + 1] == 2)
		{

			player.x = 0;
		}
		if (snakeX == playerX && snakeY == playerY)
		{

			player.death();
		}

		//cout << player.playerHealth << endl;    

		app.clear();
		
		app.draw(background);
		app.draw(chest);
		
		
		player.attack();
		player.move();
		player.player.setPosition(player.x, player.y);
		
			
		
			
		
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				
			spawn(floor ,empty,wall, &tile[gamefield[i][j]], j, i);
				

			}
			
		}

		app.draw(Snake.Enemy);
		app.draw(player.player);
		//Gravity(velocity, accelaration, x, y, player);
		app.display();
	}
	return 0;
}