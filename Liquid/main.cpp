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
#include "liquid.h"
#include "easing.h"

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

Block blocks[BL_MAX];
int poison_hanlde;
int break_handle;
int BB_handle;
int BB_timer;
int BB_flag;

//ステージ切り替え演出用変数
boolean isGoal;
int goal_performance_tiemr;
float easeExpo;
float transparency_amount;
int text_back_handle;
int clear_handle;

//サウンドハンドル
int melt_sound;
int goal_sound;

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
    BB_handle = LoadGraph("Data\\Images\\BB.png");
    BB_timer = 0;
    BB_flag = false;
}

// ステージ選択更新処理
void Scene_Choice::update(int GameTime)
{
    choice_bg.update(&choice_bg);

    Stage_Select::getInstance()->update();
    if (Input::GetInstance()->GetKey(KEY_INPUT_RETURN) && Stage_Select::getInstance()->flg == 0) { BB_flag = true; }

    choice_conduct.updateDebug(&choice_conduct, &usable);   // debug
}

// ステージ選択描画処理
void Scene_Choice::draw(int GameTime)
{
    choice_bg.draw(&choice_bg);

    Stage_Select::getInstance()->draw();
    if (BB_flag)
    {
        BlackOut(&BB_handle, &BB_timer, &usable);
    }

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
    melt_sound = LoadSoundMem("Data\\Sounds\\melt.wav");
    goal_sound = LoadSoundMem("Data\\Sounds\\goal.mp3");
    isGoal = false;
    goal_performance_tiemr = 0;
    transparency_amount = 255;
    game_bg.init(&game_bg);
    map.init(Stage_Select::getInstance()->reNum());
    //map.init(0);
    initField();
    Player::getInstance()->init();

    switch (Stage_Select::getInstance()->reNum())
    {
    case 1:
        blocks[0].init(&blocks[0],7,8);
        blocks[1].init(&blocks[1],7,10);
        break;

    case 2:
        blocks[0].init(&blocks[0],7,8);
        blocks[1].init(&blocks[1], 7, 10);
        break;

    case 3:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;

    case 4:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;

    case 5:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;

    case 6:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;

    case 7:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;

    case 8:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;

    case 9:
        blocks[0].init(&blocks[0], 0, 0);
        blocks[1].init(&blocks[1], 0, 0);
        break;
    }

    poison_hanlde = LoadGraph("Data\\Images\\poisonasset.png");
    break_handle = LoadGraph("Data\\Images\\breaking.png");
    text_back_handle = LoadGraph("Data\\Images\\word_back.png");
    clear_handle = LoadGraph("Data\\Images\\stage_clear.png");
    initLiquid();
}

// ゲーム更新処理
void Scene_Game::update(int GameTime)
{
    relative.cal_relative_pos();
    game_bg.update(&game_bg);
    map.update();
    if (isGoal == false)
    {
        Player::getInstance()->update2(&blocks[0]);
        switch (Stage_Select::getInstance()->reNum())
        {
        case 1:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 2:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 3:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 4:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 5:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 6:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 7:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 8:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;

        case 9:
            blocks[0].update(&blocks[0]);
            blocks[1].update(&blocks[1]);
            break;
        }
    }
    game_conduct.updateDebug(&game_conduct, &usable);   // debug
    countPoison();
    BFS();
    spreadWave(poison_hanlde);
    meltBreakable(&melt_sound);
    BFS_FILL();
    deleteLiquid(&blocks[0]);
    Player::getInstance()->goalCheck(&isGoal);

    if (isGoal)
    {
        if (!CheckSoundMem(goal_sound))
        {
            PlaySoundMem(goal_sound, DX_PLAYTYPE_BACK);
        }
        goal_performance_tiemr++;
        DrawRotaGraph3F(0, 0, 0, 0, 1, 1, 0, text_back_handle, TRUE);
        if (goal_performance_tiemr > 120)
        {
            Stage_Select::getInstance()->numStage++;
            usable.changeSceneStateInit(Game);
        }
    }
}

// ゲーム描画処理
void Scene_Game::draw(int GameTime)
{
    game_bg.draw(&game_bg);
    map.draw();
    drawPoison(poison_hanlde);
    drawWave(poison_hanlde);
    Player::getInstance()->draw();
    map.drawBreakable();
    map.drawSpring();
    switch (Stage_Select::getInstance()->reNum())
    {
    case 1:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 2:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 3:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 4:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 5:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 6:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 7:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 8:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;

    case 9:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        break;
    }
    breakAnimation(break_handle);
    Player::getInstance()->drawHead();

    if (isGoal)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency_amount);
        DrawRotaGraph3F(0, 0, 0, 0, 1, 1, 0, text_back_handle, TRUE);
        SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);
        if (goal_performance_tiemr <= 60)
        {
            easeExpo = Expo::easeOut(goal_performance_tiemr, 0, 1, 60);
            DrawRotaGraph3F((easeExpo * 1920) - 1920, 0, 0, 0, 1, 1, 0, clear_handle, TRUE);
        }
        if (goal_performance_tiemr > 60)
        {
            easeExpo = Expo::easeIn(goal_performance_tiemr - 60, 0, 1, 60);
            DrawRotaGraph3F((easeExpo * 1920), 0, 0, 0, 1, 1, 0, clear_handle, TRUE);
        }
        if (goal_performance_tiemr > 80)
        {
            transparency_amount = 255 - ((goal_performance_tiemr - 80) * (255 / 30));
        }

    }
    sys.drawDebugString();      // debug
}

// ゲーム終了処理
void Scene_Game::end(void)
{
    game_bg.end(&game_bg);
    switch (Stage_Select::getInstance()->reNum())
    {
    case 1:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]); 
        break;

    case 2:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 3:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 4:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 5:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 6:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 7:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 8:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;

    case 9:
        blocks[0].end(&blocks[0]);
        blocks[1].end(&blocks[1]);
        break;
    }

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
