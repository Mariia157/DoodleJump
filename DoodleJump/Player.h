#pragma once
#include "IEntity.h"
#include <iostream>

class Player : public IEntity {

	Sprite* doodle = nullptr;
	int doodleW = 0, doodleH = 0;
	int speed = 0; 

public:

	Player() {
		
		int w = 0, h = 0;
		doodle = createSprite("C:/Users/Марія/source/repos/DoodleJump/x64/Debug/data/blue-lik-left.png");
		getScreenSize(w, h);
		getSpriteSize(doodle, doodleW, doodleH);

		float x = (w / 2) - (doodleW / 2);
		float y = (h / 2) - (doodleH / 2);
		setCoordinates(Coordinates(x, y));
		
		//drawSprite(doodle, (w / 2) - (doodleW / 2), (h / 2) - (doodleH / 2));
	}
	~Player() { if (doodle) destroySprite(doodle); }

	void reDraw() override {
		Coordinates curCoordinates = getCoordinates();
		drawSprite(doodle,curCoordinates.x, curCoordinates.y );
	}

	void move(FRSide side) override {
		Coordinates curCoordinates = getCoordinates();
		switch(side) {
			case FRSide::RIGHT:{
				curCoordinates.x += 5;
				setCoordinates(curCoordinates);
				break;
			}
			case FRSide::LEFT: {
				curCoordinates.x -= 5;
				setCoordinates(curCoordinates);
				break;
			}
		}
	}

	void jump() {
		Coordinates curCoordinates = getCoordinates();
		curCoordinates.y -= 20;
		setCoordinates(curCoordinates);
	}

	void fall() {
		int w, h;
		getScreenSize(w, h);
		Coordinates curCoordinates = getCoordinates();
		if (curCoordinates.y <= h - doodleH) {
			std::cout << curCoordinates.x << curCoordinates.y << std::endl;
			curCoordinates.y += 0.1;
			setCoordinates(curCoordinates);
		}
	}
};
