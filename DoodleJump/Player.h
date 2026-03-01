#pragma once
#include "IEntity.h"
#include <iostream>
#include "Environment.h"
#include "Constants.h"
#include "Hitbox.h"
class Player : public IEntity {

	Sprite* doodle = nullptr;
	int doodleW = 0, doodleH = 0;
	int speed = 0; 
	int w = 0, h = 0;
	const char* spritePathLeft = "C:/data/blue-lik-left.png";
	const char* spritePathRight = "C:/data/blue-lik-right.png";
	bool isFall = false;
	bool isUp = false;
	//Hitbox* hitbox = nullptr;

public:

	Player() {
		
		int w = 0, h = 0;
		doodle = createSprite("C:/data/blue-lik-left.png");
		getScreenSize(w, h);
		getSpriteSize(doodle, doodleW, doodleH);

		float x = (w / 2) - (doodleW / 2);
		float y = (h / 2) - (doodleH / 2);
		setCoordinates(Coordinates(x, y));
		
		//drawSprite(doodle, (w / 2) - (doodleW / 2), (h / 2) - (doodleH / 2));
	}
	~Player() { if (doodle) destroySprite(doodle); }

	bool getIsFall() { return isFall; }
	bool getIsUp() { return isUp; }

	int getDoodleH() { return doodleH; }

	void reDraw() override {
		Coordinates curCoordinates = getCoordinates();
		drawSprite(doodle,curCoordinates.x, curCoordinates.y );
	}

	void setSpritePicture(const char* path) override {
		destroySprite(doodle);
		doodle = createSprite(path);
	}

	void move(FRSide side) override {
		Coordinates curCoordinates = getCoordinates();
		getScreenSize(w, h);
		switch (side) {
		case FRSide::RIGHT: {
			setSpritePicture(spritePathRight);
			curCoordinates.x += moveSpeed;
			if (curCoordinates.x > w)
				curCoordinates.x = 0;
			setCoordinates(curCoordinates);
			break;
		}
		case FRSide::LEFT: {
			setSpritePicture(spritePathLeft);
			curCoordinates.x -= moveSpeed;
			if (curCoordinates.x < 0)
				curCoordinates.x = w;
			setCoordinates(curCoordinates);
			break;
		}
		}
	
	}

	void jump() {
		
		isUp = true;
		Coordinates curCoordinates = getCoordinates();
		curCoordinates.y -= 100;
		setCoordinates(curCoordinates);
		
	}

	void fall() {
		int w, h;
		getScreenSize(w, h);
		Coordinates curCoordinates = getCoordinates();
		
		if (curCoordinates.y <= h - doodleH) {
			isUp = false;
			isFall = true;
			curCoordinates.y += 0.5;
			setCoordinates(curCoordinates);
		}
		else isFall = false;
		
	}

	bool onCollided(IEntity* other) override {
		Coordinates currCoordinates = getCoordinates();
		if (other) {
			if (
				
				
				
				) {
				//взять ширину высоту текущего энтити с координатами, вычислить хитбокс и сравнить с хитбоксом other
			}
		}

	}
};
