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
//	�e�Q�[���Ŏg�p����N���X�C���X�^���X��O���[�o���ϐ��͂����ɋL�q
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
int temp_block_state[BL_MAX];

int poison_hanlde;
int break_handle;
int BB_handle;
int BB_timer;
int BB_flag;

int end_timer;
int end_flg;

int RB_timer;
int RB_handle;

int BG_handle;

//�X�e�[�W�؂�ւ����o�p�ϐ�
boolean isGoal;
int goal_performance_tiemr;
float easeExpo;
float transparency_amount;
int text_back_handle;
int clear_handle;

int title_timer;
int title_flg;

//�T�E���h�n���h��
int melt_sound;
int goal_sound;
int block_sound;
int poison_sound;
int select_sound;

//
// ��`�����܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������^�C�g���̏���
//

// �^�C�g������������
void Scene_Title::init(void)
{
    title_bg.init(&title_bg);
    select_sound = LoadSoundMem("Data\\Sounds\\select.mp3");
    title_timer = 0;
    title_flg = false;
}

// �^�C�g���X�V����
void Scene_Title::update(int GameTime)
{
    title_bg.update(&title_bg);
    title_conduct.updateDebug(&title_conduct, &usable);     // debug
    if (Input::GetInstance()->GetKeyDown(KEY_INPUT_Z))
    {
        title_flg = true;
        if (!CheckSoundMem(select_sound)) { PlaySoundMem(select_sound, DX_PLAYTYPE_BACK); }
    }
    if (title_flg == true)
    {
        title_timer++;
        if (title_timer > 60)
        {
            usable.changeSceneStateInit(Choice);
        }
    }
}

// �^�C�g���`�揈��
void Scene_Title::draw(int GameTime)
{
    title_bg.draw(&title_bg);
    sys.drawDebugString();      // debug

}

// �^�C�g���I������
void Scene_Title::end(void)
{
    title_bg.end(&title_bg);
}

//
//	�^�C�g���̏��������܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������X�e�[�W�I���̏���
//

// �X�e�[�W�I������������
void Scene_Choice::init(void)
{
    choice_bg.init(&choice_bg);
    Stage_Select::getInstance()->init();
    BB_handle = LoadGraph("Data\\Images\\BB.png");
    BB_timer = 0;
    BB_flag = false;
    end_timer = 0;
    end_flg = false;
}

// �X�e�[�W�I���X�V����
void Scene_Choice::update(int GameTime)
{
    choice_bg.update(&choice_bg);

    Stage_Select::getInstance()->update();
    if (Input::GetInstance()->GetKey(KEY_INPUT_Z) && Stage_Select::getInstance()->flg == 0)
    {
        BB_flag = true;
        if (!CheckSoundMem(select_sound))
        {
            PlaySoundMem(select_sound, DX_PLAYTYPE_BACK);
        }
    }
    if (Input::GetInstance()->GetKey(KEY_INPUT_END))
    {
        end_flg = true;
        if (!CheckSoundMem(select_sound)) { PlaySoundMem(select_sound, DX_PLAYTYPE_BACK); }
    }
    if (end_flg == true)
    {
        end_timer++;
        if (end_timer > 60)
        {
            usable.changeSceneStateInit(Title);
        }
    }

    choice_conduct.updateDebug(&choice_conduct, &usable);   // debug
}

// �X�e�[�W�I��`�揈��
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

// �X�e�[�W�I���I������
void Scene_Choice::end(void)
{
    choice_bg.end(&choice_bg);

    Stage_Select::getInstance()->end();
}

//
//	�X�e�[�W�I���̏��������܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������Q�[���̏���
//

