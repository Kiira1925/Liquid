#pragma once
#include "common.h"
#include "singleton.h"

#define Pair pair<int,int>

class Spring : public Sprite
{
private:
	int spawn_limit;
public:
	bool spawnCheck();
};

class Poison : public Sprite, public Singleton<Poison>
{
private:

};

void initLiquid();
void initField();
void searchRoute();
void countPoison();
void meltBreakable();
void breakAnimation(int break_handle);
void spreadWave(int handle);
void drawWave(int handle);
void drawPoison(int handle);
void BFS();