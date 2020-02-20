// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "system.h"

#include "input.h"
#include "player.h"
#include "singleton.h"

// 関数 ----------------------------------------------------------------------------------------
// デバック文字を描画
void System::drawDebugString()
{
    cr = GetColor(255, 255, 255);

    DrawFormatString(0, 0, cr, "Title:1");
    DrawFormatString(0, 20, cr, "Choice:2");
    DrawFormatString(0, 40, cr, "Game:3");
    //DrawFormatString(0, 140, cr, "%f", Player::getInstance()->);
}