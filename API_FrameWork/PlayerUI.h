#pragma once
#include "singleton.h"

class PlayerUI:public Singleton<PlayerUI>
{
private:
	image* heart;
	image* halfheart;
	image* emptyheart;
	

	int Maxhp;
	int curhp;
	int monstermaxhp;
	int monsterhp;
public:
	PlayerUI();
	~PlayerUI();
	HRESULT init();
	void release();
	void update(); //����ϴ°�
	void render(HDC hdc);
	void gethp();
	void playerhpUI();
};

