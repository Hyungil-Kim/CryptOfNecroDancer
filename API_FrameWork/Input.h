#pragma once
#include "singleton.h"
#include<bitset>
#define KEYMAX 256
class Input : public Singleton<Input>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	bool isAnyKeyDown;
public:
	Input();
	~Input();

	HRESULT init();
	void release();

	bool isOnceKeyDown(int key); //한번만 눌렀냐
	bool isOnceKeyUp(int key); //한번눌럿다가뗏냐
	bool isStayKeyDown(int key); //누르고있냐
	bool isToggleKey(int key);//토글키냐

	bool getAnyKeyDown() { return isAnyKeyDown; }
	void setAnyKeyDown(bool isAnyKeyDown) { this->isAnyKeyDown = isAnyKeyDown; }
};

