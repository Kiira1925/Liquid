#include "main.h"
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "scene_choice.h"
#include "scene_game.h"
#include "scene_title.h"
#include "system.h"
#include "map.h"
#include "relative.h"
#include "player.h"
#include "block.h"

//////////////////////////////////////////////////////////////////////////
//	各ゲームで使用するクラスインスタンスやグローバル変数はここに記述
//

Usable          usable;
System          sys;
Scene_Title     title;
Title_Bg        title_bg;
Title_Conduct   title_conduct;
Scene_Choice    choice;
Choice_Bg       choice_bg;
Choice_Conduct  choice_conduct;
Scene_Game      game;
Game_Bg         game_bg;
Game_Conduct    game_conduct;
Map             map;
Relative        relative;

Scene_State     state;


//
// 定義ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからタイトルの処理
//

// タイトル初期化処理
void Scene_Title::init(void)
{
    title_bg.init(&title_bg);
}

// タイトル更新処理
void Scene_Title::update(int GameTime)
{
    title_bg.update(&title_bg);
    title_conduct.updateDebug(&title_conduct, &usable);     // debug
}

// タイトル描画処理
void Scene_Title::draw(int GameTime)
{
    title_bg.draw(&title_bg);
    sys.drawDebugString();      // debug

}

// タイトル終了処理
void Scene_Title::end(void)
{
    title_bg.end(&title_bg);
}

//
//	タイトルの処理ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからステージ選択の処理
//

// ステージ選択初期化処理
void Scene_Choice::init(void)
{
    choice_bg.init(&choice_bg);
    Stage_Select::getInstance()->init();
}

// ステージ選択更新処理
void Scene_Choice::update(int GameTime)
{
    choice_bg.update(&choice_bg);

    Stage_Select::getInstance()->update();

    choice_conduct.updateDebug(&choice_conduct, &usable);   // debug
}

// ステージ選択描画処理
void Scene_Choice::draw(int GameTime)
{
    choice_bg.draw(&choice_bg);

    Stage_Select::getInstance()->draw();

    sys.drawDebugString();              // debug
}

// ステージ選択終了処理
void Scene_Choice::end(void)
{
    choice_bg.end(&choice_bg);

    Stage_Select::getInstance()->end();
}

//
//	ステージ選択の処理ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからゲームの処理
//

// ゲーム初期化処理
void Scene_Game::init(void)
{
    game_bg.init(&game_bg);
    map.init(Stage_Select::getInstance()->reNum());
    Player::getInstance()->init();

}

// ゲーム更新処理
void Scene_Game::update(int GameTime)
{
    relative.cal_relative_pos();
    game_bg.update(&game_bg);
    map.update();
    Player::getInstance()->update();

    game_conduct.updateDebug(&game_conduct, &usable);   // debug
}

// ゲーム描画処理
void Scene_Game::draw(int GameTime)
{
    game_bg.draw(&game_bg);
    map.draw();
    Player::getInstance()->draw();

    sys.drawDebugString();      // debug

}

// ゲーム終了処理
void Scene_Game::end(void)
{
    game_bg.end(&game_bg);
}

//
//	ゲームの処理ここまで
//////////////////////////////////////////////////////////////////////////

// DirectX初期化前処理
void Usable::BeforeInit(void)
{
    //int mbResult;
    int win_mode = TRUE;
    //
    //// フルスクリーンにするか選択する
    //mbResult = MessageBox(NULL, STR_MSG_ASKFS, STR_MSGTTL_ASKFS, MB_YESNO);
    //if (mbResult == IDYES) win_mode = FALSE;
    ChangeWindowMode(win_mode);
    // ウィンドウタイトルを設定する
    SetMainWindowText(STR_WINTTL);
}

// ゲーム開始前処理
void Usable::AfterInit(void)
{
    // InputClass
    Input::Create();
    Input::GetInstance()->Init();

    state = Title;
    title.init();
}

// ゲーム終了後処理
void Usable::End(void)
{
    // InputClassの終了処理
    Input::Destroy();
    // 全グラフィックの削除
    DxLib::InitGraph();
    // 全音データの削除
    InitSoundMem();
}

// シーン遷移処理
void Usable::changeSceneStateInit(Scene_State next_num)
{
    // 現在のシーンの終了処理
    switch (state)
    {
    case Title:
        title.end();
        break;
    case Choice:
        choice.end();
        break;
    case Game:
        game.end();
        break;
    }

    // シーン遷移時に初期化
    switch (next_num)
    {
    case Title:
        title.init();
        break;
    case Choice:
        choice.init();
        break;
    case Game:
        game.init();
        break;
    }

    state = next_num;
}

// ゲームメインループ
void Usable::MainLoop(void)
{
    unsigned int gameTime = 0;			// グローバルゲームカウンタ

    usable.AfterInit();    // ゲーム開始前処理

    while (ProcessMessage() == 0)		    // ProcessMessageが正常に処理されている間はループ
    {
        ClearDrawScreen();  				// 裏画面を削除

        Input::GetInstance()->Updata();     // 入力状態の更新処理

        switch (state)
        {
        case Title:
            title.update(gameTime);         // タイトル更新処理
            title.draw(gameTime);           // タイトル描画処理
            break;
        case Choice:
            choice.update(gameTime);        // ステージ選択更新処理
            choice.draw(gameTime);          // ステージ選択描画処理
            break;
        case Game:
            game.update(gameTime);          // ゲーム更新処理
            game.draw(gameTime);            // ゲーム描画処理
            break;
        }

        ScreenFlip();   // VSYNCを待つ

        // ESCキーだけは常に監視。押されたら直ちに終了
        int stick = CheckHitKey(KEY_INPUT_ESCAPE);
        if (stick == 1) break;
        gameTime++;						// ゲームカウンタを進める
    }
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    usable.BeforeInit();                // DirectX初期化前処理
    if (DxLib_Init() == -1) return -1;  // エラーが起きたら直ちに終了

    SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);
    SetDrawScreen(DX_SCREEN_BACK);      // 描画スクリーンを裏側に指定
    SetWaitVSyncFlag(TRUE);             // VSYNCを有効にする
    usable.AfterInit();                 // DirectX初期化後処理
    usable.MainLoop();                  // ゲーム本体(メインループ)
    usable.End();                       // ゲーム終了後処理
    DxLib_End();                        // ＤＸライブラリ使用の終了処理
    return 0;                           // ソフトの終了
}
