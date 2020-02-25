#include "liquid.h"
#include "map.h"

bool Spring::spawnCheck()
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			//Map::getInstance()->map_data[Ver][Hor]
			return 0;
		}
	}
}