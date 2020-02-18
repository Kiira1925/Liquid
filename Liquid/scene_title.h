#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"
#include "system.h"

// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class Title_Bg : public Sprite
{
public:
    void init(Title_Bg* title_bg);
    void update(Title_Bg* title_bg);
    void draw(Title_Bg* title_bg);
    void end(Title_Bg* title_bg);

};

class Title_Conduct
{
public:
    void updateDebug(Title_Conduct* title_conduct, Usable* usable);   // デバッグ用の更新処理

};