#pragma once
#include "CObstacle.h"
struct tagWall
{
	image* img;
	animation* ani;
	RECT rc;
	RECT colrc;
	WALL_TYPE _wallType;
	float x, y;
	int hard;
	bool canBreakWall = false;
	bool isDetecting = false;
	bool isHit = false;
	bool isDead = false;



};
class wallManager;
class realwallManager;
class CWall: public CObstacle
{
	protected:
		vector<tagWall> _vWall;
		vector<tagWall>::iterator _viWall;
		wallManager* _wm;
		bool _isDebug;
	public:
		CWall();
		~CWall();

		HRESULT init();
		void release();
		void update(); 
		void render();

		virtual void addWall(float x, float y);
	

		virtual void setWallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
		virtual void setrealWallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
		vector<tagWall>& getVWall() { return _vWall; }
		vector<tagWall>::iterator& getVIWall() { return _viWall; }
		void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
