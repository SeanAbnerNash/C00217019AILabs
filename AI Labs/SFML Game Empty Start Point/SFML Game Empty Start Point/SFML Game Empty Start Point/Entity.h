#pragma once
//@Author Sean Nash de Andrade
//@Login C00217019
//Lab 1-3 AI.
//Implemented Seek, Flee, Wander, Arrive, Pursue & Player Behaviours
//Implemented Vision Cones
//Time Taken: 5 Hours.

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>      
#include <math.h>
#define M_PI           3.14159265358979323846  /* pi */
class Entity
{
public:
	Entity();
	Entity(sf::Sprite &t_entitySprite, sf::Vector2f t_position, float t_angle);
	~Entity();
	void update();
	void update(sf::Vector2f t_targetPosition);
	void render(sf::RenderWindow& t_window);
	void adjustVelocity(float t_scalar);
	sf::Vector2f getVelocity();
	void adjustRotation(float t_angle);

	void setUpEntity(sf::Sprite& t_entitySprite, sf::Vector2f t_position, float t_angle);
	void setMaxSpeed(sf::Vector2f t_speed);
	void setMinSpeed(sf::Vector2f t_speed);
	void setMode(int t_mode);
	void setUpText(sf::Font &t_font);
	void setTargetVelocity(sf::Vector2f t_velocity);

	sf::Vector2f getPosition();



private:
	void throttleSpeed();
	void updateText();
	void updateVision();
	float magnitude(sf::Vector2f);
	bool withinVision();
	float getNewOrientation(sf::Vector2f t_velociy);
	void screenLoop();
	void screenLock();
	void behaviourAI();
	void seek();
	void player();
	void flee();
	void meander();
	void arrive();
	void pursue();
	float distance(sf::Vector2f t_vector, sf::Vector2f left_vector);
	float angleBetween(sf::Vector2f t_vector, sf::Vector2f left_vector);

	sf::Vector2f m_position;
	
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxSpeed{ sf::Vector2f(-31.25,-31.25) };
	sf::Vector2f m_minSpeed{ sf::Vector2f(-31.25,-31.25) };
	float m_angle;
	float m_maxRotation = 2; //3 degrees either side shift per frame.
	float m_timeToTarget = 0.5*60;
	float m_radius = 100;
	float m_timePrediction = 1;
	float m_visionDistance = 120.0f;
	float m_visionDegrees = 30.0f;//30 degrees off either side of the centre for a 60ft range.
	sf::Vector2f m_target;
	sf::Vector2f m_targetVelocity;
	int m_mode = { 0 }; //0 = Base Player, 1 = Seek, 2 = flee, 3 = Wander, 4 = Arrive

	sf::Texture m_entityTexture; 
	sf::Sprite m_entitySprite; 

	sf::Text m_name;
	sf::Font m_font;

	sf::VertexArray m_visionCone{ sf::Triangles, 3 };
	sf::Color m_coneColour;
	sf::Color m_neutralColour = sf::Color(255,255,150,120);
	sf::Color m_alertColour = sf::Color(255, 0, 0, 120);



};

