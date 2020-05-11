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
Texture blockText;


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

void collision(int playerLocationX, int playerLocationY, int blockLocationX, int blockLocationY, Sprite block, int blockX, int blockY, int playerX, int playerY)
{
	if(playerLocationX == blockLocationX && isJumping == false && facingleft == false)
	{
		iscollidedLeft = true;

		player.player.setPosition(playerLocationX - block.getGlobalBounds().width/2 - 2, playerLocationY);
		
	}
	
	else if(playerLocationX == blockLocationX && isJumping == false && facingleft == true)
	{
		iscollidedRight = true;

		player.player.setPosition(playerLocationX + 50, playerLocationY);
		
	}
	else if (playerLocationX != blockLocationX)
	{
		iscollidedRight = false;
		iscollidedLeft = false;
	
	}
	

}


void EnemyDeath1()
{
	
		
		snakes[1].Enemy.setColor(Color::Transparent);
		

	
}

void EnemyDeath2()
{
	
		
		snakes[2].Enemy.setColor(Color::Transparent);
		

	
}



void EnemySpawn(Clock& clock)
{
	


	for(int i = 1; i < 3; i++)
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
	blockText.loadFromFile("wall.png");
	
	
	
	


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

	Sprite block;
	block.setTexture(blockText);
	

	

	
	
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
		app.draw(block);
		
		
			player.move();
		
		player.player.setPosition(player.x, player.y);

		for(int i = 1; i < 3; i++)
		{
			int snakeX[3];
			int snakeY[3];

			snakeX[i] = int(snakes[i].x / 32);
			snakeY[i] = int(snakes[i].y / 32);

			player.attack(clock, chest, empty, snakeX, snakeY, playerX, playerY, EnemyDeath1, EnemyDeath2);
		}

		
			//cout << iscollided << endl;	
		
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				
			spawn(floor ,Empty,wall, &tile[gamefield[i][j]], j, i);
				

			}
			
		}
		EnemySpawn(clock);

		for(int i = 1; i < 2; i++)
	{
	 int blockLocationX = 3 * 32;
	 int blockLocationY = 7 * 32;
	 int blockX = blockLocationX/32;
	 int blockY = blockLocationY/32;
	 block.setPosition( blockLocationX * i, blockLocationY);
	
		collision(player.x, player.y, blockLocationX, blockLocationY, block, blockX, blockY, playerX, playerY);
	}

		app.draw(player.player);
		
		
		
		//Gravity(velocity, accelaration, x, y, player);
		app.display();
	}
	return 0;
}