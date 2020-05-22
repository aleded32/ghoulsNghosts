#pragma once

#include "item.h"


using namespace std;
using namespace sf;

	RenderWindow app(VideoMode(700, 285), "snakesNtigers");
	Event e;
	
	float dt;


	Vector2f velocityY = Vector2f(0, 0.1f);
	Vector2f velocityX = Vector2f(2.5f, 0.0f);
	const Vector2f gravity = Vector2f(0, 0.12f);
	const Vector2f accelarationJump = Vector2f(0, 4.5f);
	bool isJumping;
	

	bool facingleft = false; 

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



class Player
{

public:

	Texture playerText;
	float x;
	float y;
	Sprite player;
	int playerHealth;
	View playerView;
	int score;
	int snakeDamage;
	int birdDamage;
	bool isdeath1;
	bool isdeath2;
	bool isdeath3;
	bool isdeath4;
	bool iscollision;
	

	Player()
	{
		birdDamage = 10;
		snakeDamage = 10;
		playerHealth = 600;
		 x = 2*32;
		 y = 7*32;
		score = 0;
		playerText.loadFromFile("player.png");
		player.setTexture(playerText);
		player.setPosition(x, y);
		isdeath1 = false;
		isdeath2 = false;
		isdeath4 = false;
		iscollision = false;
	}

	~Player()
	{
	
	}


	void PlayerView()
	{
			playerView.reset(sf::FloatRect(0, 0, 300, 120));
			playerView.setCenter(x,  y);
			

			if (x <= 5 * 32) 
			{
			
				playerView.setCenter(150, y);
			}
			else if (x >= 17 * 32) 
			{
				playerView.setCenter(550, y);
			}
		
			app.setView(playerView);
	}

	void move()
	{

		
		 

		if (Keyboard::isKeyPressed(Keyboard::D)/*&& wall == false*/)
		{
			facingleft = false;
			x  = x + velocityX.x;
			player.setScale(1,1);
		player.setPosition(x, y);
			//cout << facingleft << endl;

		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			
			facingleft = true;
			x = x - velocityX.x; 
			player.setScale(-1,1);
			player.setPosition(x, y);
			//cout << facingleft << endl;
			
		}

		if (player.getPosition().y >= 220 && Keyboard::isKeyPressed(Keyboard::Space) && isJumping == false) 
			{
				isJumping = true;
				velocityY.y = velocityY.y - accelarationJump.y;

				y += velocityY.y * 0.5;
			}
			else if (player.getPosition().y <= 220)
			{
				velocityY.y = velocityY.y + gravity.y;

				y += velocityY.y * 0.5;
			}

			
		
	}

	
	
