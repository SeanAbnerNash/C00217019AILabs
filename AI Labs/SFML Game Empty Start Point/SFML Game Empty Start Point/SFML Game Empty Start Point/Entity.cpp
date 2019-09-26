#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(sf::Sprite& t_entitySprite, sf::Vector2f t_position,float t_angle)
{
	m_entitySprite = t_entitySprite;
	m_position = t_position;
	m_angle = t_angle;
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
}

Entity::~Entity()
{
}

void Entity::update()
{
	throttleSpeed();
	
	m_position += m_velocity;
	m_entitySprite.setPosition(m_position);

	if (m_position.x > 1600)
	{
		m_position.x = 1;
	}
	if (m_position.x < 0)
	{
		m_position.x = 1598;
	}

	if (m_position.y > 898)
	{
		m_position.y = 1;
	}
	if (m_position.y < 0)
	{
		m_position.y = 898;
	}
}

void Entity::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_entitySprite);
}

void Entity::adjustVelocity(sf::Vector2f t_velocity)
{

}

void Entity::adjustVelocity(float t_scalar)
{
	float velocityScalar = t_scalar;
	sf::Vector2f velocityAdjustment = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	velocityAdjustment *= velocityScalar;
	m_velocity += velocityAdjustment;
	throttleSpeed();
}

void Entity::adjustRotation(float t_angle)
{
	m_angle += t_angle;
	float velocityScalar = magnitude(m_velocity);
	std::cout << velocityScalar << " Vel Scalar" << std::endl;
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	m_velocity *= velocityScalar;
	m_entitySprite.setRotation(m_angle);
}

void Entity::setUpEntity(sf::Sprite& t_entitySprite, sf::Vector2f t_position, float t_angle)
{
	m_entitySprite = t_entitySprite;
	m_position = t_position;
	m_angle = t_angle;
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	m_entitySprite.setRotation(m_angle);
	
}

void Entity::setMaxSpeed(sf::Vector2f t_speed)
{
	m_maxSpeed = t_speed;
}
void Entity::setMinSpeed(sf::Vector2f t_speed)
{
	m_minSpeed = t_speed;
}

void Entity::throttleSpeed()
{
	if (m_maxSpeed != sf::Vector2f(-31.25, -31.25))
	{
		if (m_velocity.x > m_maxSpeed.x)
		{
			m_velocity.x = m_maxSpeed.x;
			
		}
		if (m_velocity.y > m_maxSpeed.y)
		{
			m_velocity.y = m_maxSpeed.y;
			
		}
	}
	if (m_minSpeed != sf::Vector2f(-31.25, -31.25))
	{
		std::cout << "HERE";
		if (m_velocity.x < m_minSpeed.x)
		{
			m_velocity.x = m_minSpeed.x;
			
		}
		if (m_velocity.y < m_minSpeed.y)
		{
			m_velocity.y = m_minSpeed.y;
			
		}
	}
}

float Entity::magnitude(sf::Vector2f t_vector)
{
	return sqrt((t_vector.x* t_vector.x) + (t_vector.y * t_vector.y));
}
