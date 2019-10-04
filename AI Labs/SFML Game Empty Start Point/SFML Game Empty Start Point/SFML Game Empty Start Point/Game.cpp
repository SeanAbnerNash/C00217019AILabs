//@Author Sean Nash de Andrade
//@Login C00217019
//Lab 1-3 AI.
//Implemented Seek, Flee, Wander, Arrive, Pursue & Player Behaviours
//Implemented Vision Cones
//Time Taken: 5 Hours.

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1600, 900, 32 }, "SFML Game" },
	m_exitGame{false}, //when true game will exit
	Player(),
	seek_NPC()
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

	//Entities Setup
	Player.setUpEntity(m_megaManSprite, m_megaManSprite.getPosition(), rand() % 360 + 1);
	Player.setMaxSpeed(sf::Vector2f(10, 10));
	Player.setMinSpeed(sf::Vector2f(-10, -10));
	Player.setUpText(m_ArialBlackfont);

	seek_NPC.setUpEntity(m_meToolSprite, m_meToolSprite.getPosition(), 90);
	seek_NPC.setMaxSpeed(sf::Vector2f(5, 5));
	seek_NPC.setUpText(m_ArialBlackfont);
	seek_NPC.setMode(1);

	flee_NPC.setUpEntity(m_fleeToolSprite, m_fleeToolSprite.getPosition(), 90);
	flee_NPC.setMaxSpeed(sf::Vector2f(2, 2));
	flee_NPC.setUpText(m_ArialBlackfont);
	flee_NPC.setMode(2);

	wander_NPC.setUpEntity(m_wanderToolSprite, m_wanderToolSprite.getPosition(), rand() % 360 + 1);
	wander_NPC.setMaxSpeed(sf::Vector2f(2, 2));
	wander_NPC.setUpText(m_ArialBlackfont);
	wander_NPC.setMode(3);

	arriveFast_NPC.setUpEntity(m_arriveFastToolSprite, m_arriveFastToolSprite.getPosition(), rand() % 360 + 1);
	arriveFast_NPC.setMaxSpeed(sf::Vector2f(50, 50));
	arriveFast_NPC.setUpText(m_ArialBlackfont);
	arriveFast_NPC.setMode(4);

	arriveSlow_NPC.setUpEntity(m_arriveSlowToolSprite, m_arriveSlowToolSprite.getPosition(), rand() % 360 + 1);
	arriveSlow_NPC.setMaxSpeed(sf::Vector2f(10, 10));
	arriveSlow_NPC.setUpText(m_ArialBlackfont);
	arriveSlow_NPC.setMode(4);

	pursue_NPC.setUpEntity(m_pursueToolSprite, m_pursueToolSprite.getPosition(), rand() % 360 + 1);
	pursue_NPC.setMaxSpeed(sf::Vector2f(15, 15));
	pursue_NPC.setUpText(m_ArialBlackfont);
	pursue_NPC.setMode(5);

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

	//Key Control Inputs
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
	seek_NPC.update(Player.getPosition());
	flee_NPC.update(Player.getPosition());
	arriveFast_NPC.update(Player.getPosition());
	arriveSlow_NPC.update(Player.getPosition());
	wander_NPC.update();
	pursue_NPC.setTargetVelocity(Player.getVelocity());
	pursue_NPC.update(Player.getPosition());


}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	//m_window.draw(m_welcomeMessage);
	Player.render(m_window);
	seek_NPC.render(m_window);
	flee_NPC.render(m_window);
	wander_NPC.render(m_window);
	arriveFast_NPC.render(m_window);
	arriveSlow_NPC.render(m_window);
	pursue_NPC.render(m_window);
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
	if (!m_fleeToolTexture.loadFromFile("ASSETS\\IMAGES\\FleetoolSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	if (!m_wanderToolTexture.loadFromFile("ASSETS\\IMAGES\\WandertoolSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	if (!m_arriveFastToolTexture.loadFromFile("ASSETS\\IMAGES\\FastoolSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	if (!m_arriveSlowToolTexture.loadFromFile("ASSETS\\IMAGES\\SlowtoolSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	if (!m_pursueToolTexture.loadFromFile("ASSETS\\IMAGES\\PursuetoolSprite.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	//Sprite Setup
	m_megaManSprite.setTexture(m_megaManTexture);
	m_megaManSprite.setOrigin(m_megaManSprite.getTexture()->getSize().x/2, m_megaManSprite.getTexture()->getSize().y/2);
	float xScale = m_megaManSprite.getTexture()->getSize().x;// 1;
	xScale = 100/ xScale;
	float yScale = m_megaManSprite.getTexture()->getSize().y;// 1;
	yScale = 100/ yScale;
	
	m_megaManSprite.setScale(xScale, yScale);
	m_megaManSprite.setPosition(100.0f, 180.0f);


	m_meToolSprite.setTexture(m_meToolTexture);
	m_meToolSprite.setOrigin(m_meToolSprite.getTexture()->getSize().x / 2, m_meToolSprite.getTexture()->getSize().y / 2);
	xScale = m_meToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_meToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_meToolSprite.setScale(xScale, yScale);
	m_meToolSprite.setPosition(300.0f, 220.0f);

	m_fleeToolSprite.setTexture(m_fleeToolTexture);
	m_fleeToolSprite.setOrigin(m_fleeToolSprite.getTexture()->getSize().x / 2, m_fleeToolSprite.getTexture()->getSize().y / 2);
	xScale = m_fleeToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_fleeToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_fleeToolSprite.setScale(xScale, yScale);
	m_fleeToolSprite.setPosition(600.0f, 220.0f);

	m_wanderToolSprite.setTexture(m_wanderToolTexture);
	m_wanderToolSprite.setOrigin(m_wanderToolSprite.getTexture()->getSize().x / 2, m_wanderToolSprite.getTexture()->getSize().y / 2);
	xScale = m_wanderToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_wanderToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_wanderToolSprite.setScale(xScale, yScale);
	m_wanderToolSprite.setPosition(300.0f, 520.0f);


	m_arriveFastToolSprite.setTexture(m_arriveFastToolTexture);
	m_arriveFastToolSprite.setOrigin(m_arriveFastToolSprite.getTexture()->getSize().x / 2, m_arriveFastToolSprite.getTexture()->getSize().y / 2);
	xScale = m_arriveFastToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_arriveFastToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_arriveFastToolSprite.setScale(xScale, yScale);
	m_arriveFastToolSprite.setPosition(300.0f, 520.0f);

	m_arriveSlowToolSprite.setTexture(m_arriveSlowToolTexture);
	m_arriveSlowToolSprite.setOrigin(m_arriveSlowToolSprite.getTexture()->getSize().x / 2, m_arriveSlowToolSprite.getTexture()->getSize().y / 2);
	xScale = m_arriveSlowToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_arriveSlowToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_arriveSlowToolSprite.setScale(xScale, yScale);
	m_arriveSlowToolSprite.setPosition(300.0f, 520.0f);

	m_pursueToolSprite.setTexture(m_pursueToolTexture);
	m_pursueToolSprite.setOrigin(m_pursueToolSprite.getTexture()->getSize().x / 2, m_pursueToolSprite.getTexture()->getSize().y / 2);
	xScale = m_pursueToolSprite.getTexture()->getSize().x;// 1;
	xScale = 60 / xScale;
	yScale = m_pursueToolSprite.getTexture()->getSize().y;// 1;
	yScale = 60 / yScale;

	m_pursueToolSprite.setScale(xScale, yScale);
	m_pursueToolSprite.setPosition(600.0f, 520.0f);
}
