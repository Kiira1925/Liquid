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

// ステージセレクト管理 --------------------------------------------------------
class Stage_Select :public Sprite
{
public:
    void init(Stage_Select* stage_slect);
    void update(Stage_Select* stage_select);
    void draw(Stage_Select* stage_select);
    void end(Stage_Select* stage_select);
    int reNum(Stage_Select* stage_select);

    int numStage;
    int timer;
    int flg;
    float ease;
private:
    int sizeX = 1920;
    int sizeY = 1080;
};