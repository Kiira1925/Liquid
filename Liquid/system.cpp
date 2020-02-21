// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "system.h"

#include "input.h"
#include "player.h"
#include "singleton.h"
#include "scene_choice.h"

// 関数 ----------------------------------------------------------------------------------------
// デバック文字を描画
void System::drawDebugString()
{
    cr = GetColor(255, 255, 255);

    DrawFormatString(0, 0, cr, "Title:1");
    DrawFormatString(0, 20, cr, "Choice:2");
    DrawFormatString(0, 40, cr, "Game:3");
    DrawFormatString(0, 140, cr, "%d", Player::getInstance()->posNumX);
    DrawFormatString(0, 160, cr, "%d", Player::getInstance()->getPosX());
    DrawFormatString(0, 200, cr, "%d", Player::getInstance()->posNumY);
    DrawFormatString(0, 220, cr, "%d", Player::getInstance()->getPosY());
    DrawFormatString(0, 260, cr, "%d", Stage_Select::getInstance()->reNum());
}