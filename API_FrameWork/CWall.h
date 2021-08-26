#pragma once
#include "gameNode.h"
struct tagWall
{
	image* img;
	animation* ani;
	RECT rc;
	WALL_TYPE _wallType;
	float x, y;
	int hard;
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
		void update();//�÷��̾� ��ġ �����ϱ����� 
		void render();

		virtual void addWall(float x, float y);
	


		vector<tagWall>& getVMonster() { return _vWall; }
		void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
