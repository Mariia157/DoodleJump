#pragma once
#include "IEntity.h"
#include <iostream>
#include "Environment.h"
#include "Constants.h"
#include "Hitbox.h"
#include "Platform.h"
#include <vector>
#include "Enemy.h"
class Player : public IEntity {

    int doodleW = 0, doodleH = 0;
	int speed = 0;
	int w = 0, h = 0;
	const char* spritePathLeft = "C:/data/blue-lik-left.png";
	const char* spritePathRight = "C:/data/blue-lik-right.png";
	bool isFall = false;
	bool isUp = false;
	Hitbox* hitbox = nullptr;
	bool isOnPlatform = false;
	float fallSpeed = 10.0f;
	bool canJump = true;  // флаг для блокировки повторного прыжка в воздухе
public:

	Player() {

        int w = 0, h = 0;
		setSpritePicture("C:/data/blue-lik-left.png");
		getScreenSize(w, h);
		getSpriteSize(sprite, doodleW, doodleH);

		float x = (w / 2) - (doodleW / 2);
		float y = (h / 2) - (doodleH / 2);
		setCoordinates(Coordinates(x, y));

		drawSprite(sprite, x, y);
		//std::cout << "Player created at (" << x << ", " << y << ")" << std::endl;
	}
    ~Player() = default;

	bool getIsFall() { return isFall; }
	bool getIsUp() { return isUp; }

	virtual int getWidth() { return doodleW; };
	virtual int getHeight() { return doodleH; };

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
		if (!canJump) return;  // блокируем повторный прыжок

		canJump = false;
		isUp = true;
		fallSpeed = -10.0f;  // импульс вверх, fall() будет двигать плавно
	}

	void fall() {
		int sw, sh;
		getScreenSize(sw, sh);
		Coordinates cur = getCoordinates();

		// Разрешаем прыжок только когда летим вниз
		if (fallSpeed > 0) {
			canJump = true;
			isFall = true;
			isUp = false;
		}

		// Гравитация
		cur.y += fallSpeed;
		// Разная гравитация для подъёма и падения
		if (fallSpeed < 0) {
			fallSpeed += 0.1f;  // подъём — слабая гравитация
		}
		else {
			fallSpeed += 0.05f;  // падение — ещё слабее
		}

		//Пол
		if (cur.y >= sh - doodleH) {
			cur.y = sh - doodleH;
			fallSpeed = 0.0f;
			isFall = false;
			jump();  // прыжок от пола
		}

		setCoordinates(cur);
	}
	virtual void collide(IEntity* other) override {
		if (!other) return;
		Platform* platform = dynamic_cast<Platform*>(other);
		if (!platform) return;

		if (!isFall) return;

		Hitbox hitbox;
		hitbox.setEntity(this);
		hitbox.setHitboxSize(getWidth(), getHeight());
		Coordinates pos = getCoordinates();
		hitbox.setHitboxCoordinates(static_cast<int>(pos.x), static_cast<int>(pos.y));

		if (hitbox.isCollidedAbove(other)) {
			isFall = false;
			isOnPlatform = true;  // ✅ запоминаем что стоим на платформе
			jump();
			return;
		}
		
		// Коллизия с врагом
		Enemy* enemy = dynamic_cast<Enemy*>(other);
		if (enemy && !enemy->getIsDead()) {
			Hitbox hitbox;
			hitbox.setEntity(this);
			hitbox.setHitboxSize(getWidth(), getHeight());
			Coordinates pos = getCoordinates();
			hitbox.setHitboxCoordinates(pos.x, pos.y);

			if (hitbox.isCollidedAbove(other)) {
				// Прыгнули сверху — убиваем врага
				enemy->die();
				jump();
			}
			else if (hitbox.onCollided(other)) {
				// Столкнулись сбоку — игрок умирает
				// TODO: gameOver()
			}
		}
	}

	void attack(FRMouseButton lmb) {
		
	}
};