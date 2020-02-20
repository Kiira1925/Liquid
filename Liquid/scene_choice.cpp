// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "scene_choice.h"

// 関数 ----------------------------------------------------------------------------------------
void Choice_Bg::init(Choice_Bg* choice_bg)
{
    choice_bg->handle = LoadGraph("Data\\Images\\Choice_Bg.png");
}

void Choice_Bg::update(Choice_Bg* choice_bg)
{

}

void Choice_Bg::draw(Choice_Bg* choice_bg)
{
    DrawGraphF(choice_bg->posX, choice_bg->posY, choice_bg->handle, true);
}

void Choice_Bg::end(Choice_Bg* choice_bg)
{
    DeleteGraph(choice_bg->handle);
}

void Choice_Conduct::updateDebug(Choice_Conduct* choice_conduct, Usable* usable)
{
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_1)) usable->changeSceneStateInit(Title);
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_2)) usable->changeSceneStateInit(Choice);
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_3)) usable->changeSceneStateInit(Game);
}


