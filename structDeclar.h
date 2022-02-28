#pragma once

typedef enum PLAYER { user = 0, ai } PLAYER;
typedef enum STATS{att = 0, def, cardnum}STATS;
typedef enum ACTION {Att = 0, Upg} ACTION;


typedef struct _tag_land_link
{
	int num; //land 번호
	struct land_link* next;
}land_link;

typedef struct _tag_land {
	char att;
	char def;
	int owner;
	//land* link;
	struct land_link* link;
}land;
typedef struct player {
	int valid_land;		/*credit으로서 유효한 랜드의 개수(수도 랜드와 연결)*/
	int total_land;		/*총 랜드의 개수 */
	int card_num;		/*사용가능한 카드의 개수*/
}player;

typedef enum what { // 어떤 항목을 강화하는지를 나타내는 나열형 변수 
	nothing = 0,
	atk,
	dff,
	cardraw
}what;

typedef struct card {
	struct card* left_node;
	what thing1; // 강화하는 것이 무엇이지 알려주는 변수 1
	what thing2; // 강화하는 것이 무엇이지 알려주는 변수 2
	int plus;
	int price;
	int buy;  // 0이 안산 카드, 1이 산 카드 
	struct card* right_node;
}card;


typedef enum function {
	none = 0,  // addwork를 위한 값.
	atck, // 공격카드 
	upgradeatk, // 공격력 강화 카드 
	upgradedef, // 방어력 강화 카드 
	percard, // 다음턴 카드사용횟수 증가 카드 
}function;

typedef struct basiccard {
	function basicwork;
	function addwork;
	int basicpower;
	int addpower;
}basiccard;

