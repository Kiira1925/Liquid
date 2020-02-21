// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "scene_choice.h"
#include "easing.h"
#include "player.h"
#include "singleton.h"

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

void Stage_Select::init() 
{
    handle = LoadGraph("Data\\Images\\select1.png");
    numStage = 0;
    timer = 0;
    flg = 0;
    ease = 0.0f;
    easePosX = 0.0f;
}

void Stage_Select::update()
{
 

    if (flg == 0) {
        switch (numStage)
        {
        case 0:
            // 右に進む ----------------------------------------------------
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
                {
                    flg = 1;
                }
            }

            // 左に進む --------------------------------------------------
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 1:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 2:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }


            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 3:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;

            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 4:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 5:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 6:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 7:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        case 8:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    flg = 2;
                }
            }

            break;
        }
    }
    if (flg == 1) 
    {
        
        ease = Back::easeOut(timer, 0, 1,25);
        timer++;
        easePosX = (1920*ease);

        if (timer ==25) 
        {
            easePosX = 0;
            flg = 0;
            numStage++;
            timer = 0;
            ease = 0;
            if (numStage == 9)
            {
                numStage = 0;
            }
        }
    }
    else if (flg == 2) 
    {
        ease = Back::easeOut(timer, 0, -1, 25);
        timer++;
        easePosX = (1920 * ease);
        if (easePosX == -1920)
        {
            easePosX = 0;
            flg = 0;
            numStage--;
            timer = 0;
            ease = 0;
            if (numStage == -1)
            {
                numStage = 8;
            }
        }
    }
}

void Stage_Select::draw()
{
    //DrawRectGraph(stage_select->posX - stage_select->sizeX, 0, stage_select->sizeX * ((stage_select->numStage - 1) % 3), stage_select->sizeY * ((stage_select->numStage - 1) / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
    //DrawRectGraph(posX, 0, stage_select->sizeX * (stage_select->numStage % 3), stage_select->sizeY * (stage_select->numStage / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
    //DrawRectGraph(stage_select->posX + stage_select->sizeX, 0, stage_select->sizeX * ((stage_select->numStage + 1) % 3), stage_select->sizeY * ((stage_select->numStage + 1) / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
     DrawRectGraph(0, 0, (sizeX)*(numStage+1) + easePosX, sizeY*0, sizeX, sizeY, handle, true, false);
     DrawFormatString(0, 80, GetColor(0, 0, 0), "%f", ease);
     DrawFormatString(0, 100, GetColor(0, 0, 0), "%d", numStage);
}

void Stage_Select::end()
{
    
}

int Stage_Select::reNum() 
{
    int num = numStage + 1;
    return  num;
}
