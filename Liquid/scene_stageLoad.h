#pragma once
// �C���N���[�h ---------------------------------------------------------
#include "common.h"
#include "main.h"

// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class Stage_Load
{
public:
    int timer;
    int handle;
    int posX;

    void init(Stage_Load* load);
    void update(Stage_Load* load);
    void draw(Stage_Load* load);
    void end(Stage_Load* load);

private:

};

class Game_Conduct
{
public:
    void updateDebug(Game_Conduct* game_conduct, Usable* usable);   // �f�o�b�O�p�̍X�V����

};