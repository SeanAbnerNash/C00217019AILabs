#include "Entity.h"

Entity::Entity()
{
	m_visionCone[0].position = sf::Vector2f(-10.f, -10.f);
	m_visionCone[1].position = sf::Vector2f(-100.f, -10.f);
	m_visionCone[2].position = sf::Vector2f(-100.f, -100.f);
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
	behaviourAI();
	
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
	m_name.setPosition(m_position.x, m_position.y + 60);
}

void Entity::update(sf::Vector2f t_targetPosition)
{
	m_target = t_targetPosition;
	behaviourAI();
	m_position += m_velocity;
	m_entitySprite.setPosition(m_position);

	if (m_position.x > 1550)
	{
		m_position.x = 1545;
	}
	if (m_position.x < 50)
	{
		m_position.x = 55;
	}

	if (m_position.y > 870)
	{
		m_position.y = 865;
	}
	if (m_position.y < 20)
	{
		m_position.y = 25;
	}
	m_name.setPosition(m_position.x, m_position.y + 60);
	updateVision();
}

void Entity::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_visionCone);
	t_window.draw(m_entitySprite);
	t_window.draw(m_name);
}


void Entity::adjustVelocity(float t_scalar)
{
	float velocityScalar = t_scalar;
	sf::Vector2f velocityAdjustment = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	velocityAdjustment *= velocityScalar;
	m_velocity += velocityAdjustment;
}

sf::Vector2f Entity::getVelocity()
{
	return m_velocity;
}

void Entity::adjustRotation(float t_angle)
{
	m_angle += t_angle;
	float velocityScalar = magnitude(m_velocity);
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

void Entity::setMode(int t_mode)
{
	m_mode = t_mode;
	updateText();

}

void Entity::setUpText(sf::Font& t_font)
{
	m_font = t_font;
	m_name.setString("Player");
	m_name.setFont(m_font);
	m_name.setCharacterSize(20);
	m_name.setStyle(sf::Text::Bold);
	m_name.setFillColor(sf::Color::White);
	m_name.setPosition(m_position.x, m_position.y + 60);
}

void Entity::setTargetVelocity(sf::Vector2f t_velocity)
{
	m_targetVelocity = t_velocity;
}

sf::Vector2f Entity::getPosition()
{
	return m_position;
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

void Entity::updateText()
{
	switch (m_mode) {
	case 0: m_name.setString("Player");
		break;   
	case 1: m_name.setString("Seek");
		break;
	case 2: m_name.setString("Flee");
		break;      
	case 3: m_name.setString("Wander");
		break;
	case 4: m_name.setString("Arrive");
		break;      
	case 5: m_name.setString("Pursue");
		break;
	}
}

void Entity::updateVision()
{
	m_visionCone[0].position = m_position;
	m_visionCone[1].position = sf::Vector2f(cos((m_angle+130) * M_PI / 180), sin((m_angle + 130) * M_PI / 180));
	m_visionCone[1].position = m_visionCone[1].position * 150.0f;
	m_visionCone[1].position = m_position + m_visionCone[1].position;
	m_visionCone[2].position = sf::Vector2f(cos((m_angle+50 ) * M_PI / 180), sin((m_angle+50) * M_PI / 180));
	m_visionCone[2].position = m_visionCone[2].position * 150.0f;
	m_visionCone[2].position = m_position + m_visionCone[2].position;
	
	if (m_mode == 5)
	{

		std::cout << m_angle + 30 << std::endl;
		std::cout << m_angle << std::endl;
		std::cout << m_angle - 30 << std::endl;
		//std::cout << m_visionCone[0].position.x << " X  " << m_visionCone[0].position.y << " Y  in arrive" << std::endl;
		//std::cout << m_visionCone[1].position.x << " X  " << m_visionCone[1].position.y << " Y  in arrive" << std::endl;
		//std::cout << m_visionCone[2].position.x << " X  " << m_visionCone[2].position.y << " Y  in arrive" << std::endl;
	}

	m_visionCone[0].color = m_coneColour;
	m_visionCone[1].color = m_coneColour;
	m_visionCone[2].color = m_coneColour;
}

float Entity::magnitude(sf::Vector2f t_vector)
{
	return sqrt((t_vector.x* t_vector.x) + (t_vector.y * t_vector.y));
}

float Entity::getNewOrientation(sf::Vector2f t_velociy)
{
		if (magnitude(t_velociy) > 0)//If the ship is still moving it changes the angle.
			// note atan2 returns an angle in radians which you 
			// may want to convert to degrees.
		{
			return ((atan2(-m_velocity.x, m_velocity.y) * 180 )/ M_PI );  //Returns the angle of the current vector.
		}
		else
		{
			return m_angle;
		}
}

void Entity::behaviourAI()
{
	switch (m_mode) {
	case 0:
		player();
		break;       // and exits the switch
	case 1: 
		seek();
		break;
	case 2:
		flee();
		break;
	case 3:
		meander();
		break;
	case 4:
		arrive();
		break;
	case 5:
		pursue();
		break;
	}

}

void Entity::seek()
{
	m_velocity = m_target - m_position;
	m_angle = getNewOrientation(m_velocity);
	m_velocity = (m_velocity / magnitude(m_velocity) )* magnitude(m_maxSpeed);//Normalizes the vector and scales it by the length of the max speed.
	m_entitySprite.setRotation(m_angle);

}

void Entity::player()
{
	throttleSpeed();
}

void Entity::flee()
{
	m_velocity = m_position - m_target;
	m_angle = getNewOrientation(m_velocity);
	m_velocity = (m_velocity / magnitude(m_velocity)) * magnitude(m_maxSpeed);//Normalizes the vector and scales it by the length of the max speed.
	m_entitySprite.setRotation(m_angle);

}

void Entity::meander()
{
	float tempAdjuster = (((rand() % 20 + 1)));
	tempAdjuster -= 10;
	tempAdjuster /= 10;//Gives a number between 1 and 20, -10 to give a range of -9 and 10, divide by 10 to give a range of -0.9 and 1
	m_angle = m_angle + (m_maxRotation * tempAdjuster); 
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	m_velocity *= magnitude(m_maxSpeed);//Scales it by the length of the max speed.
	m_entitySprite.setRotation(m_angle);
}

void Entity::arrive()
{
	m_velocity = m_target - m_position;

	if (magnitude(m_velocity) < m_radius)
	{
		m_velocity = sf::Vector2f(0.0, 0.0);
		

	}
	else
	{
		m_velocity = m_velocity / m_timeToTarget;
		if (magnitude(m_velocity) > magnitude(m_maxSpeed))
		{
			m_velocity = m_velocity/ magnitude(m_velocity);
			m_velocity = m_velocity * magnitude(m_maxSpeed);
			
		}
	}
	m_angle = getNewOrientation(m_velocity);
	m_entitySprite.setRotation(m_angle);
	updateVision();

}

void Entity::pursue()
{
	sf::Vector2f direction = m_target - m_position;
	float distance = magnitude(direction);
	float	speed = magnitude(m_maxSpeed);
	m_timePrediction = distance / speed;
	sf::Vector2f predictedTarget = m_target + (m_targetVelocity * m_timePrediction);
	m_target = predictedTarget;
	arrive();
}


