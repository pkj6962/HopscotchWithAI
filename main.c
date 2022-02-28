#pragma once
#include "MacroNHeader.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"

int main(void)
{
	int output;
	int end=1;
	int n;
	setbasiccard();




	while(end){
		system("cls");
		printf("어떤 행동을 할 지 선택해주세요\n");
		printf("1 : 전투    2 : 상점이용   3 : 게임끄기 => ");
		scanf(" %d", &n);
		switch(n)
		{ 
		case(1):system("cls");
				output = GameProgress(); 
				break; 
		case(2): system("cls");
				 buy();
				 break;
		case(3): end = 0;  break;
		default: 	
				printf("\n잘못된 입력입니다. 다시 선택해 주세요. 선택은 1~4만 가능합니다\n");
				system("pause");
				break;
		}
		printf("Bye!\n"); 
	}
	return 0;
}










