#pragma once
#include"CObject.h"
class CTile : public CObject
{
private:

public:
	CTile();
	CTile(POINT _pos, POINT _size, image* _img = nullptr, animation* _ani = nullptr);
	~CTile();

	HRESULT init();
	void release();
	void update();
	void render();

};

