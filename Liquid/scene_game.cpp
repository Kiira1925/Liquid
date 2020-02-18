// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "input.h"
#include "scene_game.h"

// 関数 ----------------------------------------------------------------------------------------
void Game_Bg::init(Game_Bg* game_bg)
{
    game_bg->handle = LoadGraph("Data\\Images\\Game_Bg.png");
}

void Game_Bg::update(Game_Bg* game_bg)
{

}

void Game_Bg::draw(Game_Bg* game_bg)
{
    DrawGraphF(game_bg->posX, game_bg->posY, game_bg->handle, true);
}

void Game_Bg::end(Game_Bg* game_bg)
{
    DeleteGraph(game_bg->handle);
}

void Game_Conduct::updateDebug(Game_Conduct* game_conduct, Usable* usable)
{
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_1)) usable->changeSceneStateInit(Title);
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_2)) usable->changeSceneStateInit(Choice);
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_3)) usable->changeSceneStateInit(Game);
}