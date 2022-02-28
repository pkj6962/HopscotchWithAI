#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"


void user_choice(int* card_list)
{
    /*유저가 자신의 행동력 개수만큼 카드를 뽑는다. 중복 처리, 예외 처리 꼼꼼히*/
    int k = SUGGEST_CARD_NUM;
    int i, j;
    int num;
    int avail_num = User->card_num;
    User->card_num = DEFAULT_CARD_AVAIL;
    int avail = avail_num;  /*최초에 사용가능했던 카드 개수 */
    int* used = (int*)malloc(sizeof(int) * avail_num); /*사용한 카드*/
    int idx_for_used = 0;
    for (i = 0; i < avail_num; i++)
    {
        used[i] = -1;
    }

    for (i = 0; i < avail_num; i++)
    {
        printf("\n카드를 선택해주세요(남은 카드 사용 횟수 : %d): ", avail);
        scanf("%d", &num);
        num--; /*인덱스를 1증가시켜서 제시했기 때문에 1 감소시켜야 한다.*/

        /*card_list에 없는 카드를 선택한 경우 다시*/
        for (j = 0; j < k; j++)
        {
            if (num == card_list[j])
                break;
        }
        if (j == k) /*유저가 선택한 카드가 이안에 없다는 뜻*/
        {
            printf("선택할 수 없는 카드입니다. 다시 선택해주세요.\n"); Sleep(1000);
            i--;
            continue;
        }

        for (j = 0; j < avail; j++)
        {
            if (num == used[j])
            {
                break;
            }
        }
        if (j != avail)  /*유저가 선택한 카드가 사용한 카드에 있다는 뜻*/
        {
            printf("이미 사용한 카드입니다. 다시 선택해주세요. \n"); Sleep(1000);
            i--;
            continue;
        }

        used[idx_for_used++] = num;
        avail--;


        /*선택한 카드에 따라 유저가 공격하거나 업그레이드를 한다. */
        int first, second, first_increment, second_increment;
        first = cardlist[num].basicwork;
        second = cardlist[num].addwork;
        first_increment = cardlist[num].basicpower;
        second_increment = cardlist[num].addpower;

        switch (first) {
        case (atk):         attack(user); break;
        case(upgradeatk):   upgrade(user, att, first_increment); break;
        case(upgradedef):   upgrade(user, def, first_increment); break;
        case(percard):      upgrade(user, cardnum, first_increment); break;
        }
        /*유저가 수도노드를 점령했을 때의 중단 지점. */

        switch (second) {
        case(none):         break;
        case(atk):          attack(user); break;
        case(upgradeatk):   upgrade(user, att, second_increment); break;
        case(upgradedef):   upgrade(user, def, second_increment); break;
        case(percard):      upgrade(user, cardnum, second_increment); break; 
        }
        printf("턴 종료.\n\n"); Sleep(1000); 
    }
    /*여기서 사용자의 카드 사용횟수를 디폴트로 되돌린다? 만약에 유저가 카드 사용횟수를 늘렸으면?
    디폴트로 되돌리지 않으면, 유저의 카드 사용횟수는 영구적으로 증가한 상태로 유지된다. */
}

void ai_choice(void)
{
    /*ai의 알고리즘 
    
    출력: ai가 두뇌를 굴리는 중입니다 
    ai가 최선의 행동을 고민하는 중입니다
    ai가 모든 경우의 수를 분석하는 중입니다 

    ai가 취할 수 있는 경우의 수 
    1. 공격
    2. 공격력 강화  : findTarget을 했는데 from의 공격력보다 to의 방어력이 높을 때
    3. 방어력 강화 
    4. 카드 사용 횟수 증가 --> 얘는 빼자. 
    
    언제? 무엇을? 
    */
    int from, to; 
    int AttOrDef;
    int increment;
    increment = level;

    printf("AI가 계산 중입니다...\n\n"); 
    Sleep(1500); 

    srand(time(NULL)); 
    AttOrDef = rand() % 2; 

    if (AttOrDef)   /*1이면 공격(혹은 공격력 강화)*/
    {
        findTarget(ai, &from, &to); 
        if (land_list[from]->att < land_list[to]->def)
            upgrade(ai, att, increment);
        else
            attack(ai);
    }
    else {      /*0이면 방어력 강화*/
        findTarget(user, &from, &to);
        upgrade(ai, def, increment); 
    }
    printf("턴 종료.\n\n"); Sleep(1500); 




    
}