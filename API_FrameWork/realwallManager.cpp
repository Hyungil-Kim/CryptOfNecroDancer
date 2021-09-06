#include "framework.h"
#include "realwallManager.h"
#include "CWall.h"
realwallManager::realwallManager()
{
}

realwallManager::~realwallManager()
{
}

HRESULT realwallManager::init()
{
	_swall = new makeSoftWall;
	_hwall = new makeHardWall;
	_uwall = new makeUnBrokeWall;


	
	return S_OK;
}

void realwallManager::release()
{
	_swall->release();
	_hwall->release();
	_uwall->release();
	SAFE_DELETE(_swall);
	SAFE_DELETE(_hwall);
	SAFE_DELETE(_uwall);
}

void realwallManager::update()
{
	_swall->update();
	_hwall->update();
	_uwall->update();

}

void realwallManager::render()
{
	_swall->render();
	_hwall->render();
	_uwall->render();
}
