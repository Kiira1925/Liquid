#pragma once
#include "common.h"
#include "main.h"
#include "singleton.h"

#define FastPx 8
#define FastPy 7

#define BL_MAX 5

enum HitType 
{
    NONE,
    ROAD,
    WALL,
    BREAK,
    DOOR
    
};

class Block :public Sprite
{
public:
    void init(Block* block,int x,int y);
    void update(Block* block,int block_sound);
    void draw(Block* block);
    void end(Block* block);

    //int getPosX() { return posX; }
    //int getPosY() { return posY; }
    //void setRelPosX(int x) { rel_posX = x; }
    //void setRelPosY(int y) { rel_posY = y; }
    //void setPosX(int x) { posX = x; }
    //void setPosY(int y) { posY = y; }
    int timer;
    int drawState;
    int aniState;
    int state;
    int posNumX;
    int posNumY;

    int blockState;
    bool flg;
protected:
    //int posX = 0;
    //int posY = 0;
    //int rel_posX = 0;
    //int rel_posY = 0;

    //int width = 0;
    //int height = 0;
    //int handle = 0;
};

class Player :public Sprite ,public Singleton<Player> 
{
private:
	//static const int OBJ_MAX = 1;   

public:
	void init();
    void update();
    void draw();
    void end();
    void update2(Block* block, Block* zero, int* temp_block_state);
    void update3(int* temp_block_state);

    void playerDamage(int* RB_timer);

    void drawHead();
    void goalCheck(boolean* isGoal);

    int timer;
    int drawState;
    int aniState;
    int state;
    int posNumX;
    int posNumY;

    int blockState;
    bool flg;
    //int posX = 0;  �@�@�@�V�X�e���������W
    //int posY = 0;
    //int rel_posX = 0;�@�@�`����W
    //int rel_posY = 0;

    //int width = 0;�@�@�@�T�C�Y
    //int height = 0;

    //int handle = 0;
};
