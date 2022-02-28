#pragma once
void player_initialize();
void map_initialize();
void landAssign(void);
void land_initialize();
void edge_initialize();
void capital_initialize();

void print_basic_info();
void print_map();
void printLink(int idx);
void printAction(int player, int action, int stats, int from, int to, int value_before_change);
void connection_with_capital(void);
void linkLand(int from, int to); /*FROM land의 연결 랜드로 TO land를 포함시킨다.*/

void user_choice(int*);		
void ai_choice(void);		
void attack(int player);
void upgrade(int player, int stats, int increment);

void ai_attack(void);		/*삭제 예정 */
void findTarget(int player, int* from, int* to); /*AI의 최적의 공격루트를 찾는 함수*/

int GameProgress(void);
int WinOrLose(void); 

void dfs(int*, int v);		/*삭제 예정 */
void push(int idx);
int pop(void);
int is_Empty(void);

int* cardShuffle();  /*8장의 카드 중 k개의 카드를 뽑는다. */
void suggestCard(int*); 
void select_card(int*); 

void buy(void); 
void show(card* target);
void setbasiccard(); // 사용자의 기본 덱을 세팅하는 함수 
void printbox(char* str);
void gentreeatk(card** temp);
void gentreeatkplus(card** temp);
void gentreedefplus(card** temp);
void gentreecarduse(card** temp);
card* check(card** target);
