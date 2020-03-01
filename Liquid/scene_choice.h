#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"
#include "main.h"
#include "singleton.h"

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
class Stage_Select :public Sprite,public Singleton<Stage_Select>
{
public:
    void init();
    void update();
    void draw();
    void end();
    int reNum();

    int numStage;
    int timer;
    int flg;
    float ease;
    float easePosX;
    
private:
    int sizeX = 1920;
    int sizeY = 1080;
};

// プロトタイプ宣言 --------------------------------------------------------
void BlackOut(int* BB_handle, int* BB_timer, Usable* usable);