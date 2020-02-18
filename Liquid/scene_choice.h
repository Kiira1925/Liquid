#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"
#include "main.h"

// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class Choice_Bg : public Sprite
{
public:
    void init(Choice_Bg* choice_bg);
    void update(Choice_Bg* choice_bg);
    void draw(Choice_Bg* choice_bg);
    void end(Choice_Bg* choice_bg);

private:

};

class Choice_Conduct
{
public:
    void updateDebug(Choice_Conduct* choice_conduct, Usable* usable);   // デバッグ用の更新処理

};