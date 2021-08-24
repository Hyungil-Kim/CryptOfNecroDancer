#include "framework.h"
#include "Player.h"
#include"dummyMap.h"
HRESULT Player::init()
{
	_player.hp = 12;
	_player.atk = 0;
	_player.def = 0;
	_player.sight = 2;
	_player.sholve = 0;
	_player.ishit = false;
	_player.x = 50;
	_player.y = 50;
	_player._speed = 1800;
	_player.hitFireTile = false;
	_player.hitIceTile = false;
	_movestate = MOVESTATE::RIGHT;
	_player.isCurrentRight = true;
	player_headL=IMAGE->addFrameImage("�÷��̾���ʸӸ�", "images/player/player_headL.bmp", 384, 48 , 16, 2, true, RGB(255, 0, 255));
	player_bodyL=IMAGE->addFrameImage("�÷��̾���ʸ�", "images/player/player_bodyL.bmp", 384 , 336 , 16, 14, true, RGB(255, 0, 255));
	player_headR=IMAGE->addFrameImage("�÷��̾�����ʸӸ�", "images/player/player_headR.bmp", 384 , 48 , 16, 2, true, RGB(255, 0, 255));
	player_bodyR=IMAGE->addFrameImage("�÷��̾�����ʸ�", "images/player/player_bodyR.bmp", 384 , 336 , 16, 14, true, RGB(255, 0, 255));
	
	Aplayer_headL=ANIMATION->addNoneKeyAnimation("�÷��̾���ʸӸ�", 15, 13, 10, false, true);
	Aplayer_bodyL=ANIMATION->addNoneKeyAnimation("�÷��̾���ʸ�", 15,13,10, false, true);
	Aplayer_headR=ANIMATION->addNoneKeyAnimation("�÷��̾�����ʸӸ�", 0,3, 10, false, true);
	Aplayer_bodyR=ANIMATION->addNoneKeyAnimation("�÷��̾�����ʸ�", 0,3, 10, false, true);

	_player.player_rc = RectMake(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
	
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	this->inputCheck();
	this->inputDirectionCheck();
	this->stateCheck();
	this->moveCharater();
	_player.player_rc = RectMake(_player.x, _player.y, player_headL->getFrameWidth(), player_bodyL->getFrameHeight());
}

void Player::render(HDC hdc)
{
	char strBlock[128];
	sprintf_s(strBlock, "������ġ  X: %d�� Ÿ��, Y: %d�� Ÿ��", tileX, tileY);
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 300, 10, strBlock, strlen(strBlock));
	if (_state == STATE::STOP)
	{
		if ((_player.isCurrentRight == false && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == false && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == false && _movestate ==MOVESTATE::LEFT))
		{
			ZORDER->ZorderAniRender(player_headL, 4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL, 4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyL);
		}
		else if ((_player.isCurrentRight == true && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == true && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == true && _movestate == MOVESTATE::RIGHT))
		{
			ZORDER->ZorderAniRender(player_headR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyR);
		}
	}
	if (_state == STATE::MOVE)
	{
		if ((_player.isCurrentRight == false && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == false && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == false && _movestate == MOVESTATE::LEFT))
		{
			ZORDER->ZorderAniRender(player_headL,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyL);
		}
		else if ((_player.isCurrentRight == true && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == true && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == true && _movestate == MOVESTATE::RIGHT))
		{
			ZORDER->ZorderAniRender(player_headR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyR);
		}
	}
	

	//ZORDER->ZorderAniRender(player_headR, 3, player_body_rc.bottom,x,y, Aplayer_headR);
	//ZORDER->ZorderAniRender(player_bodyR, 3, player_body_rc.bottom,x,y, Aplayer_bodyR);
	if (_isDebug)
	{
		ZORDER->ZorderRectangle(_player.player_rc, 3);
		//ZORDER->ZorderRectangle(player_head_rc, 4);
		//ZORDER->ZorderRectangle(player_body_rc, 4);
	}
}



void Player::moveCharater()
{
	switch (_state)
	{
	case STATE::STOP:    
		break;
	case STATE::ATTACK:
		break;
	case STATE::DIGGING:
		break;
	case STATE::MOVE:
		playMove();
	case STATE::HIT:
		break;
	default:
		break;
	}
}

