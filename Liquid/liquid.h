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
void spreadWave(int handle);
void drawPoison(int handle);
void BFS();