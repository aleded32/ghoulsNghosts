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

snake snakes[4];
Player player;
shuriken Shuriken;
dagger Dagger;




int tileX = 1;
int tileY = 8;

void spawn(Sprite floor, Sprite empty, Sprite wall, Texture tile[3],  int tileX, int tileY) 
{

	


	floor.setTexture(tile[0]);
	floor.setPosition(tileX * 32, tileY * 32);




	app.draw(floor);
	

}

void EnemyDeath()
{
	for (int i = 1; i < 2; i++)
	{
		
		snakes[i].Enemy.setColor(Color::Transparent);
		

	}
}



void EnemySpawn(Clock& clock)
{
	


	for(int i = 1; i < 2; i++)
		{
			snakes[i].EnemySpeed = Vector2f(20, 0);

			snakes[i].y = 7 * 33;
			snakes[i].x = (i*6) * 32;
			

			if(player.x >= snakes[i].x - 100  && player.x <= snakes[i].x)
			{

				snakes[i].x -=   6 * (snakes[i].EnemySpeed.x * dt);
			} 
			
			 

			snakes[i].Enemy.setPosition(snakes[i].x, snakes[i].y);
			app.draw(snakes[i].Enemy);

			
		}
}



int main()
{
	Clock clock;
	app.setFramerateLimit(60);
	
	

	Sprite floor;
	Sprite wall;
	wall.setColor(Color::Transparent);
	floorText.loadFromFile("floor.png");
	
	
	
	


	Texture tile[3] = { empty, floorText, wallT};


	

	Sprite background;
	backgroundText.loadFromFile("background.png");
	background.setTexture(backgroundText);
	background.setPosition(0, 0);
	background.setScale(0.5f, 0.5f);

	
	
	Sprite chest;
	chestText.loadFromFile("chest.png");
	chest.setTexture(chestText);
	chest.setPosition(10 * 32, 7 * 32);



	
	
	Thread t1(&Player::PlayerView, &player);

	Sprite Empty;
	Empty.setColor(Color::Transparent);


	

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
		
		int ShurikenX = int(Shuriken.x / 32);
		int ShurikenY = int(Shuriken.y / 32);
		int DaggerX = int(Dagger.x / 32);
		int DaggerY = int(Dagger.y / 32);

		

		cout << int(Shuriken.x / 32) << endl;

		//collision for player		
		if (gamefield[playerY+1][playerX] == 1) 
		{
			velocityY.y = NULL;
			isJumping = false;
			

		}
		else if (gamefield[playerY][playerX] == 0)
		{
			
			velocityY.y = velocityY.y + gravity.y;

		
			 player.y += velocityY.y;
		}
		

		//cout << player.playerHealth << endl;    
		shuriken Shuriken;
		

		app.clear();
		
		app.draw(background);
		app.draw(chest);
		
		
		
		player.move(clock);
		player.player.setPosition(player.x, player.y);

		for(int i = 1; i < 2; i++)
		{
			int snakeX[3];
			int snakeY[3];

			snakeX[i] = int(snakes[i].x / 32);
			snakeY[i] = int(snakes[i].y / 32);

			player.attack(clock, chest, empty, snakeX, snakeY, playerX, playerY, EnemyDeath);
		}

		
				
		
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				
			spawn(floor ,Empty,wall, &tile[gamefield[i][j]], j, i);
				

			}
			
		}
		EnemySpawn(clock);
		app.draw(player.player);
		
		
		//Gravity(velocity, accelaration, x, y, player);
		app.display();
	}
	return 0;
}