#pragma once
#include "IEntity.h"
#include "Framework.h"

class Enemy : public IEntity {
public:
	Enemy(float x, float y, const char* path) {
		setSpritePicture(path);  // загружает спрайт и обновляет w, h через IEntity
		setCoordinates(Coordinates(x, y));
	}

	~Enemy() = default;  // деструктор спрайта уже в ~IEntity()

	void collide(IEntity* other) override {}  // логика коллизии на стороне Player
};