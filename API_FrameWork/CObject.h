#pragma once
#include "gameNode.h"
class CObject : public gameNode
{
protected:
	POINT pos;
	POINT size;
	RECT rc;

	image* img;
	image* img2;
	animation* ani;
	bool _isDebug;
public:
	CObject();
	CObject(POINT _pos, RECT _rc);
	CObject(POINT _pos,POINT _size, image* _img, animation* _ani);
	~CObject();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getRC() { return rc; }
	POINT getPos() { return pos; }
	POINT getSize() { return size; }
	image* getImg() { return img; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

