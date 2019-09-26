#pragma once
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#define M_PI           3.14159265358979323846  /* pi */
class Entity
{
public:
	Entity();
	Entity(sf::Sprite &t_entitySprite, sf::Vector2f t_position, float t_angle);
	~Entity();
	void update();
	void render(sf::RenderWindow& t_window);
	void adjustVelocity(sf::Vector2f t_velocity);
	void adjustVelocity(float t_scalar);
	void adjustRotation(float t_angle);

	void setUpEntity(sf::Sprite& t_entitySprite, sf::Vector2f t_position, float t_angle);
	void setMaxSpeed(sf::Vector2f t_speed);
	void setMinSpeed(sf::Vector2f t_speed);


private:
	void throttleSpeed();
	float magnitude(sf::Vector2f);
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxSpeed{ sf::Vector2f(-31.25,-31.25) };
	sf::Vector2f m_minSpeed{ sf::Vector2f(-31.25,-31.25) };

	float m_angle;
	//angle rotation

	sf::Texture m_entityTexture; 
	sf::Sprite m_entitySprite; // sprite used for sfml logo




};

