#pragma once
#include "IEntity.h"
#include "Environment.h"
#include "Hitbox.h"
#include "Platform.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include "ImmunityOrb.h"

class Player : public IEntity {
	int doodleW = 0, doodleH = 0;
	const char* spritePathLeft = "./data/blue-lik-left.png";
	const char* spritePathRight = "./data/blue-lik-right.png";
	bool isFall = false;
	bool isUp = false;
	bool isOnPlatform = false;
	float fallSpeed = 10.0f;
	bool canJump = true;
	int moveSpeed = 3;
	float velocityX = 0.0f;
	float normalJumpSpeed = -2.0f;  // обычный прыжок
	float boostJumpSpeed = -6.0f;  // 300% от обычного
	bool isImmune = false;
	float immunityTimer = 0.0f;
	const float IMMUNITY_DURATION = 20.0f * 60.0f;  // 20 секунд * 60 кадров

public:
	Player() {
		int sw = 0, sh = 0;
		setSpritePicture(spritePathLeft);  
		getScreenSize(sw, sh);
		doodleW = getWidth();  
		doodleH = getHeight();

		float x = (sw / 2) - (doodleW / 2);
		float y = (sh / 2) - (doodleH / 2);
		setCoordinates(Coordinates(x, y));
	}

	~Player() = default;

	bool getIsFall() { return isFall; }
	bool getIsUp() { return isUp; }

	int getWidth()  override { return doodleW; }
	int getHeight() override { return doodleH; }

	float getVelocityX() { return velocityX; }
	float getFallSpeed() { return fallSpeed; }
	bool getIsImmune() { return isImmune; }

	void setVelocityX(float vx) { velocityX = vx; }
	void setFallSpeed(float fs) { fallSpeed = fs; }

	void setSpritePicture(const char* path) override;

	void move(FRSide side) override;

	void jump();

	void boostedJump();

	void fall();

	void activateImmunity();

	void updateImmunity();

	void collide(IEntity* other) override;
};