// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_megaManTexture; 
	sf::Sprite m_megaManSprite;

	sf::Texture m_meToolTexture; 
	sf::Sprite m_meToolSprite;

	sf::Texture m_fleeToolTexture;
	sf::Sprite m_fleeToolSprite;

	sf::Texture m_wanderToolTexture;
	sf::Sprite m_wanderToolSprite;

	sf::Texture m_arriveFastToolTexture;
	sf::Sprite m_arriveFastToolSprite;

	sf::Texture m_arriveSlowToolTexture;
	sf::Sprite m_arriveSlowToolSprite;

	sf::Texture m_pursueToolTexture;
	sf::Sprite m_pursueToolSprite;

	Entity Player;
	Entity seek_NPC;
	Entity flee_NPC;
	Entity wander_NPC;
	Entity arriveFast_NPC;
	Entity arriveSlow_NPC;
	Entity pursue_NPC;


	bool m_exitGame; // control exiting game

};

#endif // !GAME

