#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include <SFML\Audio.hpp>


using namespace std;
using namespace sf;





Texture floorText;
Texture empty;
Texture backgroundText;
Texture blockText;
Texture heartText;
bool isleft = true;

Texture chestText;
Texture wallT;

snake snakes[MAX_ENEMIES];
bird  birds[MAX_ENEMIES];




void EnemyMove(Clock& clock, snake snakes[], bird birds[])
	{
		float deltaTime = clock.getElapsedTime().asSeconds();
		float frequency = 2.5f;
		float amplitude = 70.0f;
		float distance =  100.0f;

		for(int i = 1; i < MAX_ENEMIES; i++)
			{
				snakes[i].EnemySpeed = Vector2f(1, 0);
				birds[i].EnemySpeed = Vector2f(1.1, 0);
				
				birds[i].Bird.setScale(-1,1);
				birds[i].y = 5 * 32;
				birds[i].x = ((i+1)*7) * 32;
				
			
				if(snakes[1].x < 200 && isleft == true)
				{	
					snakes[i].x -=  snakes[i].EnemySpeed.x;
					
				}
				else if(snakes[1].x < 200 && isleft == false)
				{
					snakes[i].x +=  snakes[i].EnemySpeed.x;
				}

				if(snakes[1].x <= 100)
				{
					isleft = false;
				}
				if(snakes[1].x >= 199)
				{
					isleft = true;
				}

				birds[i].x -=  distance * (birds[i].EnemySpeed.x * deltaTime);
				birds[i].y += (sin(frequency * deltaTime) * amplitude);
				

				if(deltaTime >=4)
				{
					clock.restart();
				}

				birds[i].Bird.setPosition(birds[i].x, birds[i].y);
				snakes[i].Enemy.setPosition(snakes[i].x, snakes[i].y);
				app.draw(birds[i].Bird);
				app.draw(snakes[i].Enemy);
				
			}
	}



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







int main()
{
	//clocks used in game
	Clock clock;
	Clock weaponClock;
	app.setFramerateLimit(60);
	

	//spawning in sprites and textures
	Sprite floor;
	Sprite wall;
	wall.setColor(Color::Transparent);
	floorText.loadFromFile("floor.png");
	blockText.loadFromFile("wall.png");
	
	heartText.loadFromFile("heart.png");
	 

	Texture tile[3] = { empty, floorText, wallT};


	//music
	SoundBuffer buffer;
	buffer.loadFromFile("background.wav");
	sf::Sound backgroundMusic;
	backgroundMusic.setBuffer(buffer);
	backgroundMusic.play();
	backgroundMusic.setLoop(true);


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
	
	//spawn enemies in the game
	for(int i = 1; i < MAX_ENEMIES; i++)
	{
		snakes[i].y = 7 * 33;
		snakes[i].x = (i*6)  * 32;	
	}
	
	

	Sprite Empty;
	Empty.setColor(Color::Transparent);


	//pointers and classes called
	Player player;
	Player *ptrPlayer;

	ptrPlayer = &player;

	shuriken Shuriken;
	dagger Dagger;

	
	//creating a thread to place the playerview on
	Thread t1(&Player::PlayerView, &player);

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

		//generate text and imagaes for health and score
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

		//gameOver screen
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
		if(player.x <= 10)
		{
			player.x = 10;
			
			
		}

		   
		
		
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

			for(int i = 1; i < MAX_ENEMIES; i++)
			{
				int snakeX[3];
				int snakeY[3];
				int birdX[3];
				int birdY[3];

				snakeX[i] = int(snakes[i].x / 32);
				snakeY[i] = int(snakes[i].y / 32);
				birdX[i] = int(birds[i].x / 32);
				birdY[i] = int(birds[i].y / 32);

				if (snakes[i].Enemy.getGlobalBounds().intersects(player.player.getGlobalBounds()))
					{
							
							ptrPlayer ->playerHealth -= ptrPlayer ->snakeDamage;
							ptrPlayer ->death();
							
					}

				else if (birds[i].Bird.getGlobalBounds().intersects(player.player.getGlobalBounds()))
					{
							ptrPlayer ->playerHealth -= ptrPlayer ->birdDamage;
							ptrPlayer ->death();
							
					}
				
						
					
						

				ptrPlayer ->attack(weaponClock,empty,snakeX,snakeY,birdX, birdY, playerX, playerY, EnemyDeath1, EnemyDeath2, EnemyDeath3, EnemyDeath4);
			}
			
			if(player.player.getGlobalBounds().intersects(chest.getGlobalBounds()))
			{
					
						
						ptrPlayer ->itemSelected = 1;
						chest.setPosition(-50,-50);
						cout << 1 << endl;
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
		
		
		
			
		ptrPlayer ->player.setPosition(player.x, player.y);
		app.draw(ptrPlayer ->player);
		EnemyMove(clock, snakes, birds);


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