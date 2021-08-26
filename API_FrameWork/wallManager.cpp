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
	_makeHardWall = new makeHardWall;

	//makeDungeon();
	return S_OK;
}

void wallManager::release()
{
	_makeSoftWall->release();
	_makeHardWall->release();


	SAFE_DELETE(_makeSoftWall);
}

void wallManager::update()
{
	_makeSoftWall->update();
	_makeHardWall->update();
}

void wallManager::render()
{
	_makeSoftWall->render();
	_makeHardWall->render();
}

void wallManager::makeDungeon(int i , int k)
{
	
}
