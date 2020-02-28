#pragma once
#include <iostream>
#include "common.h"
#include "main.h"
#include "singleton.h"

#define FastPx 8
#define FastPy 7

#define BL_MAX 5
using namespace std;
#define Search pair<int,int>

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
    void update(Block* block,Block* zero);
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
    int blockFront;
    int blockBack;
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
    void update2(Block* block, int* temp_block_state);
    void update3(int* temp_block_state);

    int timer;
    int drawState;
    int aniState;
    int state;
    int posNumX;
    int posNumY;

    int blockState;
    bool flg;
    //int posX = 0;  　　　システム内部座標
    //int posY = 0;
    //int rel_posX = 0;　　描画座標
    //int rel_posY = 0;

    //int width = 0;　　　サイズ
    //int height = 0;

    //int handle = 0;
};

