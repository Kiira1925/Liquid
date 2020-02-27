#include "singleton.h"
#include "player.h"
#include "input.h"
#include "scene_choice.h"

#include "map.h"

#include "DxLib.h"

extern Block blocks;

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

	blockState = 0;
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

	if ((posNumY == blocks.posNumY) && (posNumX + 1 == blocks.posNumX))
	{
		blockState = 1;
	}
	else if (posNumY == blocks.posNumY && posNumX - 1 == blocks.posNumX)
	{
		blockState = 2;
	}
	else if (posNumY - 1 == blocks.posNumY && posNumX == blocks.posNumX)
	{
		blockState = 3;
	}
	else if (posNumY + 1 == blocks.posNumY && posNumX == blocks.posNumX)
	{
		blockState = 4;
	}
	else { blockState = 0; }


	switch (state)
	{
	case 1:
		// Right
		if (Map::getInstance()->map_data[posNumY][posNumX + 1] == ROAD && blockState != 1) {
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
		if (Map::getInstance()->map_data[posNumY][posNumX - 1] == ROAD && blockState != 2) {
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
		if (Map::getInstance()->map_data[posNumY - 1][posNumX] == ROAD && blockState != 3) {
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
		if (Map::getInstance()->map_data[posNumY + 1][posNumX] == ROAD && blockState != 4) {
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


void Block::init(Block* block) 
{
	block->handle = LoadGraph("Data\\Images\\block.png");

	block->posX = 0;  // �ړ��̑�����
	block->posY = 0;

	block->rel_posX = 420;  // �`��ǉ���
	block->rel_posY = 0;

	block->width = 48;      // �摜�T�C�Y
	block->height = 72;

	block->timer = 0;       // �^�C�}�[
	block->state = 0;       // �L�[���͂̎��(0:����1:�E2:��3:��4:��)
	block->posNumX = FastPx + 1;     // �������W(�}�b�v�`�b�v�̈ʒu)
	block->posNumY = FastPy;
	block->drawState = 0;   // �A�j���[�V�����̏��(����)
	block->aniState = 0;    // ���[�V����

	block->blockState = 0;
	block->flg = true;

}

void Block::update(Block* block) 
{
	if ((Player::getInstance()->posNumY == block->posNumY) && (Player::getInstance()->posNumX + 1 == block->posNumX))
	{
		block->blockState = 2;
	}
	else if (Player::getInstance()->posNumY == block->posNumY && Player::getInstance()->posNumX - 1 == block->posNumX)
	{
		block->blockState = 1;
	}
	else if (Player::getInstance()->posNumY - 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX)
	{
		block->blockState = 4;
	}
	else if (Player::getInstance()->posNumY + 1 == block->posNumY && Player::getInstance()->posNumX == block->posNumX)
	{
		block->blockState = 3;
	}
	else { block->blockState = 0; }


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
		if (Input::GetInstance()->GetKey(KEY_INPUT_RIGHT) && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 1;
			block->state = 1;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_LEFT) && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 2;
			block->state = 2;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_UP) && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 3;
			block->state = 3;
		}
		else if (Input::GetInstance()->GetKey(KEY_INPUT_DOWN) && block->blockState != 0 && Input::GetInstance()->GetKey(KEY_INPUT_Z))
		{
			//block->drawState = 4;
			block->state = 4;
		}

	}


	switch (block->state)
	{
	case 1:
		// Right
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX + 1] == ROAD&&block->blockState!=1) {
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
		}
		else {
			block->state = 0;
		}
		break;

	case 2:
		// Left
		if (Map::getInstance()->map_data[block->posNumY][block->posNumX - 1] == ROAD && block->blockState != 2) {
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
		}
		else {
			block->state = 0;
		}
		break;

	case 3:
		// Up
		if (Map::getInstance()->map_data[block->posNumY - 1][block->posNumX] == ROAD && block->blockState != 3) {
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
		}
		else {
			block->state = 0;
		}
		break;

	case 4:
		// Down
		if (Map::getInstance()->map_data[block->posNumY + 1][block->posNumX] == ROAD && block->blockState != 4) {
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
		}
		else {
			block->state = 0;
		}
		break;
	}

}
void Block::draw(Block* block) 
{
	//���ۂ̕`��ʒu+(�`�b�v�T�C�Y�~���Ԗڂ̃`�b�v��)�{�ǉ�������W[y�͔�яo������24�𑫂�],,�摜�T�C�Y�~�摜��State,,�`��T�C�Y,,
	DrawRectGraph(block->rel_posX + (CHIP_SIZE * block->posNumX) + block->posX, block->rel_posY + (CHIP_SIZE * block->posNumY) + block->posY - 24, block->width * block->aniState, block->height * block->drawState, block->width, block->height, block->handle, true, false);

}

void Block::end(Block* block) 
{

}
