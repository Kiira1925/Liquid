// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "scene_title.h"
#include "main.h"
// 関数 ----------------------------------------------------------------------------------------
void Title_Bg::init(Title_Bg* title_bg)
{
    title_bg->handle = LoadGraph("Data\\Images\\Title_Bg.png");
}

void Title_Bg::update(Title_Bg* title_bg)
{
}

void Title_Bg::draw(Title_Bg* title_bg)
{
    DrawGraphF(title_bg->posX, title_bg->posY, title_bg->handle, true);
}

void Title_Bg::end(Title_Bg* title_bg)
{
    DeleteGraph(title_bg->handle);
}

void Title_Conduct::updateDebug(Title_Conduct* title_conduct, Usable* usable)
{
    //if (Input::GetInstance()->GetKeyDown(KEY_INPUT_1)) usable->changeSceneStateInit(Title);
    //if (Input::GetInstance()->GetKeyDown(KEY_INPUT_2)) usable->changeSceneStateInit(Choice);
    //if (Input::GetInstance()->GetKeyDown(KEY_INPUT_3)) usable->changeSceneStateInit(Game);
}