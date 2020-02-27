#include <iostream>
#include <vector>
#include <queue>
#include "liquid.h"
#include "map.h"
#include "DxLib.h"

using namespace std;
//using Field = vector<vector<int>>;

//地形情報を格納する配列
int Liquid[22][22];
//探索プログラムの訪問状況を保存する配列
int Visit[22][22];
//各ブロックの訪問順を保存する配列
int Count[22][22];

//ゴール地点を保存する変数
Pair goalPos;
//道順を保存する配列
Pair route[40];
//歩数計
int stream_count;
int stream_max;
int stream_timer;
//水源の上限値
int liquid_max = 8;


void initLiquid()
{
	//マップの読み込み
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			Liquid[Ver][Hor] = 0;
			//道かそれ以外かで区別する
			if (Map::getInstance()->map_data[Ver][Hor] > 1 && (Map::getInstance()->map_data[Ver][Hor] != 5))
			{
				Liquid[Ver][Hor] = -1;
			}
			//else if(Map::getInstance()->map_data[Ver][Hor] == 1)
			//{
			//	Liquid[Ver][Hor] = 0;
			//}

			////スタート地点を設定
			//if (Map::getInstance()->map_data[Ver][Hor] == 4)
			//{
			//	Liquid[Ver][Hor] = 10;
			//}
			////ゴール地点を設定
			//if (Map::getInstance()->map_data[Ver][Hor] == 5)
			//{
			//	Liquid[Ver][Hor] = 11;
			//}
		}
	}
}

void initField()
{
	//訪問チェック配列の初期化
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			//スタート地点を設定
			if (Map::getInstance()->map_data[Ver][Hor] == 5)
			{
				Liquid[Ver][Hor] = 10;
			}
			Visit[Ver][Hor] = -1;
			Count[Ver][Hor] = -1;
		}
	}

	for (int i = 0; i < 40; i++)
	{
		route[i] = {-1, -1};
	}

	stream_count = 0;
	stream_max = 0;
	stream_timer = 5;
}

void searchRoute()
{
	Pair nowPos = goalPos;
	for (int count = 0; count < Count[goalPos.first][goalPos.second]; count++)
	{
		//上
		if (Count[nowPos.first - 1][nowPos.second] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//ゴールから離れた値に対応した配列番に座標を格納
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first,nowPos.second);
			nowPos = make_pair(nowPos.first - 1, nowPos.second);
			continue;
		}
		//下
		if (Count[nowPos.first + 1][nowPos.second] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//ゴールから離れた値に対応した配列番に座標を格納
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first , nowPos.second);
			nowPos = make_pair(nowPos.first + 1, nowPos.second);
			continue;
		}
		//左
		if (Count[nowPos.first][nowPos.second -1] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//ゴールから離れた値に対応した配列番に座標を格納
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first, nowPos.second);
			nowPos = make_pair(nowPos.first, nowPos.second -1);
			continue;
		}
		//右
		if (Count[nowPos.first][nowPos.second + 1] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//ゴールから離れた値に対応した配列番に座標を格納
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first, nowPos.second);
			nowPos = make_pair(nowPos.first, nowPos.second + 1);
			continue;
		}
	}
}

void spreadWave(int handle)
{
	bool exist_wave = false;
	if (stream_max == 0) { stream_max = Count[goalPos.first][goalPos.second]; }
	if(stream_count < stream_max)
	{
		exist_wave = true;
		if (stream_timer == 5)
		{
			stream_count++;
			stream_timer = 0;
		}
		stream_timer++;
	}


	if (stream_count == stream_max)
	{
		Liquid[route[stream_count].first][route[stream_count].second] = 1;
		initField();
	}
	
	if (exist_wave == true)
	{
		DrawRectGraph(route[stream_count].second * CHIP_SIZE + 420, route[stream_count].first * CHIP_SIZE, CHIP_SIZE * 0, CHIP_SIZE * 15, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
	}
}

void drawPoison(int handle)
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Liquid[Ver][Hor] == 1)
			{
				DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * 0, CHIP_SIZE * 1, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
			}
		}
	}
}

void BFS()
{
	//ゴール判定
	bool isGoal = false;
	//座標型キュー
	queue<Pair> que;

	//スタート地点をキューに格納
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Liquid[Ver][Hor] == 10)
			{
				que.push(Pair(Ver, Hor));
				Count[Ver][Hor] = 0;
				break;
			}
		}
	}

	//for (int i = 0; i < 80; i++)
	while (!isGoal)
	{
		//格納用変数
		Pair p;
		//先頭のキューを取り出す
		if (!que.empty())
		{
			p = que.front();
		}

		//該当キューの訪問チェックを訪問済みに変更
		Visit[p.first][p.second] = 1;
		
		//上方向の隣接ブロックを探索
		if (Liquid[p.first - 1][p.second] == 1)
		{
			//隣接するブロックが探索済みでなければ処理を行う
			if (Visit[p.first - 1][p.second] == -1)
			{
				//探索予定リストに挿入
				que.push(Pair((p.first - 1), p.second));
				//訪問チェック配列の対応する地点を探索予定に変更
				Visit[p.first - 1][p.second] = 0;
				//訪問順を記録
				Count[p.first - 1][p.second] = Count[p.first][p.second] + 1;
			}
		}
		//目標地点を発見した場合
		if (Liquid[p.first - 1][p.second] == 0)
		{
			Count[p.first - 1][p.second] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first - 1, p.second);
			searchRoute();
			isGoal = true;
			break;
		}

		//下方向の隣接ブロックを探索
		if (Liquid[p.first + 1][p.second] == 1)
		{
			if (Visit[p.first + 1][p.second] == -1)
			{
				que.push(Pair((p.first + 1), p.second));
				Visit[p.first + 1][p.second] = 0;
				Count[p.first + 1][p.second] = Count[p.first][p.second] + 1;
			}
		}
		//目標地点を発見した場合
		if (Liquid[p.first + 1][p.second] == 0)
		{
			Count[p.first + 1][p.second] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first + 1, p.second);
			searchRoute();
			isGoal = true;
			break;
		}

		//左方向の隣接ブロックを探索
		if (Liquid[p.first][p.second - 1] == 1)
		{
			if (Visit[p.first][p.second - 1] == -1)
			{
				que.push(Pair(p.first, (p.second - 1)));
				Visit[p.first][p.second - 1] = 0;
				Count[p.first][p.second - 1] = Count[p.first][p.second] + 1;
			}
		}
		//目標地点を発見した場合
		if (Liquid[p.first][p.second - 1] == 0)
		{
			Count[p.first][p.second - 1] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first, p.second - 1);
			searchRoute();
			isGoal = true;
			break;
		}

		//右方向の隣接ブロックを探索
		if (Liquid[p.first][p.second + 1] == 1)
		{
			if (Visit[p.first][p.second + 1] == -1)
			{
				que.push(Pair(p.first, (p.second + 1)));
				Visit[p.first][p.second + 1] = 0;
				Count[p.first][p.second + 1] = Count[p.first][p.second] + 1;
			}
		}
		//目標地点を発見した場合
		if (Liquid[p.first][p.second + 1] == 0)
		{
			Count[p.first][p.second + 1] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first, p.second + 1);
			searchRoute();
			isGoal = true;
			break;
		}

		//先頭キューを削除
		if (!que.empty())
		{
			que.pop();
		}
		//目標地点が見つからなかった場合初期化して終了
		else
		{
			//初期化
			initField();
			break;
		}
	}
}

bool Spring::spawnCheck()
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			return 0;
		}
	}
}