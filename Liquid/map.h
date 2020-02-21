#pragma once
// �C���N���[�h ---------------------------------------------------------
#include "common.h"
#include "singleton.h"
#include <stdio.h>

// �萔 ----------------------------------------------------------------
#define		CHIP_SIZE			(48)
#define		MAPDATA_H_MAX		(22)
#define		MAPDATA_V_MAX		(22)
#define		MAP_DRAW_POSITION_X	(420)
#define		MAP_DRAW_POSITION_Y	(0)

class Map : public Sprite, public Singleton<Map>
{
private:
	int map_data[MAPDATA_V_MAX][MAPDATA_H_MAX];
	const char* MapFileName;
	const char* ObjFileName;
public:
	void init(int stage_num);
	void update();
	void draw();
	void end();


	void drawMap();
	void loadChipData();
	void loadMapData(int stage_num);
};