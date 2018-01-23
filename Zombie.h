#pragma once
#include "visiblegameobject.h"


class Zombie :
	public VisibleGameObject
{
public:
	Zombie();
	virtual ~Zombie();
	void Update(float);
	//static bool transform;
	bool transform;
private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
};
