#pragma once
#include"CObject.h"
class CTile : public CObject
{
private:
	bool _isDebug;
public:
	CTile();
	CTile(POINT _pos, POINT _size, image* _img = nullptr, animation* _ani = nullptr);
	~CTile();

	HRESULT init();
	void release();
	void update();
	void render();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