// �Q�[������������
void Scene_Game::init(void)
{
    blocks[0].init(&blocks[0], 10, 10);
    blocks[1].init(&blocks[1],7,10);

    RB_handle = LoadGraph("Data\\Images\\RB.png");
    RB_timer = 0;

    melt_sound = LoadSoundMem("Data\\Sounds\\melt.wav");
    goal_sound = LoadSoundMem("Data\\Sounds\\goal.mp3");
    block_sound = LoadSoundMem("Data\\Sounds\\Block.ogg");
    poison_sound = LoadSoundMem("Data\\Sounds\\poison.mp3");
    isGoal = false;
    goal_performance_tiemr = 0;
    transparency_amount = 255;
    switch (Stage_Select::getInstance()->reNum())
    {
    case 1:
        BG_handle = LoadGraph("Data\\Images\\stage0.png");
        break;
    case 2:
        BG_handle = LoadGraph("Data\\Images\\stage1.png");
        break;
    case 3:
        BG_handle = LoadGraph("Data\\Images\\stage2.png");
        break;
    case 4:
        BG_handle = LoadGraph("Data\\Images\\stage3.png");
        break;
    case 5:
        BG_handle = LoadGraph("Data\\Images\\stage4.png");
        break;
    case 6:
        BG_handle = LoadGraph("Data\\Images\\stage5.png");
        break;
    case 7:
        BG_handle = LoadGraph("Data\\Images\\stage6.png");
        break;
    case 8:
        BG_handle = LoadGraph("Data\\Images\\stage7.png");
        break;
    case 9:
        BG_handle = LoadGraph("Data\\Images\\stage8.png");
        break;
    }
    //game_bg.init(&game_bg);
    map.init(Stage_Select::getInstance()->reNum());
    //map.init(0);
    initField();
    Player::getInstance()->init();

    switch (Stage_Select::getInstance()->reNum())
    {
    case 1:
        blocks[0].init(&blocks[0],10,10);
        //blocks[1].init(&blocks[1],7,10);
        break;

    case 2:
        blocks[0].init(&blocks[0],10,9);
        //blocks[1].init(&blocks[1], 7, 10);
        break;

    case 3:
        blocks[0].init(&blocks[0], 8, 12);
        blocks[1].init(&blocks[1], 10, 8);
        break;

    case 4:
        blocks[0].init(&blocks[0], 9, 10);
        blocks[1].init(&blocks[1], 11, 12);
        break;

    case 5:
        blocks[0].init(&blocks[0], 11, 9);
        blocks[1].init(&blocks[1], 12, 13);
        break;

    case 6:
        blocks[0].init(&blocks[0], 6, 8);
        blocks[1].init(&blocks[1], 12, 11);
        break;

    case 7:
        blocks[0].init(&blocks[0], 8, 11);
        blocks[1].init(&blocks[1], 11, 16);
        blocks[2].init(&blocks[2], 11, 8);
        break;

    case 8:
        blocks[0].init(&blocks[0], 13, 9);
        blocks[1].init(&blocks[1], 10, 9);
        blocks[2].init(&blocks[2], 8, 11);
        break;

    case 9:
        blocks[0].init(&blocks[0], 4, 14);
        blocks[1].init(&blocks[1], 11, 6);
        blocks[2].init(&blocks[2], 13, 11);
        break;
    }

    end_timer = 0;
    end_flg = false;

    poison_hanlde = LoadGraph("Data\\Images\\poisonasset.png");
    break_handle = LoadGraph("Data\\Images\\breaking.png");
    text_back_handle = LoadGraph("Data\\Images\\word_back.png");
    clear_handle = LoadGraph("Data\\Images\\stage_clear.png");
    initLiquid();
}

// �Q�[���X�V����
void Scene_Game::update(int GameTime)
{
    relative.cal_relative_pos();
    game_bg.update(&game_bg);
    map.update();
    if (isGoal == false)
    {
        Player::getInstance()->update2(&blocks[0],&blocks[0],&temp_block_state[0]);
        switch (Stage_Select::getInstance()->reNum())
        {
        case 1:
            blocks[0].update(&blocks[0],block_sound);
            //blocks[1].update(&blocks[1]);
            break;

        case 2:
            blocks[0].update(&blocks[0], block_sound);
            //blocks[1].update(&blocks[1]);
            break;

        case 3:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            break;

        case 4:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            break;

        case 5:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            break;

        case 6:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            break;

        case 7:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            blocks[2].update(&blocks[2], block_sound);
            break;

        case 8:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            blocks[2].update(&blocks[2], block_sound);
            break;

        case 9:
            blocks[0].update(&blocks[0], block_sound);
            blocks[1].update(&blocks[1], block_sound);
            blocks[2].update(&blocks[2], block_sound);
            break;
        }
    }
    Player::getInstance()->update3(&temp_block_state[0]);
    game_conduct.updateDebug(&game_conduct, &usable,select_sound);   // debug
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
            if (Stage_Select::getInstance()->numStage == 8)
            {
                usable.changeSceneStateInit(Title);
            }
            else
            {
                Stage_Select::getInstance()->numStage++;
                usable.changeSceneStateInit(Game);
            }
        }
    }

    Player::getInstance()->playerDamage(&RB_timer);
    if (RB_timer > 40)
    {
        usable.changeSceneStateInit(Game);
    }
    if (Input::GetInstance()->GetKey(KEY_INPUT_END))
    {
        end_flg = true;
        if (!CheckSoundMem(select_sound)) { PlaySoundMem(select_sound, DX_PLAYTYPE_BACK); }
    }
    if (end_flg == true)
    {
        end_timer++;
        if (end_timer > 60)
        {
            usable.changeSceneStateInit(Title);
        }
    }
}

