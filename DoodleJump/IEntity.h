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

	Coordinates coordinates;

public:

	virtual Coordinates getCoordinates() { return coordinates; }
	virtual void setCoordinates(Coordinates coordinatesNew) { coordinates = coordinatesNew; }

	virtual void move(FRSide side) = 0;

	virtual void reDraw() = 0;
};

//func = 0; обязательная реализация для наследников