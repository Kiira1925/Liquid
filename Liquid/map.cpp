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
			DrawRectGraph(MAP_DRAW_POSITION_X + Hor*48, MAP_DRAW_POSITION_Y + Ver * 48, map_data[Ver][Hor] * 48, 0, 48, 48, handle, TRUE, FALSE);
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
		FileName = "Data\\Map\\TestStage.csv";
		break;
	case 1:
		FileName = "Data\\Map\\Stage1.csv";
		break;
	case 2:
		FileName = "Data\\Map\\Stage2.csv";
		break;
	case 3:
		FileName = "Data\\Map\\Stage3.csv";
		break;
	case 4:
		FileName = "Data\\Map\\Stage4.csv";
		break;
	case 5:
		FileName = "Data\\Map\\Stage5.csv";
		break;
	case 6:
		FileName = "Data\\Map\\Stage6.csv";
		break;
	case 7:
		FileName = "Data\\Map\\Stage7.csv";
		break;
	case 8:
		FileName = "Data\\Map\\Stage8.csv";
		break;
	case 9:
		FileName = "Data\\Map\\Stage9.csv";
		break;
	default:
		break;
	}

	fp = fopen(FileName, "r");

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