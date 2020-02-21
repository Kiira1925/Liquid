#pragma once
#include "common.h"
#include "main.h"
#include "singleton.h"

enum HitType 
{
    NONE,
    ROAD,
    WALL,
    BLOCK,
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

    int timer;
    int drawState;
    int state;
    int posNumX;
    int posNumY;
    //int posX = 0;  　　　システム内部座標
    //int posY = 0;
    //int rel_posX = 0;　　描画座標
    //int rel_posY = 0;

    //int width = 0;　　　サイズ
    //int height = 0;

    //int handle = 0;
};