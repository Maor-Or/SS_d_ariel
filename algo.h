#include "graph.h"

char A_func(node **head, int nodeAmount);
char B_func(node **head);
char D_func(node **head);
char S_func(node **head);
char T_func(node **head);
void checkMemError(void *p);
int T_Dijkstra_func(node **p_head, int srcNodeNum, int destNodeNum); // for command T
void T_Combinations(node **p_head, int *arr, int start, int end);
