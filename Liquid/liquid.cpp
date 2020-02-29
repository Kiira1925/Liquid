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
//int temp_count[22][22];
int temp_visit[22][22];
int fill_visit[22][22];

//�S�[���n�_��ۑ�����ϐ�
Pair goalPos;
//������ۑ�����z��
Pair route[40];
//�����v
int stream_count;
int stream_max;
int stream_timer;
//�����̏���l
int liquid_max;
int liquid_count;
//�g�̎��̃t���O
bool exist_wave;
//�ŏ��p�A�j���[�V�����^�C�}�[
int poison_aniTimer;
//�A�̍��W
Pair bubble_pos[3];
//����A�j���[�V�����p�ϐ�
Pair breakPoint[5];
bool nowBreaking[5];
int breakAnimeTimer[5];



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
			fill_visit[Ver][Hor] = -1;
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
	liquid_max = 20;
	poison_aniTimer = 0;
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

void meltBreakable()
{
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			 //�����ǂ𔭌���
			if (Map::getInstance()->map_data[Ver][Hor] == 3)
			{
				//�אڂ���u���b�N�ɐ������݂���ꍇ
				if (Liquid[Ver - 1][Hor] == 1 || Liquid[Ver + 1][Hor] == 1 || Liquid[Ver][Hor - 1] == 1 || Liquid[Ver][Hor + 1] == 1)
				{
					Map::getInstance()->map_data[Ver][Hor] = 1;
					for (int i = 0; i < 5; i++)
					{
						if (nowBreaking[i] == false)
						{
							nowBreaking[i] = true;
							breakPoint[i] = { Ver,Hor };
							break;
						}
					}
				}
			}
		}
	}
}

void breakAnimation(int break_handle)
{
	for (int i = 0; i < 5; i++)
	{
		if (nowBreaking[i] == true)
		{
			DrawRectGraph(breakPoint[i].second*CHIP_SIZE+420, breakPoint[i].first*CHIP_SIZE-26, (breakAnimeTimer[i]%40/8) * CHIP_SIZE, 0, 48, 74, break_handle, TRUE);
			breakAnimeTimer[i]++;
			if (breakAnimeTimer[i] >= 40)
			{
				nowBreaking[i] = false;
				breakAnimeTimer[i] = 0;
			}
		}
	}
}

void spreadWave(int handle)
{
	exist_wave = false;

	if (liquid_count >= liquid_max)
	{
		initField();
		return;
	}

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
		stream_max--;
		initField();
	}
	
	//if (exist_wave == true)
	//{
	//	DrawRectGraph(route[stream_count].second * CHIP_SIZE + 420, route[stream_count].first * CHIP_SIZE, CHIP_SIZE * 0, CHIP_SIZE * 15, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
	//}
}