void Player::inputCheck()
{
	if (INPUT->isOnceKeyDown(VK_RIGHT))
	{
		_inputdirection.isRight = true;
		_inputdirection.isLeft = false;
		_player.isCurrentRight = true;
		
	}
	else _inputdirection.isRight = false;

	if (INPUT->isOnceKeyDown(VK_LEFT))
	{
		_inputdirection.isLeft = true;
		_inputdirection.isRight = false;
		_player.isCurrentRight = false;
	}
	else _inputdirection.isLeft = false;

	if (INPUT->isOnceKeyDown(VK_UP)) 
		_inputdirection.isUp = true;
	else _inputdirection.isUp = false;

	if (INPUT->isOnceKeyDown(VK_DOWN))
		_inputdirection.isDown = true;
	else _inputdirection.isDown = false;
	
}

void Player::stateCheck()
{
	if (_inputdirection.isRight || _inputdirection.isLeft || _inputdirection.isDown || _inputdirection.isUp)
	{
		_state = STATE::MOVE;
	}
	else
	{
		_state = STATE::STOP;
	}
}

void Player::inputDirectionCheck()
{
	if (_inputdirection.isLeft == true) _movestate = LEFT;
	
	if (_inputdirection.isRight == true ) _movestate = RIGHT;
	
	if (_inputdirection.isDown == true)_movestate = DOWN;
	if (_inputdirection.isUp == true) _movestate = UP;


}

void Player::changeAttackRange()
{
	
}

void Player::playMove()
{
	RECT rcCollision;
	int tileIndex[2] = { 0, };//�˻�� Ÿ��
	rcCollision = _player.player_rc;

	float elpasedTime = TIME->getElapsedTime();

	float moveSpeed = elpasedTime * _player._speed;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_movestate)
	{
	case MOVESTATE::LEFT:
		
		_player.x -= moveSpeed;
		rcCollision = RectMakeCenter(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
		break;
	case MOVESTATE::RIGHT:
		
		_player.x += moveSpeed;
		rcCollision = RectMakeCenter(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
		break;
	case MOVESTATE::UP:
		
		_player.y -= moveSpeed;
		rcCollision = RectMakeCenter(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
		break;
	case MOVESTATE::DOWN:
		
		_player.y += moveSpeed;
		rcCollision = RectMakeCenter(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
		break;
	}

	switch (_movestate)
	{
	case MOVESTATE::LEFT:
		tileIndex[0] = tileX + tileY * TILEX;//��ũ�� ��� �ִ� �༮
		tileIndex[1] = tileX + (tileY + 1) * TILEX;//��ũ�� ��� �ִ� ����
		break;
	case MOVESTATE::RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;//��ũ�� ��� �ִ� ������
		break;
	case MOVESTATE::UP:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + 1 + tileY * TILEX;
		break;
	case MOVESTATE::DOWN:
		tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	}
	for (size_t i = 0; i < 2; i++)
	{
		RECT rc;

		//�ش� Ÿ���� �Ӽ��� �������� ���ϴ� ���̸�
		if (((_dummyMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVABLE) == ATTR_UNMOVABLE) &&
			IntersectRect(&rc, &_dummyMap->getMap()[tileIndex[i]].rcTile, &rcCollision))
		{
			switch (_movestate)

			{
			case MOVESTATE::LEFT:

				_player.player_rc.left = _dummyMap->getMap()[tileIndex[i]].rcTile.right;//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_player.player_rc.right = _player.player_rc.left + player_bodyL->getFrameWidth();			//��ũ�� ũ�⸸ŭ
				_player.x = _player.player_rc.left + (_player.player_rc.right - _player.player_rc.left) / 2;				//��ũ X�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����)
				break;
			case MOVESTATE::RIGHT:
				_player.player_rc.right = _dummyMap->getMap()[tileIndex[i]].rcTile.left;
				_player.player_rc.left = _player.player_rc.right - player_bodyL->getFrameWidth();
				_player.x = _player.player_rc.left + (_player.player_rc.right - _player.player_rc.left) / 2;
				break;
			case MOVESTATE::UP:
				_player.player_rc.top = _dummyMap->getMap()[tileIndex[i]].rcTile.bottom;
				_player.player_rc.bottom = _player.player_rc.top + player_bodyL->getFrameHeight();
				_player.y = _player.player_rc.top + (_player.player_rc.bottom - _player.player_rc.top) / 2;
				break;
			case MOVESTATE::DOWN:
				_player.player_rc.bottom = _dummyMap->getMap()[tileIndex[i]].rcTile.top;
				_player.player_rc.top = _player.player_rc.bottom - player_bodyL->getFrameHeight();
				_player.y = _player.player_rc.top + (_player.player_rc.bottom - _player.player_rc.top) / 2;
				break;
			}
			return;
		}

	}//end of for
	rcCollision = RectMake(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
	_player.player_rc = rcCollision;
}


