#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"
#include <stdio.h>

// 定数 ----------------------------------------------------------------
#define		MAPDATA_H_MAX		(22)
#define		MAPDATA_V_MAX		(22)
#define		MAP_DRAW_POSITION_X	(420)
#define		MAP_DRAW_POSITION_Y	(0)

class Map : public Sprite
{
private:
	int map_data[MAPDATA_V_MAX][MAPDATA_H_MAX];
	const char* FileName;
	//char StageFile1[24] = "Data\\Map\\Stage1.csv\0";
	//char StageFile2[24] = "Data\\Map\\Stage2.csv\0";
	//char StageFile3[24] = "Data\\Map\\Stage3.csv\0";
	//char StageFile4[24] = "Data\\Map\\Stage4.csv\0";
	//char StageFile5[24] = "Data\\Map\\Stage5.csv\0";
	//char StageFile6[24] = "Data\\Map\\Stage6.csv\0";
	//char StageFile7[24] = "Data\\Map\\Stage7.csv\0";
	//char StageFile8[24] = "Data\\Map\\Stage8.csv\0";
	//char StageFile9[24] = "Data\\Map\\Stage9.csv\0";
public:
	void init(int stage_num);
	void update();
	void draw();
	void end();


	void drawMap();
	void loadChipData();
	void loadMapData(int stage_num);
};