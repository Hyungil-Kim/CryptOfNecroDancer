#include "framework.h"
#include "Player.h"

HRESULT Player::init()
{
	hp = 12;
	atk = 0;
	def = 0;
	sight = 2;
	sholve = 0;
	hitFireTile = false;
	hitIceTile = false;
	player_headL=IMAGE->addFrameImage("플레이어왼쪽머리", "images/player/player_headL.bmp", 384*3, 48 * 3, 16, 2, true, RGB(255, 0, 255));
	player_bodyL=IMAGE->addFrameImage("플레이어왼쪽몸", "images/player/player_bodyL.bmp", 384 * 3, 336 * 3, 16, 14, true, RGB(255, 0, 255));
	player_headR=IMAGE->addFrameImage("플레이어오른쪽머리", "images/player/player_headR.bmp", 384 * 3, 48 * 3, 16, 2, true, RGB(255, 0, 255));
	player_bodyR=IMAGE->addFrameImage("플레이어오른쪽몸", "images/player/player_bodyR.bmp", 384 * 3, 336 * 3, 16, 14, true, RGB(255, 0, 255));
	
	Aplayer_headL=ANIMATION->addNoneKeyAnimation("플레이어왼쪽머리", 15, 12, 10, false, true);
	Aplayer_bodyL=ANIMATION->addNoneKeyAnimation("플레이어왼쪽몸", 15,12,10, false, true);
	Aplayer_headR=ANIMATION->addNoneKeyAnimation("플레이어오른쪽머리", 1,4, 10, false, true);
	Aplayer_bodyR=ANIMATION->addNoneKeyAnimation("플레이어오른쪽몸", 1,4, 10, false, true);

	player_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, player_headL->getFrameWidth(), player_headL->getFrameHeight() + player_bodyL->getFrameHeight());
	player_head_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, player_headL->getFrameWidth(), -player_headL->getFrameHeight());
	player_body_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	
}

void Player::render()
{
	if (_isDebug)
	{
		ZORDER->ZorderRectangle(player_rc, 3);
		ZORDER->ZorderRectangle(player_head_rc, 4);
		ZORDER->ZorderRectangle(player_body_rc, 4);
	}
	ZORDER->ZorderAniRender(player_headL, 3, player_body_rc.bottom,WINSIZEX/2 ,WINSIZEY/2 , Aplayer_headL);
	ZORDER->ZorderAniRender(player_bodyL, 3, player_body_rc.bottom,WINSIZEX/2 ,WINSIZEY/2, Aplayer_bodyL);

}


