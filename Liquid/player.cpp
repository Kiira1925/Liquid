#include "map.h"
#include "singleton.h"
#include "player.h"
#include "input.h"
#include "scene_choice.h"
#include <iostream>


#include "DxLib.h"
#define Search pair<int,int>

extern int Liquid[22][22];
extern Block blocks[BL_MAX];
using namespace std;

bool searchNum(Block* block, int x, int y);

void Player::init() 
{
	handle= LoadGraph("Data\\Images\\player.png");

	posX = 0;  // 移動の増加量
	posY = 0;

	rel_posX = 420;  // 描画追加量
	rel_posY = 0;

	width = 48;      // 画像サイズ
	height = 77;

	timer = 0;       // タイマー
	state = 0;       // キー入力の種類(0:無し1:右2:左3:上4:下)
	switch(Stage_Select::getInstance()->numStage)
	{
	case 0:
		posNumX = 13;
		posNumY = 11;
		break;
	case 1:
		posNumX = 8;
		posNumY = 11;
		break;
	case 2:
		posNumX = 10;
		posNumY = 13;
		break;
	case 3:
		posNumX = 13;
		posNumY = 13;
		break;
	case 4:
		posNumX = 13;
		posNumY = 7;
		break;
	case 5:
		posNumX = 9;
		posNumY = 9;
		break;
	case 6:
		posNumX = 6;
		posNumY = 14;
		break;
	case 7:
		posNumX = 15;
		posNumY = 10;
		break;
	case 8:
		posNumX = 9;
		posNumY = 15;
		break;
	}
	//posNumX = FastPx;     // 初期座標(マップチップの位置)
	//posNumY = FastPy;
	drawState = 0;   // アニメーションの状態(方向)
	aniState = 0;    // モーション

	blockState = 0;
	flg = true;

}

void Player::update3(int* temp_block_state)
{
	bool block_pass = true;
	bool block_pass2 = true;
	bool block_pass3 = true;
	bool block_pass4 = true;
	for (int i = 0; i < Map::getInstance()->block_max; i++)
	{
		if (*(temp_block_state + i) == 1)
		{
			block_pass = false;
		}
	}
	for (int i = 0; i < Map::getInstance()->block_max; i++)
	{
		if (*(temp_block_state + i) == 2)
		{
			block_pass2 = false;
		}
	}
	for (int i = 0; i < Map::getInstance()->block_max; i++)
	{
		if (*(temp_block_state + i) == 3)
		{
			block_pass3 = false;
		}
	}
	for (int i = 0; i < Map::getInstance()->block_max; i++)
	{
		if (*(temp_block_state + i) == 4)
		{
			block_pass4 = false;
		}
	}

	//switch (state)
	//{
	//case 1:
	//	// Right
	//	//if (Map::getInstance()->map_data[posNumY][posNumX + 1] == ROAD && blockState != 1) {
	//	if (Map::getInstance()->map_data[posNumY][posNumX + 1] == ROAD && block_pass)
	//	{
	//		posX += 3;
	//		if (posX % 12 == 0)
	//		{
	//			aniState++;
	//		}
	//		if (posX == 48)
	//		{
	//			state = 0;
	//			posX = 0;
	//			posNumX++;
	//			aniState = 0;
	//		}
	//	}
	//	else {
	//		state = 0;
	//	}
	//	break;

	//case 2:
	//	// Left
	//	if (Map::getInstance()->map_data[posNumY][posNumX - 1] == ROAD && block_pass2) {
	//		posX -= 3;
	//		if (posX % 12 == 0)
	//		{
	//			aniState++;
	//		}
	//		if (posX == -48)
	//		{
	//			state = 0;
	//			posX = 0;
	//			posNumX--;
	//			aniState = 0;
	//		}
	//	}
	//	else {
	//		state = 0;
	//	}
	//	break;

	//case 3:
	//	// Up
	//	if (Map::getInstance()->map_data[posNumY - 1][posNumX] == ROAD && block_pass3) {
	//		posY -= 3;
	//		if (posY % 12 == 0)
	//		{
	//			aniState++;
	//		}
	//		if (posY == -48)
	//		{
	//			state = 0;
	//			posY = 0;
	//			posNumY--;
	//			aniState = 0;
	//		}
	//	}
	//	else {
	//		state = 0;
	//	}
	//	break;

	//case 4:
	//	// Down
	//	if (Map::getInstance()->map_data[posNumY + 1][posNumX] == ROAD && block_pass4) {
	//		posY += 3;
	//		if (posY % 12 == 0)
	//		{
	//			aniState++;
	//		}
	//		if (posY == 48)
	//		{
	//			state = 0;
	//			posY = 0;
	//			posNumY++;
	//			aniState = 0;
	//		}
	//	}
	//	else {
	//		state = 0;
	//	}
	//	break;
	//}

}