	void attack(Clock& clock, Sprite chest, Texture empty, int snakeX[2],int snakeY[2],int birdX[2], int birdY[2], int playerX, int playerY, void EnemyDeath1 (), void EnemyDeath2(), void EnemyDeath3(), void EnemyDeath4())
	{
		
		int itemSelected = 0;
		dt = clock.getElapsedTime().asSeconds();

		dagger Dagger;
		shuriken Shuriken;

			
			Shuriken.ShurikenSpeed = Vector2f(300.0f,0);
			

			if(x >= chest.getPosition().x)
			{
					
						chest.setColor(Color::Transparent);
						itemSelected = 1;
					
					
			}
			else
			{
				int itemSelected = 0;
			}
			

		
				if(itemSelected == 0)
				{
					if(Keyboard::isKeyPressed(Keyboard::L) && !facingleft && !Keyboard::isKeyPressed(Keyboard::D))
					{
				
						Dagger.x = x + 10;
						Dagger.y = y;

						Dagger.Dagger.setPosition(Dagger.x, Dagger.y);

						app.draw(Dagger.Dagger);
				
				
					}
					else if(Keyboard::isKeyPressed(Keyboard::L) && facingleft && !Keyboard::isKeyPressed(Keyboard::A))
					{
				
						Dagger.Dagger.setScale(-1,1);
						Dagger.x = x - 10;
						Dagger.y = y;

						

						Dagger.Dagger.setPosition(Dagger.x, Dagger.y);

						app.draw(Dagger.Dagger);
					}

				}
				if(itemSelected == 1)
				{
					
					if(Keyboard::isKeyPressed(Keyboard::L) && (!facingleft) && !Keyboard::isKeyPressed(Keyboard::D))
					{
						//fired = true;
						Shuriken.x = x;
						Shuriken.y = y;
						Shuriken.x += (Shuriken.ShurikenSpeed.x * dt);
						Shuriken.Shuriken.setPosition(Shuriken.x,Shuriken.y);
						app.draw(Shuriken.Shuriken);
						

					}
					else if(Keyboard::isKeyPressed(Keyboard::L) && (facingleft) && !Keyboard::isKeyPressed(Keyboard::A))
					{
						//fired = true;
						Shuriken.x = x;
						Shuriken.y = y;
						Shuriken.Shuriken.setScale(-1,1);
						Shuriken.x -= (Shuriken.ShurikenSpeed.x * dt);
						Shuriken.Shuriken.setPosition(Shuriken.x,Shuriken.y);
						app.draw(Shuriken.Shuriken);
						
					}
				
				}

				if(dt >= 1)
					{
						clock.restart();
					}

				int ShurikenX = (int)Shuriken.x/32;
				int ShurikenY = (int)Shuriken.y/32;
				int daggerX = (int)Dagger.x/32;
				int daggerY = (int)Dagger.y/32;

				for(int i = 1; i < 3; i++ )
				{
	
					if (snakeX[i] == playerX && snakeY[i] == playerY)
					{
							playerHealth -= snakeDamage;
							death();

					}
					if (birdX[i] == playerX  && birdY[i] == playerY)
					{
						playerHealth -= birdDamage;
						death();
					}
				}
			
					if(snakeX[1] == ShurikenX && snakeY[1] == ShurikenY)
					{
						
						if(isdeath1 = false)
						{
						EnemyDeath1();
						score+=20;
						}
						isdeath1 = true;
						snakeDamage = 0;
						
						
						
					}
					else if(snakeX[1] == daggerX && snakeY[1] == daggerY)
					{
					 
						if(isdeath1 == false)
						{
						 EnemyDeath1();
						 score += 20;
						}
						isdeath1 = true;
						snakeDamage = 0;
						
					}
					else if(snakeX[2] == ShurikenX && snakeY[2] == ShurikenY)
					{
					 
						if(isdeath2 == false)
						{
						 EnemyDeath2();
						 score += 20;
						}
						isdeath2 = true;
						snakeDamage = 0;
						
 					}
					else if(snakeX[2] == daggerX && snakeY[2] == daggerY)
					{
					 
						if(isdeath2 == false)
						{
						 EnemyDeath2();
						 score += 20;
						}
						isdeath2 = true;
						snakeDamage = 0;
						
						
					}
					else if(birdX[1] == daggerX && birdY[1] == daggerY)
					{
					 
						if(isdeath3 == false)
						{
						 EnemyDeath3();
						 score += 40;
						}
						isdeath3 = true;
						birdDamage = 0;
						
						
					}
					else if(birdX[2] == daggerX && birdY[2] == daggerY)
					{
					 
						if(isdeath4 == false)
						{
						 EnemyDeath4();
						 score += 40;
						}
						isdeath4 = true;
						birdDamage = 0;
					}	
					else if(birdX[1] == ShurikenX && birdY[1] == ShurikenY)
					{
					 
						if(isdeath3 == false)
						{
						 EnemyDeath3();
						 score += 40;
						}
						isdeath3 = true;
						birdDamage = 0;
						
					}
					else if(birdX[2] == ShurikenX && birdY[2] == ShurikenY)
					{
					 
						if(isdeath4 == false)
						{
						 EnemyDeath4();
						 score += 40;
						}
						isdeath4 = true;
						birdDamage = 0;
					
					}
				

			
				
			
		}

	 
	void death() 
	{
	    


		if (playerHealth <= 0) 
		{
			app.close();
		}
	}
	


};