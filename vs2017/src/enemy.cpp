#include <Enemy.h>


Enemy::Enemy(Vector2D<int> position_mouse): angle_buffer(0), distance_travel(0)
{
	readConfigFile();

	float x = rand() % 1280;
	float y = rand() % 720;
	catched_mouse = false;

	while (x - position_mouse.X() < 400 && x - position_mouse.X() > -400)
	{
		x = rand() % 1280;
	}
		 
	while (y - position_mouse.Y() < 200 && y - position_mouse.Y() > -200) 
	{
		y = rand() % 720;
	}
		
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(x, y);
	sprite.setOrigin(sprite.getSize().x/2, sprite.getSize().y / 2);
}

Enemy::Enemy(const Enemy & other)
{
	    angle_buffer = 0;
		distance_travel = 0;
		readConfigFile();
		float x = rand() % 1280;
		float y = rand() % 720;
		sprite.setFillColor(sf::Color::Green);
		sprite.setPosition(x, y);
		catched_mouse = false;
		sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}


Enemy::~Enemy()
{
}

void Enemy::move(Vector2D<float> vec_cible)
{
	*vec = vec_cible - sprite.getPosition();
	Vector2D<float> vec_buff = *vec;
	Vector2D<float> pos = sprite.getPosition();
	float angle = pos.angle_With(vec_cible);
	vec->normalize();

	if (pos.X() != vec_cible.X() || pos.Y() != vec_cible.Y())
	{
		sprite.setRotation(angle);
		if(angle - angle_buffer > 20 || angle - angle_buffer < -20)
		{
			clock.restart();
		}
		if (vec_cible.X() > 1230 || vec_cible.X() < 0 || vec_cible.Y() < 0 || vec_cible.Y() > 690)
			catched_mouse = true;

		if (vec_buff.X() < 180 && vec_buff.X() > -180 && vec_buff.Y() < 180 && vec_buff.Y() > -180) 
		{
			sprite.move(vec->X() * max_speed + acceleration.X(), vec->Y() * max_speed + acceleration.Y());
			addToDistanceTravel(vec->X() + vec->Y());	
		}
		else
		{
			sprite.move(vec->X() * curr_speed + acceleration.X(), vec->Y() * curr_speed + acceleration.Y());
			addToDistanceTravel(vec->X() + vec->Y());
		}		
		setAcceleration();
		angle_buffer = angle;
	}
}

void Enemy::addToDistanceTravel(float d_traveled)
{
	if (d_traveled < 0)
		distance_travel -= d_traveled / 1000;
	else
		distance_travel += d_traveled / 1000;
}

void Enemy::setAcceleration()
{
	if(clock.getElapsedTime().asSeconds() < 3)
	{
		acceleration.set_X(acceleration.X() + vec->X() / 2);
		acceleration.set_Y(acceleration.Y() + vec->Y() / 2);
	}
}

void Enemy::readConfigFile()
{	
		std::fstream fichier("../assets/config.ini", std::ios::in | std::ios::out );  

		if (fichier)
		{			
			std::string word1, word2, word3;
			fichier >> word1 >> word2 >> curr_speed >> word3; 
			fichier >> word1 >> word2 >> max_speed >> word3;
			fichier.close();
		}
		else
			std::cout << "FILE DOESN'T EXIST" << std::endl;
}
