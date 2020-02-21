#include "singleton.h"
#include "player.h"
#include "input.h"

#include "map.h"

#include "DxLib.h"

void Player::init() 
{
	handle= LoadGraph("Data\\Images\\player.png");

	posX = 0;  // 移動の増加量
	posY = 0;

	rel_posX = 420;  // 
	rel_posY = 0;

	width = 48;
	height = 72;

	timer = 0;
	state = 0;
	posNumX = 5;
	posNumY = 5;
	drawState = 0;
}

void Player::update() 
{
	if (state == 0) 
	{   // 単押し
		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
		{
			state = 1;
		}// 長押し
		else if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT)) 
		{
			state = 1;
		}

		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_LEFT))
		{
			state = 2;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT))
		{
			state = 2;
		}

		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_UP))
		{
			state = 3;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_UP))
		{
			state = 3;
		}

		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_DOWN))
		{
			state = 4;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_DOWN))
		{
			state = 4;
		}
	}

	switch (state) 
	{
	case 1:
		// Right
		posX += 3;
		timer++;
		if (posX == 48) 
		{
			state = 0;
			posX = 0;
			posNumX++;
		}
		break;

	case 2:
		// Left
		posX -= 3;
		timer++;
		if (posX == -48)
		{
			state = 0;
			posX = 0;
			posNumX--;
		}
		break;

	case 3:
		// Up
		posY -= 3;
		timer++;
		if (posY == -48)
		{
			state = 0;
			posY = 0;
			posNumY--;
		}
		break;

	case 4:
		// Down
		posY += 3;
		timer++;
		if (posY == 48)
		{
			state = 0;
			posY = 0;
			posNumY++;
		}
		break;
	}

}

void Player::draw() 
{   //実際の描画位置+(チップサイズ×何番目のチップか)＋追加する座標[yは飛び出た分の24を足す],,画像サイズ×画像のState,,描画サイズ,,
	DrawRectGraph(rel_posX + (CHIP_SIZE * posNumX)+posX , rel_posY + (CHIP_SIZE * posNumY)+posY -24, width * drawState, height * drawState, width, height, handle, true, false);
}

void Player::end() 
{

}
