#pragma once

using namespace std;
using namespace sf;

class enemy
{
public:
	
	float x;
	float y;
	int enemyHealth;
};

class snake : public enemy
{
public:

	Texture enemyTile;
	Sprite Enemy;

	snake()
	{


		x = 7 * 32;
		y = 7 * 33;
		 

		

		enemyTile.loadFromFile("snake.png");
		Enemy.setTexture(enemyTile);
		Enemy.setPosition(x, y);
		Enemy.setScale(1, 1);

	}



	~snake()
	{

	}

	

};

