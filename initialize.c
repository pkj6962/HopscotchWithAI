#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"


void player_initialize()
{
	User = (player*)malloc(sizeof(player));
	Ai = (player*)malloc(sizeof(player));

	User->card_num = DEFAULT_CARD_AVAIL;
	Ai->card_num = DEFAULT_CARD_AVAIL;
	return;
}

void map_initialize()
{
	int i, j;
	int idx, k;
	int Att[4] = { 'A', 'T', 'T', ':' };
	int Def[4] = { 'D', 'E', 'F', ':' };

	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			map[i][j] = ' ';

	/*랜드 간을 연결시켜주는 엣지 초기화  */

	for (i = 1; i < NODE_NUM; i++)
	{
		if (i % 6 == 0)
			continue;
		for (j = 0; j < LINE_NUM; j++)
		{
			ptr[EDGE_ROW[i][j]] = '-';
			//ptr[EDGE_ROW[i][j] + 110] = '-'; 
		}
	}


	for (i = 1; i < EDGE_COL_NUM; i++)
	{
		ptr[EDGE_COL[i]] = '|';
	}



	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < 5; j++)
			map[i][j] = '\t';
	/*
	for (i = 1; i < NODE_NUM; i++)
		for (j = 0; j < EDGE_NUM; j++)
			ptr[NODE[i][j]] = '#';
	*/


	/*공격력, 방어력 표시*/
	for (i = 1; i < NODE_NUM; i++)
	{
		for (j = 0; j < 4; j++)
		{
			ptr[Att_index[i] + j] = Att[j];
			ptr[Att_index[i] + MAP_COL + j] = Def[j];
		}
		ptr[Att_index[i] + 5] = land_list[i]->att + 48;
		ptr[Att_index[i] + MAP_COL + 5] = land_list[i]->def + 48;
	}





	for (i = 1; i < NODE_NUM; i++)
		if (land_list[i]->owner == 0) /*땅의 소유권이 user에게 있으면*/
		{
			for (j = 0; j < EDGE_NUM; j++)
				ptr[NODE[i][j]] = '@';
		}
		else if (land_list[i]->owner == 1)
		{
			for (j = 0; j < EDGE_NUM; j++)
				ptr[NODE[i][j]] = '*';
		}
		else
		{
			for (j = 0; j < EDGE_NUM; j++)
				ptr[NODE[i][j]] = '\\';
			for (j = 0; j < NODE_COL - 2; j++)						/*중립 랜드의 내부는 '까맣게' 채워진다.  */
			{
				idx = newtral_index[j];
				for (k = NODE[i][idx]; k != NODE[i][idx + 1]; k++)
					ptr[k] = '\\';
			}
			/*중립인덱스에서 하나씩 가져와서 그 안을 '\'로 칠한다. */

		}

	for (i = 0; i < MAP_ROW; i++)
		map[i][MAP_COL - 1] = '\n';
}

/*24개의 랜드 중 임의의 4개는 중립지대로, 10개는 user의 토지로, 10개는 AI의 토지로 할당하는 함수  */
void landAssign(void)
{
	/*3번, 10번, 10번의 loop. 관건은 RAND() 출력된 값이 이미 선택된 값일 경우 배제하는 것이 필요 */
	/*1, 2, 7번은 무조건 유저의 랜드. 24, 23, 18은 무조건 AI의 랜드*/
	int Usersland[3] = { 1, 2, 7 };
	int AIsland[3] = { 18, 23, 24 };
	int i, j, n;
	/*최초에는 모든 영토를 -1(중립지대)로 설정*/

	for (i = 1; i < NODE_NUM; i++)
	{
		land_owner[i] = -1;
	}
	for (i = 0; i < 3; i++)
	{
		land_owner[Usersland[i]] = 0;
		land_owner[AIsland[i]] = 1;
	}
	srand(time(NULL));



	for (i = 0; i < 7; i++)
	{
		n = rand() % 24 + 1;
		if ((land_owner[n] == 0) || (land_owner[n] == 1))		/*이미 선택된 넘버면*/
		{
			i--;
			continue;				/*그 반복 분기는 없던 걸로 하고 다시 반복*/
		}
		land_owner[n] = 0;
	}
	User->total_land = 10;


	for (i = 0; i < 7; i++)
	{
		n = rand() % 24 + 1;
		if ((land_owner[n] == 0) || (land_owner[n] == 1))
		{
			i--;
			continue;
		}
		land_owner[n] = 1;
	}
	Ai->total_land = 10;

	for (i = 1, j = 0; i < NODE_NUM; i++)
	{
		if (land_owner[i] == -1)
		{
			newtral_land[j] = i;
			j++;
		}
	}
}
void land_initialize()
{
	/*중립지대와 AI, 유저의 랜드를 임의로 할당한다. 공격력과 방어력은 *0으로 초기화한다.--> 공격력은 1이상의 정수*/

	int i, j;

	for (i = 0; i < NODE_NUM; i++)
	{
		land_list[i] = (land*)malloc(sizeof(land));
	}

	landAssign();			/*중립지대와 AI, 유저의 랜드를 임의로 할당 */
	printf("3");



	for (i = 0; i < NODE_ROW; i++)
	{
		for (j = 1; j < NODE_COL + 1; j++)
		{
			//scanf("%d", &owner); /*get 0(player) or 1(ai)*/
			land_list[i * NODE_COL + j]->att = DEFAULT_ATT;
			land_list[i * NODE_COL + j]->def = DEFAULT_DEF;
			/*1~24번째 인덱스의 땅의 정보를 초기화한다.*/
			land_list[i * NODE_COL + j]->owner = land_owner[i * NODE_COL + j];
			land_list[i * NODE_COL + j]->link = NULL;
		}
	}
}
void linkLand(int from, int to) /*FROM land의 연결 랜드로 TO land를 포함시킨다.*/
{
	//land_list[from]의 linked list에 TO land의 인덱스 포함. 
	/*링크드리스트를 통한 연결관계의 구축
	from 인덱스를 가진 랜드의 링크에 to 인덱스를 가진 랜드를 연결한다. */
	land_link* temp = (land_link*)malloc(sizeof(land_link));
	temp->num = to;
	temp->next = NULL;


	if (land_list[from]->link != NULL)
	{
		temp->next = land_list[from]->link;
	}
	land_list[from]->link = temp;
}
void edge_initialize()
/*---------------------------------------*/
/*land간의 연결관계를 초기화한다.*/
{
	int n;
	for (n = 1; n < NODE_NUM; n++)
	{
		if (n % 6 != 0)
			linkLand(n, n + 1);
		if (n % 6 != 1)
			linkLand(n, n - 1);
		if (n <= 18)
			linkLand(n, n + 6);
		if (n > 6)
			linkLand(n, n - 6);
	}

}

