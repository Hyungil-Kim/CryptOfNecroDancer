#include "framework.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI()
{
    emptyheart = IMAGE->addImage("빈하트", "images/UI/heart_empty.bmp", 24*2, 22*2, true);
    heart = IMAGE->addImage("하트", "images/UI/heart.bmp", 24 * 2, 22 * 2, true);
    halfheart = IMAGE->addImage("절반하트", "images/UI/heart_half.bmp", 24 * 2, 22 * 2, true);

  
}

PlayerUI::~PlayerUI()
{
}

HRESULT PlayerUI::init()
{
    Maxhp = PLAYER->getPlayerAddress().maxhp;
    curhp = 12;//PLAYER->getPlayerAddress().hp;
    return S_OK;
}

void PlayerUI::release()
{
}

void PlayerUI::update()
{
    gethp();
}

void PlayerUI::render(HDC hdc)
{
    playerhpUI();
  

}

void PlayerUI::gethp()
{
    Maxhp = PLAYER->getPlayerAddress().maxhp;
    curhp = PLAYER->getPlayerAddress().hp;


}

void PlayerUI::playerhpUI()
{
    //empty heart
    for (int i = 0; i < Maxhp / 2; i++)
    {
        int k;
        if (i / 5 < 1) k = 0;
        else  k = 1;
        {
            ZORDER->UIRender(emptyheart, 8, 0, WINSIZEX - i % 5 * 50 - 50, 50 + k * 50);
        }
    }
    for (int i = 0; i < curhp / 2; i++)
    {

        int k;
        if (i / 5 < 1) k = 0;
        else  k = 1;
        {
            ZORDER->UIRender(heart, 9, 0, WINSIZEX - (i % 5 + 1) * 50, 50 + k * 50);
        }

        if (curhp % 2 != 0)
        {
            int t = curhp / 2;
            int k;
            if (i / 4 < 1) k = 0;
            else  k = 1;
            {
                ZORDER->UIRender(halfheart, 9, 0, WINSIZEX - (t % 5 + 1) * 50, 50 + k * 50);
            }
        }
    }
}

