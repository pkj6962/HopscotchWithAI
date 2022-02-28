
//#include <stdio.h>
//#define LAND_NUM 35
/*
typedef  player user, ai;

typedef struct player {
	int attck;
	int land_num; 
	land current;
};
land land_list[LAND_NUM];

void attack_land(player user, land land);
void land_initialize();
*/

/*land들의 hp를 모두 0으로 초기화, 영토들의 소유를 반으로 가릑 */
/*
void land_initialize()
{
	int i;
	for (i = 0; i < LAND_NUM; i++)
	{	
		land_list[i].hp = 0;
	}
	/*최초의 세팅에 따라 유저와 ai의 영토 소유를 initialize하자
}*/





//void attack_land(player user, land land) /*플레이어가 땅을 공격한다. 일정한 계산에 따라 소유권을 빼앗는다*/
//{
//	if (land.owner == user)
//	{
//		printf("자신의 땅을 대상으로 공격할 수 없습니다.\n");
//		return;
//	}



//}
//void upgrade_land(); /*플레이어가 땅을 업그레이드한다.*/ /*영토의 소유권을 가진 사람만 할 수 있어야 함*/
