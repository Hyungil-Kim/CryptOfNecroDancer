#include "framework.h"
#include "Title.h"

Title::Title()
{
	_title = IMAGE->addImage("타이틀", "images/title/mainmenu.bmp", WINSIZEX, WINSIZEY,true);
	_continue = IMAGE->addImage("표시", "images/title/continue.bmp", 440, 36, true);
	_isStart = false;
	_isDone = false;
}

Title::~Title()
{
}

HRESULT Title::init()
{
	return S_OK;
}

void Title::release()
{
}

void Title::update()
{
	if (InputManager->isOnceKeyDown(VK_SPACE))
	{
		SCENE->changeScene("1층");
		_isDone = true;
	}
}

void Title::render()
{
	ZORDER->UIRender(_title, ZFLOORMAP, 0, 0, 0);

	ZORDER->UIRender(_continue, 3, 0, WINSIZEX / 3, WINSIZEY - 150);
}
