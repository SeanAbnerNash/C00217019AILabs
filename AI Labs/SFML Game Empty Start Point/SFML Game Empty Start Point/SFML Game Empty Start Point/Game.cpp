// author Peter Lowe

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1600, 900, 32 }, "SFML Game" },
	m_exitGame{false}, //when true game will exit
	Player(),
	NPC()
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	Player.setUpEntity(m_megaManSprite, m_megaManSprite.getPosition(), rand() % 360 + 1);
	Player.setMaxSpeed(sf::Vector2f(10, 10));
	Player.setMinSpeed(sf::Vector2f(-10, -10));
	NPC.setUpEntity(m_meToolSprite, m_meToolSprite.getPosition(), rand() % 360 + 1);
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Player.adjustVelocity(0.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Player.adjustVelocity(-0.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Player.adjustRotation(0.05);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Player.adjustRotation(-0.05);
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	Player.update();
	NPC.update();

}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	//m_window.draw(m_welcomeMessage);
	Player.render(m_window);
	NPC.render(m_window);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_megaManTexture.loadFromFile("ASSETS\\IMAGES\\MegaManSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	if (!m_meToolTexture.loadFromFile("ASSETS\\IMAGES\\MetoolSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_megaManSprite.setTexture(m_megaManTexture);
	m_megaManSprite.setOrigin(m_megaManSprite.getTexture()->getSize().x/2, m_megaManSprite.getTexture()->getSize().y/2);
	float xScale = m_megaManSprite.getTexture()->getSize().x;// 1;
	xScale = 100/ xScale;
	float yScale = m_megaManSprite.getTexture()->getSize().y;// 1;
	yScale = 100/ yScale;
	
	m_megaManSprite.setScale(xScale, yScale);
	m_megaManSprite.setPosition(100.0f, 180.0f);


	m_meToolSprite.setTexture(m_meToolTexture);
	xScale = m_meToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_meToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_meToolSprite.setScale(xScale, yScale);
	m_meToolSprite.setPosition(300.0f, 220.0f);
}
