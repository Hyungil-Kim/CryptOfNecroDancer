#pragma once
#include "gameNode.h"
struct tagWall
{
	image* img;
	animation* ani;
	RECT rc;
	float x, y;
	int hp;
	bool canBreakWall = false;
	bool isDetecting = false;
	bool isHit = false;
	bool isDead = false;

};
class CWall: public gameNode
{
	protected:
		vector<tagWall> _vWall;
		vector<tagWall>::iterator _viWall;

		bool _isDebug;
	public:
		CWall();
		~CWall();

		HRESULT init();
		void release();
		void update();//플레이어 위치 참고하기위해 
		void render();

		virtual void addWall(float x, float y);
	


		vector<tagWall>& getVMonster() { return _vWall; }
		void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
