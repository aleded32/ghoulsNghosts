#pragma once

using namespace std;
using namespace sf;

	RenderWindow app(VideoMode(700, 285), "snakesNtigers");

	Vector2f velocity = Vector2f(0, 0.1f);
	const Vector2f gravity = Vector2f(0, 0.12f);
	const Vector2f accelarationJump = Vector2f(0, 4.0f);
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
	
	View playerView;
	

	Player()
	{
		

		 x = 1*32;
		 y = 7*32;

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
		
		app.setView(playerView);
	}

	void move()
	{
		if (Keyboard::isKeyPressed(Keyboard::D) /*&& wall == false*/)
		{

			x  = x + 2;
		player.setPosition(x, y);
			

		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{

			x = x - 2;
			player.setPosition(x, y);

		}

		if (player.getPosition().y >= 220 && Keyboard::isKeyPressed(Keyboard::Space) && isJumping == false) 
			{
				isJumping = true;
				velocity.x = velocity.x - accelarationJump.x;
				velocity.y = velocity.y - accelarationJump.y;

				x += velocity.x;
				y += velocity.y;
			}
			else if (player.getPosition().y <= 220)
			{
				velocity.x = velocity.x + gravity.x;
				velocity.y = velocity.y + gravity.y;

				x += velocity.x;
				y += velocity.y;
			}
	}

	 


};