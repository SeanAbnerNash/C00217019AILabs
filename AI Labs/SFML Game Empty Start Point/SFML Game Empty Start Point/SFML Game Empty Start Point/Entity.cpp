#include "Entity.h"
//@Author Sean Nash de Andrade
//@Login C00217019
//Lab 1-3 AI.
//Implemented Seek, Flee, Wander, Arrive, Pursue & Player Behaviours
//Implemented Vision Cones
//Time Taken: 5 Hours.

Entity::Entity()//Setting up the Vision cones off screen initially so it doesn't appear for those that don't need them.
{
	m_visionCone[0].position = sf::Vector2f(-10.f, -10.f);
	m_visionCone[1].position = sf::Vector2f(-100.f, -10.f);
	m_visionCone[2].position = sf::Vector2f(-100.f, -100.f);
	m_coneColour = m_neutralColour;
}

Entity::Entity(sf::Sprite& t_entitySprite, sf::Vector2f t_position,float t_angle)//Setting up the Class, passing in the sprite position & angle
{
	m_entitySprite = t_entitySprite;
	m_position = t_position;
	m_angle = t_angle;
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
}

Entity::~Entity()
{
}
//This is the update loop for units without a target. 
//They are looped when they go offscreen. The player and Wander entities use this
void Entity::update()
{
	behaviourAI();//A function that makes the entity act according to it's mode.
	
	m_position += m_velocity;
	
	screenLoop();//Loops the entity if they go offscreen.
	m_entitySprite.setPosition(m_position);//Moves and sets the sprite.
	m_name.setPosition(m_position.x, m_position.y + 60);
}

//The update loop for entities with a target.
//Passes the position of the target with every frame.
void Entity::update(sf::Vector2f t_targetPosition)
{
	m_target = t_targetPosition;//Setting the position on the member variable
	behaviourAI();//Behaviour Actions

	m_position += m_velocity;
	screenLock();//Locks and returns the entity on screen
	m_entitySprite.setPosition(m_position);
	m_name.setPosition(m_position.x, m_position.y + 60);//Moves and sets names & sprites.
	updateVision();//Moves the cone of vision and adjusts for angle changes.
}

void Entity::render(sf::RenderWindow& t_window)//Draws the sprite, name and vision cone
{
	t_window.draw(m_visionCone);
	t_window.draw(m_entitySprite);
	t_window.draw(m_name);
}

//Adjusts the current velocity Passing in a scalar.
//A unit vector is made in the direction of the current angle of travel.
//It is scaled by the given scalar and applied to the velocity
//This increases or reduces the current speed by scaled values of one (Unit vectors have length 1) in the direction of travel.
// Passing in 0.5 would speed up the entity by 0.5 units per frame.
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

//Takes in a new angle, gets the current velocity's magnitude
//creates a unit vector at the new angle and scales it according to the old velocity's magnitude.
//Before updating the sprite rotation.
void Entity::adjustRotation(float t_angle)
{
	m_angle += t_angle;
	float velocityScalar = magnitude(m_velocity);
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	m_velocity *= velocityScalar;
	m_entitySprite.setRotation(m_angle);
}

//Passes in address sprite, position & angle. Unit vector is made from the angle
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


//Sets the mode of the Entity. This defines what behaviour it uses
//It also updates the text to show the correct name.
void Entity::setMode(int t_mode)
{
	m_mode = t_mode;
	updateText();

}

void Entity::setUpText(sf::Font& t_font)//Initial Name text set up.
{
	m_font = t_font;
	m_name.setString("Player");
	m_name.setFont(m_font);
	m_name.setCharacterSize(20);
	m_name.setStyle(sf::Text::Bold);
	m_name.setFillColor(sf::Color::White);
	m_name.setPosition(m_position.x, m_position.y + 60);
}

//Sets the target velocity. Used by Pursue only to predict player position.
void Entity::setTargetVelocity(sf::Vector2f t_velocity)
{
	m_targetVelocity = t_velocity;
}

sf::Vector2f Entity::getPosition()
{
	return m_position;
}

void Entity::throttleSpeed()//If the max & min speed is set overwritting the specific bases then it limits the speed within certain limits.
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

void Entity::updateText()//Sets the Name string according to mode.
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

void Entity::updateVision()//Updates the vertex array used to draw the vision cone.
{
	m_visionCone[0].position = m_position;//The centrepoint, used to calculate the others.

	//The second position is adjusted for current direction of travel then the m_visionDegrees
	//is used to define the cone width. In this case +/- 30 degrees off the centre
	//This angle is used to make a unit vector
	m_visionCone[1].position = sf::Vector2f(cos((m_angle+90 + m_visionDegrees) * M_PI / 180), sin((m_angle + 90 + m_visionDegrees) * M_PI / 180));
	//This unit vector is scaled by the desired vision distance
	m_visionCone[1].position = m_visionCone[1].position * m_visionDistance;
	//Then the central point is used to find where the other points are by adding the scaled vector to it.
	m_visionCone[1].position = m_position + m_visionCone[1].position;

	m_visionCone[2].position = sf::Vector2f(cos((m_angle + 90 - m_visionDegrees) * M_PI / 180), sin((m_angle + 90 - m_visionDegrees) * M_PI / 180));
	m_visionCone[2].position = m_visionCone[2].position * m_visionDistance;
	m_visionCone[2].position = m_position + m_visionCone[2].position;
	
	//Setting the Colours
	m_visionCone[0].color = m_coneColour;
	m_visionCone[1].color = m_coneColour;
	m_visionCone[2].color = m_coneColour;
}

