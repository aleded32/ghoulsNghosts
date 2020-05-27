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
Texture heartText;


Texture chestText;
Texture wallT;

snake snakes[4];
bird  birds[3];
Player player;
shuriken Shuriken;
dagger Dagger;




int tileX = 1;
int tileY = 8;


void spawn(Sprite game, Texture tile[3],  int tileX, int tileY) 
{

	


	game.setTexture(tile[0]);
	game.setPosition(tileX * 32, tileY * 32);




	app.draw(game);
	

}




void EnemyDeath1()
{
	
		
		snakes[1].Enemy.setColor(Color::Transparent);
		
		

	
}

void EnemyDeath2()
{
	
		
		snakes[2].Enemy.setColor(Color::Transparent);
		

	
}

void EnemyDeath3()
{
	
		
		birds[1].Bird.setColor(Color::Transparent);
		

	
}

void EnemyDeath4()
{
	
		
		birds[2].Bird.setColor(Color::Transparent);
		
	
}



void EnemySpawn(Clock& clock)
{
	
	float frequency = 2.5f;
	float amplitude = 70.0f;
	int distance = 80;

	for(int i = 1; i < 3; i++)
		{
			snakes[i].EnemySpeed = Vector2f(10, 0);

			snakes[i].y = 7 * 33;
			snakes[i].x = (i*6)  * 32;

			birds[i].Bird.setScale(-1,1);
			birds[i].y = 5 * 32;
			birds[i].x = ((i+1)*7) * 32;
			

			

			snakes[i].x -=   6 * (snakes[i].EnemySpeed.x * dt);
			
			
			
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
	
	
	heartText.loadFromFile("heart.png");
	
	


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

	/*Sprite Empty;
	Empty.setColor(Color::Transparent);*/


	
	

	//initallizes gamefield
	

	while (app.isOpen()) 
	{
			Event e;
		while (app.pollEvent(e)) 
		{
			if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) 
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
		Text health;
		Font font;
		font.loadFromFile("Acadian_Runes-Regular_PERSONAL_USE.ttf");
		score.setFont(font);
		score.setCharacterSize(18);
		score.setFillColor(Color::White);
		string scoreStr = to_string(player.score);
		score.setString("Score: " + scoreStr);
		health.setFont(font);
		health.setCharacterSize(18);
		health.setFillColor(Color::White);
		health.setString("health: ");
		Text gameOver;
		gameOver.setFont(font);
		gameOver.setCharacterSize(18);
		gameOver.setFillColor(Color::Black);
		gameOver.setString("Game Over, press Esc to close game");

		if (player.x <= 5 * 32) 
		{
			score.setPosition(50, player.y - 50);
			health.setPosition(150, player.y - 50);
			gameOver.setPosition(0, player.y- 20);

		}
		else if (player.x >= 17 * 32) 
		{
			score.setPosition(450, player.y - 50);
			health.setPosition(550, player.y - 50);
			gameOver.setPosition(410, player.y - 20);
		}
		else
		{
			score.setPosition(player.x - 100, player.y - 50);
			health.setPosition(player.x, player.y - 50);
			gameOver.setPosition(player.x - 140, player.y - 20);
		}

		
		

		

		

		//collision for player		
		if (gamefield[playerY+1][playerX] == 1) 
		{
			velocityY.y = 0;
			isJumping = false;
			

		}
		else if (gamefield[playerY][playerX] == 0)
		{
			
			velocityY.y = velocityY.y + gravity.y;

		
			 player.y += velocityY.y;
		}
		

		   
		shuriken Shuriken;
		
		
		app.clear();
		
		app.draw(background);
		app.draw(chest);
		app.draw(block);
		app.draw(score);
		app.draw(health);

		for(int i = 0; i < 3; i++)
		{
			Sprite Heart[3];
			Heart[i].setTexture(heartText);
			if (player.x <= 5 * 32) 
			{
				Heart[i].setPosition((i*20) + 210, player.y - 45);
			}
			else if (player.x >= 17 * 32) 
			{
				Heart[i].setPosition((i*20) + 610, player.y - 45);
			}
			else
			{
				Heart[i].setPosition((i*20) + player.x + 60, player.y - 45);
			}

			if(player.playerHealth <= 400)
			{
				Heart[2].setColor(Color::Transparent);
			}
			if(player.playerHealth <= 200)
			{
				Heart[1].setColor(Color::Transparent);
			}
			if (player.playerHealth <= 0)
			{
				Heart[0].setColor(Color::Transparent);
			}

			app.draw(Heart[i]);
	}
		if(!isgameOver)
		{
			player.move();

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

		}
		
		else
		{
			app.draw(gameOver);
		}

		if(playerX >= 22)
		{
			
			isgameOver = true;
		}
		else if (player.x <= 0)
		{
			
			velocityX.x = -1;	
		}
		else if(player.x >= 8)
		{
		    velocityX.x = + 2.5;
		}
		
		
			
		player.player.setPosition(player.x, player.y);
		app.draw(player.player);
		EnemySpawn(clock);


		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				
			spawn(floor, &tile[gamefield[i][j]], j, i);
				

			}
			
		}
		

		

		
		
		
		
		app.display();
	}
	return 0;
}