#include "StdAfx.h"
#include "Player.h"
#include "Game.h"


Player::Player():
_velocity(0),
_maxVelocity(600.0f)
{
	Load("images/human.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);

}


Player::~Player()
{
}

void Player::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float Player::GetVelocity() const
{
	return _velocity;
}

void Player::Update(float elapsedTime)
{
	//float moveAmount = _velocity  * elapsedTime;
	sf::Vector2f pos = this->GetPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && pos.x  >= GetSprite().getLocalBounds().width / 2)
	{
		//_velocity += -3.0f;
		GetSprite().move(-5.0f, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x <= (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
	{
		GetSprite().move(5.0f, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos.y + GetSprite().getGlobalBounds().height / 2 < Game::SCREEN_HEIGHT )
	{
		GetSprite().move(0, 5.0f);
	}	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && pos.y - GetSprite().getGlobalBounds().height / 2 > 0 )
	{
		GetSprite().move(0, -5.0f);
	}

	/*
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;
	*/

	//sf::Vector2f pos = this->GetPosition();
	/*
	if (pos.x  < GetSprite().getLocalBounds().width/ 2
		|| pos.x > (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
	{
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}

	GetSprite().move(_velocity * elapsedTime, 0);

	*/

	
	if (Zombie().transform == true)
	{
		life = false;
	}
/*
static bool life = true;

if (Zombie::transform == true)
{
	life = false;
}

*/
}