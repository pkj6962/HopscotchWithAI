#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"


void connection_with_capital(void) /*<-- 수도 노드와 연결된 랜드들을 capital[]에 반영한다. .*/
{
	int i = 0;
	int idx;
	land_link* linked;
	short int visited[NODE_NUM];
	int owner;
	int CAPITAL[] = { 1, 24 };
	int player[] = { 0, 1 };
	int cap;
	int count;

	capital_initialize();
	for (i = 1; i < NODE_NUM; i++)
	{
		visited[i] = 0;
	}



	for (int j = 0; j < 2; j++)
	{
		cap = CAPITAL[j];
		owner = land_list[cap]->owner;
		count = 0;

		push(cap);
		visited[cap] = 1;
		count++;
		while (!is_Empty())
		{
			idx = pop();
			linked = land_list[idx]->link;
			for (; linked; linked = linked->next)
			{
				if (visited[linked->num] == 1)
					continue;
				if (land_list[linked->num]->owner == owner)
				{
					capital[linked->num] = capital[cap];
					push(linked->num);
					visited[linked->num] = 1;
					count++;
				}
			}
		}
		if (j == 0)
			User->valid_land = count;
		else
			Ai->valid_land = count;

		/*
		고려해야 하는 부분
		1. 상대방의 영토를 빼앗았을 때(공격지점 함수 재가동)
		2. 빼앗겼을 떄(빼앗긴 랜드가 수도와 연결되었는지 확인 -> 있으면 수도에서부터 다시 확인 시작
		*/
	}

	return;

}
void capital_initialize(void)
{
	int i;
	for (i = 1; i < NODE_NUM; i++)
	{
		capital[i] = i;
	}
}
void findTarget(int player, int* from, int* to) /*AI의 최적의 공격루트를 찾는 함수*/
{
	/*
		0. valid land를 표시한 capital을 복사한다.
		1. 자신의 유효 랜드 중 상대 영토와 인접한 영토를 찾아서 저장한다.(malloc 사용)
		2. 해당 영토들에서 공격가능한 모든 경우를 돌면서, 상대 영토를 점령했을 때
		생기는 유효랜드의 변화를 확인한다.
		3. (점령후)(ai의 유효랜드의 수 - 유저의 유효랜드의 수)가 최대가 되는 경우(from, to)를 저장한다.
		4. 모든 경우를 돌면서 최대가 되는 경우로 공격한다.
	*/

	/*유저입장에서의 최선의 공격루트도 찾을 수 있게 함수를 개량해서 AI가 방어력 강화를 할 랜드를 선택할 수 있게 해야 한다. */


	int i, j;
	int copy_capital[NODE_NUM];
	land_link* Att_avail_land = (land_link*)malloc(sizeof(land_link));
	Att_avail_land = NULL;
	int* valid_land;


	struct player* Att, * Def;

	if (player == user)
	{
		Att = User;
		Def = Ai;
	}
	else
	{
		Att = Ai;
		Def = User;
	}

	valid_land = (int*)malloc(sizeof(int) * (Att->valid_land));


	for (i = 1; i < NODE_NUM; i++)
	{
		copy_capital[i] = capital[i];
	}
	/*나중에 원복시킬 것임.*/

	j = 0;
	for (i = NODE_NUM - 1; i != 0; i--)
	{
		/*수도 노드부터 돌면서 유효랜드를 확인한다.*/

		if (j == Att->valid_land)
			break;

		if (capital[i] == capital_of_player[player])
			valid_land[j++] = i;
	}

	int valSave[2];
	int land_num;
	land_link* node;
	int diff;  /*Ai's valid land  - User's valid land*/
	int highest = -24; /*diff 중 최대 차이: 가장 효과적인 공격루트 */
	int source;	/*highest일 때의 공격출발지*/
	int dest; /*highest일 떄의 공격도착지*/


	/*valid 랜드를 돌면서, 상대 영토와 인접한, 공격가능한 랜드를 찾아 저장한다*/
	for (i = 0; i < Att->valid_land; i++)
	{
		land_num = valid_land[i];
		node = land_list[land_num]->link;

		for (; node; node = node->next)
		{
			if (land_list[node->num]->owner == !player)		/*인접한 땅이 상대의 땅일 때*/
			{
				/*이 상대 땅을 점령했을 때의 player의 유효랜드의 차를 구한다.*/

				int valSave[2];
				valSave[0] = User->valid_land;
				valSave[1] = Ai->valid_land;


				land_list[node->num]->owner = player;		/*Attacker의 땅으로 소유권을 바꾼 뒤 바뀐 후의 유효랜드의 수의 차를 계산해본다.*/

				connection_with_capital();

				diff = Att->valid_land - Def->valid_land;

				if (highest < diff)
				{
					highest = diff;
					source = land_num;
					dest = node->num;
				}

				/*3. 복원*/
				User->valid_land = valSave[0];
				Ai->valid_land = valSave[1];
				for (j = 1; j < NODE_NUM; j++)
				{
					capital[j] = copy_capital[j];
				}
				land_list[node->num]->owner = !player;
			}
			//다음 인접 랜드에 대해서 반복
		}


	}
	*from = source;
	*to = dest;
}