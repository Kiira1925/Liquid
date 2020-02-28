#define _CRT_SECURE_NO_WARNINGS
#include <DxLib.h>
#include "map.h"

void Map::init(int stage_num)
{
	loadChipData();
	loadMapData(stage_num);
}

void Map::update()
{

}

void Map::draw()
{
	drawMap();
}

void Map::end()
{

}




void Map::loadChipData()
{
	handle = LoadGraph("Data\\Images\\chip.png");
}

void Map::drawMap()
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, Map::getInstance()->map_data[Ver][Hor] * CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
		}
	}
}

//�}�b�v�f�[�^�i�O���ۑ��j�̓ǂݍ���
void Map::loadMapData(int stage_num)
{
	FILE* fp;
	switch (stage_num)
	{
	case 0:
		Map::getInstance()->MapFileName = "Data\\Map\\TestStage.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\TestObject.csv";
		block_max = 1;
		break;
	case 1:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage1.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object1.csv";
		block_max = 2;
		break;
	case 2:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage2.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object2.csv";
		block_max = 1;
		break;
	case 3:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage3.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object3.csv";
		block_max = 1;
		break;
	case 4:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage4.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object4.csv";
		block_max = 1;
		break;
	case 5:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage5.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object5.csv";
		block_max = 1;
		break;
	case 6:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage6.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object6.csv";
		block_max = 1;
		break;
	case 7:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage7.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object7.csv";
		block_max = 1;
		break;
	case 8:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage8.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object8.csv";
		block_max = 1;
		break;
	case 9:
		Map::getInstance()->MapFileName = "Data\\Map\\Stage9.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\Object9.csv";
		block_max = 1;
		break;
	default:
		break;
	}

	fp = fopen(Map::getInstance()->MapFileName, "r");
	if (fp == NULL)
	{
		OutputDebugString("�X�e�[�W�t�@�C���̓ǂݍ��݂Ɏ��s���܂���\n");
		return;
	}

	//�ǂݍ��񂾃f�[�^�̊i�[
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			fscanf(fp, "%d,", &Map::getInstance()->map_data[Ver][Hor]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}