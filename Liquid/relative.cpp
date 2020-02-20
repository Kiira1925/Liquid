#include "relative.h"

void Relative::cal_relative_pos(Map map)
{
	map.setRelPosX(map.getPosX() + CHIP_DRAW_POSITION_X);
}