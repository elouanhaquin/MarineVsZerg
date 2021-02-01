#include "BlockingCube.h"



BlockingCube::BlockingCube(Vector2D<int> position):blocking_cube_exist(true)
{

	sprite.setFillColor(sf::Color::Yellow);
	sprite.setPosition(position.X() - 25, position.Y() - 25);
}


BlockingCube::~BlockingCube()
{
	blocking_cube_exist = false;
}
