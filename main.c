#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "nodes.h"
#include "edges.h"
#include "algo.h"
#include "graph.h"

int main()
{
    pnode head = NULL;

    char choice;
    scanf("%c", &choice);
    while (1)
    {
        switch (choice)
        {
        case 'A':
            int nodeAmount = 0;
            scanf("%d", &nodeAmount);
            choice = A_func(&head, nodeAmount);
            break;
        case 'B':

            choice = B_func(&head);
            break;

        case 'D':
            choice = D_func(&head);
            break;
        case 'S':
           
            choice = S_func(&head);
            break;
        case 'T':
           
            choice = T_func(&head);
            break;
        case 'R': //end-case - when we get EOF we go here and delete the graph and free the heap
                //before we end
            delete_all_nodes(&head);

            return 0;
            break;
        default:
        }
    }
    return 0;
}











