#include "framework.h"
#include "loading.h"

loading::loading()
{
	_title = IMAGE->addImage("·Îµù", "images/title/loading.bmp", WINSIZEX, WINSIZEY, true);
	_isStart = false;
	_isDone = false;
}

loading::~loading()
{
}

HRESULT loading::init()
{
	loadingCount = 0;
	_isDone = false;
    return S_OK;
}

void loading::release()
{
}

void loading::update()
{
	_isStart = true;
	loadingCount++;
	if (loadingCount >= 180) {
		_isDone = true;
	}
}

void loading::render()
{
	ZORDER->UIRender(_title, 8, 0, 0, 0);

}
