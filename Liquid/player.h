#pragma once
#include "common.h"
#include "main.h"
#include "singleton.h"

#define FastPx 8
#define FastPy 7

enum HitType 
{
    NONE,
    ROAD,
    WALL,
    BREAK,
    DOOR
    
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

class Block :public Sprite
{
public:
    void init(Block* block);
    void update(Block* block);
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