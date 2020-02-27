#include "singleton.h"
#include "player.h"
#include "input.h"
#include "scene_choice.h"

#include "map.h"

#include "DxLib.h"



void Player::init() 
{
	handle= LoadGraph("Data\\Images\\player.png");

	posX = 0;  // �ړ��̑�����
	posY = 0;

	rel_posX = 420;  // �`��ǉ���
	rel_posY = 0;

	width = 48;      // �摜�T�C�Y
	height = 72;

	timer = 0;       // �^�C�}�[
	state = 0;       // �L�[���͂̎��(0:����1:�E2:��3:��4:��)
	posNumX = FastPx;     // �������W(�}�b�v�`�b�v�̈ʒu)
	posNumY = FastPy;
	drawState = 0;   // �A�j���[�V�����̏��(����)
	aniState = 0;    // ���[�V����

	blockState = -1;
	flg = true;

}

void Player::update() 
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



	switch (state)
	{
	case 1:
		// Right
		if (Map::getInstance()->map_data[posNumY][posNumX + 1] == 1) {
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
		if (Map::getInstance()->map_data[posNumY][posNumX - 1] == 1) {
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
		if (Map::getInstance()->map_data[posNumY - 1][posNumX] == 1) {
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
		if (Map::getInstance()->map_data[posNumY + 1][posNumX] == 1) {
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

}

void Player::draw() 
{   //���ۂ̕`��ʒu+(�`�b�v�T�C�Y�~���Ԗڂ̃`�b�v��)�{�ǉ�������W[y�͔�яo������24�𑫂�],,�摜�T�C�Y�~�摜��State,,�`��T�C�Y,,
	DrawRectGraph(rel_posX + (CHIP_SIZE * posNumX)+posX , rel_posY + (CHIP_SIZE * posNumY)+posY -24, width*aniState, height * drawState, width, height, handle, true, false);

}

void Player::end() 
{

}