// �Q�[���`�揈��
void Scene_Game::draw(int GameTime)
{
    //game_bg.draw(&game_bg);
    DrawGraph(0, 0, BG_handle, TRUE);
    map.draw();
    drawPoison(poison_hanlde,poison_sound);
    drawWave(poison_hanlde);
    map.drawGoal();
    Player::getInstance()->draw();
    switch (Stage_Select::getInstance()->reNum())
    {
    case 1:
        blocks[0].draw(&blocks[0]);
        //blocks[1].draw(&blocks[1]);
        break;

    case 2:
        blocks[0].draw(&blocks[0]);
        //blocks[1].draw(&blocks[1]);
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
        blocks[2].draw(&blocks[2]);
        break;

    case 8:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        blocks[2].draw(&blocks[2]);
        break;

    case 9:
        blocks[0].draw(&blocks[0]);
        blocks[1].draw(&blocks[1]);
        blocks[2].draw(&blocks[2]);
        break;
    }
    map.drawBreakable();
    map.drawSpring();
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
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (RB_timer * 6));
    DrawGraph(0, 0, RB_handle, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    sys.drawDebugString();      // debug
}

// �Q�[���I������
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
//	�Q�[���̏��������܂�
//////////////////////////////////////////////////////////////////////////

// DirectX�������O����
void Usable::BeforeInit(void)
{
    //int mbResult;
    int win_mode = TRUE;
    //
    //// �t���X�N���[���ɂ��邩�I������
    //mbResult = MessageBox(NULL, STR_MSG_ASKFS, STR_MSGTTL_ASKFS, MB_YESNO);
    //if (mbResult == IDYES) win_mode = FALSE;
    ChangeWindowMode(win_mode);
    // �E�B���h�E�^�C�g����ݒ肷��
    SetMainWindowText(STR_WINTTL);
}

// �Q�[���J�n�O����
void Usable::AfterInit(void)
{
    // InputClass
    Input::Create();
    Input::GetInstance()->Init();

    state = Title;
    title.init();
}

// �Q�[���I���㏈��
void Usable::End(void)
{
    // InputClass�̏I������
    Input::Destroy();
    // �S�O���t�B�b�N�̍폜
    DxLib::InitGraph();
    // �S���f�[�^�̍폜
    InitSoundMem();
}

// �V�[���J�ڏ���
void Usable::changeSceneStateInit(Scene_State next_num)
{
    // ���݂̃V�[���̏I������
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

    // �V�[���J�ڎ��ɏ�����
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

// �Q�[�����C�����[�v
void Usable::MainLoop(void)
{
    unsigned int gameTime = 0;			// �O���[�o���Q�[���J�E���^

    usable.AfterInit();    // �Q�[���J�n�O����

    while (ProcessMessage() == 0)		    // ProcessMessage������ɏ�������Ă���Ԃ̓��[�v
    {
        ClearDrawScreen();  				// ����ʂ��폜

        Input::GetInstance()->Updata();     // ���͏�Ԃ̍X�V����

        switch (state)
        {
        case Title:
            title.update(gameTime);         // �^�C�g���X�V����
            title.draw(gameTime);           // �^�C�g���`�揈��
            break;
        case Choice:
            choice.update(gameTime);        // �X�e�[�W�I���X�V����
            choice.draw(gameTime);          // �X�e�[�W�I��`�揈��
            break;
        case Game:
            game.update(gameTime);          // �Q�[���X�V����
            game.draw(gameTime);            // �Q�[���`�揈��
            break;
        }

        ScreenFlip();   // VSYNC��҂�

        // ESC�L�[�����͏�ɊĎ��B�����ꂽ�璼���ɏI��
        int stick = CheckHitKey(KEY_INPUT_ESCAPE);
        if (stick == 1) break;
        gameTime++;						// �Q�[���J�E���^��i�߂�
    }
}

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    usable.BeforeInit();                // DirectX�������O����
    if (DxLib_Init() == -1) return -1;  // �G���[���N�����璼���ɏI��

    SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);
    SetDrawScreen(DX_SCREEN_BACK);      // �`��X�N���[���𗠑��Ɏw��
    SetWaitVSyncFlag(TRUE);             // VSYNC��L���ɂ���
    usable.AfterInit();                 // DirectX�������㏈��
    usable.MainLoop();                  // �Q�[���{��(���C�����[�v)
    usable.End();                       // �Q�[���I���㏈��
    DxLib_End();                        // �c�w���C�u�����g�p�̏I������
    return 0;                           // �\�t�g�̏I��
}
