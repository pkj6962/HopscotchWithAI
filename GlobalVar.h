#pragma once
#include "MacroNHeader.h"
#include "structDeclar.h"

extern char map[][MAP_COL]; 
extern int* NODE[];
extern int* EDGE_ROW[];
extern int  EDGE_COL[]; 
extern int Att_index[]; 
extern int newtral_index[]; 
extern land* land_list[]; 
extern int land_owner[];
extern int newtral_land[];
extern int capital[];
extern int capital_of_player[];
extern int remaining_turns; 

extern land_link* stack_pointer; 
extern land_link* validLand[2]; 
extern int stack[];
extern int top;
extern char* ptr;

extern char USER[];
extern char AI[];
extern char* PlayerList[];

extern char ATT_POWER[];
extern char DEF_POWER[];
extern char CARD_AVAIL[]; 
extern char* StatsList[]; 

extern player* User; 
extern player* Ai; 

extern int level;

extern struct basiccard cardlist[8];
extern int money;
extern int set; 
extern card* temp[]; 