float Entity::magnitude(sf::Vector2f t_vector)//Takes a vector, returns magnitude or length as a float.
{
	return sqrt((t_vector.x* t_vector.x) + (t_vector.y * t_vector.y));
}

bool Entity::withinVision()//Calculates if target is within vision
{
	bool result = false;
	m_coneColour = m_neutralColour;//Sets the base flags to false initially.
;
	if (distance(m_position, m_target) < m_visionDistance + 30)//If the player is within the spotting distance
	{

		sf::Vector2f vectorBetween = m_position - m_target;//It finds an vector between the player and the target
		float angle = angleBetween(vectorBetween, m_velocity);//Gets the angle between the player and the direction the entity is facing and moving in
		if (angle < 30)//if the player is withing the cone of vision, 30 degrees above or below the central direction
		{
			result = true;//Then they are spotted and the cone is shifted in colour
			m_coneColour = m_alertColour;
		}
	}
	return result;
}

float Entity::getNewOrientation(sf::Vector2f t_velociy)
{
		if (magnitude(t_velociy) > 0)
		{
			return ((atan2(-m_velocity.x, m_velocity.y) * 180 )/ M_PI );  //Returns the angle of the current vector.
		}
		else
		{
			return m_angle;
		}
}

void Entity::screenLoop()//Returns something back to the other side of the screen.
{
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

void Entity::screenLock()//Keeps something onscreen if it reaches the borders.
{
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
}

void Entity::behaviourAI()//Picks the behaviour function depending on function
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

void Entity::seek()//Seeks a target constantly. Moves towards it at max speed.
{
	m_velocity = m_target - m_position;//Finds  a vector between entity and target
	m_angle = getNewOrientation(m_velocity); //Gets the angle of the new velocity
	m_velocity = (m_velocity / magnitude(m_velocity) )* magnitude(m_maxSpeed);//Normalizes the vector and scales it by the length of the max speed.
	m_entitySprite.setRotation(m_angle);//Updates Rotation

}

void Entity::player()//The player controls their own behaviour, the only thing out of their control is the max/ min speed throttling.
{
	throttleSpeed();
}

void Entity::flee()//Flees a target constantly. Moves at max speed away from it.
{
	m_velocity = m_position - m_target;//Finds  a vector between entity and target
	m_angle = getNewOrientation(m_velocity);//Gets the angle of the new velocity
	m_velocity = (m_velocity / magnitude(m_velocity)) * magnitude(m_maxSpeed);//Normalizes the vector and scales it by the length of the max speed.
	m_entitySprite.setRotation(m_angle);//Updates Rotation

}

void Entity::meander()//Wanders aimlessly
{
	float tempAdjuster = (((rand() % 20 + 1)));//Gives a number between 1 and 20
	tempAdjuster -= 10; //-10 to give a range of -9 and 10,
	tempAdjuster /= 10;  //divide by 10 to give a range of -0.9 and 1
	m_angle = m_angle + (m_maxRotation * tempAdjuster); //Randomly changes current angle by the max which is scaled by the random scalar
	m_velocity = sf::Vector2f(cos(m_angle * M_PI / 180), sin(m_angle * M_PI / 180));//Generates a unit vector in the given angle.
	m_velocity *= magnitude(m_maxSpeed);//Scales it by the length of the max speed.
	m_entitySprite.setRotation(m_angle);//Updates Sprite
}

void Entity::arrive()//Seeks new target. Moves towards them at varying speed depending on distance.
{
	m_velocity = m_target - m_position;//Finds vector between target and position

	if (withinVision())//Stops if the target is in the cone of vision.
	{
		m_velocity = sf::Vector2f(0.0, 0.0);
		

	}
	else
	{
		m_velocity = m_velocity / m_timeToTarget;//Finds the velocity scaled by the time they want to take to arrive.
		if (magnitude(m_velocity) > magnitude(m_maxSpeed))//If the speed is more than the max then it sets the current velocity back to max.
		{
			m_velocity = m_velocity / magnitude(m_velocity);
			m_velocity = m_velocity * magnitude(m_maxSpeed);
			
		}
	}
	m_angle = getNewOrientation(m_velocity);
	m_entitySprite.setRotation(m_angle);
	updateVision();//Updates Angle, sprite and vision cones

}

void Entity::pursue()//This predicts a point the player will be in after a given amount of time based on their current speed and position
{
	sf::Vector2f direction = m_target - m_position;
	float distance = magnitude(direction);
	float	speed = magnitude(m_maxSpeed);
	m_timePrediction = distance / speed;//Amount of time needed to cross the distance at max speed.
	sf::Vector2f predictedTarget = m_target + (m_targetVelocity * m_timePrediction);//Target prediction, current position plus the speed times the time it takes to reach it
	m_target = predictedTarget;//Overwrites the old target
	arrive();//Runs the arrive code with the new target to move the entity
}

float Entity::distance(sf::Vector2f t_vector, sf::Vector2f left_vector)//Distance formula. Takes two points returns distance between them as a float
{
	return sqrt(pow(left_vector.x - t_vector.x, 2) + pow(left_vector.y - t_vector.y, 2));
}

float Entity::angleBetween(sf::Vector2f t_vector, sf::Vector2f left_vector)//Angle between two vectors. Takes two vectors and returns the angle as a float
{
	float dot = t_vector.x * left_vector.x + t_vector.y * left_vector.y;//   # dot product;
	float det = t_vector.x * left_vector.y - t_vector.y * left_vector.x;//    # determinant;
	float angle = atan2(det, dot);
	angle = angle * (M_PI / 180);
	return angle;
}


