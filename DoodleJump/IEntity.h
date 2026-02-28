#pragma once

struct Coordinates {
	int x = 0;
	int y = 0;
};

class IEntity {

	Coordinates coordinates;

public:

	virtual Coordinates getCoordinates() { return coordinates; }

	virtual void move(Coordinates coordinates) = 0;

	virtual void reDraw() = 0;
};

//func = 0; обязательная реализация для наследников