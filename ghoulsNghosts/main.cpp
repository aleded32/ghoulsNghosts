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
bird  birds[3];
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




void EnemyDeath1()
{
	
		
		snakes[1].Enemy.setColor(Color::Transparent);
		player.enemydeaths += 1;
		

	
}

void EnemyDeath2()
{
	
		
		snakes[2].Enemy.setColor(Color::Transparent);
		player.enemydeaths += 1;

	
}

void EnemyDeath3()
{
	
		
		birds[1].Bird.setColor(Color::Transparent);
		player.enemydeaths += 1;

	
}

void EnemyDeath4()
{
	
		
		birds[2].Bird.setColor(Color::Transparent);
		player.enemydeaths += 1;
	
}



void EnemySpawn(Clock& clock)
{
	
	float frequency = 5.0f;
	float amplitude = 70.0f;
	int distance = 80;

	for(int i = 1; i < 3; i++)
		{
			snakes[i].EnemySpeed = Vector2f(10, 0);

			snakes[i].y = 7 * 33;
			snakes[i].x = (i*6) * 32;

			birds[i].Bird.setScale(-1,1);
			birds[i].y = 5 * 32;
			birds[i].x = ((i+1)*7) * 32;
			

			if(player.x >= snakes[i].x - 100  && player.x <= snakes[i].x)
			{

				snakes[i].x -=   6 * (snakes[i].EnemySpeed.x * dt);
			} 
			
			
			birds[i].x += distance *(-2 * dt);
			birds[i].y += (sin(frequency * dt) * amplitude);
			

			birds[i].Bird.setPosition(birds[i].x, birds[i].y);
			snakes[i].Enemy.setPosition(snakes[i].x, snakes[i].y);
			app.draw(birds[i].Bird);
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

		Text score;
		Font font;
		font.loadFromFile("Acadian_Runes-Regular_PERSONAL_USE.ttf");
		score.setFont(font);
		score.setCharacterSize(18);
		score.setFillColor(Color::White);
		score.setPosition(player.x - 100, player.y - 50);
		string scoreStr = to_string(player.score);
		score.setString("Score: " + scoreStr);


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
		app.draw(score);
		
			player.move();
		
		player.player.setPosition(player.x, player.y);

		for(int i = 1; i < 3; i++)
		{
			int snakeX[3];
			int snakeY[3];
			int birdX[3];
			int birdY[3];

			snakeX[i] = int(snakes[i].x / 32);
			snakeY[i] = int(snakes[i].y / 32);
			birdX[i] = int(birds[i].x / 32);
			birdY[i] = int(birds[i].y / 32);

			

			player.attack(clock, chest, empty, snakeX, snakeY, birdX, birdY, playerX, playerY, EnemyDeath1, EnemyDeath2, EnemyDeath3, EnemyDeath4);
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
		
		
		
		
		app.display();
	}
	return 0;
}