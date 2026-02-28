
#include <iostream>
#include "Framework.h"
#include "Player.h"
#include "IEntity.h"
/* Test Framework realization */
class MyFramework : public Framework {
	Player* doodle = nullptr;
	
	
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 320;
		height = 200;
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

        drawTestBackground();
		if (doodle) {
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
		switch (k)
		{
		case FRKey::RIGHT:
			doodle->move(FRSide::RIGHT);
			break;
		case FRKey::LEFT:
			doodle->move(FRSide::LEFT);
			break;
		case FRKey::DOWN:
			break;
		case FRKey::UP:
			doodle->jump();
			break;
		default:
			break;
		} {
			
		}
	}

	virtual void onKeyReleased(FRKey k) {
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
