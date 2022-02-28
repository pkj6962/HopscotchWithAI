#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"

int* cardShuffle() /*8장의 카드 중 k개의 카드를 뽑는다. */
{
    int i, j, num, temp;
    int k = SUGGEST_CARD_NUM;
    int* card_list = (int*)malloc(sizeof(int) * k);
    for (i = 0; i < k; i++)
    {
        card_list[i] = -1;
    }

    int idx = 0;
    srand(time(NULL));
    for (i = 0; i < k; i++)
    {
        num = rand() % 8;
        for (j = 0; j < k; j++)
        {
            if (num == card_list[j])
                break;
        }
        if (j != k) /*이미 선택된 카드라는 뜻*/
        {
            i--;
            continue;
        }
        else {
            card_list[idx++] = num;
        }
    }

    /*sort를 진행*/
    for (i = 0; i < k - 1; i++)
    {
        for (j = 0; j < k - 1; j++)
        {
            if (card_list[j] > card_list[j + 1])
            {
                temp = card_list[j + 1];
                card_list[j + 1] = card_list[j];
                card_list[j] = temp;
            }
        }
    }
    return card_list; 
}
void suggestCard(int card_list[])
{
    /*유저에게 k장*/
    int num, i; 
    int k = SUGGEST_CARD_NUM; 
    int first, second; 
    for (i = 0; i < k; i++)
    {
        num = card_list[i]; 
        printf("%d. ", num + 1); 
        first = cardlist[num].basicwork; 
        second = cardlist[num].addwork; 
        
        switch (first) {
        case(atk):          printf("공격 ");     break;
        case(upgradeatk):   printf("공격력 강화 "); break;
        case(upgradedef):   printf("방어력 강화 "); break; 
        case(percard):      printf("카드 사용 횟수 증가 "); break; 
        }
        switch (second) {
        case(none):         printf("\n");  break;
        case(atk):          printf("+ 공격\n");  break; 
        case(upgradeatk):   printf("+ 공격력 강화\n"); break; 
        case(upgradedef):   printf("+ 방어력 강화\n"); break; 
        case(percard):      printf("+ 카드 사용 횟수 증가\n"); break; 
        }
    }
}
