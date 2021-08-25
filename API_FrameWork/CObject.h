#pragma once
#include "gameNode.h"
class CObject : public gameNode
{
protected:
	POINT pos;
	POINT size;

	image* img;
	animation* ani;
public:
	CObject();
	CObject(POINT _pos,POINT _size, image* _img, animation* _ani);
	~CObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	POINT getPos() { return pos; }
	POINT getSize() { return size; }
	image* getImg() { return img; }
};

