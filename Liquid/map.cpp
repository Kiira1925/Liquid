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
			DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, map_data[Ver][Hor] * CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
		}
	}
}

//マップデータ（外部保存）の読み込み
void Map::loadMapData(int stage_num)
{
	FILE* fp;
	switch (stage_num)
	{
	case 0:
		MapFileName = "Data\\Map\\TestStage.csv";
		ObjFileName = "Data\\Map\\TestObject.csv";
		break;
	case 1:
		MapFileName = "Data\\Map\\Stage1.csv";
		ObjFileName = "Data\\Map\\Object1.csv";
		break;
	case 2:
		MapFileName = "Data\\Map\\Stage2.csv";
		ObjFileName = "Data\\Map\\Object2.csv";
		break;
	case 3:
		MapFileName = "Data\\Map\\Stage3.csv";
		ObjFileName = "Data\\Map\\Object3.csv";
		break;
	case 4:
		MapFileName = "Data\\Map\\Stage4.csv";
		ObjFileName = "Data\\Map\\Object4.csv";
		break;
	case 5:
		MapFileName = "Data\\Map\\Stage5.csv";
		ObjFileName = "Data\\Map\\Object5.csv";
		break;
	case 6:
		MapFileName = "Data\\Map\\Stage6.csv";
		ObjFileName = "Data\\Map\\Object6.csv";
		break;
	case 7:
		MapFileName = "Data\\Map\\Stage7.csv";
		ObjFileName = "Data\\Map\\Object7.csv";
		break;
	case 8:
		MapFileName = "Data\\Map\\Stage8.csv";
		ObjFileName = "Data\\Map\\Object8.csv";
		break;
	case 9:
		MapFileName = "Data\\Map\\Stage9.csv";
		ObjFileName = "Data\\Map\\Object9.csv";
		break;
	default:
		break;
	}

	fp = fopen(MapFileName, "r");

	if (fp == NULL)
	{
		OutputDebugString("ステージファイルの読み込みに失敗しました\n");
		return;
	}

	//読み込んだデータの格納
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			fscanf(fp, "%d,", &map_data[Ver][Hor]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}