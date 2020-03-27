#pragma once

using namespace std;
using namespace sf;

class enemy
{
public:
	
	float x;
	float y;
	int enemyHealth;
	Vector2f EnemySpeed;
};

class snake : public enemy
{
public:

	Texture enemyTile;
	Sprite Enemy;
	


	snake()
	{

		enemyHealth = 20;
		
		enemyTile.loadFromFile("snake.png");
		Enemy.setTexture(enemyTile);
		
		

		
		

	}



	~snake()
	{

	}



};

