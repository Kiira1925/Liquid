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

    if (Input::GetInstance()->GetKey(KEY_INPUT_RETURN)) { usable->changeSceneStateInit(Game); }
}

void Stage_Select::init(Stage_Select* stage_select) 
{
    stage_select->handle = LoadGraph("Data\\Images\\select1.png");
    stage_select->numStage = 0;
    stage_select->posX = 0;
    stage_select->posY = 0;
    stage_select->timer = 0;
    stage_select->flg = 0;
    stage_select->ease = 0.0f;
}

void Stage_Select::update(Stage_Select* stage_select)
{
 

    if (stage_select->flg == 0) {
        switch (numStage)
        {
        case 0:
            // 右に進む ----------------------------------------------------
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
                {
                    stage_select->flg = 1;
                }
            }

            // 左に進む --------------------------------------------------
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 1:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->numStage = 0;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 2:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }


            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 3:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;

            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 4:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 5:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 6:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 7:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        case 8:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                stage_select->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    stage_select->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                stage_select->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    stage_select->flg = 2;
                }
            }

            break;
        }
    }
    if (stage_select->flg == 1) 
    {
        
        stage_select->ease = Back::easeOut(stage_select->timer, 0, 1,25);
        stage_select->timer++;
        stage_select->posX = (1920*stage_select->ease);

        if (stage_select->timer ==25) 
        {
            stage_select->posX = 0;
            stage_select->flg = 0;
            stage_select->numStage++;
            stage_select->timer = 0;
            stage_select->ease = 0;
            if (stage_select->numStage == 9)
            {
                stage_select->numStage = 0;
            }
        }
    }
    else if (stage_select->flg == 2) 
    {
        stage_select->ease = Back::easeOut(stage_select->timer, 0, -1, 25);
        stage_select->timer++;
        stage_select->posX = (1920 * stage_select->ease);
        if (stage_select->posX == -1920)
        {
            stage_select->posX = 0;
            stage_select->flg = 0;
            stage_select->numStage--;
            stage_select->timer = 0;
            stage_select->ease = 0;
            if (stage_select->numStage == -1)
            {
                stage_select->numStage = 8;
            }
        }
    }
  
}

void Stage_Select::draw(Stage_Select* stage_select)
{
    //DrawRectGraph(stage_select->posX - stage_select->sizeX, 0, stage_select->sizeX * ((stage_select->numStage - 1) % 3), stage_select->sizeY * ((stage_select->numStage - 1) / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
    //DrawRectGraph(posX, 0, stage_select->sizeX * (stage_select->numStage % 3), stage_select->sizeY * (stage_select->numStage / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
    //DrawRectGraph(stage_select->posX + stage_select->sizeX, 0, stage_select->sizeX * ((stage_select->numStage + 1) % 3), stage_select->sizeY * ((stage_select->numStage + 1) / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
     DrawRectGraph(0, 0, (stage_select->sizeX)*(stage_select->numStage+1) + stage_select->posX, stage_select->sizeY*0, stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
     DrawFormatString(0, 80, GetColor(0, 0, 0), "%f", stage_select->ease);
     DrawFormatString(0, 100, GetColor(0, 0, 0), "%d", stage_select->numStage);
}

void Stage_Select::end(Stage_Select* stage_select)
{
    
}

int Stage_Select::reNum(Stage_Select* stage_select) 
{
    return  stage_select->numStage+ 1;
}
