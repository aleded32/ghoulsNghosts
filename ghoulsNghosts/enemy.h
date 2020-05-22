#pragma once

using namespace std;
using namespace sf;

class enemy
{
public:
	
	float x;
	float y;
	
	Vector2f EnemySpeed;
};

class snake : public enemy
{
public:

	Texture enemyTile;
	Sprite Enemy;
	


	snake()
	{

		
		enemyTile.loadFromFile("snake.png");
		Enemy.setTexture(enemyTile);
		
		

		
		

	}



	~snake()
	{

	}



};

class bird : public enemy
{

	public:

		Texture enemyTile;
		Sprite  Bird;
		

		bird()
		{
			enemyTile.loadFromFile("bird.png");
			Bird.setTexture(enemyTile);
			
		}

		~bird(){}

};

