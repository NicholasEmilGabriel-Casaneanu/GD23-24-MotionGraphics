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
	m_player.setFillColor(sf::Color::Cyan);
	m_playerPos.x = m_window.getSize().x / 2.0f;
	m_playerPos.y = m_window.getSize().y - 50.0f;
	m_player.setPosition(m_playerPos);

	m_isLeftPressed = false;
	m_isRightPressed = false;

	generateWall();

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
		case sf::Keyboard::Left:
			m_isLeftPressed = true;
			break;
		case sf::Keyboard::Right:
			m_isRightPressed = true;
			break;
		default:
			break;
		}
	}
	if (sf::Event::KeyReleased == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			m_isLeftPressed = false;
			break;
		case sf::Keyboard::Right:
			m_isRightPressed = false;
			break;
		default:
			break;
		}
	}
}

void Game::moveLeft()
{
	m_playerPos.x -= 5;
	m_player.setPosition(m_playerPos);
}

void Game::moveRight()
{
	m_playerPos.x += 5;
	m_player.setPosition(m_playerPos);
}

void Game::generateWall()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_wallArray[(i * 10) + j] == 1)
			{
				m_shapeArrayOne[i][j].setPosition(CHUNK_WIDTH * j, -i * CHUNK_HEIGHT);
				m_shapeArrayOne[i][j].setSize(sf::Vector2f(CHUNK_WIDTH, CHUNK_HEIGHT));
				m_shapeArrayOne[i][j].setFillColor(sf::Color::Magenta);
				std::cout << i << "  " << j << "\n";
			}
			if (i == 9 && j == 9)
			{
				float firstY = -i * CHUNK_HEIGHT - CHUNK_HEIGHT;
			}
		}
	}
}

void Game::updateWall()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_shapeArrayOne[i][j].setPosition(m_shapeArrayOne[i][j].getPosition().x, m_shapeArrayOne[i][j].getPosition().y + 5.f);
			firstY = m_shapeArrayOne[i][j].getPosition().y;
		}
	}
	std::cout << firstY << "\n";
	if (firstY >= ScreenSize::s_height)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				m_shapeArrayOne[i][j].setPosition(-50.0f, -50.0f);

			}
		}
		generateWall();
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	if (m_isLeftPressed)
		moveLeft();
	if (m_isRightPressed)
		moveRight();

	updateWall();
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
#ifdef TEST_FPS
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
	m_window.draw(m_player);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_window.draw(m_shapeArrayOne[i][j]);
		}
	}
#endif
	m_window.display();
}





