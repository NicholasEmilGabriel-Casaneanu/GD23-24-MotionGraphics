/// <summary>
/// simple game loop for SFML[2.5.1]
/// 
/// @author Peter Lowe
/// @date May 2019
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


//#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
//int main()
//{
//	Game game;
//	game.run();
//
//	return 1; // success
//}

// platform game.....
// Author :Noel O' Hara

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;


	sf::RectangleShape playerShape;
	sf::Sprite playerSprite;

	sf::Texture playerTexture;
	int frameWidth = 299, frameHeight = 275, frameCounter = 0, currentFrame = 0;

	float velocityX = 0, velocityY = 0, gravity = 0.3;




	static const int numRows = 20;
	static const int numCols = 60;
	int levelData[numRows][numCols] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,1,1,1,0,1,1,1,1,0,0,1,0,1,0,1,0,0,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,2,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,1,1,0,0,0,2,0,0,0,0,0,1,0,0,0,0,1,2,0,1,0,0,3,0,0,0,0,0,1,0,0,2,2,0,0,0,0,0,1,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,3,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, };

	sf::RectangleShape level[numRows][numCols];
	sf::Texture brick1;
	sf::Texture brick2;
	sf::Texture brick3;
	sf::Texture* brick1ptr;
	sf::Texture* brick2ptr;
	sf::Texture* brick3ptr;
	sf::Texture spike1;
	sf::Texture spike2;
	sf::Texture spike3;
	sf::Texture* spike1ptr;
	sf::Texture* spike2ptr;
	sf::Texture* spike3ptr;
	sf::Texture bee1;
	sf::Texture* bee1ptr;

	Game()
	{
		window.create(sf::VideoMode(800, 600), "Endless Runner Game");
	}
	void init()
	{

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(40, 40));
		playerShape.setPosition(160, 500);

		if (!brick1.loadFromFile("ASSETS/IMAGES/brick1.png"))
			std::cout << "horse";
		if (!brick2.loadFromFile("ASSETS/IMAGES/brick2.png"))
			std::cout << "horse";
		if (!brick3.loadFromFile("ASSETS/IMAGES/brick3.png"))
			std::cout << "horse";
		if (!spike1.loadFromFile("ASSETS/IMAGES/spike1.png"))
			std::cout << "horse";
		if (!spike2.loadFromFile("ASSETS/IMAGES/spike2.png"))
			std::cout << "horse";
		if (!spike3.loadFromFile("ASSETS/IMAGES/spike3.png"))
			std::cout << "horse";
		if (!bee1.loadFromFile("ASSETS/IMAGES/bee1.png"))
			std::cout << "horse";

		brick1ptr = &brick1;
		brick2ptr = &brick2;
		brick3ptr = &brick3;

		spike1ptr = &spike1;
		spike2ptr = &spike2;
		spike3ptr = &spike3;

		bee1ptr = &bee1;

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{

				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					//level[row][col].setFillColor(sf::Color::Red);
					int roll = rand() % 3;
					switch (roll) {
					case 0:
						level[row][col].setTexture(brick1ptr);
						break;
					case 1:
						level[row][col].setTexture(brick2ptr);
						break;
					case 2:
						level[row][col].setTexture(brick3ptr);
						break;
					default:
						break;
					}
					
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					//level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					//level[row][col].setFillColor(sf::Color::Blue);

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					//level[row][col].setFillColor(sf::Color::Yellow);

				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					//level[row][col].setFillColor(sf::Color::Green);

				}

			}
			std::cout << std::endl;
		}

		if (!playerTexture.loadFromFile("ASSETS/IMAGES/Untitled2.png"))
			std::cout << "horse";

		playerSprite.setTexture(playerTexture);
		currentFrame = 0;
		frameCounter = 0;
		playerSprite.setTextureRect(sf::IntRect(frameWidth * (currentFrame % 4), frameHeight * (currentFrame / 4), frameWidth, frameHeight));
		playerSprite.setScale(0.14, 0.15);

	}
	void run()
	{
		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock;
		clock.restart();
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			timeSinceLastUpdate += clock.restart();
			if (timeSinceLastUpdate > timePerFrame)
			{
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						level[row][col].move(-3.7, 0);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
				{
					velocityY = -11.8;
				}
				velocityY = velocityY + gravity;
				playerShape.move(0, velocityY);
				gravity = 0.6;
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (velocityY >= 0)
						{
							if (levelData[row][col] == 1)
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocityY = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										break;
									}
									else {
										init();
									}
								}
							}
						}
						if (velocityY < 0)
						{
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
								}
							}
						}
						if (levelData[row][col] == 2)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 3)
						{
							level[row][col].move(-10.0f, 0.0f);
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 4)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								window.close();
							}
						}
					}
				}
				if (playerShape.getPosition().y > 600)
				{
					init();
				}
				playerSprite.setPosition(playerShape.getPosition());
				animate();
				window.clear();
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);
					}
				}
				window.draw(playerShape);
				window.draw(playerSprite);
				window.display();
				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}

	void animate() {
		frameCounter++;
		if (frameCounter >= 6)
		{
			frameCounter = 0;
			currentFrame++;
			std::cout << "The current frame is " << currentFrame << "\n";
			if (currentFrame >= 8)
			{
				currentFrame = 0;
				std::cout << "The current frame is " << currentFrame << "\n";
			}
			playerSprite.setTextureRect(sf::IntRect(0 + (frameWidth * (currentFrame % 4)), 0 + (frameHeight * (currentFrame / 4)), frameWidth, frameHeight));
			for (int row = 0; row < numRows; row++)
			{
				for (int col = 0; col < numCols; col++)
				{

					if (levelData[row][col] == 1)
					{
						//level[row][col].setFillColor(sf::Color::Red);
						int roll = rand() % 3;
						switch (roll) {
						case 0:
							level[row][col].setTexture(brick1ptr);
							break;
						case 1:
							level[row][col].setTexture(brick2ptr);
							break;
						case 2:
							level[row][col].setTexture(brick3ptr);
							break;
						default:
							break;
						}

					}
					if (levelData[row][col] == 0)
					{
						level[row][col].setFillColor(sf::Color::Black);
					}
					if (levelData[row][col] == 2)
					{
						//level[row][col].setFillColor(sf::Color::Blue);
						int roll = rand() % 3;
						switch (roll) {
						case 0:
							level[row][col].setTexture(spike1ptr);
							break;
						case 1:
							level[row][col].setTexture(spike2ptr);
							break;
						case 2:
							level[row][col].setTexture(spike3ptr);
							break;
						default:
							break;
						}

					}
					if (levelData[row][col] == 3)
					{
						//level[row][col].setFillColor(sf::Color::Yellow);
						level[row][col].setTexture(bee1ptr);
					}
					if (levelData[row][col] == 4)
					{
						level[row][col].setFillColor(sf::Color::Green);
					}

				}
				std::cout << std::endl;
			}
		}

		if (velocityY > 0 || velocityY < 0)
			playerSprite.setTextureRect(sf::IntRect(0 + (frameWidth * (1 % 4)), 0 + (frameHeight * (1 / 4)), frameWidth, frameHeight));

	}
};

int main()
{
	Game game;

	game.init();
	game.run();

	return 0;
}
