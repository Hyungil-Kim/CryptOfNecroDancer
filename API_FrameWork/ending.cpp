#include "framework.h"
#include "ending.h"

ending::ending()
{
	_title = IMAGE->addImage("¿£µù", "images/title/end.bmp", WINSIZEX, WINSIZEY, true);
	_isStart = false;
	_isDone = false;
}

ending::~ending()
{
}

HRESULT ending::init()
{
	return S_OK;
}

void ending::release()
{
}

void ending::update()
{	
		_isDone = true;
}

void ending::render()
{
	ZORDER->UIRender(_title, ZFLOORMAP, 0, 0, 0);

}
