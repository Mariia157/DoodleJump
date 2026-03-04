#pragma once
#include "Framework.h"

struct Coordinates {
	Coordinates() {}
	Coordinates(float x_, float y_) {
		this->x = x_;
		this->y = y_;
	}
	Coordinates& operator= (Coordinates other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
	Coordinates& operator+ (Coordinates other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	float x = 0;
	float y = 0;
};

class IEntity {
protected:
	Sprite* sprite = nullptr;
	Coordinates coordinates;
	int w = 0, h = 0;      
	bool isDead = false;  

public:

	// Координаты
	virtual Coordinates getCoordinates() { return coordinates; }
	virtual void setCoordinates(Coordinates coordinatesNew) { coordinates = coordinatesNew; }

	virtual Coordinates getCentreCoordinates();

	// Размеры — берутся из w, h которые задаются через loadSprite
	virtual int getWidth() { return w; }
	virtual int getHeight() { return h; }
	virtual bool getIsDead() { return isDead; }
	virtual void die() { isDead = true; }

	virtual void setSpritePicture(const char* path);

	virtual void reDraw();
	
	virtual void move(FRSide side) {}
	
	virtual void collide(IEntity* other) = 0;

	virtual ~IEntity() {
		if (sprite) {
			destroySprite(sprite);
			sprite = nullptr;
		}
	}
};