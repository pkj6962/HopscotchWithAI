#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"
#include "FunctionList.h"
#include "structDeclar.h"

void buy()
{
	int i, x, y; // x : 강화하고자 하는 카드 선택, y : 강화하고자 하는 트리 선택 
	
	char sen[50];
	if(set==0){
		gentreeatk(&temp[0]);
		gentreeatk(&temp[1]);
		gentreeatkplus(&temp[2]);
		gentreeatkplus(&temp[3]);
		gentreedefplus(&temp[4]);
		gentreedefplus(&temp[5]);
		gentreecarduse(&temp[6]);
		gentreecarduse(&temp[7]);
		set=1; 
	}
	
	while(1){
	start: // goto의 레이블 
	printf("%d %d %d %d %d\n", cardlist[0].basicwork, cardlist[0].basicpower, cardlist[0].addwork, cardlist[0].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[1].basicwork, cardlist[1].basicpower, cardlist[1].addwork, cardlist[1].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[2].basicwork, cardlist[2].basicpower, cardlist[2].addwork, cardlist[2].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[3].basicwork, cardlist[3].basicpower, cardlist[3].addwork, cardlist[3].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[4].basicwork, cardlist[4].basicpower, cardlist[4].addwork, cardlist[4].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[5].basicwork, cardlist[5].basicpower, cardlist[5].addwork, cardlist[5].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[6].basicwork, cardlist[6].basicpower, cardlist[6].addwork, cardlist[6].addpower, money);
	printf("%d %d %d %d %d\n", cardlist[7].basicwork, cardlist[7].basicpower, cardlist[7].addwork, cardlist[7].addpower, money);
	
	for(i=1;i<9;i++){
		if(cardlist[i-1].basicwork==1){
			if(cardlist[i-1].addwork==2){
				sprintf(sen, "             %d : 공격 + 공격력 + %d강화 카드", i, cardlist[i-1].addpower);
				printbox(sen);	
			}
			else if(cardlist[i-1].addwork==3){
				sprintf(sen, "             %d : 공격 + 방어력 + %d강화 카드", i, cardlist[i-1].addpower);
				printbox(sen);	
			}
			else if(cardlist[i-1].addwork==0){
				sprintf(sen, "             %d : 공격 카드", i);
				printbox(sen);	
			}
		}
		
		else if(cardlist[i-1].basicwork==2){
			if(cardlist[i-1].addwork==4){
				sprintf(sen, "     %d : 공격력 +%d강화 + 카드사용횟수 %d 증가 카드", i, cardlist[i-1].basicpower, cardlist[i-1].addpower);
				printbox(sen);	
			}
			else if(cardlist[i-1].addwork==0){
				sprintf(sen, "             %d : 공격력 +%d강화 카드", i, cardlist[i-1].basicpower);
				printbox(sen);	
			}
		}
		
		else if(cardlist[i-1].basicwork==3){
			if(cardlist[i-1].addwork==4){
				sprintf(sen, "     %d : 방어력 +%d강화 + 카드사용횟수 %d 증가 카드", i, cardlist[i-1].basicpower, cardlist[i-1].addpower);
				printbox(sen);	
			}
			else if(cardlist[i-1].addwork==0){
				sprintf(sen, "             %d : 방어력 +%d강화 카드", i, cardlist[i-1].basicpower);
				printbox(sen);	
			}
		}
		
		else if(cardlist[i-1].basicwork==4){
			sprintf(sen, "             %d : 카드사용횟수 %d 증가 카드", i, cardlist[i-1].basicpower);
			printbox(sen);	
		}
	}
	
	printf("\n\n");
	
	printf("강화할 카드의 번호를 입력해 주세요(9 : 종료)\n\n"); 
	scanf("%d", &x);
	if(x==9){
		break;
	}
	else if(temp[x-1]->right_node==NULL&&temp[x-1]->left_node==NULL&&temp[x-1]->buy==1){
			printf("더 이상 가능한 업그레이드가 없습니다\n");
			system("pause");
			system("cls");
			goto start;

	}
	system("cls");
	temp[x-1]=check(&temp[x-1]);
	show(temp[x-1]);
	
		if(x==1||x==2){
			printf("\n\n");
		    printf("구매하고 싶은 카드의 번호를 입력해주세요\n\n");
			scanf("%d", &y);
			if(temp[x-1]->right_node!=NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						money=money-temp[x-1]->price;
						cardlist[x-1].addwork=2;
						cardlist[x-1].addpower=temp[x-1]->plus;
						temp[x-1]->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else if(y==2){
					if(money>(temp[x-1]->right_node->price)){
						money=money-temp[x-1]->price;
						cardlist[x-1].addwork=3;
						cardlist[x-1].addpower=temp[x-1]->right_node->plus;
						temp[x-1]->right_node->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");
				}
			}
			
			else if(temp[x-1]->right_node==NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						if(temp[x-1]->thing1==1){
							money=money-temp[x-1]->price;
							cardlist[x-1].addwork=2;
							cardlist[x-1].addpower=temp[x-1]->plus;
							temp[x-1]->buy=1;
							system("cls");
							printf("구매되었습니다!\n");
							system("pause"); 
						}
						else if(temp[x-1]->thing1==2){
							money=money-temp[x-1]->price;
							cardlist[x-1].addwork=3;
							cardlist[x-1].addpower=temp[x-1]->plus;
							temp[x-1]->buy=1;
							system("cls");
							printf("구매되었습니다!\n");
							system("pause"); 
						}
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");	
				}
			}
		}
		
		if(x==3||x==4){
			printf("\n\n");
		    printf("구매하고 싶은 카드의 번호를 입력해주세요\n\n");
			scanf("%d", &y);
			if(temp[x-1]->right_node!=NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						money=money-temp[x-1]->price;
						cardlist[x-1].addwork=0;
						cardlist[x-1].basicpower=temp[x-1]->plus;
						temp[x-1]->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else if(y==2){
					if(money>(temp[x-1]->right_node->price)){
						money=money-temp[x-1]->price;
						cardlist[x-1].addwork=4;
						cardlist[x-1].addpower=1;
						cardlist[x-1].basicpower=temp[x-1]->plus;
						temp[x-1]->right_node->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");
				}
			}
			
			else if(temp[x-1]->right_node==NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						if(temp[x-1]->thing2==3){
							money=money-temp[x-1]->price;
							cardlist[x-1].basicpower=temp[x-1]->plus;
							temp[x-1]->buy=1;
							system("cls");
							printf("구매되었습니다!\n");
							system("pause"); 
						}
						else if(temp[x-1]->thing2==0){
							money=money-temp[x-1]->price;
							cardlist[x-1].basicpower=temp[x-1]->plus;
							temp[x-1]->buy=1;
							system("cls");
							printf("구매되었습니다!\n");
							system("pause"); 
						}
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");	
				}
			}
		}
		
		if(x==5||x==6){
			printf("\n\n");
		    printf("구매하고 싶은 카드의 번호를 입력해주세요\n\n");
			scanf("%d", &y);
			if(temp[x-1]->right_node!=NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						money=money-temp[x-1]->price;
						cardlist[x-1].addwork=0;
						cardlist[x-1].basicpower=temp[x-1]->plus;
						temp[x-1]->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else if(y==2){
					if(money>(temp[x-1]->right_node->price)){
						money=money-temp[x-1]->price;
						cardlist[x-1].addwork=4;
						cardlist[x-1].addpower=1;
						cardlist[x-1].basicpower=temp[x-1]->plus;
						temp[x-1]->right_node->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");
				}
			}
			
			else if(temp[x-1]->right_node==NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						if(temp[x-1]->thing2==3){
							money=money-temp[x-1]->price;
							cardlist[x-1].basicpower=temp[x-1]->plus;
							temp[x-1]->buy=1;
							system("cls");
							printf("구매되었습니다!\n");
							system("pause"); 
						}
						else if(temp[x-1]->thing2==0){
							money=money-temp[x-1]->price;
							cardlist[x-1].basicpower=temp[x-1]->plus;
							temp[x-1]->buy=1;
							system("cls");
							printf("구매되었습니다!\n");
							system("pause"); 
						}
					}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");	
				}
			}
		}
		
		if(x==7||x==8){
			printf("\n\n");
		    printf("구매하고 싶은 카드의 번호를 입력해주세요\n\n");
			scanf("%d", &y);
			if(temp[x-1]->right_node==NULL){
				if(y==1){
					if(money>temp[x-1]->price){
						money=money-temp[x-1]->price;
						cardlist[x-1].basicpower=temp[x-1]->plus;
						temp[x-1]->buy=1;
						system("cls");
						printf("구매되었습니다!\n");
						system("pause"); 
						}
					else if(money<temp[x-1]->price){
						system("cls");
						printf("금액이 부족합니다\n"); 
						system("pause");
					}
				}
				else{
					system("cls");
					printf("잘못된 선택입니다\n");
					system("pause");	
				}
			}
		}
		
		system("cls");
		
	}
	return 0;
}
card *check(card **target){
	if( (*target)->right_node==NULL && (*target)->left_node==NULL ){
		return *target;
	}
	if( (*target)->right_node==NULL){
		if((*target)->buy==0){
			return *target;
		}
		else if( (*target)->buy==1 ){
			check( &( (*target)->left_node) );
		}
	}
	else if( (*target)->right_node!=NULL ){
		if( (*target)->buy==0&&(*target)->right_node->buy==0 ){
			return *target;
		}
		else if( (*target)->buy==1 ){
			check( &((*target)->left_node) );
		}
		else if( (*target)->right_node->buy==1 ){
			check( &((*target)->right_node) );
		}
	}
}
void setbasiccard(){
	cardlist[0].basicwork=1;
	cardlist[0].addwork=0;
	cardlist[0].basicpower=1;
	cardlist[0].addpower=0;
		
	cardlist[1].basicwork=1;
	cardlist[1].addwork=0;
	cardlist[1].basicpower=1;
	cardlist[1].addpower=0;
	
	cardlist[2].basicwork=2;
	cardlist[2].addwork=0;
	cardlist[2].basicpower=1;
	cardlist[2].addpower=0;
	
	cardlist[3].basicwork=2;
	cardlist[3].addwork=0;
	cardlist[3].basicpower=1;
	cardlist[3].addpower=0;
	
	cardlist[4].basicwork=3;
	cardlist[4].addwork=0;
	cardlist[4].basicpower=1;
	cardlist[4].addpower=0;
	
	cardlist[5].basicwork=3;
	cardlist[5].addwork=0;
	cardlist[5].basicpower=1;
	cardlist[5].addpower=0;
	
	cardlist[6].basicwork=4;
	cardlist[6].addwork=0;
	cardlist[6].basicpower=1;
	cardlist[6].addpower=0;
	
	cardlist[7].basicwork=4;
	cardlist[7].addwork=0;
	cardlist[7].basicpower=1;
	cardlist[7].addpower=0;
}
void show(card *target){
	char sentence[50];
	int i=1;
	if(target->right_node!=NULL){
		if(target->buy==0&&target->right_node->buy==0){
			if(target->thing1==1&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "공격력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
				target=target->right_node;
			}
			else if(target->thing1==2&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "방어력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
				target=target->right_node;
			}
			else if(target->thing1==3&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "카드사용횟수", target->plus, target->price);
				printbox(sentence);
				i=i+1;
				target=target->right_node;
			}
			else if(target->thing1==1&&target->thing2==3){
				sprintf(sentence, "   %d :  카드사용횟수 +1 및 %s +%d     가격 : %d ", i,"공격력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
				target=target->right_node;
			}
			else if(target->thing1==2&&target->thing2==3){
				sprintf(sentence, "   %d :  카드사용횟수 +1 및 %s +%d     가격 : %d ", i, "방어력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
				target=target->right_node;
			}

			if(target->thing1==1&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "공격력", target->plus, target->price);
				printbox(sentence);
			}
			else if(target->thing1==2&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "방어력", target->plus, target->price);
				printbox(sentence);
			}
			else if(target->thing1==3&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "카드사용횟수", target->plus, target->price);
				printbox(sentence);
			}
			else if(target->thing1==1&&target->thing2==3){
				sprintf(sentence, "   %d :  카드사용횟수 + 1 및 %s  +%d     가격 : %d ", i, "공격력", target->plus, target->price);
				printbox(sentence);
			}
			else if(target->thing1==2&&target->thing2==3){
				sprintf(sentence, "   %d :  카드사용횟수 +1 및 %s +%d     가격 : %d ", i, "방어력", target->plus, target->price);
				printbox(sentence);
			}
		}
	}
	
	else if(target->right_node==NULL){
		if(target->buy==0){
			if(target->thing1==1&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "공격력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
			}
			else if(target->thing1==2&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "방어력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
			}
			else if(target->thing1==3&&target->thing2==0){
				sprintf(sentence, "       %d :  %s +%d     가격 : %d ", i, "카드사용횟수", target->plus, target->price);
				printbox(sentence);
				i=i+1;
			}
			else if(target->thing1==1&&target->thing2==3){
				sprintf(sentence, "   %d :  카드사용횟수 1 증가 및 %s +%d     가격 : %d ", i, "공격력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
			}
			else if(target->thing1==2&&target->thing2==3){
				sprintf(sentence, "   %d :  카드사용횟수 +1 및 %s +%d     가격 : %d ", i, "방어력", target->plus, target->price);
				printbox(sentence);
				i=i+1;
			}	
		}
	}
	
}
void printbox(char *str){
	int i;
	printf("┌");
	for(i=0;i<60;i++){
		printf("─");
	}
	printf("┐\n");
	printf("│%58s  │\n"," ");
	printf("│%-*s│\n", 60, str);
	printf("│%58s  │\n"," ");
	printf("└");
	for(i=0;i<60;i++){
		printf("─");
	}
	printf("┘\n");
	
}
void gentreeatk(card **temp){
	card *card1, *card2, *card3, *card4, *card5, *card6;
	card1=(card *)malloc(sizeof(card));
	card2=(card *)malloc(sizeof(card));
	card3=(card *)malloc(sizeof(card));
	card4=(card *)malloc(sizeof(card));
	card5=(card *)malloc(sizeof(card));
	card6=(card *)malloc(sizeof(card));
	card1->right_node=card2; card1->left_node=card3;
	card2->left_node=card4;	card2->right_node=NULL;
	card4->left_node=card6; card4->right_node=NULL;
	card3->right_node=NULL;	card3->left_node=card5;
	card5->left_node=NULL; card5->right_node=NULL;
	card6->right_node=NULL; card6->left_node=NULL;
	card1->buy=0; card1->plus=1; card1->price=5; card1->thing1=1; card1->thing2=0;
	card2->buy=0; card2->plus=1; card2->price=5; card2->thing1=2; card2->thing2=0;
	card3->buy=0; card3->plus=2; card3->price=14; card3->thing1=1; card3->thing2=0;
	card4->buy=0; card4->plus=2; card4->price=14; card4->thing1=2; card4->thing2=0;
	card5->buy=0; card5->plus=3; card5->price=27; card5->thing1=1; card5->thing2=0;
	card6->buy=0; card6->plus=3; card6->price=27; card6->thing1=2; card6->thing2=0;
	*temp=card1;
}
void gentreeatkplus(card **temp){
	card *card1, *card2, *card3, *card4, *card5, *card6;
	card1=(card *)malloc(sizeof(card));
	card2=(card *)malloc(sizeof(card));
	card3=(card *)malloc(sizeof(card));
	card4=(card *)malloc(sizeof(card));
	card5=(card *)malloc(sizeof(card));
	card6=(card *)malloc(sizeof(card));

	card1->left_node=card3; card1->right_node=card2;
	card2->left_node=card4; card2->right_node=NULL;
	card3->left_node=card5; card3->right_node=NULL;
	card4->left_node=card6; card4->right_node=NULL;
	card5->left_node=NULL; card5->right_node=NULL;
	card6->left_node=NULL; card6->right_node=NULL;
	card1->buy=0; card1->plus=5; card1->price=5; card1->thing1=1; card1->thing2=0;
	card2->buy=0; card2->plus=2; card2->price=5; card2->thing1=1; card2->thing2=3;
	card3->buy=0; card3->plus=7; card3->price=14; card3->thing1=1; card3->thing2=0;
	card4->buy=0; card4->plus=4; card4->price=14; card4->thing1=1; card4->thing2=3;
	card5->buy=0; card5->plus=9; card5->price=27; card5->thing1=1; card5->thing2=0;
	card6->buy=0; card6->plus=6; card6->price=27; card6->thing1=1; card6->thing2=3;
	*temp=card1;
}
void gentreedefplus(card **temp){
	card *card1, *card2, *card3, *card4, *card5, *card6;
	card1=(card *)malloc(sizeof(card));
	card2=(card *)malloc(sizeof(card));
	card3=(card *)malloc(sizeof(card));
	card4=(card *)malloc(sizeof(card));
	card5=(card *)malloc(sizeof(card));
	card6=(card *)malloc(sizeof(card));

	card1->left_node=card3; card1->right_node=card2;
	card2->left_node=card4; card2->right_node=NULL;
	card3->left_node=card5; card3->right_node=NULL;
	card4->left_node=card6; card4->right_node=NULL;
	card5->left_node=NULL; card5->right_node=NULL;
	card6->left_node=NULL; card6->right_node=NULL;
	card1->buy=0; card1->plus=5; card1->price=5; card1->thing1=2; card1->thing2=0;
	card2->buy=0; card2->plus=2; card2->price=5; card2->thing1=2; card2->thing2=3;
	card3->buy=0; card3->plus=7; card3->price=14; card3->thing1=2; card3->thing2=0;
	card4->buy=0; card4->plus=4; card4->price=14; card4->thing1=2; card4->thing2=3;
	card5->buy=0; card5->plus=9; card5->price=27; card5->thing1=2; card5->thing2=0;
	card6->buy=0; card6->plus=6; card6->price=27; card6->thing1=2; card6->thing2=3;
	*temp=card1;
}
void gentreecarduse(card **temp){
	card *card1, *card2, *card3;
	card1=(card *)malloc(sizeof(card));
	card2=(card *)malloc(sizeof(card));
	card3=(card *)malloc(sizeof(card));
	
	card1->left_node=card2; card1->right_node=NULL;
	card2->left_node=card3; card2->right_node=NULL;
	card3->left_node=NULL; card3->right_node=NULL;
	card1->buy=0; card1->plus=1; card1->price=5; card1->thing1=3; card1->thing2=0;
	card2->buy=0; card2->plus=2; card2->price=10; card2->thing1=3; card2->thing2=0;
	card3->buy=0; card3->plus=3; card3->price=15; card3->thing1=3; card3->thing2=0;
	*temp=card1;
}