void Player::update() {}

void Player::update2(Block* block, Block* zero, int* temp_block_state)
{
//for (int i = 0; i < Stage_Select::getInstance()->reNum(); i++) {
//	block[i].update(&block[i]);

//}
//if (flg == true) {


	if (state == 0)
	{

		if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
		{
			drawState = 1;
			state = 1;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT))
		{
			drawState = 2;
			state = 2;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_UP))
		{
			drawState = 3;
			state = 3;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_DOWN))
		{
			drawState = 4;
			state = 4;
		}

	}

	if ((Player::getInstance()->posNumY == block->posNumY) && (Player::getInstance()->posNumX + 1 == block->posNumX))
	{
		blockState = 1;
	}
	else if (Player::getInstance()->posNumY == block->posNumY && Player::getInstance()->posNumX - 1 == block->posNumX)
	{
		blockState = 2;
	}
	else if (Player::getInstance()->posNumY - 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX)
	{
		blockState = 3;
	}
	else if (Player::getInstance()->posNumY + 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX)
	{
		blockState = 4;
	}
	else { blockState = 0; }


	switch (state)
	{
	case 1:
		// Right
		if ((Map::getInstance()->map_data[Player::getInstance()->posNumY][Player::getInstance()->posNumX + 1] == ROAD || Map::getInstance()->map_data[posNumY][Player::getInstance()->posNumX + 1] == DOOR) && !searchNum(zero,Player::getInstance()->posNumX + 1,Player::getInstance()->posNumY)/*blockState != 1*/) {
			posX += 3;
			if (posX % 12 == 0)
			{
				aniState++;
			}
			if (posX == 48)
			{
				state = 0;
				posX = 0;
				Player::getInstance()->posNumX++;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;

	case 2:
		// Left
		if ((Map::getInstance()->map_data[posNumY][Player::getInstance()->posNumX - 1] == ROAD || Map::getInstance()->map_data[Player::getInstance()->posNumY][Player::getInstance()->posNumX - 1] == DOOR) && !searchNum(zero, Player::getInstance()->posNumX-1, posNumY)/*blockState != 2*/) {
			posX -= 3;
			if (posX % 12 == 0)
			{
				aniState++;
			}
			if (posX == -48)
			{
				state = 0;
				posX = 0;
				Player::getInstance()->posNumX--;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;

	case 3:
		// Up
		if ((Map::getInstance()->map_data[Player::getInstance()->posNumY - 1][Player::getInstance()->posNumX] == ROAD || Map::getInstance()->map_data[posNumY - 1][Player::getInstance()->posNumX] == DOOR) && !searchNum(zero, Player::getInstance()->posNumX, Player::getInstance()->posNumY-1)/*blockState != 3*/) {
			posY -= 3;
			if (posY % 12 == 0)
			{
				aniState++;
			}
			if (posY == -48)
			{
				state = 0;
				posY = 0;
				Player::getInstance()->posNumY--;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;

	case 4:
		// Down
		if ((Map::getInstance()->map_data[Player::getInstance()->posNumY + 1][Player::getInstance()->posNumX] == ROAD || Map::getInstance()->map_data[Player::getInstance()->posNumY + 1][Player::getInstance()->posNumX] == DOOR) && !searchNum(zero, Player::getInstance()->posNumX, Player::getInstance()->posNumY+1)/*blockState != 4*/) {
			posY += 3;
			if (posY % 12 == 0)
			{
				aniState++;
			}
			if (posY == 48)
			{
				state = 0;
				posY = 0;
				Player::getInstance()->posNumY++;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;
	}
	*temp_block_state = blockState;
}

void Player::draw() 
{   //実際の描画位置+(チップサイズ×何番目のチップか)＋追加する座標[yは飛び出た分の24を足す],,画像サイズ×画像のState,,描画サイズ,,
	DrawRectGraph(rel_posX + (CHIP_SIZE * Player::getInstance()->posNumX)+posX , rel_posY + (CHIP_SIZE * Player::getInstance()->posNumY)+posY -29, width*aniState, height * drawState, width, height, handle, true, false);
}

void Player::drawHead()
{
	DrawRectGraph(rel_posX + (CHIP_SIZE * Player::getInstance()->posNumX) + posX, rel_posY + (CHIP_SIZE * Player::getInstance()->posNumY) + posY - 29, width * aniState, height * drawState, width, height-48, handle, true, false);
}

void Player::goalCheck(boolean* isGoal)
{
	int goalY;
	int goalX;
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Map::getInstance()->map_data[Ver][Hor] == 4)
			{
				goalY = Ver;
				goalX = Hor;
			}
		}
	}
	if (Player::getInstance()->posNumY == goalY && Player::getInstance()->posNumX == goalX)
	{
		*isGoal = true;
	}
}

void Player::playerDamage(int* RB_timer)
{
	if (Liquid[Player::getInstance()->posNumY][Player::getInstance()->posNumX] == 1)
	{
		*RB_timer += 1;
	}
	else if (*RB_timer > 0)
	{
		*RB_timer -= 1;
	}
}

void Player::end() 
{

}


void Block::init(Block* block,int x,int y) 
{
	block->handle = LoadGraph("Data\\Images\\mapasset.png");

	block->posX = 0;  // 移動の増加量
	block->posY = 0;

	block->rel_posX = 420;  // 描画追加量
	block->rel_posY = 0;

	block->width = 48;      // 画像サイズ
	block->height = 70;

	block->timer = 0;       // タイマー
	block->state = 0;       // キー入力の種類(0:無し1:右2:左3:上4:下)
	block->posNumX = x;     // 初期座標(マップチップの位置)
	block->posNumY = y;
	block->drawState = 0;   // アニメーションの状態(方向)
	block->aniState = 0;    // モーション

	block->blockState = 0;
	block->flg = true;

}

void Block::update(Block* block, int block_sound) 
{

	// 隣接していて、かつ壁・プレイヤー・岩でないなら
	if ((Player::getInstance()->posNumY == block->posNumY) && (Player::getInstance()->posNumX + 1 == block->posNumX)&& (Map::getInstance()->map_data[block->posNumY][block->posNumX - 2] != ROAD))
	{
		block->blockState = 2;// Platerが左、岩が右
	}
	else if (Player::getInstance()->posNumY == block->posNumY && Player::getInstance()->posNumX - 1 == block->posNumX && (Map::getInstance()->map_data[block->posNumY][block->posNumX + 2] != ROAD))
	{
		block->blockState = 1;// Platerが右
	}
	else if (Player::getInstance()->posNumY - 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX && (Map::getInstance()->map_data[block->posNumY + 2][block->posNumX] != ROAD))
	{
		block->blockState = 4;// Platerが下
	}
	else if (Player::getInstance()->posNumY + 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX && (Map::getInstance()->map_data[block->posNumY - 2][block->posNumX] != ROAD))
	{
		block->blockState = 3;// Platerが上
	}
	else if((Player::getInstance()->posNumY == block->posNumY) && (Player::getInstance()->posNumX + 1 == block->posNumX)|| Player::getInstance()->posNumY == block->posNumY && Player::getInstance()->posNumX - 1 == block->posNumX||
		Player::getInstance()->posNumY - 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX|| Player::getInstance()->posNumY + 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX)
	{ 
		block->blockState = 5;
	}
	else 
	{
		block->blockState = 0;
	}

	//if (block->blockState == 1 && (Map::getInstance()->map_data[block->posNumY][block->posNumX + 2] == ROAD)) 
	//{
	//	block->blockState == 1;
	//}
	//else if (block->blockState == 2 && (Map::getInstance()->map_data[block->posNumY][block->posNumX - 2] == ROAD))
	//{
	//	block->blockState == 2;
	//}
	//else if (block->blockState == 3 && (Map::getInstance()->map_data[block->posNumY - 2][block->posNumX] == ROAD)) 
	//{
	//	block->blockState == 3;
	//}
	//else if (block->blockState == 4 && (Map::getInstance()->map_data[block->posNumY + 2][block->posNumX] == ROAD))
	//{
	//	block->blockState == 4;
	//}
	//else 
	//{
	//	block->blockState = 5;
	//}

	if (block->state == 0)
	{

		//if (Input::GetInstance()->GetKey(KEY_INPUT_D))
		//{
		//	//block->drawState = 1;
		//	block->state = 1;
		//}
		//else if (Input::GetInstance()->GetKey(KEY_INPUT_A))
		//{
		//	//block->drawState = 2;
		//	block->state = 2;
		//}
		//else if (Input::GetInstance()->GetKey(KEY_INPUT_W))
		//{
		//	//block->drawState = 3;
		//	block->state = 3;
		//}
		//else if (Input::GetInstance()->GetKey(KEY_INPUT_S))
		//{
		//	//block->drawState = 4;
		//	block->state = 4;
		//}
		if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT) && block->blockState != 1 && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 1;
			block->state = 1;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT) && block->blockState != 2 && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 2;
			block->state = 2;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_UP) && block->blockState != 3 && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 3;
			block->state = 3;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_DOWN) && block->blockState != 4 && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 4;
			block->state = 4;
		}

	}


	switch (block->state)
	{
	case 1:
		// Right
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX + 1] == ROAD/* && block->blockState != 0*/) {
			block->posX += 3;
			if (block->posX % 12 == 0)
			{
				//block->aniState++;
			}
			if (block->posX == 48)
			{
				block->state = 0;
				block->posX = 0;
				block->posNumX++;
				block->aniState = 0;
			}
			if (!CheckSoundMem(block_sound))
			{
				PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);
			}
		}
		else {
			block->state = 0;
		}
		break;

	case 2:
		// Left
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX - 1] == ROAD /*&& block->blockState != 0*/) {
			block->posX -= 3;
			if (block->posX % 12 == 0)
			{
				//block->aniState++;
			}
			if (block->posX == -48)
			{
				block->state = 0;
				block->posX = 0;
				block->posNumX--;
				block->aniState = 0;
			}
			if (!CheckSoundMem(block_sound))
			{
				PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);
			}
		}
		else {
			block->state = 0;
		}
		break;

	case 3:
		// Up
		if (Map::getInstance()->map_data[block->posNumY - 1][block->posNumX] == ROAD /*&& block->blockState != 0*/) {
			if(block->blockState != 1 && block->blockState!= 2)
			{
			block->posY -= 3;
			if (block->posY % 12 == 0)
			{
				//block->aniState++;
			}
			if (block->posY == -48)
			{
				block->state = 0;
				block->posY = 0;
				block->posNumY--;
				block->aniState = 0;
			}
			if (!CheckSoundMem(block_sound))
			{
				PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);
			}
			}
		}
		else {
			block->state = 0;
		}
		break;

	case 4:
		// Down
		//if (Map::getInstance()->map_data[block->posNumY + 2][block->posNumX] != ROAD) 
		//{
		//	block->state = 0;
		//	block->blockState = 0;
		//}
		if (Map::getInstance()->map_data[block->posNumY + 1][block->posNumX] == ROAD /*&& block->blockState != 0*/) {
			if (block->blockState != 1 && block->blockState != 2)
			{
			block->posY += 3;
			if (block->posY % 12 == 0)
			{
				//block->aniState++;
			}
			if (block->posY == 48)
			{
				block->state = 0;
				block->posY = 0;
				block->posNumY++;
				block->aniState = 0;
			}
			if (!CheckSoundMem(block_sound))
			{
				PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);
			}
			}
		}
		else {
			block->state = 0;
		}
		break;
	}

}
void Block::draw(Block* block) 
{
	//実際の描画位置+(チップサイズ×何番目のチップか)＋追加する座標[yは飛び出た分の24を足す],,画像サイズ×画像のState,,描画サイズ,,
	DrawRectGraph(block->rel_posX + (CHIP_SIZE * block->posNumX) + block->posX, block->rel_posY + (CHIP_SIZE * block->posNumY) + block->posY - 22, 0, CHIP_SIZE * 4, block->width, block->height, block->handle, true, false);

}

void Block::end(Block* block) 
{
	DeleteGraph(block->handle);
}

bool searchNum(Block* block, int x, int y)
{
	Search search;
	Search player;
	player = { y,x };
	for (int i = 0; i < Map::getInstance()->block_max; i++)
	{
		search = { (block + i)->posNumY,(block + i)->posNumX };
		if (search == player)
		{
			return true;
		}
	}
	return false;
}
