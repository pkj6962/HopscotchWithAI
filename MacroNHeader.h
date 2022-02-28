#pragma once
#define MAX_TURNS 100
#define MAX 50
#define MAP_ROW 33
#define MAP_COL 110

#define NODE_ROW 4
#define NODE_COL 6 

#define LINE_NUM 3		/*랜드를 연결하는 가로 엣지의 선('-')의 숫자*/
#define EDGE_NUM 30		/* 땅의 엣지(테두리 윤곽선) 숫자*/
#define NODE_NUM 24+1		//24개. 인덱스를 1부터 시작하므로 plus 1
#define EDGE_COL_NUM 18 + 1		/*종간에 연결된 랜드를 연결하는 엣지의 개수*/
#define NUM 20

#define DEFAULT_ATT 5
#define MIN_ATT 1		/*자기 공격력을 모두 소진했을 때 최소 공격력*/
#define DEFAULT_DEF 10

#define DEFAULT_AI_INCREMENT 5 /*Ai의 업그레이드 시 default 증가분  */

#define DEFAULT_CARD_AVAIL 1	/*플레이어가 사용가능한 기본 카드 개수 */
#define MAX_STATS 35	/*stat(공격력과 방어력)의 최댓값 */


#define MAX_CARD_NUM 6
#define GAME_TURN_NUM 3
#define SUGGEST_CARD_NUM 6	/*유저에게 제시되는 카드의 개수*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>