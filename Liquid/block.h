#pragma once

#include "block.h"
#include "common.h"

#define B_ReNum 20
#define B_MAX 16
#define PLAYER Player::getInstance()

class Block
{
public:
	void init(Block* block);
	void update(Block* block);
	void draw(Block* block);
	void end(Block* block);
    int reNum();
    int judgeBlock(Block* block);


    int posX;
    int posY;
    int rel_posX;
    int rel_posY;

    int width;
    int height;
    int handle;

    int posNumX;
    int posNumY;

    int state;
    int flg;

    int aniState;

};