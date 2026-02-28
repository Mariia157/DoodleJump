
#include <iostream>
#include "Framework.h"
#include "Player.h"
#include "IEntity.h"
#include "Environment.h"
#include "Constants.h"

/* Test Framework realization */
class MyFramework : public Framework {
	Player* doodle = nullptr;
	
	
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 600;
		height = 500;
		fullscreen = false;
	}

	virtual bool Init() {
		
		doodle = new Player();
		

		return true;
	}

	virtual void Close() {
		delete doodle;
	}

	virtual bool Tick() {
		Coordinates curCoordinates = doodle->getCoordinates();
		int w, h;
		int doodleH = doodle->getDoodleH();
		getScreenSize(w, h);
        drawTestBackground();{
		if (isPressed) {
			switch (currentKey) {
			case FRKey::RIGHT:
				doodle->move(FRSide::RIGHT);
				break;
			case FRKey::LEFT:
				doodle->move(FRSide::LEFT);
				break;
			
			default:
				break;
			}
		}
		if (curCoordinates.y > h - doodleH) {
			doodle->jump();
			isFall = true;
		}
			doodle->fall();
			doodle->reDraw();
		}
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) {
		isPressed = true;
		currentKey = k;

		
	}

	virtual void onKeyReleased(FRKey k) {
		isPressed = false;
	}
	
	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
