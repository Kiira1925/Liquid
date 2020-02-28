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
	handle = LoadGraph("Data\\Images\\mapasset.png");
}

void Map::drawMap()
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Map::getInstance()->map_data[Ver][Hor] == 1)
			{
				DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 0 * CHIP_SIZE, 3 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
			}
			if (Map::getInstance()->map_data[Ver][Hor] == 2)
			{
				bool up = (Map::getInstance()->map_data[Ver - 1][Hor] == 2);
				bool down = (Map::getInstance()->map_data[Ver + 1][Hor] == 2);
				bool left = (Map::getInstance()->map_data[Ver][Hor - 1] == 2);
				bool right = (Map::getInstance()->map_data[Ver][Hor + 1] == 2);

				if (!up && down && !left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 0 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && down && left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 1 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && down && left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 2 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && down && !left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 0 * CHIP_SIZE, 1 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && down && left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 1 * CHIP_SIZE, 1 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && down && left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 2 * CHIP_SIZE, 1 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && !down && !left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 0 * CHIP_SIZE, 2 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && !down && left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 1 * CHIP_SIZE, 2 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && !down && left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 2 * CHIP_SIZE, 2 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && down && !left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 3 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && down && !left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 3 * CHIP_SIZE, 1 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (up && !down && !left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 3 * CHIP_SIZE, 2 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && !down && !left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 4 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && !down && left && right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 5 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && !down && left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 6 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
				if (!up && !down && !left && !right)
				{
					DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, 7 * CHIP_SIZE, 0 * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
				}
			}
			//DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE, Map::getInstance()->map_data[Ver][Hor] * CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, handle, TRUE, FALSE);
		}
	}
}

void Map::drawBreakable()
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Map::getInstance()->map_data[Ver][Hor] == 3)
			{
				DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE - 26, 0 * CHIP_SIZE, 262, CHIP_SIZE, CHIP_SIZE + 26, handle, TRUE, FALSE);
			}
		}
	}
}

void Map::drawSpring()
{
	Map::getInstance()->anime_timer++;
	int anime_frame = Map::getInstance()->anime_timer %48 /8;
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Map::getInstance()->map_data[Ver][Hor] == 5)
			{
				DrawRectGraph(Map::getInstance()->rel_posX + Hor * CHIP_SIZE, MAP_DRAW_POSITION_Y + Ver * CHIP_SIZE - 24, anime_frame * CHIP_SIZE, 360, CHIP_SIZE, CHIP_SIZE + 24, handle, TRUE, FALSE);
			}
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
		Map::getInstance()->MapFileName = "Data\\Map\\TestStage.csv";
		Map::getInstance()->ObjFileName = "Data\\Map\\TestObject.csv";
		Map::getInstance()->block_max = 2;
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
		OutputDebugString("ステージファイルの読み込みに失敗しました\n");
		return;
	}

	//読み込んだデータの格納
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