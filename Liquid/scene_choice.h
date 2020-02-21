#pragma once
// �C���N���[�h ---------------------------------------------------------
#include "common.h"
#include "main.h"
#include "singleton.h"

// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class Choice_Bg : public Sprite
{
public:
    void init(Choice_Bg* choice_bg);
    void update(Choice_Bg* choice_bg);
    void draw(Choice_Bg* choice_bg);
    void end(Choice_Bg* choice_bg);

private:

};

class Choice_Conduct
{
public:
    void updateDebug(Choice_Conduct* choice_conduct, Usable* usable);   // �f�o�b�O�p�̍X�V����

};

// �X�e�[�W�Z���N�g�Ǘ� --------------------------------------------------------
class Stage_Select :public Sprite,public Singleton<Stage_Select>
{
public:
    void init();
    void update();
    void draw();
    void end();
    int reNum();

    int numStage;
    int timer;
    int flg;
    float ease;
    float easePosX;
private:
    int sizeX = 1920;
    int sizeY = 1080;
};