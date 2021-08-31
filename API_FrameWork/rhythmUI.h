#pragma once
#include "gameNode.h"

struct tagerhythm {
	image* _bluebeatImg;
	image* _greenbeatImg;
	image* _redbeatImg;
	RECT rc;
	float x, y;
	float speed;
	bool iscol;
	float count;
};

class wallManager;
class rhythmUI :public gameNode
{
private:
	image* _heartImage;
	animation* _heartAni;
	wallManager* _wm;
	int spawnbeat;
	RECT rc;
	float _heartX;
	float _heartY;
private:
	vector<tagerhythm> _vbeat;
	vector<tagerhythm>::iterator _vibeat;
	bool _isDebug;
public:
	rhythmUI();
	~rhythmUI();
	HRESULT init();
	void release();
	void update(); //계산하는곳
	void render();
	void UIrender();
	void spawnBeat(int x , int y);
	void moveBeat();
	void step();
	bool checkstep();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	void setwallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	vector<tagerhythm>& getVbeat() { return _vbeat; }
	vector<tagerhythm>::iterator& getVIbeat() { return _vibeat; }
};

