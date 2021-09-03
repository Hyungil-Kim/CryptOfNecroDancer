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
class monsterManager;
class wallManager;
class rhythmUI :public gameNode
{
private:
	image* _heartImage;
	animation* _heartAni;
	wallManager* _wm;
	monsterManager* _mm;
	int spawnbeat;
	RECT rc;
	float _heartX;
	float _heartY;
	float _check;
private:
	vector<tagerhythm> _vbeat;
	vector<tagerhythm>::iterator _vibeat;
	bool _isDebug;
public:
	rhythmUI();
	~rhythmUI();
	HRESULT init();
	void release();
	void update(); //����ϴ°�
	void render();
	void UIrender();
	void spawnBeat(int x , int y);
	void moveBeat();
	void step();
	bool checkstep();
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
	void setwallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { _mm = monsterManager; }
	vector<tagerhythm>& getVbeat() { return _vbeat; }
	vector<tagerhythm>::iterator& getVIbeat() { return _vibeat; }
};

