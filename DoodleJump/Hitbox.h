#pragma once
#include "IEntity.h"
struct Hitbox {
protected:
	IEntity* entity = nullptr;

public:
	int x, y;
	int h, w;

	virtual ~Hitbox() = default;
	void setHitboxCoordinates(int spriteX, int spriteY) { 
		x = spriteX;
		y = spriteY;
	}
	void setHitboxSize(int spriteW, int spriteH) {
		w = spriteW;
		h = spriteH;
		}

	void setEntity(IEntity* e) { entity = e; }

	virtual bool onCollided(IEntity* other) {
		if (!other || !entity) return false;

		Coordinates cur = entity->getCoordinates();
		Coordinates otherPos = other->getCoordinates();

		int otherW = other->getWidth();
		int otherH = other->getHeight();

		// Проверка пересечения прямоугольников
		bool collided =
			cur.x < otherPos.x + otherW &&
			cur.x + entity->getWidth() > otherPos.x &&
			cur.y < otherPos.y + otherH &&
			cur.y + entity->getHeight() > otherPos.y;

		return collided;

	};
	 
	bool isCollidedAbove(IEntity* other) {
		if (!other || !entity) return false;

		Coordinates cur = entity->getCoordinates();
		Coordinates otherPos = other->getCoordinates();
		int otherW = other->getWidth();
		int otherH = other->getHeight();
		int entityH = entity->getHeight();
		int entityW = entity->getWidth();

		// Нижняя граница игрока находится в пределах платформы
		bool verticalHit =
			cur.y + entityH >= otherPos.y &&          // ✅ нижняя граница игрока ниже верха платформы
			cur.y + entityH <= otherPos.y + otherH &&  // ✅ но не ниже низа платформы
			cur.y < otherPos.y;                        // ✅ игрок выше центра платформы

		// Горизонтальное перекрытие
		bool horizontalHit =
			cur.x < otherPos.x + otherW &&
			cur.x + entityW > otherPos.x;

		return verticalHit && horizontalHit;
	}
	
};