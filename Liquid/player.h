#pragma once
#include "common.h"
#include "main.h"
#include "singleton.h"

class Player :public Sprite ,public Singleton<Player> 
{
private:
	//static const int OBJ_MAX = 1;   

public:
	void init();
    void update();
    void draw();
    void end();
};