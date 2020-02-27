#include "singleton.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "scene_choice.h"

#include "map.h"

#include "DxLib.h"



Block           block[B_MAX];

void Player::init() 
{
	handle= LoadGraph("Data\\Images\\player.png");

	posX = 0;  // 移動の増加量
	posY = 0;

	rel_posX = 420;  // 描画追加量
	rel_posY = 0;

	width = 48;      // 画像サイズ
	height = 72;

	timer = 0;       // タイマー
	state = 0;       // キー入力の種類(0:無し1:右2:左3:上4:下)
	posNumX = FastPx;     // 初期座標(マップチップの位置)
	posNumY = FastPy;
	drawState = 0;   // アニメーションの状態(方向)
	aniState = 0;    // モーション

	blockState = -1;
	flg = true;

	for (int i = 0; i < Stage_Select::getInstance()->reNum(); i++) {
		block[i].init(&block[i]);
	}
}

void Player::update() 
{
//for (int i = 0; i < Stage_Select::getInstance()->reNum(); i++) {
//	block[i].update(&block[i]);

//}
//if (flg == true) {


	if (state == 0)
	{
		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_Z))
		{
			state = -1;
		}
		//else if (Input::GetInstance()->GetKey(KEY_INPUT_Z))
		//{
		//	state = -1;
		//}

		// 単押し
		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
		{
			drawState = 1;
			state = 1;
		}// 長押し
		else if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))
		{
			drawState = 1;
			state = 1;
		}

		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
		{
			drawState = 2;
			state = 2;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT))
		{
			drawState = 2;
			state = 2;
		}

		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_UP))
		{
			drawState = 3;
			state = 3;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_UP))
		{
			drawState = 3;
			state = 3;
		}

		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_DOWN))
		{
			drawState = 4;
			state = 4;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_DOWN))
		{
			drawState = 4;
			state = 4;
		}

	}
	if (state == -1) 
	{
		if (Input::GetInstance()->GetKey(KEY_INPUT_Z)&&((Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))|| (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT))))
		{
			state = 1;
			block->state = 1;
		}
	}


	switch (state)
	{
		//case 0:
		//	timer++;
		//	drawState = 0;
		//	if (timer % 12 == 0)
		//	{
		//		aniState++;
		//		if (aniState == 4) 
		//		{
		//			aniState = 0;
		//		}
		//	}
		//	break;

	case 1:
		// Right
		if (Map::getInstance()->map_data[posNumY][posNumX + 1] == 1 && (posNumX + 1 != block->posNumX || posNumY != block->posNumY)) {
			posX += 3;
			if (posX % 12 == 0)
			{
				aniState++;
			}
			if (posX == 48)
			{
				state = 0;
				posX = 0;
				posNumX++;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;

	case 2:
		// Left
		if (Map::getInstance()->map_data[posNumY][posNumX - 1] == 1 && (posNumX - 1 != block->posNumX || posNumY != block->posNumY)) {
			posX -= 3;
			if (posX % 12 == 0)
			{
				aniState++;
			}
			if (posX == -48)
			{
				state = 0;
				posX = 0;
				posNumX--;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;

	case 3:
		// Up
		if (Map::getInstance()->map_data[posNumY - 1][posNumX] == 1 && (posNumX != block->posNumX || posNumY - 1 != block->posNumY)) {
			posY -= 3;
			if (posY % 12 == 0)
			{
				aniState++;
			}
			if (posY == -48)
			{
				state = 0;
				posY = 0;
				posNumY--;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;

	case 4:
		// Down
		if (Map::getInstance()->map_data[posNumY + 1][posNumX] == 1 && (posNumX != block->posNumX || posNumY + 1 != block->posNumY)) {
			posY += 3;
			if (posY % 12 == 0)
			{
				aniState++;
			}
			if (posY == 48)
			{
				state = 0;
				posY = 0;
				posNumY++;
				aniState = 0;
			}
		}
		else {
			state = 0;
		}
		break;
	}

	switch (block->state) 
	{
	case 1:
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX + 1] == 1 && Map::getInstance()->map_data[PLAYER->posNumY][PLAYER->posNumX + 1] == 1)
		{
			block->posX += 3;
			if (block->posX == 48)
			{
				block->state = 0;
				block->posX = 0;
				block->posNumX++;
			}

		}
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;
	}


}

void Player::draw() 
{   //実際の描画位置+(チップサイズ×何番目のチップか)＋追加する座標[yは飛び出た分の24を足す],,画像サイズ×画像のState,,描画サイズ,,
	DrawRectGraph(rel_posX + (CHIP_SIZE * posNumX)+posX , rel_posY + (CHIP_SIZE * posNumY)+posY -24, width*aniState, height * drawState, width, height, handle, true, false);

	for (int i = 0; i < Stage_Select::getInstance()->reNum(); i++) {
		block[i].draw(&block[i]);
	}

}

void Player::end() 
{
	for (int i = 0; i < Stage_Select::getInstance()->reNum(); i++) {
		block[i].end(&block[i]);
	}
}
