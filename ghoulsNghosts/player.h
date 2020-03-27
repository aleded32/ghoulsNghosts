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
	bool facingleft;
	
	
	

	Player()
	{
		
		playerHealth = 300;
		 x = 2*32;
		 y = 7*32;
		 facingleft = false;
		
		
	playerText.loadFromFile("player.png");
	player.setTexture(playerText);
		player.setPosition(x, y);

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

	void move(Clock& clock)
	{
		
		 dt = clock.getElapsedTime().asSeconds();

		if (Keyboard::isKeyPressed(Keyboard::D) /*&& wall == false*/)
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

				y += velocityY.y * dt;
			}
			else if (player.getPosition().y <= 220)
			{
				velocityY.y = velocityY.y + gravity.y;

				y += velocityY.y * dt;
			}

			
		
	}

	
	
	void attack(Clock& clock, Sprite chest, Texture empty)
	{
		
		int itemSelected = 0;
		dt = clock.getElapsedTime().asSeconds();

		dagger Dagger;
		shuriken Shuriken;

			Shuriken.x = x;
			Shuriken.y = y;
			Shuriken.ShurikenSpeed = Vector2f(300.0f,0);

			if(x >= chest.getPosition().x)
			{
					
						chest.setTexture(empty);
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
						Shuriken.x += (Shuriken.ShurikenSpeed.x * dt);
						Shuriken.Shuriken.setPosition(Shuriken.x,Shuriken.y);
						app.draw(Shuriken.Shuriken);
						

					}
					else if(Keyboard::isKeyPressed(Keyboard::L) && (facingleft) && !Keyboard::isKeyPressed(Keyboard::A))
					{
						//fired = true;
						Shuriken.Shuriken.setScale(-1,1);
						Shuriken.x -= (Shuriken.ShurikenSpeed.x * dt);
						Shuriken.Shuriken.setPosition(Shuriken.x,Shuriken.y);
						app.draw(Shuriken.Shuriken);
						
					}
				
				
					

					
				
				}

				if(dt >= 0.5)
					{

						
						clock.restart();
					}

				
			
	}

	 
	void death() 
	{
		
		playerHealth -= 10;

		if (playerHealth <= 0) 
		{
			app.close();
		}
	}


};