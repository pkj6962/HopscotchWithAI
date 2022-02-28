#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"


void printLink(int idx)
/***************************************************
/idx번째 인덱스의 랜드와 연결된 랜드들의 목록을 출력*/
{
	printf("랜드 %2d의 연결 랜드:  ", idx);
	land_link* temp;
	temp = land_list[idx]->link;

	for (; temp; temp = temp->next)
		printf("%d ", temp->num);
	printf("\n");
	return;
}
void print_basic_info()
{
	system("cls"); 

	printf("남은 턴 수:  %d\n", remaining_turns);
	printf("유저의 유효토지 보유 수  / 총 토지 보유 수: %d / %d\n", User->valid_land, User->total_land);
	printf("AI의 유효토지 보유 수 / 총 토지 보유 수: %d / %d\n", Ai->valid_land, Ai->total_land);
	return;
}
void print_map()
{
	int i, j;

	/*공격, 강화 후 공/방어력 변화 및 소유권 변화를 재반영 */
	for (i = 1; i < NODE_NUM; i++)
	{

		/*공격력이 10이상일 경우와 그렇지 않을 경우를 나눠서 할당*/

		if (land_list[i]->att >= 10) {
			ptr[Att_index[i] + 5] = land_list[i]->att + 55;
		}
		else {
			ptr[Att_index[i] + 5] = land_list[i]->att + 48;
		}

		if (land_list[i]->def >= 10) {
			ptr[Att_index[i] + MAP_COL + 5] = land_list[i]->def + 55;
		}
		else {
			ptr[Att_index[i] + MAP_COL + 5] = land_list[i]->def + 48;

		}
		if (land_list[i]->owner == 0)
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
			for (j = 0; j < 4; j++)
			{
				ptr[Att_index[newtral_land[j]] + 5] = '\\';
				ptr[Att_index[newtral_land[j]] + 110 + 5] = '\\';
			}
		}
	}




	printf("\n");
	printf("\t\t\t\t\t   USER\n\t\t\t\t\t    ↓\n");

	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			printf("%c", map[i][j]);

	for (i = 0; i < 134; i++)
		printf(" ");
	printf("↑\n");
	for (i = 0; i < 134; i++)
		printf(" ");
	printf("AI\n");

}
void printAction(int player, int action, int stats, int from, int to, int value_before_change)
{
	struct player* Player; 
	if (player == user)
		Player = User;
	else
		Player = Ai;

	if (action == Att)
	{
		printf("\n%s가 랜드[%d]에서 랜드[%d]을(를) 공격했습니다.\n", PlayerList[player], from, to);
		Sleep(2000);
		if (land_owner[to] == player)
		{
			printf("%s가 랜드[%d]을(를) 점령했습니다.\n", PlayerList[player], to);	Sleep(2000);

			if (to == capital_of_player[!player])
			{
				printf("%s가 수도랜드를 점령했습니다.\n", PlayerList[player]); Sleep(2000);

				printf("%s가 전투에서 승리하였습니다!\n", PlayerList[player]); Sleep(2000); 
			}
		
		}
		else {
			printf("랜드[%d]의 방어력이 %d에서 %d이(가) 되었습니다.\n", to, value_before_change, land_list[to]->def); Sleep(2000); 
		}
	}
	else if (action == Upg)
	{
		if (stats == att)
		{
			printf("%s가 랜드[%d]의 %s을(를) %d에서 %d로 업그레이드하였습니다.\n", PlayerList[player], from, StatsList[stats], value_before_change,land_list[from]->att); Sleep(2000); 
		} 
		else if (stats == def)
		{
			printf("%s가 랜드[%d]의 %s을(를) %d에서 %d로 업그레이드하였습니다.\n", PlayerList[player], from, StatsList[stats], value_before_change, land_list[from]->def); Sleep(2000);
		}
		else /*stats == cardnum*/
		{
			printf("%s가 자신의 %s을(를) %d에서 %d로 업그레이드하였습니다.\n", PlayerList[player], StatsList[stats], value_before_change, Player->card_num); Sleep(2000);
		}
	}

	
	/*player의 행동의 결과를 출력한다.
	공격시:
	~~가 랜드 a에서 랜드 b를 공격했습니다.
	점령시
	~~가 랜드 b를 점령했습니다.
		수도 노드 점령시
		~~가 ~~의 수도 노드를 점령했습니다.
		~~가 전투에서 승리하였습니다!
		~~포인트를 획득하셨습니다. 
	
	점령실패시 
	랜드b의 방어력이 i에서 j이(가) 되었습니다. 
	
	업그레이드시
	~가 랜드a의 공격력을 k만큼 업그레이드했습니다. 
	~가 랜드a의 방어력을 k만큼 업그레이드했습니다.
	~가 자신의 행동력을 k만큼 업그레이드했습니다. 
	*/
}

