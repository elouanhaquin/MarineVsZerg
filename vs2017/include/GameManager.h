#pragma once
#include <ctime>
#include <sstream>
#include <iomanip>
#include <list>
#include <string>

#include <Player.h>
#include <enemy.h>
#include <BlockingCube.h>


class GameManager
{
private:
	sf::RenderWindow* window;
	sf::Font* font;
	sf::Font font_interjection;
	sf::Text* score;
	sf::Text* interjection;
	sf::Clock time_alive;

	std::list<Enemy> list_enemies;
	std::vector<std::string> interjection_vec;
	std::list<Enemy>::iterator iterator_enemies;
	
	Player* player;
	BlockingCube* blockingcube;
	Vector2D<int> mousePos;
	
	int buffer_time_interjection;
	int random_word;
	int malus;
	int fps;

public:
	GameManager();
	~GameManager();

	void start();
	void loop();
	void end();

	void renderFrame();

	//Text Functions
	void printInterjection();
	void setTextElements();
	void setInterjectionVec();
	
	//Movement functions
	void moveEntities();
	void setMouseToRandomPos();
	void instantiateBlockingCube();

	//List Functions
	void addingEnemyToList();
	void increasedListDifficulty();
	void renderListElements();
	void moveListElements();
	bool isAnyoneMakeCollision();

};