void drawWave(int handle)
{
	if (exist_wave == true)
	{
		DrawRectGraph(route[stream_count].second * CHIP_SIZE + 420, route[stream_count].first * CHIP_SIZE, CHIP_SIZE * 0, CHIP_SIZE * 15, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
	}
}

void drawPoison(int handle)
{
	poison_aniTimer++;
	int anime_frame = poison_aniTimer%48/8;
	int anime_frame2 = (poison_aniTimer - 16) % 48 / 8;
	int anime_frame3 = (poison_aniTimer - 24) % 48 / 8;
	int bubble_timer = poison_aniTimer % 48;
	bool exist_poison = false;
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Liquid[Ver][Hor] == 1)
			{
				bool up = (Liquid[Ver - 1][Hor] == 1 || Liquid[Ver - 1][Hor] == -1 || Liquid[Ver - 1][Hor] == 10);
				bool down  = (Liquid[Ver + 1][Hor] == 1 || Liquid[Ver + 1][Hor] == -1 || Liquid[Ver + 1][Hor] == 10);
				bool left = (Liquid[Ver][Hor - 1] == 1 || Liquid[Ver][Hor - 1] == -1 || Liquid[Ver][Hor - 1] == 10);
				bool right = (Liquid[Ver][Hor + 1] == 1 || Liquid[Ver][Hor + 1] == -1 || Liquid[Ver][Hor + 1] == 10);


				if ((up && down && left && right) || (up && down && !left && !right) || (!up && !down && left && right))
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 1, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (!up && down && !left && right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 2, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (!up && down && left && right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 3, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (!up && down && left && !right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 4, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (up && down && left && !right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 5, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (up && !down && left && !right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 6, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (up && !down && left && right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 7, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (up && !down && !left && right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 8, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (up && down && !left && right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 9, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (!up && down && !left && !right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 10, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (!up && !down && left && !right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 11, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (up && !down && !left && !right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 12, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
				if (!up && !down && !left && right)
				{
					DrawRectGraph(Hor * CHIP_SIZE + 420, Ver * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 13, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
				}
			}
		}
	}

	//�A�̕\��
	if (liquid_count != 0)
	{
		if (bubble_timer == 0)
		{
			do
			{
				bubble_pos[0] = { GetRand(21), GetRand(21) };
			} while (Liquid[bubble_pos[0].first][bubble_pos[0].second] != 1);
		}
		if (bubble_timer == 12)
		{
			do
			{
				bubble_pos[1] = { GetRand(21), GetRand(21) };
			} while (Liquid[bubble_pos[1].first][bubble_pos[1].second] != 1);
		}
		if (bubble_timer == 24)
		{
			do
			{
				bubble_pos[2] = { GetRand(21), GetRand(21) };
			} while (Liquid[bubble_pos[2].first][bubble_pos[2].second] != 1);
		}
		DrawRectGraph(bubble_pos[0].second * CHIP_SIZE + 420, bubble_pos[0].first * CHIP_SIZE, CHIP_SIZE * anime_frame, CHIP_SIZE * 14, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
		DrawRectGraph(bubble_pos[1].second * CHIP_SIZE + 420, bubble_pos[1].first * CHIP_SIZE, CHIP_SIZE * anime_frame2, CHIP_SIZE * 14, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
		DrawRectGraph(bubble_pos[2].second * CHIP_SIZE + 420, bubble_pos[2].first * CHIP_SIZE, CHIP_SIZE * anime_frame3, CHIP_SIZE * 14, CHIP_SIZE, CHIP_SIZE, handle, TRUE);
	}
}

void countPoison()
{
	liquid_count = 0;
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Liquid[Ver][Hor] == 1)
			{
				liquid_count++;
			}
		}
	}
}

void deleteLiquid(Block* instanceOfZERO)
{
	//�u���b�N�̑��ݍ��W����x���Z�b�g
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (Liquid[Ver][Hor] == -2)
			{
				Liquid[Ver][Hor] = 0;
			}
		}
	}

	//�u���b�N�̑��݂��Ă���`�b�v��ǂ̔���ɐ؂�ւ���
	for (int i = 0; i < Map::getInstance()->block_max; i++)
	{
		//if (Liquid[(instanceOfZERO + i)->posNumY][(instanceOfZERO + i)->posNumX] == 1)
		{
			Liquid[(instanceOfZERO + i)->posNumY][(instanceOfZERO + i)->posNumX] = -2;
		}

		//for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
		//{
		//	for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		//	{
		//		Pair liquid_pos = { Ver, Hor };
		//		Pair block_pos = { (instanceOfZERO + i)->posNumY, (instanceOfZERO + i)->posNumX };
		//		if (liquid_pos == block_pos)
		//		{
		//			Liquid[Ver][Hor] = -2;
		//		}

		//		if(Liquid[Ver][Hor] == -2)
		//		{
		//			Liquid[Ver][Hor] = 0;
		//		}
		//	}
		//}
	}

	//�����ւ̃��[�g�����݂��Ȃ��������폜
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			if (temp_visit[Ver][Hor] == -1 && Liquid[Ver][Hor] == 1)
			{
				Liquid[Ver][Hor] = 0;
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
			for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
			{
				/*for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
				{
					temp_count[Ver][Hor] = Count[Ver][Hor];
				}*/
			}
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
			for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
			{
				//for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
				//{
				//	temp_count[Ver][Hor] = Count[Ver][Hor];
				//}
			}
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
			for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
			{
				//for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
				//{
				//	temp_count[Ver][Hor] = Count[Ver][Hor];
				//}
			}
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
			for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
			{
				//for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
				//{
				//	temp_count[Ver][Hor] = Count[Ver][Hor];
				//}
			}
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
			for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
			{
				//for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
				//{
				//	temp_count[Ver][Hor] = Count[Ver][Hor];
				//}
			}
			//������
			initField();
			break;
		}
	}
}

void BFS_FILL()
{
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
				break;
			}
		}
	}

	while (!que.empty())
	{
		//�i�[�p�ϐ�
		Pair p;
		//�擪�̃L���[�����o��
		if (!que.empty())
		{
			p = que.front();
		}

		//�Y���L���[�̖K��`�F�b�N��K��ς݂ɕύX
		fill_visit[p.first][p.second] = 1;

		//������̗אڃu���b�N��T��
		if (Liquid[p.first - 1][p.second] == 1)
		{
			//�אڂ���u���b�N���T���ς݂łȂ���Ώ������s��
			if (fill_visit[p.first - 1][p.second] == -1)
			{
				//�T���\�胊�X�g�ɑ}��
				que.push(Pair((p.first - 1), p.second));
				//�K��`�F�b�N�z��̑Ή�����n�_��T���\��ɕύX
				fill_visit[p.first - 1][p.second] = 0;
			}
		}

		//�������̗אڃu���b�N��T��
		if (Liquid[p.first + 1][p.second] == 1)
		{
			if (fill_visit[p.first + 1][p.second] == -1)
			{
				que.push(Pair((p.first + 1), p.second));
				fill_visit[p.first + 1][p.second] = 0;
			}
		}

		//�������̗אڃu���b�N��T��
		if (Liquid[p.first][p.second - 1] == 1)
		{
			if (fill_visit[p.first][p.second - 1] == -1)
			{
				que.push(Pair(p.first, (p.second - 1)));
				fill_visit[p.first][p.second - 1] = 0;
			}
		}

		//�E�����̗אڃu���b�N��T��
		if (Liquid[p.first][p.second + 1] == 1)
		{
			if (fill_visit[p.first][p.second + 1] == -1)
			{
				que.push(Pair(p.first, (p.second + 1)));
				fill_visit[p.first][p.second + 1] = 0;
			}
		}

		//�擪�L���[���폜
		if (!que.empty())
		{
			que.pop();
		}
	}
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			temp_visit[Ver][Hor] = fill_visit[Ver][Hor];
		}
	}
	for (int Ver = 0; Ver < MAPDATA_V_MAX; Ver++)
	{
		for (int Hor = 0; Hor < MAPDATA_H_MAX; Hor++)
		{
			fill_visit[Ver][Hor] = -1;
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