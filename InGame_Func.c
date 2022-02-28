#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"

void unionLand(int x, int y)
{
	/*x는 1(user의 수도) 아니면 24(AI의 수도)이다. Y를 x와 연결된 랜드로 편입시킨다. */
	if (x == 1)
	{
		capital[y] = capital[x];
	}
	else /*24, 즉 ai의 수도이면*/
	{
		capital[x] = capital[y];
	}
	return;
}
int choose_from(int player, int action)
{
	int from, owner;
	do {
		printf("아군의 영토를 선택해주십시오.(1-24): ");
		scanf("%d", &from);

		if ((from > 24) || (from <= 0))
		{
			printf("잘못된 입력입니다.\n\n");
			Sleep(500);
			continue;
		}
		owner = land_list[from]->owner;
		if (owner != player)
		{
			printf("잘못된 접근입니다. 아군의 영토에만 접근할 수 있습니다.\n\n");
			Sleep(500);
			continue;
		}
		if ((action == Att) && (capital[from] != capital_of_player[player])) /*플레이어의 선택이 '공격'인데 수도노드와 인접하지 않으면 */
		{
			printf("수도와 인접한 영토에서만 선택할 수 있습니다.\n\n");
			Sleep(500);
			continue;
		}
		break;
	} while (1);





	return from;
}
int choose_to(int player, int* from)
{
	int to, owner, exit_flag;
	land_link* temp;
	temp = land_list[*from]->link;
	
	do {
		printf("몇 번 영토를 공격하시겠습니까?(이전으로 되돌아가기: 0번): ");
		scanf("%d", &to);
		if (to == 0)
		{
			*from = choose_from(player, Att);
			to = choose_to(player, from);
		}
		if ((to > 24) || (to <= 0))
		{
			printf("잘못된 입력입니다.\n\n");
			continue;
		}
		owner = land_list[to]->owner;
		if (owner == -1) /*중립지대를 선택했으면*/
		{
			printf("중립지대는 공격할 수 없습니다.\n\n");
			continue;
		}
		if (owner == player)	/*아군의 영토를 공격 대상으로 삼았으면*/
		{
			printf("잘못된 접근입니다. 아군의 영토는 공격할 수 없습니다.\n\n");
			continue;
		}
		/*from land의 인접 랜드를 돌면서 to land가 있는지 찾는다. 있으면 break, 없으면 반복*/
		for (temp = land_list[*from]->link; temp; temp = temp->next)
		{
			if (temp->num == to)
			{
				break;
				exit_flag = 1;
			}
		}
		if (!temp)
		{
			printf("잘못된 접근입니다. 인접한 영토만 공격할 수 있습니다.\n\n");
			continue;
		}
		break;
	} while (1);
	return to;
}
void attack(int player)
{
	int from, to;
	int exit_flag = 0; /*while문을 탈출하기 위한 flag */
	int def_before_change; /*공격 받기 전 방어영토의 방어력. printAction의 parameter로 쓰기 위해 선언 */

	if (player == user)
	{
		from = choose_from(player, Att);
		to = choose_to(player, &from);
	}
	else {
		findTarget(ai, &from, &to); 
	}

	land* ATT = land_list[from];
	land* DEF = land_list[to];


	def_before_change = DEF->def; 
	if (DEF->def - ATT->att > 0)
	{
		DEF->def = DEF->def - ATT->att;
		ATT->att = MIN_ATT;
	}
	else   /*DEF <= ATT : 영토 소유권 이전, connection 관계 재확인 */
	{
		if (ATT->att == DEF->def)
			ATT->att = DEFAULT_ATT;
		else
			ATT->att = ATT->att - DEF->def;

		DEF->def = DEFAULT_DEF; /*default 값으로 */

		DEF->owner = player;
		land_owner[to] = player;
		connection_with_capital();

		if (player == user)
		{
			User->total_land++;
			Ai->total_land--;
		}
		else
		{
			User->total_land--;
			Ai->total_land++;
		}
	}
	printAction(player, Att, 0, from, to, def_before_change); 




	return;

}
void ai_attack()
{
	//findTarget(); 
	//attack(ai);

}

void upgrade(int player,int stats, int increment) 
{
		/*Player의 특정 랜드의 공격력(방어력) 혹은 Player의 행동력을 증가시켜주는 함수
		*statts: 공격력인경우 --> land_list[land_num]->att을 증가시킨다. 
		stats: 방어력인경우 --> land_list[land_num]->def을 증가시킨다.
		지역 변수 : land_num: Ai면 User입장에서의 findTarget()으로써 강화할 영토를 정한다. User면 choose_from()함수를 통해 입력받는다.  
		*/ 
	struct player* Player; 
	int land_num;
	int from, to; 
	int value_before_change; 
	/*stats과 increment을 입력받도록 개량*/

	if (stats == cardnum)
	{
		value_before_change = User->card_num;
		if (User->card_num + increment >= MAX_CARD_NUM)
			User->card_num = MAX_CARD_NUM;
		else
			User->card_num += increment;
		printAction(player, Upg, stats, 0, 0, value_before_change);
		return; 

	}
	if (player == user)
	{
		Player = User;
		land_num = choose_from(user, Upg);
	}
	else
	{
		Player = Ai;
		
		findTarget(user, &from, &to); /*User입장에서의 공격의 맥을 찾는다. 해당 영토를 강화한다.*/
		/*to에 해당하는 랜드가 AI의 유효랜드로서 존재하는지 확인*/
		
		land_num = to; 
	}

	/*stats에 따라서 Player의 land의 공격력/방어력 또는 행동력 강화 */
	
	land* target = land_list[land_num]; 
	if (stats == att)
	{
		value_before_change = target->att; 
		if ((target->att + increment) >= MAX_STATS)
			target->att = MAX_STATS;
		else {
			target->att += increment; 
		}
	}
	else if (stats == def)
	{
		value_before_change = target->def ; 
		if ((target->def + increment) >= MAX_STATS)
			target->def = MAX_STATS; 
		else {
			target->def += increment; 
		}
	}
	else    /*stats의 유저의 행동력(card_num)인 경우*/
	{
		value_before_change = Player->card_num; 
		if (Player->card_num + increment >= MAX_CARD_NUM)
			Player->card_num = MAX_CARD_NUM; 
		else
			Player->card_num += increment;
	}

	printAction(player, Upg, stats, land_num, 0, value_before_change); 
}

