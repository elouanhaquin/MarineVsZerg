#pragma once
#include <Entity.h>
#include <fstream>
#include <string>

#define PI 3.141592f

class Enemy: public Entity 
{
private:
	int max_speed, curr_speed;
	float distance_travel, angle_buffer;
	bool catched_mouse; 
	Vector2D<float> acceleration;
	sf::Clock clock;

public:
	Enemy(Vector2D<int> position);
	Enemy(const Enemy& enemy);
	~Enemy();

	void move(Vector2D<float> vec);
	void addToDistanceTravel(float d_traveled);
	void increaseDifficulty() { max_speed += 3; curr_speed += 2; };
	void setAcceleration();

	bool mouseIsCatched() { return this->catched_mouse; }
	float getDistanceTraveled() { return this->distance_travel; }

	void readConfigFile();
};

