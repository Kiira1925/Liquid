// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "scene_choice.h"
#include "easing.h"

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


void Stage_Select::init(Stage_Select* stage_select) 
{
    stage_select->handle = LoadGraph("Data\\Images\\select.png");
    stage_select->numStage = 0;
    stage_select->posX = 1920;
    stage_select->posY = 1080;
    stage_select->timer = 0;
    stage_select->flgtimer = 0;
}

void Stage_Select::update(Stage_Select* stage_select)
{
    switch (numStage)
    {
    case 0:
        // 右に進む ----------------------------------------------------
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 1;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
            { 
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 1;
                    stage_select->timer = 0;
                }
            }
        }

        // 左に進む --------------------------------------------------
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 8;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 8;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 1:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 2;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 2;
                    stage_select->timer = 0;
                }
            }
        }

        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 0;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 0;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 2:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 3;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 3;
                    stage_select->timer = 0;
                }             
            }
        }


        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 1;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 1;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 3:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 4;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 4;
                    stage_select->timer = 0;
                }
            }
        }

        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 2;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 2;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 4:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 5;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 5;
                    stage_select->timer = 0;
                }
            }
        }

        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 3;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 3;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 5:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 6;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 6;
                    stage_select->timer = 0;
                }
            }
        }

        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 4;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 4;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 6:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 7;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 7;
                    stage_select->timer = 0;
                }             
            }
        }

        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 5;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 5;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 7:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 8;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 8;
                    stage_select->timer = 0;
                }              
            }
        }
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 6;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 6;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    case 8:
        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
        {
            stage_select->numStage = 0;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 0;
                    stage_select->timer = 0;
                }
            }
        }

        if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
        {
            stage_select->numStage = 7;
            stage_select->timer = 0;
        }
        else {
            if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                stage_select->timer++;
                if (stage_select->timer == 60) {
                    stage_select->numStage = 7;
                    stage_select->timer = 0;
                }
            }
        }

        break;
    }
}

void Stage_Select::draw(Stage_Select* stage_select)
{
  
    DrawRectGraph(0, 0, stage_select->posX * (stage_select->numStage % 3), stage_select->posY * (stage_select->numStage / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
   // DrawRectGraph(0, 0, stage_select->flgtimer, stage_select->posY * (stage_select->numStage / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);

}

void Stage_Select::end(Stage_Select* stage_select)
{

}

int StageNum(int number) 
{
    return number + 1;
}

