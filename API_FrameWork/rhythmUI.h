#pragma once
#include "singleton.h"

struct tagerhythm {
	image* _bluebeatImg;
	image* _greenbeatImg;
	image* _redbeatImg;
	RECT rc;
	float x, y;
	float speed;

};

class wallManager;
class rhythmUI :public Singleton<rhythmUI>
{
private:
	image* _heartImage;
	animation* _heartAni;
	wallManager* _wm;
	float count; //1.9167 115bpm
	int spawnbeat;
	RECT rc;
	float _heartX;
	float _heartY;
private:
	vector<tagerhythm> _vbeat;
	vector<tagerhythm>::iterator _vibeat;
public:
	rhythmUI();
	~rhythmUI();
	HRESULT init();
	void release();
	void update(); //계산하는곳
	void render(HDC hdc);
	void UIrender(HDC hdc);
	void spawnBeat(int x , int y);
	void moveBeat();
	bool step();

	void setwallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	vector<tagerhythm>& getVbeat() { return _vbeat; }
	vector<tagerhythm>::iterator& getVIbeat() { return _vibeat; }
};

