#pragma once
// インクルード ---------------------------------------------------------
#include "common.h"
#include "singleton.h"
#include <stdio.h>

// 定数 ----------------------------------------------------------------
#define		CHIP_SIZE			(48)
#define		MAPDATA_H_MAX		(22)
#define		MAPDATA_V_MAX		(22)
#define		MAP_DRAW_POSITION_X	(420)
#define		MAP_DRAW_POSITION_Y	(0)

enum MapNum { Void, Road, Wall, Breakable, Spring, Goal };
enum ObjectNum {None,PlayerSpawnPoint,};
class Map : public Sprite, public Singleton<Map>
{
private:
public:
	int anime_timer;

	const char* MapFileName;
	const char* ObjFileName;
	//1~20:地形チップ 20~:オブジェクトチップ
	int map_data[MAPDATA_V_MAX][MAPDATA_H_MAX];

	void init(int stage_num);
	void update();
	void draw();
	void end();

	void drawMap();
	void drawBreakable();
	void drawSpring();
	void loadChipData();
	void loadMapData(int stage_num);
};