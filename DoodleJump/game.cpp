

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
		
		Player* doodle = new Player();
		

		return true;
	}

	virtual void Close() {
		delete doodle;
	}

	virtual bool Tick() {

        drawTestBackground();
		doodle->move(doodle->getCoordinates());
		

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) {
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
