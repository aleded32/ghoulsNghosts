#pragma once


using namespace std;
using namespace sf;

class item
{
public:
	
	float x;
	float y;
	int dmg;

	
};

class dagger : public item
{
public:

	
	Texture itemDagger;
	Sprite Dagger;

	dagger()
	{
		

		dmg = 30;

		itemDagger.loadFromFile("itemDagger.png");
		Dagger.setTexture(itemDagger);
		
	}

	~dagger(){}

};

class shuriken : public item
{

	public:

	Texture itemShuriken;
	Sprite Shuriken;
	Vector2f ShurikenSpeed;
	float MaxRangeX;

	shuriken()
	{
		
		dmg = 50;
		itemShuriken.loadFromFile("boomerang.png");
		Shuriken.setTexture(itemShuriken);

	}

	~shuriken(){}


};