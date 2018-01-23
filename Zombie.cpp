#include "StdAfx.h"
#include "Zombie.h"
#include "Game.h"
#include"GameOver.h"

Zombie::Zombie() :
	_velocity(250.0f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());
	float random_integer = std::rand() % 360 + 1; //Gives random number between 1 and 360.
	_angle = random_integer;
	GetSprite().setOrigin(0, 0);
}

Zombie::~Zombie()
{
}

static bool transform = false;

void Zombie::Update(float elapsedTime) //Parameter is the time since last frame in seconds. VERY small number.
{
	_elapsedTimeSinceStart += elapsedTime;

	// Delay game from starting until 3 seconds have passed
	if (_elapsedTimeSinceStart < 5.0f)
		return;

	float moveAmount = _velocity  * elapsedTime;


	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

	/*
	if (fmod(_elapsedTimeSinceStart, 0.016f) <= 0.1f)
	{
		_angle = std::rand() % 360 + 1;
		GetSprite().move(moveByX, moveByY);
	}
	*/

	//collide with the left side of the screen
	
	if (GetPosition().x + moveByX <= 0 + GetWidth() / 2 || GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		//Ricochet
		_angle = 360.0f - _angle;
		if (_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveByX = -moveByX;
		//_velocity -= 0.15*_velocity;
	}

	

	Player* player1 = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("Player1"));
	if (player1 != NULL)
	{
		sf::Rect<float> p1BB = player1->GetBoundingRect();

		
		
		if (fmod(_elapsedTimeSinceStart, 0.0016f) <= 0.01f)
		{
			sf::Vector2f distance = sf::Vector2f(player1->GetPosition() - Zombie().GetPosition());
			float norm = sqrt(distance.x * distance.x + distance.y * distance.y);
			std::cout << "checking norm " << norm << std::endl;
			if (norm < 200.0f)
			{				
				std::cout << "Stop chasing me" << std::endl;
				if (distance.x >= 0 && distance.y >= 0)
				{
					_angle =  std::asin(distance.y / norm);
				}
				else 
					if (distance.x >= 0 && distance.y < 0)
					{
						_angle = -std::asin(-distance.y / norm);
					}
					else
						if (distance.x < 0 && distance.y < 0)
						{
							_angle = 180.0 - std::asin(-distance.y / norm);
						}
						else
							if (distance.x < 0 && distance.y >= 0)
							{
								_angle = 180 - std::asin(distance.y / norm);
							}			
				
			}
			else 
			{
				_angle = std::rand() % 360 + 1;				
			}
			GetSprite().move(moveByX, moveByY);
		}
		

		if (p1BB.intersects(GetBoundingRect()))       
		{
			

			//currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;
			//Game::ShowGameOver();
			
			//GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			//_angle = (rand() % 360) + 1;
			//_velocity = 250.0f;
			//_elapsedTimeSinceStart = 0.0f;
			
			//bool a = player1->life();

			//a = false;
			transform = true;
			//std::cout << "Too close" << transform << std::endl;
			

		}

		if (GetPosition().y - GetHeight() / 2 <= 0)
		{
			_angle = 180 - _angle;
			moveByY = -moveByY;
			//_velocity -= 0.15*_velocity;
		}
		

		//if(GetPosition().y - GetSprite().GetSize().y/2 - moveByY <= 0 || GetPosition().y + GetSprite().GetSize().y/2 + moveByY >= Game::SCREEN_HEIGHT)
		if (GetPosition().y + GetHeight() / 2 >= Game::SCREEN_HEIGHT)
		{
			/*
			GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			_angle = (rand() % 360) + 1;
			_velocity = 230.0f;
			_elapsedTimeSinceStart = 0.0f;
			*/

			_angle = 180 - _angle;
			moveByY = -moveByY;
			//_velocity -= 0.15*_velocity;


		}

		GetSprite().move(moveByX, moveByY);
	}
}

float Zombie::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float Zombie::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}
