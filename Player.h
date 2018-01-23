#pragma once
#include "VisibleGameObject.h"

class Player :
	public VisibleGameObject
{
public:
	Player();
	~Player();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	float GetVelocity() const;
	//static bool life;
	bool life;

private:
	float _velocity;  // -- left ++ right
	float _maxVelocity;
	

};

