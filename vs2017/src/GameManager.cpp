#include "GameManager.h"

GameManager::GameManager(): buffer_time_interjection (0), fps (60), malus (0)
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "MARINE AND ZERGS");
	player = new Player();
	
	mousePos = sf::Mouse::getPosition(*window);

	Enemy enemy = Enemy(mousePos);

	list_enemies.push_front(enemy);
	iterator_enemies = list_enemies.begin();

	font = new sf::Font();
	score = new sf::Text();
	interjection = new sf::Text();
}


GameManager::~GameManager()
{
	delete window;
	delete player;
	delete score;
	delete interjection;
}

void GameManager::start()
{
	window->setFramerateLimit(fps);
	window->setMouseCursorVisible(false);
	setMouseToRandomPos();
	setInterjectionVec();
	setTextElements();

}

void GameManager::loop()
{

	sf::Clock clock; 
	
	while (window->isOpen())
	{
		sf::Event event;
		std::stringstream ss;

		ss << std::fixed << std::setprecision(2) << time_alive.getElapsedTime().asSeconds() - malus;
		
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed )
				window->close();	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				instantiateBlockingCube();
		
		}
		if (isAnyoneMakeCollision() || list_enemies.front().mouseIsCatched())  //can use mouse is catcehd only with fornt because it will detect if mouse is out of screen
			window->close();
	
		if(clock.getElapsedTime().asSeconds() > 3)
		{
			addingEnemyToList();
			increasedListDifficulty();
			clock.restart();
		}

		interjection->setString(" ");
		score->setString(ss.str() + " SECONDS");
		moveEntities();
		printInterjection();
		renderFrame();
	}
}

void GameManager::end()
{
}

void GameManager::renderFrame()
{
	window->clear();
	window->draw(player->getRectangleShape());
	renderListElements();
	if(blockingcube!=nullptr)
		window->draw(blockingcube->getRectangleShape());
	window->draw(*score);
	window->draw(*interjection);
	window->display();
}

void GameManager::moveEntities()
{
	mousePos = sf::Mouse::getPosition(*window);
	player->move(mousePos);
	moveListElements();
}

void GameManager::setMouseToRandomPos()
{
	int x = rand() % 1230 + 50;
	int y = rand() % 680 + 50;
	sf::Mouse mouse = sf::Mouse();

	Vector2D<int> mouseSetterPosVector(false, x, y, 0);
	mouse.setPosition(mouseSetterPosVector.toSiVector(), *window);
}

void GameManager::instantiateBlockingCube()
{
	if (blockingcube == nullptr)
		blockingcube = new BlockingCube(mousePos);
}

void GameManager::printInterjection()
{
	if (time_alive.getElapsedTime().asSeconds() - buffer_time_interjection > 5)
	{			
		int r = rand() % 220 + 120;
		int g = rand() % 220 + 120;
		int b = rand() % 220 + 120;

		interjection->setString(interjection_vec[random_word]);
		interjection->setFillColor(sf::Color(r, g, b, 255));
		score->setFillColor(sf::Color(r, g, b, 255));
	}

	if(time_alive.getElapsedTime().asSeconds() - buffer_time_interjection > 7)
	{
		random_word = rand() % 10;
		buffer_time_interjection = time_alive.getElapsedTime().asSeconds();
		score->setFillColor(sf::Color::White);
	}
}

void GameManager::setTextElements()
{
	int r = rand() % 220 + 120;
	int g = rand() % 220 + 120;
	int b = rand() % 220 + 120;

	if (!font->loadFromFile("../assets/SCOREBOARD.ttf") || !font_interjection.loadFromFile("../assets/ARCADE.ttf"))
	{
		std::cout << "ERROR WITH FONT INITIALIZATION" << std::endl;
	}

	score->setFont(*font);
	score->setCharacterSize(50);
	score->setFillColor(sf::Color::White);
	score->setPosition(475, 10);

	interjection->setFont(font_interjection);
	interjection->setCharacterSize(40);
	interjection->setFillColor(sf::Color(r,g,b,255));
	interjection->setPosition(490, 70);
}

void GameManager::setInterjectionVec()
{
	interjection_vec = { " AMAZING ! ", " MAIS NON ! ", " WOW ! ", " WHAT A PLAYER ! ", " SUCH BEAUTIFUL ! ",
	                     " BETTER THAN A VECTOR ! "," RASTERIZER MASTER ! ", " DEFINETLY A GOD ! ",  " ONLY SKILLS ! "," GENIUS ! "};
	random_word = rand() % 10;
}

void GameManager::addingEnemyToList()
{
	Enemy enemy = Enemy(mousePos);
	list_enemies.push_back(enemy);
}

void GameManager::increasedListDifficulty()
{
	while (iterator_enemies != list_enemies.end())
	{
		iterator_enemies->increaseDifficulty();
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
}

void GameManager::renderListElements()
{
	while (iterator_enemies != list_enemies.end())
	{
		window->draw(iterator_enemies->getRectangleShape());
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
}

void GameManager::moveListElements()
{
	while (iterator_enemies != list_enemies.end())
	{
		iterator_enemies->move(sf::Vector2f(mousePos.X() - 25, mousePos.Y() - 25));
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
}

bool GameManager::isAnyoneMakeCollision()
{
	while (iterator_enemies != list_enemies.end())
	{
		if (blockingcube != nullptr && iterator_enemies->getRectangleShape().getGlobalBounds().intersects(blockingcube->getRectangleShape().getGlobalBounds()))
		{
			iterator_enemies->getRectangleShape().setSize(Vector2D<float>().toSfVector());
			blockingcube = nullptr;
			malus += 4;
		}
		if (iterator_enemies->getRectangleShape().getGlobalBounds().intersects(player->getRectangleShape().getGlobalBounds()))
		{
			iterator_enemies = list_enemies.begin();
			return true;
		}
		iterator_enemies++;
	}
	iterator_enemies = list_enemies.begin();
	return false;
}
