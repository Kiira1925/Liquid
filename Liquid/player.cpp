#include "singleton.h"
#include "player.h"
#include "input.h"

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

	// timer = 0;       // �^�C�}�[
	state = 0;       // �L�[���͂̎��(0:����1:�E2:��3:��4:��)
	posNumX = 5;     // �������W(�}�b�v�`�b�v�̈ʒu)
	posNumY = 5;
	drawState = 0;   // �A�j���[�V�����̏��
}

void Player::update() 
{

	//Map* map = Map::getInstance();
	//int mapchip = map->map_data[5][6];
	if (state == 0) 
	{   // �P����
		if (Input::GetInstance()->GetKeyDown(KEY_INPUT_RIGHT))
		{
			state = 1;
		}// ������
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
		if (posNumX + 1 != 15) {
			posX += 3;
			if (posX == 48)
			{
				state = 0;
				posX = 0;
				posNumX++;
			}
		}
		else {
			state = 0;
		}
		break;

	case 2:
		// Left
		if (posNumX - 1 != 5) {
			posX -= 3;
			if (posX == -48)
			{
				state = 0;
				posX = 0;
				posNumX--;
			}
		}
		else {
			state = 0;
		}
		break;

	case 3:
		// Up
		if (posNumY - 1 != 6) {
			posY -= 3;
			if (posY == -48)
			{
				state = 0;
				posY = 0;
				posNumY--;
			}
		}
		else {
			state = 0;
		}
		break;

	case 4:
		// Down
		if (posNumY + 1 != 15) {
			posY += 3;
			if (posY == 48)
			{
				state = 0;
				posY = 0;
				posNumY++;
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
	DrawRectGraph(rel_posX + (CHIP_SIZE * posNumX)+posX , rel_posY + (CHIP_SIZE * posNumY)+posY -24, width * drawState, height * drawState, width, height, handle, true, false);
}

void Player::end() 
{

}
