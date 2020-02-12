#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


RenderWindow app(VideoMode(700, 285), "snakesNtigers");



Texture floorText;
Texture empty;
Texture backgroundText;
Texture playerText;
Texture chestText;





int tileX = 1;
int tileY = 8;

void spawn(Sprite floor, Sprite empty, Texture tile[3],  int tileX, int tileY) 
{

	floor.setTexture(tile[0]);
	floor.setPosition(tileX * 32, tileY * 32);
	empty.setTexture(tile[1]);
	empty.setPosition(tileX * 32, tileY * 32);
	

	app.draw(floor);
	app.draw(empty);

}






int main()
{
	app.setFramerateLimit(60);
	Sprite floor;
	floorText.loadFromFile("floor.png");
	
	
	
	


	Texture tile[2] = { empty, floorText};

	Vector2f velocity = Vector2f(0, 0.1f);
	const Vector2f accelaration = Vector2f(0, 0.12f);
	const Vector2f accelarationJump = Vector2f(0, 4.0f);
	bool isJumping;
	bool wall;
	float x = 1*32;
	float y = 7*32;


	

	Sprite background;
	backgroundText.loadFromFile("background.png");
	background.setTexture(backgroundText);
	background.setPosition(0, 0);
	background.setScale(0.5f, 0.5f);

	Sprite player;
	playerText.loadFromFile("player.png");
	player.setTexture(playerText);
	player.setPosition(x, y);
	
	Sprite chest;
	chestText.loadFromFile("chest.png");
	chest.setTexture(chestText);
	chest.setPosition(18 * 32, 7 * 32);


	
	


	Sprite empty;
	empty.setColor(Color::Transparent);


	/* 0 = nothing 
	   1 = platform
	   2 = chest
	   3 = ogre
	   4 = crow
	*/
	int gamefield[9][22] = 
	{
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	 
	};



	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j<22; j++)
		{
		
			cout << gamefield[i][j] << " ";
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

			x = x + 2;
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
				velocity.x = velocity.x + accelaration.x;
				velocity.y = velocity.y + accelaration.y;

				x += velocity.x;
				y += velocity.y;
			}

		
			
			

		


		

		player.setPosition(x, y);

		app.clear();
		
		app.draw(background);
		app.draw(chest);
		
		
		//gravity for player
		

		int playerX = int(x / 32);
		int playerY = int(y / 32);
		
		if (gamefield[playerY+1][playerX] == 1) 
		{
			y = 224;
			velocity.y = NULL;
			velocity.x = 0;
			isJumping = false;
			
			
			cout << "collision";
		}
		else if (gamefield[playerY][playerX] == 0)
		{
			velocity.x = velocity.x + accelaration.x;
			velocity.y = velocity.y + accelaration.y;

			x += velocity.x;
			y += velocity.y;
		}
		
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				
				spawn(floor ,empty, &tile[gamefield[i][j]], j, i);
				

			}
			
		}
		app.draw(player);
		//Gravity(velocity, accelaration, x, y, player);
		app.display();
	}
	return 0;
}