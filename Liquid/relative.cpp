#include "relative.h"
#include "map.h"
#include "player.h"

void Relative::cal_relative_pos()
{
	Map::getInstance()->setRelPosX(Map::getInstance()->getPosX() + CHIP_DRAW_POSITION_X);
	Map::getInstance()->setRelPosY(Map::getInstance()->getPosY());
}