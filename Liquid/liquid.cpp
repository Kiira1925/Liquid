#include <iostream>
#include <vector>
#include <queue>
#include "liquid.h"
#include "map.h"
#include "DxLib.h"

using namespace std;
//using Field = vector<vector<int>>;

//�n�`�����i�[����z��
int Liquid[22][22];
//�T���v���O�����̖K��󋵂�ۑ�����z��
int Visit[22][22];
//�e�u���b�N�̖K�⏇��ۑ�����z��
int Count[22][22];

//�S�[���n�_��ۑ�����ϐ�
Pair goalPos;
//������ۑ�����z��
Pair route[40];
//�����v
int stream_count;
int stream_max;
int stream_timer;
//�����̏���l
int liquid_max = 8;


void initLiquid()
{
	//�}�b�v�̓ǂݍ���
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			Liquid[Ver][Hor] = 0;
			//��������ȊO���ŋ�ʂ���
			if (Map::getInstance()->map_data[Ver][Hor] > 1 && (Map::getInstance()->map_data[Ver][Hor] != 5))
			{
				Liquid[Ver][Hor] = -1;
			}
			//else if(Map::getInstance()->map_data[Ver][Hor] == 1)
			//{
			//	Liquid[Ver][Hor] = 0;
			//}

			////�X�^�[�g�n�_��ݒ�
			//if (Map::getInstance()->map_data[Ver][Hor] == 4)
			//{
			//	Liquid[Ver][Hor] = 10;
			//}
			////�S�[���n�_��ݒ�
			//if (Map::getInstance()->map_data[Ver][Hor] == 5)
			//{
			//	Liquid[Ver][Hor] = 11;
			//}
		}
	}
}

void initField()
{
	//�K��`�F�b�N�z��̏�����
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			//�X�^�[�g�n�_��ݒ�
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
		//��
		if (Count[nowPos.first - 1][nowPos.second] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//�S�[�����痣�ꂽ�l�ɑΉ������z��Ԃɍ��W���i�[
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first,nowPos.second);
			nowPos = make_pair(nowPos.first - 1, nowPos.second);
			continue;
		}
		//��
		if (Count[nowPos.first + 1][nowPos.second] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//�S�[�����痣�ꂽ�l�ɑΉ������z��Ԃɍ��W���i�[
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first , nowPos.second);
			nowPos = make_pair(nowPos.first + 1, nowPos.second);
			continue;
		}
		//��
		if (Count[nowPos.first][nowPos.second -1] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//�S�[�����痣�ꂽ�l�ɑΉ������z��Ԃɍ��W���i�[
			route[Count[nowPos.first][nowPos.second]] = make_pair(nowPos.first, nowPos.second);
			nowPos = make_pair(nowPos.first, nowPos.second -1);
			continue;
		}
		//�E
		if (Count[nowPos.first][nowPos.second + 1] == (Count[nowPos.first][nowPos.second] - 1))
		{
			//�S�[�����痣�ꂽ�l�ɑΉ������z��Ԃɍ��W���i�[
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
	//�S�[������
	bool isGoal = false;
	//���W�^�L���[
	queue<Pair> que;

	//�X�^�[�g�n�_���L���[�Ɋi�[
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
		//�i�[�p�ϐ�
		Pair p;
		//�擪�̃L���[�����o��
		if (!que.empty())
		{
			p = que.front();
		}

		//�Y���L���[�̖K��`�F�b�N��K��ς݂ɕύX
		Visit[p.first][p.second] = 1;
		
		//������̗אڃu���b�N��T��
		if (Liquid[p.first - 1][p.second] == 1)
		{
			//�אڂ���u���b�N���T���ς݂łȂ���Ώ������s��
			if (Visit[p.first - 1][p.second] == -1)
			{
				//�T���\�胊�X�g�ɑ}��
				que.push(Pair((p.first - 1), p.second));
				//�K��`�F�b�N�z��̑Ή�����n�_��T���\��ɕύX
				Visit[p.first - 1][p.second] = 0;
				//�K�⏇���L�^
				Count[p.first - 1][p.second] = Count[p.first][p.second] + 1;
			}
		}
		//�ڕW�n�_�𔭌������ꍇ
		if (Liquid[p.first - 1][p.second] == 0)
		{
			Count[p.first - 1][p.second] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first - 1, p.second);
			searchRoute();
			isGoal = true;
			break;
		}

		//�������̗אڃu���b�N��T��
		if (Liquid[p.first + 1][p.second] == 1)
		{
			if (Visit[p.first + 1][p.second] == -1)
			{
				que.push(Pair((p.first + 1), p.second));
				Visit[p.first + 1][p.second] = 0;
				Count[p.first + 1][p.second] = Count[p.first][p.second] + 1;
			}
		}
		//�ڕW�n�_�𔭌������ꍇ
		if (Liquid[p.first + 1][p.second] == 0)
		{
			Count[p.first + 1][p.second] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first + 1, p.second);
			searchRoute();
			isGoal = true;
			break;
		}

		//�������̗אڃu���b�N��T��
		if (Liquid[p.first][p.second - 1] == 1)
		{
			if (Visit[p.first][p.second - 1] == -1)
			{
				que.push(Pair(p.first, (p.second - 1)));
				Visit[p.first][p.second - 1] = 0;
				Count[p.first][p.second - 1] = Count[p.first][p.second] + 1;
			}
		}
		//�ڕW�n�_�𔭌������ꍇ
		if (Liquid[p.first][p.second - 1] == 0)
		{
			Count[p.first][p.second - 1] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first, p.second - 1);
			searchRoute();
			isGoal = true;
			break;
		}

		//�E�����̗אڃu���b�N��T��
		if (Liquid[p.first][p.second + 1] == 1)
		{
			if (Visit[p.first][p.second + 1] == -1)
			{
				que.push(Pair(p.first, (p.second + 1)));
				Visit[p.first][p.second + 1] = 0;
				Count[p.first][p.second + 1] = Count[p.first][p.second] + 1;
			}
		}
		//�ڕW�n�_�𔭌������ꍇ
		if (Liquid[p.first][p.second + 1] == 0)
		{
			Count[p.first][p.second + 1] = Count[p.first][p.second] + 1;
			goalPos = make_pair(p.first, p.second + 1);
			searchRoute();
			isGoal = true;
			break;
		}

		//�擪�L���[���폜
		if (!que.empty())
		{
			que.pop();
		}
		//�ڕW�n�_��������Ȃ������ꍇ���������ďI��
		else
		{
			//������
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