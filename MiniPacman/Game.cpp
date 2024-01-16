#include "Game.h"
#include <iostream>

// Our target FPS
static double const FPS{ 60.0f };

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
{
	init();

}

////////////////////////////////////////////////////////////
void Game::init()
{
	// Really only necessary is our target FPS is greater than 60.
	m_window.setVerticalSyncEnabled(true);

	if (!m_arialFont.loadFromFile("BebasNeue.otf"))
	{
		std::cout << "Error loading font file";
	}

	m_player.setRadius(20.0f);
	m_player.setOrigin(20.0f, 20.0f);
	m_player.setFillColor(sf::Color::Yellow);
	m_player.setPosition(50.0f, 100.0f);

	for (int i = 0; i < 30; i++)
	{
		m_bitArray[i].setRadius(5.0f);
		m_bitArray[i].setOrigin(5.0f, 5.0f);
		m_bitArray[i].setFillColor(sf::Color::White);
		m_bitArray[i].setPosition(100.0f + (i * 20), 100.0f);
	}


#ifdef TEST_FPS
	x_updateFPS.setFont(m_arialFont);
	x_updateFPS.setPosition(20, 300);
	x_updateFPS.setCharacterSize(24);
	x_updateFPS.setFillColor(sf::Color::White);
	x_drawFPS.setFont(m_arialFont);
	x_drawFPS.setPosition(20, 350);
	x_drawFPS.setCharacterSize(24);
	x_drawFPS.setFillColor(sf::Color::White);
#endif
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asMilliseconds()); //60 fps
#ifdef TEST_FPS
			x_secondTime += timePerFrame;
			x_updateFrameCount++;
			if (x_secondTime.asSeconds() > 1)
			{
				std::string updatesPS = "UPS " + std::to_string(x_updateFrameCount - 1);
				x_updateFPS.setString(updatesPS);
				std::string drawsPS = "DPS " + std::to_string(x_drawFrameCount);
				x_drawFPS.setString(drawsPS);
				x_updateFrameCount = 0;
				x_drawFrameCount = 0;
				x_secondTime = sf::Time::Zero;
			}
#endif
		}
		render(); // as many as possible
#ifdef TEST_FPS
		x_drawFrameCount++;
#endif
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		case sf::Keyboard::Up:
			// Up key was pressed...
			break;
		case sf::Keyboard::Left:
			std::cout << "key_left\n";
			m_isFacingRight = false;
			break;
		case sf::Keyboard::Right:
			std::cout << "key_right\n";
			m_isFacingRight = true;
			break;
		default:
			break;
		}
	}
}

void Game::movePlayer()
{
	sf::Vector2f currentPosition = m_player.getPosition();
	if (m_isFacingRight)
	{
		m_player.setPosition(currentPosition.x + 1, currentPosition.y);
	}
	else
	{
		m_player.setPosition(currentPosition.x - 1, currentPosition.y);
	}
}

bool Game::checkCollision(sf::CircleShape t_circleOne, sf::CircleShape t_CircleTwo)
{
	float distance = std::abs(t_circleOne.getPosition().x - t_CircleTwo.getPosition().x);
	float radiusSum = t_circleOne.getRadius() + t_CircleTwo.getRadius();
	std::cout << "d:" << distance << " r:" << radiusSum << "\n";
	if (radiusSum >= distance)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	movePlayer();
	for (int i = 0; i < 30; i++)
	{
		if (checkCollision(m_player, m_bitArray[i]))
			m_bitArray[i].setPosition(-50.0f, -50.0f);
	}
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	m_window.draw(m_player);
	for (int i = 0; i < 30; i++)
	{
		m_window.draw(m_bitArray[i]);
	}
#ifdef TEST_FPS
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
#endif
	m_window.display();
}





