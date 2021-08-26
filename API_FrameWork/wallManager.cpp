#include "framework.h"
#include "wallManager.h"

wallManager::wallManager()
{
}

wallManager::~wallManager()
{
}

HRESULT wallManager::init()
{
	_makeSoftWall = new makeSoftWall;

	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
		
			_makeSoftWall->addWall(48 * i, 48 * k-25);
		}
	}
	




	return S_OK;
}

void wallManager::release()
{
	_makeSoftWall->release();



	SAFE_DELETE(_makeSoftWall);
}

void wallManager::update()
{
	_makeSoftWall->update();
}

void wallManager::render()
{
	_makeSoftWall->render();
}
