#pragma once
#include "IEntity.h"
#include "Framework.h"
#include <windows.h> // for GetAsyncKeyState and VK_RIGHT/VK_LEFT

class Player : public IEntity {

	Sprite* doodle = nullptr;
	int doodleW = 0, doodleH = 0;
	int w = 0, h = 0;
	int speed = 0; // initialize to avoid C26495

public:

	Player() {
		doodle = createSprite("C:/Users/Марія/source/repos/DoodleJump/x64/Debug/data/blue-lik-left.png");
		getScreenSize(w, h);
		getSpriteSize(doodle, doodleW, doodleH);
		// center the sprite (use doodleH for vertical centering)
		drawSprite(doodle, (w / 2) - (doodleW / 2), (h / 2) - (doodleH / 2));
	}
	~Player() { if (doodle) destroySprite(doodle); }

	void reDraw() override {
		drawSprite(doodle, (w / 2) - (doodleW / 2), (h / 2) - (doodleH / 2));
	}

	void move(Coordinates coordinates) override {
		// Do not instantiate Framework (abstract). Poll keyboard state via WinAPI.
		speed = 5;

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			coordinates.x += speed;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			coordinates.x -= speed;
		}

		// keep inside screen bounds
		if (coordinates.x < 0) coordinates.x = 0;
		if (coordinates.x > w - doodleW) coordinates.x = w - doodleW;

		// redraw at updated coordinates
		drawSprite(doodle, coordinates.x, coordinates.y);
	}

};
