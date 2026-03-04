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

	virtual bool onCollided(IEntity* other);;
	 
	bool isCollidedAbove(IEntity* other);
	
};