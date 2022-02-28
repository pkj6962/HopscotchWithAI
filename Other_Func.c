#pragma once 
#include "MacroNHeader.h"
#include "structDeclar.h"
#include "GlobalVar.h"


void push(int idx)
{
	land_link* temp = (land_link*)malloc(sizeof(land_link));
	temp->num = idx;
	temp->next = NULL;

	if (!stack_pointer)
		stack_pointer = temp;
	else
	{
		temp->next = stack_pointer;
		stack_pointer = temp;
	}
	return;
}
int pop(void)
{
	if (!stack_pointer)
	{
		printf("Stack is Empty.\n");
		exit(1);
	}
	land_link* temp;
	int temp_num;
	temp = stack_pointer;
	temp_num = temp->num;
	stack_pointer = temp->next;
	free(temp);

	return temp_num;
}
int is_Empty(void)
{
	if (!stack_pointer)
		return 1;
	else
		return 0;
}

void dfs(int* visited, int v)
{
	int i;

	land_link* w;

	printf("%5d", v);
	visited[v] = 1;
	for (w = land_list[v]->link; w; w = w->next)
		if (!visited[w->num])
			dfs(visited, w->num);
	return;
}
void bfs(int* visited, int v)
{

}