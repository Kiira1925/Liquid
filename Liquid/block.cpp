#include "DxLib.h"
#include "block.h"
#include "player.h"
#include "scene_choice.h"
#include "input.h"
#include "map.h"

void Block::init(Block* block)
{

	block->handle = LoadGraph("Data\\Images\\block.png");
	block->posX = 0;
	block->posY = 0;
	block->rel_posX = 420;
	block->rel_posY = 0;
	block->width = 48;
	block->height = 72;

	block->posNumX = 7;
	block->posNumY = 7;

	block->state = 0;
	block->flg = 0;
	block->aniState = 0;
}

void Block::update(Block* block)
{
	if (block->flg == 0) {
		if (block->state == -1) {
			block->judgeBlock(block);
		}

		if (block->state == 0)
		{
			if (Input::GetInstance()->GetKey(KEY_INPUT_Z))
			{
				PLAYER->flg = false;
				if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
				{
					block->state = 1;
				}// ’·‰Ÿ‚µ
				else if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
				{
					block->state = 1;
				}

				if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
				{
					block->state = 2;
				}
				else if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT))
				{
					block->state = 2;
				}

				if (Input::GetInstance()->GetKeyDown(KEY_INPUT_UP))
				{
					block->state = 3;
				}
				else if (Input::GetInstance()->GetKey(KEY_INPUT_UP))
				{
					block->state = 3;
				}

				if (Input::GetInstance()->GetKeyDown(KEY_INPUT_DOWN))
				{
					block->state = 4;
				}
				else if (Input::GetInstance()->GetKey(KEY_INPUT_DOWN))
				{
					block->state = 4;
				}
			}
		}
	}

	switch (block->state) 
	{
	case 1:
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX+1] == 1&&Map::getInstance()->map_data[PLAYER->posNumY][PLAYER->posNumX+1]==1) 
		{
			block->posX += 3;
			//PLAYER->setPosX(PLAYER->getPosX() + 1);
			if (block->posX % 12 == 0) 
			{
				PLAYER->aniState++;
			}
			if (block->posX == 48) 
			{
				block->state = 0;
				block->posX = 0;
				block->posNumX++;
				//PLAYER->posNumX++;
				PLAYER->setPosX(0);
				PLAYER->aniState = 0;
				PLAYER->flg = true;
			}
		}
		else {
			block->state = 0;
			PLAYER->flg = true;
		}
		break;

	case 2:
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX-1] == 1 && Map::getInstance()->map_data[PLAYER->posNumY][PLAYER->posNumX - 1] == 1)
		{
			block->posX -= 3;
			//PLAYER->setPosX(PLAYER->getPosX() - 1);
			if (block->posX % 12 == 0)
			{
				PLAYER->aniState++;
			}
			if (block->posX == -48)
			{
				block->state = 0;
				block->posX = 0;
				block->posNumX--;
				//PLAYER->posNumX--;
				PLAYER->setPosX(0);
				PLAYER->aniState = 0;
				PLAYER->flg = true;
			}
		}
		else {
			block->state = 0;
			PLAYER->flg = true;
		}
		break;

	case 3:
		if (Map::getInstance()->map_data[block->posNumY-1][block->posNumX] == 1 && Map::getInstance()->map_data[PLAYER->posNumY-1][PLAYER->posNumX] == 1)
		{
			block->posY -= 3;
			//PLAYER->setPosY(PLAYER->getPosY() - 1);
			if (block->posY % 12 == 0)
			{
				PLAYER->aniState++;
			}
			if (block->posY == -48)
			{
				block->state = 0;
				block->posY = 0;
				block->posNumY--;
				//PLAYER->posNumY--;
				PLAYER->setPosY(0);
				PLAYER->aniState = 0;
				PLAYER->flg = true;
			}
		}
		else {
			block->state = 0;
			PLAYER->flg = true;
		}
		break;

	case 4:
		if (Map::getInstance()->map_data[block->posNumY+1][block->posNumX] == 1 && Map::getInstance()->map_data[PLAYER->posNumY+1][PLAYER->posNumX] == 1)
		{
			block->posY += 3;
			//PLAYER->setPosY(PLAYER->getPosY() + 1);
			if (block->posY % 12 == 0)
			{
				PLAYER->aniState++;
			}
			if (block->posY == 48)
			{
				block->state = 0;
				block->posY = 0;
				block->posNumY++;
				//PLAYER->posNumY++;
				PLAYER->setPosY(0);
				PLAYER->aniState = 0;
				PLAYER->flg = true;
			}
		}
		else {
			block->state = 0;	
			PLAYER->flg = true;

		}
		break;

	}

}

void Block::draw(Block* block)
{
	DrawRectGraph(block->rel_posX + (CHIP_SIZE * block->posNumX) + block->posX, block->rel_posY + (CHIP_SIZE * block->posNumY) + block->posY - 24, 0, 0, block->width, block->height, block->handle, true, false);
}

void Block::end(Block* block)
{
	DeleteGraph(block->handle);
}

int Block::reNum() 
{
	return B_ReNum;// ‘®«’l
}

int Block::judgeBlock(Block* block) 
{
	if ((PLAYER->posNumX + 1 == block->posNumX)&&(PLAYER->posNumY==block->posNumY))
	{
		block->flg = 1;
		return block->flg;
	}
	else if ((PLAYER->posNumX - 1 == block->posNumX) && (PLAYER->posNumY == block->posNumY)) 
	{
		block->flg = 1;
		return block->flg;
	}
	else if ((PLAYER->posNumX == block->posNumX) && (PLAYER->posNumY + 1 == block->posNumY)) 
	{
		block->flg = 1;
		return block->flg;
	}
	else if ((PLAYER->posNumX == block->posNumX) && (PLAYER->posNumY - 1 == block->posNumY))
	{
		block->flg = 1;
		return block->flg;
	}
	else 
	{
		block->flg = 0;
		return block->flg;
	}

}

