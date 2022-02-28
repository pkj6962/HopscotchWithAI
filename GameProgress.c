#pragma once
#include "MacroNHeader.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"

int GameProgress()
{
	/*게임을 시작해서 유저에게 승패 판정을 내리는 함수.
	이기면 1을, 지면 0, 무승부이면 -1을  반환한다.*/
	/*판수는 Default Value로 정한 값. 일단 20판으로 한다.
	20판을 다 돌거나, 플레이어가 상대방의 수도를 점령하면 게임이 끝난다.
	턴을 다 돌았을 때 최종 유효랜드의 개수에 따라 승, 패가 결정된다.
	유효랜드의 수가 동일하면 총 랜드의 수를 비교하여 결정한다.
	총 랜드의 수도 모두 같으면 무승부 처리된다.*/
	//int remaining_turns = GAME_TURN_NUM;
	int* card_list; 
	printf("게임을 시작합니다.\n");

	do {
		printf("난이도를 입력하세요(1-10)\n");
		scanf("%d", &level);
		if (!(level >= 1 && level <= 10))
			printf("잘못된 입력입니다. 다시 입력해주세요.\n");
		else
			break; 
	} while (1); 
	

	printf("영토를 할당하는 중입니다.\n");
	Sleep(2000);
	printf("중립지대를 설정하는 중입니다...");
	Sleep(2000);


	player_initialize();
	land_initialize();
	edge_initialize();
	map_initialize();
	capital_initialize();
	connection_with_capital();

	while (remaining_turns > 0)	/*서로의 수도노드를 서로가 가지고 있는 동안*/
	{
		print_basic_info();
		print_map();

		card_list = cardShuffle();
		setbasiccard();
		suggestCard(card_list);
		user_choice(card_list);
		if (land_owner[24] == user)
			return 1;
		ai_choice();
		if (land_owner[1] == ai)
			return 0;
		remaining_turns--;

		system("pause"); 
	}	
	return WinOrLose(); 
}
/*게임의 승패를 가려주는 함수*/
int WinOrLose(void)
{
	printf("게임이 끝났습니다. 승패를 결정합니다.\n");
	printf("유효 랜드의 수: User	%2d : %2d	Ai\n", User->valid_land, Ai->valid_land);
	printf("  총 랜드의 수: User	%2d : %2d	Ai\n", User->total_land, Ai->total_land);
	Sleep(2000);
	if (User->valid_land > Ai->valid_land) {
		printf("유저가 승리하였습니다!");
		return 1;
	}
	else if (User->valid_land < Ai->valid_land) {
		printf("AI가 승리하였습니다!");
		return 0;
	}
	else if (User->total_land > Ai->total_land) {
		printf("User가 승리하였습니다!\n");
			return 1;
	}
	else if (User->total_land < Ai->total_land) {
		printf("AI가 승리하였습니다!\n");
		return 0;
	}
	else {
		printf("무승부 처리되었습니다.");
		return -1;
	}
	system("pause");
	}
	