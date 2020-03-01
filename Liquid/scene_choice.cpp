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

void BlackOut(int* BB_handle,int* BB_timer, Usable* usable)
{
    *(BB_timer)+=1;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (*(BB_timer) * 3));
    DrawGraph(0, 0, *(BB_handle), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    if (*(BB_timer) > 85)
    {
        usable->changeSceneStateInit(Game);
    }
}

void Choice_Conduct::updateDebug(Choice_Conduct* choice_conduct, Usable* usable)
{
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_1)) usable->changeSceneStateInit(Title);
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_2)) usable->changeSceneStateInit(Choice);
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_3)) usable->changeSceneStateInit(Game);
    if (Stage_Select::getInstance()->flg == 0) {
        //if (Input::GetInstance()->GetKey(KEY_INPUT_RETURN)) { BlackOut(BB_handle); } //usable->changeSceneStateInit(Game);
    }
}

void Stage_Select::init() 
{
    handle = LoadGraph("Data\\Images\\select1.png");
    Stage_Select::getInstance()->numStage = 0;
    timer = 0;
    Stage_Select::getInstance()->flg = 0;
    ease = 0.0f;
    easePosX = 0.0f;
}

void Stage_Select::update()
{
 

    if (Stage_Select::getInstance()->flg == 0) {
        switch (Stage_Select::getInstance()->numStage)
        {
        case 0:
            // 右に進む ----------------------------------------------------
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
                {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            // 左に進む --------------------------------------------------
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 1:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 2:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }


            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 3:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;

            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 4:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 5:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 6:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 7:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        case 8:
            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
            {
                Stage_Select::getInstance()->flg = 1;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) {
                    Stage_Select::getInstance()->flg = 1;
                }
            }

            if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
            {
                Stage_Select::getInstance()->flg = 2;
            }
            else {
                if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT)) {
                    Stage_Select::getInstance()->flg = 2;
                }
            }

            break;
        }
    }
    if (Stage_Select::getInstance()->flg == 1) 
    {
        
        ease = Back::easeOut(timer, 0, 1,25);
        timer++;
        easePosX = (1920*ease);

        if (timer ==25) 
        {
            easePosX = 0;
            Stage_Select::getInstance()->flg = 0;
            Stage_Select::getInstance()->numStage++;
            timer = 0;
            ease = 0;
            if (Stage_Select::getInstance()->numStage == 9)
            {
                Stage_Select::getInstance()->numStage = 0;
            }
        }
    }
    else if (Stage_Select::getInstance()->flg == 2) 
    {
        ease = Back::easeOut(timer, 0, -1, 25);
        timer++;
        easePosX = (1920 * ease);
        if (easePosX == -1920)
        {
            easePosX = 0;
            Stage_Select::getInstance()->flg = 0;
            Stage_Select::getInstance()->numStage--;
            timer = 0;
            ease = 0;
            if (Stage_Select::getInstance()->numStage == -1)
            {
                Stage_Select::getInstance()->numStage = 8;
            }
        }
    }
}

void Stage_Select::draw()
{
    //DrawRectGraph(stage_select->posX - stage_select->sizeX, 0, stage_select->sizeX * ((stage_select->numStage - 1) % 3), stage_select->sizeY * ((stage_select->numStage - 1) / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
    //DrawRectGraph(posX, 0, stage_select->sizeX * (stage_select->numStage % 3), stage_select->sizeY * (stage_select->numStage / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
    //DrawRectGraph(stage_select->posX + stage_select->sizeX, 0, stage_select->sizeX * ((stage_select->numStage + 1) % 3), stage_select->sizeY * ((stage_select->numStage + 1) / 3), stage_select->sizeX, stage_select->sizeY, stage_select->handle, true, false);
     DrawRectGraph(0, 0, (sizeX)*(Stage_Select::getInstance()->numStage+1) + easePosX, sizeY*0, sizeX, sizeY, handle, true, false);
     DrawFormatString(0, 80, GetColor(0, 0, 0), "%f", ease);
     DrawFormatString(0, 100, GetColor(0, 0, 0), "%d", Stage_Select::getInstance()->numStage);
}

void Stage_Select::end()
{
    
}

int Stage_Select::reNum() 
{
    int num = Stage_Select::getInstance()->numStage + 1;
    return  num;
}