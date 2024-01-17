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

	m_isPaused = true;

	m_player.setRadius(20.0f);
	m_player.setOrigin(20.0f, 20.0f);
	m_player.setFillColor(sf::Color::Yellow);
	m_player.setPosition(50.0f, 100.0f);

	m_enemy.setRadius(20.0f);
	m_enemy.setOrigin(20.0f,20.0f);
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setPosition(750.0f, 100.0f);
	m_isEnemyAlive = true;

	//ROLL FOR BIGBIT
	m_bigBitIndex = rand() % 20;
	for (int i = 0; i < 20; i++)
	{
		m_bitArray[i].setRadius(5.0f);
		m_bitArray[i].setOrigin(5.0f, 5.0f);
		m_bitArray[i].setFillColor(sf::Color::White);
		m_bitArray[i].setPosition(20.0f + (i * 40), 100.0f);
		if (i == m_bigBitIndex)
		{
			m_bitArray[i].setRadius(10.0f);
			m_bitArray[i].setOrigin(10.0f, 10.0f);
		}
	}
	m_bitsCount = 20;

	m_score = 0;
	m_scoreText.setFont(m_arialFont);
	m_scoreText.setPosition(20, 20);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setFillColor(sf::Color::White);

	m_hiScoreText.setFont(m_arialFont);
	m_hiScoreText.setPosition(660, 20);
	m_hiScoreText.setCharacterSize(24);
	m_hiScoreText.setFillColor(sf::Color::White);


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
			//std::cout << "key_left\n";
			//m_isFacingRight = false;
			break;
		case sf::Keyboard::Right:
			//std::cout << "key_right\n";
			//m_isFacingRight = true;
			break;
		case sf::Keyboard::Space:
			std::cout << "Spacebar Pressed\n";
			if(!m_isSpacePressed)
			{
				if (m_isPaused)
				{
					m_isPaused = false;
				}
				else
				{
					m_isFacingRight = !m_isFacingRight;
				}
				m_isSpacePressed = true;
			}
			break;
		default:
			break;
		}
	}

	if (sf::Event::KeyReleased == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
			std::cout << "Spacebar Released\n";
			if(m_isSpacePressed)
				m_isSpacePressed = false;
			break;
		default:
			break;
		}
	}
}

void Game::movePlayer()
{
	sf::Vector2f currentPosition = m_player.getPosition();
	if (currentPosition.x <= -40)
		currentPosition.x = 840;
	else if (currentPosition.x >= 840)
		currentPosition.x = -40;
	if (m_isFacingRight)
	{
		m_player.setPosition(currentPosition.x + 1.5f, currentPosition.y);
	}
	else
	{
		m_player.setPosition(currentPosition.x - 1.5f, currentPosition.y);
	}
}

void Game::moveEnemy()
{
	sf::Vector2f currentPosition = m_enemy.getPosition();
	if(!m_isPoweredUp)
	{
		if (m_player.getPosition().x > currentPosition.x)
		{
			if ((currentPosition.x + 1.0f) < 780.0f)
			m_enemy.setPosition(currentPosition.x + 1.0f, currentPosition.y);
		}
		else
		{
			if ((currentPosition.x + 1.0f) > 20.0f)
			m_enemy.setPosition(currentPosition.x - 1.0f, currentPosition.y);
		}
	}
	else
	{
		if (m_player.getPosition().x > currentPosition.x)
		{
			if ((currentPosition.x + 1.0f) > 20.0f)
			m_enemy.setPosition(currentPosition.x - 1.0f, currentPosition.y);
		}
		else
		{
			if ((currentPosition.x + 1.0f) < 780.0f)
			m_enemy.setPosition(currentPosition.x + 1.0f, currentPosition.y);
		}
	}
}

bool Game::checkCollision(sf::CircleShape t_circleOne, sf::CircleShape t_CircleTwo)
{
	float distance = std::abs(t_circleOne.getPosition().x - t_CircleTwo.getPosition().x);
	float radiusSum = t_circleOne.getRadius() + t_CircleTwo.getRadius();
	std::cout << "d:" << distance << " r:" << radiusSum << "\n";
	if (radiusSum >= distance)
	{
		return true;
	}
	else
		return false;
}

void Game::spawnEnemy()
{
	if (m_player.getPosition().x >= 400)
	{
		m_enemy.setPosition(50.0f, 100.0f);
	}
	else
		m_enemy.setPosition(750.0f, 100.0f);
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	if(!m_isPaused)
	{
		std::string updateScore = "Score: " + std::to_string(m_score);
		m_scoreText.setString(updateScore);
		if (m_score > m_hiScore)
			m_hiScore = m_score;
		std::string updateHiScore = "HighScore: " + std::to_string(m_hiScore);
		m_hiScoreText.setString(updateHiScore);

		movePlayer();
		if (m_isEnemyAlive)
			moveEnemy();
		for (int i = 0; i < 20; i++)
		{
			if (checkCollision(m_player, m_bitArray[i]))
			{
				m_bitArray[i].setPosition(-100.0f, -100.0f);
				if (i == m_bigBitIndex)
				{
					m_powerTimer = 300;
					m_isPoweredUp = true;
				}
				m_score += 10;
				m_bitsCount--;
			}
		}
		if (m_bitsCount <= 0)
		{
			m_bigBitIndex = rand() % 20;
			for (int i = 0; i < 20; i++)
			{
				m_bitArray[i].setRadius(5.0f);
				m_bitArray[i].setOrigin(5.0f, 5.0f);
				m_bitArray[i].setFillColor(sf::Color::White);
				m_bitArray[i].setPosition(20.0f + (i * 40), 100.0f);
				if (i == m_bigBitIndex)
				{
					m_bitArray[i].setRadius(10.0f);
					m_bitArray[i].setOrigin(10.0f, 10.0f);
				}
			}

			m_bitsCount = 20;
		}
		if (checkCollision(m_player, m_enemy))
		{
			if (m_isPoweredUp)
			{
				m_isEnemyAlive = false;
				m_enemy.setPosition(-200.0f, -200.0f);
				m_enemyTimer = 300;
			}
			else
			{
				init();
			}
		}
		if (m_isPoweredUp) m_player.setFillColor(sf::Color::Green);
		else m_player.setFillColor(sf::Color::Yellow);

		if (m_powerTimer > 0)
			m_powerTimer--;
		if (m_powerTimer < 0)
			m_powerTimer = 0;
		if (m_powerTimer == 0)
		{
			m_player.setFillColor(sf::Color::Yellow);
			m_isPoweredUp = false;
		}

		if (m_enemyTimer > 0)
			m_enemyTimer--;
		if (m_enemyTimer < 0)
			m_enemyTimer = 0;
		if (m_enemyTimer == 0 && !m_isEnemyAlive)
		{
			spawnEnemy();
			m_isEnemyAlive = true;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	m_window.draw(m_player);
	for (int i = 0; i < 20; i++)
	{
		m_window.draw(m_bitArray[i]);
	}
	m_window.draw(m_enemy);
	m_window.draw(m_scoreText);
	m_window.draw(m_hiScoreText);
#ifdef TEST_FPS
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
#endif
	m_window.display();
}





