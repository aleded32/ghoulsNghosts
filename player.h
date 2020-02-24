#pragma once

using namespace std;
using namespace sf;

RenderWindow app(VideoMode(700, 285), "snakesNtigers");
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


};