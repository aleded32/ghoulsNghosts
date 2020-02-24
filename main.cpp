#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"

using namespace std;
using namespace sf;





Texture floorText;
Texture empty;
Texture backgroundText;

Texture chestText;
Texture wallT;






int tileX = 1;
int tileY = 8;

void spawn(Sprite floor, Sprite empty, Sprite wall, Texture tile[3],  int tileX, int tileY) 
{

	floor.setTexture(tile[0]);
	floor.setPosition(tileX * 32, tileY * 32);
	empty.setTexture(tile[1]);
	empty.setPosition(tileX * 32, tileY * 32);
	wall.setTexture(tile[2]);
	wall.setPosition(tileX * 32, tileY * 32);

	app.draw(wall);
	app.draw(floor);
	app.draw(empty);

}






int main()
{
	app.setFramerateLimit(60);
	
	

	Sprite floor;
	Sprite wall;
	wall.setColor(Color::Transparent);
	floorText.loadFromFile("floor.png");
	
	
	
	


	Texture tile[3] = { empty, floorText, wallT};

	Vector2f velocity = Vector2f(0, 0.1f);
	const Vector2f accelaration = Vector2f(0, 0.12f);
	const Vector2f accelarationJump = Vector2f(0, 4.0f);
	bool isJumping;
	
	Player player;

	



	

	Sprite background;
	backgroundText.loadFromFile("background.png");
	background.setTexture(backgroundText);
	background.setPosition(0, 0);
	background.setScale(0.5f, 0.5f);

	
	
	Sprite chest;
	chestText.loadFromFile("chest.png");
	chest.setTexture(chestText);
	chest.setPosition(18 * 32, 7 * 32);


	
	


	Sprite empty;
	empty.setColor(Color::Transparent);


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
		Event e;
		while (app.pollEvent(e)) 
		{
			if (e.type == Event::Closed) 
			{
				
				app.close();
			}
			
		}

		if (Keyboard::isKeyPressed(Keyboard::D) /*&& wall == false*/)
		{

			player.x  = player.x + 2;
		player.player.setPosition(player.x, player.y);
			

		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{

			player.x = player.x - 2;
			player.player.setPosition(player.x, player.y);

		}

		
			if (player.player.getPosition().y >= 220 && Keyboard::isKeyPressed(Keyboard::Space) && isJumping == false) 
			{
				isJumping = true;
				velocity.x = velocity.x - accelarationJump.x;
				velocity.y = velocity.y - accelarationJump.y;

				player.x += velocity.x;
				player.y += velocity.y;
			}
			else if (player.player.getPosition().y <= 220)
			{
				velocity.x = velocity.x + accelaration.x;
				velocity.y = velocity.y + accelaration.y;

				player.x += velocity.x;
				player.y += velocity.y;
			}

		
			
			

		


		

		player.player.setPosition(player.x, player.y);

		app.clear();
		
		app.draw(background);
		app.draw(chest);
		
		
		
		

			int playerX = int(player.x / 32);
			int playerY = int(player.y / 32);
		
		
			Thread t1(&Player::PlayerView, &player);
			t1.launch();			
		
			

		
		if (gamefield[playerY+1][playerX] == 1) 
		{
			
			velocity.y = NULL;
			velocity.x = 0;
			isJumping = false;
			
			
			//cout << "collision";
		}
		else if (gamefield[playerY][playerX] == 0)
		{
			velocity.x = velocity.x + accelaration.x;
			velocity.y = velocity.y + accelaration.y;

			player.x += velocity.x;
			 player.y += velocity.y;
		}
		if (gamefield[playerY][playerX + 1] == 2)
		{

			player.x = 0;
			
			//isJumping = false;


			//cout << "collision";
		}
		
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				
			spawn(floor ,empty,wall, &tile[gamefield[i][j]], j, i);
				

			}
			
		}
		app.draw(player.player);
		//Gravity(velocity, accelaration, x, y, player);
		app.display();
	}
	return 0;
}