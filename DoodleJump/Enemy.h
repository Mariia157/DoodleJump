#pragma once
#include "IEntity.h"
#include "Framework.h"

class Enemy : public IEntity {
public:
	Enemy(float x, float y, const char* path) {
		setSpritePicture(path);
		setCoordinates(Coordinates(x, y));
	}

	~Enemy() = default;

	void collide(IEntity* other) override {}
};