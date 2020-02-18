#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"
#include "main.h"

// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class Game_Bg : public Sprite
{
public:
    void init(Game_Bg* game_bg);
    void update(Game_Bg* game_bg);
    void draw(Game_Bg* game_bg);
    void end(Game_Bg* game_bg);

private:

};

class Game_Conduct
{
public:
    void updateDebug(Game_Conduct* game_conduct, Usable* usable);   // デバッグ用の更新処理

};