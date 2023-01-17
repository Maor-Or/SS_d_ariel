#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "nodes.h"
#include "edges.h"
#include "algo.h"

int sumOfDijkstra;
int minimunOfPaths = INT_MAX;

char A_func(node **p_head, int nodeAmount)
{
    int EOF_Check;
    int currNodeNum = 0;
    pnode temp = NULL;

    if (*(p_head) != NULL)
    {
        // make a func - free_entire_graph
        delete_all_nodes(p_head);
    }

    if (nodeAmount > 0)
    {
        (*p_head) = makeNode();
        (*p_head)->node_num = 0;
        temp = *p_head;
    }

    for (int i = 1; i < nodeAmount; i++)
    {
        temp->next = makeNode();

        temp->next->node_num = i;
        temp = temp->next;
    }
    temp->next = NULL;

    int nextNumber = 0;
    int destNodeNum = 0;
    int edgeWeight = 0;
    char mode = 'A';

    // we expect to receive 'n'
    if (scanf("%d", &nextNumber) == 0)
    {
        scanf("%c", &mode);
    }

    int flag = 0;

    while (flag == 0)
    {
        if (mode == 'n')
        {
            scanf("%d", &currNodeNum);

            temp = findNode(*p_head, currNodeNum);
            if (temp == NULL) // if the searched node doesnt exist yet
            {
                // invalid input!!!!
                printf("no such node exist yet");
                exit(1);
            }
            EOF_Check = scanf("%d", &destNodeNum);

            // if we get EOF we send 'R' for program ending state,
            if (EOF_Check != EOF)
            {
                if (EOF_Check == 0)
                {
                    scanf("%c", &mode);
                    return mode;
                }
            }
            else if (EOF_Check == EOF)
            {
                // if EOF reached we return R
                return 'R';
            }
            scanf("%d", &edgeWeight);
            pnode destNode = findNode(*p_head, destNodeNum);
            addToEdges(temp, edgeWeight, destNode);

            EOF_Check = scanf("%d", &nextNumber);
            if (EOF_Check != EOF)
            {
                if (EOF_Check == 0)
                {
                    scanf("%c", &mode);
                    if (mode != 'n')
                    {
                        return mode;
                    }
                }
                else
                {
                    destNodeNum = nextNumber;
                    mode = 'M';
                }
            }
            else
            {
                // if EOF reached we return R
                return 'R';
            }
        }
        if (mode == 'M')
        {
            scanf("%d", &edgeWeight);
            pnode destNode = findNode(*(p_head), destNodeNum);
            addToEdges(temp, edgeWeight, destNode);

            EOF_Check = scanf("%d", &nextNumber);
            if (EOF_Check != EOF)
            {
                if (EOF_Check == 0)
                {
                    scanf("%c", &mode);
                    if (mode != 'n')
                    {
                        return mode;
                    }
                }
                else
                {
                    destNodeNum = nextNumber;
                    mode = 'M';
                }
            }
            else
            {
                // if EOF reached we return R
                return 'R';
            }
        }
    }
    return 'R';
}

char B_func(node **p_head)
{
    int nodeNum;
    scanf("%d", &(nodeNum));
    pnode temp = NULL;
    temp = *p_head;
    pnode nodeCheck = findNode(temp, nodeNum);
    if (nodeCheck != NULL) // if the node already exist,
                           // first we delete all it's edges and then keep going
    {
        deleteAllEdges(nodeCheck);
        temp = nodeCheck;
    }
    else
    { // if the node doesnt exist, we first create it
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = makeNode();
        temp->next->node_num = nodeNum;
        temp = temp->next;
    }

    // nextNumber is for the case we cought a number and not a new char,
    // we need to save that number and update the destNodeNum for the next pair of input numbers
    int edgeWeight, destNodeNum, nextNumber;
    char mode;
    scanf("%d", &destNodeNum);
    scanf("%d", &edgeWeight);
    pnode destNode = findNode(*p_head, destNodeNum);
    addToEdges(temp, edgeWeight, destNode);

    int EOF_Check = scanf("%d", &nextNumber);
    if (EOF_Check != EOF)
    {
        if (EOF_Check == 0)
        {
            scanf("%c", &mode);
            return mode;
        }
        else
        {
            destNodeNum = nextNumber;
            mode = 'M';
        }
    }
    else
    {
        // if EOF reached we return R
        return 'R';
    }

    while (mode == 'M')
    {
        scanf("%d", &edgeWeight);
        pnode destNode = findNode(*(p_head), destNodeNum);
        addToEdges(temp, edgeWeight, destNode);

        int EOF_Check = scanf("%d", &nextNumber);
        if (EOF_Check != EOF)
        {
            if (EOF_Check == 0)
            {
                scanf("%c", &mode);
                return mode;
            }
            else
            {
                destNodeNum = nextNumber;
                mode = 'M';
            }
        }
        else
        {
            // if EOF reached we return R
            return 'R';
        }
    }

    return 'R';
}

char D_func(node **p_head)
{
    pnode temp = *p_head;
    int nodeToDelete;
    scanf("%d", &nodeToDelete);

    while (temp->next != NULL)
    {
        delete_all_edges_to_n(temp, nodeToDelete);
        temp = temp->next;
    }
    delete_all_edges_to_n(temp, nodeToDelete);
    temp = findNode((*p_head), nodeToDelete);
    deleteAllEdges(temp);
    deleteNode(p_head, nodeToDelete);

    // if we get EOF we send 'R' for program ending state,
    int nextNumber = 0;
    char mode;
    int EOF_Check = scanf("%d", &nextNumber);
    if (EOF_Check != EOF)
    {
        if (EOF_Check == 0)
        {
            scanf("%c", &mode);
            return mode;
        }
    }
    else
    {
        // if EOF reached we return R
        return 'R';
    }
    return 'R';
}

void checkMemError(void *p)
{
    if (p == NULL)
    {
        perror("error allocating memory");
        exit(1);
    }
}

char S_func(node **p_head)
{
    pnode_pointer QH = makeQueue(p_head);
    node_pointer **p_QH = &QH;
    pnode temp_head = (*p_head);
    int srcNodeNum, destNodeNum;
    scanf("%d", &srcNodeNum);
    scanf("%d", &destNodeNum);

    pnode srcNode = findNode(temp_head, srcNodeNum);
    srcNode->distance = 0;  // initializing the srcNode to have d[s]=0
    while ((*p_QH) != NULL) // going through all the nodes in the queue
    {

        pnode u = ExtractMin(p_QH);
        pedge temp_edge = u->edges;
        if (temp_edge == NULL)
        {
            break;
        }
        while (temp_edge->next != NULL)
        {
            // relax-start
            if (temp_edge->endpoint->distance > (u->distance + temp_edge->weight))
            {
                temp_edge->endpoint->distance = (u->distance + temp_edge->weight);
            }
            // relax-end
            temp_edge = temp_edge->next;
        }
        // relax-start
        if (temp_edge->endpoint->distance > (u->distance + temp_edge->weight))
        {
            temp_edge->endpoint->distance = (u->distance + temp_edge->weight);
        }
        // relax-end
    }

    // cleaning heap memory
    pnode_pointer temp = QH, freeNode;
    while (temp != NULL)
    {
        freeNode = temp;
        temp = temp->next;
        free(freeNode);
    }
    free(temp);

    pnode destNode = findNode(temp_head, destNodeNum);
    if (destNode->distance < INT_MAX)
    {
        printf("Dijsktra shortest path: %d \n", destNode->distance);
    }
    else
    {
        printf("Dijsktra shortest path: -1 \n");
    }

    // if we get EOF we send 'R' for program ending state,
    int nextNumber = 0;
    char mode;
    int EOF_Check = scanf("%d", &nextNumber);
    if (EOF_Check != EOF)
    {
        if (EOF_Check == 0)
        {
            scanf("%c", &mode);
            return mode;
        }
    }
    else
    {
        // if EOF reached we return R
        return 'R';
    }
    return 'R';
}

void T_Combinations(node **p_head, int *arr, int start, int end)
{
    if (start == end)
    {
        // calculate the permutation
        sumOfDijkstra = 0;
        int flag = 0;
        for (int i = 0; i < end; i++)
        {
            int currDijkstra = T_Dijkstra_func(p_head, arr[i], arr[i + 1]);
            if (currDijkstra == -1)
            {
                sumOfDijkstra = INT_MAX;
                flag = 1;
                break;
            }

            sumOfDijkstra += currDijkstra;
        }
        if (sumOfDijkstra < minimunOfPaths && flag == 0)
        {
            minimunOfPaths = sumOfDijkstra;
        }
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            // swap the current element with the start element
            int temp = arr[start];
            arr[start] = arr[i];
            arr[i] = temp;

            // recursively permute the remaining elements
            T_Combinations(p_head, arr, start + 1, end);

            // swap the elements back to their original positions
            arr[i] = arr[start];
            arr[start] = temp;
        }
    }
}

char T_func(node **head)
{
    minimunOfPaths = INT_MAX;
    int amountOfNums;
    scanf("%d", &amountOfNums);
    int *arr = (int *)malloc(amountOfNums * sizeof(int));
    checkMemError(arr);
    for (int i = 0; i < amountOfNums; i++)
    {
        scanf("%d", &arr[i]);
    }
    T_Combinations(head, arr, 0, amountOfNums - 1);
    if (minimunOfPaths == INT_MAX)
    {
        printf("TSP shortest path: -1 \n");
    }
    else
    {
        printf("TSP shortest path: %d \n", minimunOfPaths);
    }

    free(arr);
    // if we get EOF we send 'R' for program ending state,
    int nextNumber = 0;
    char mode;
    int EOF_Check = scanf("%d", &nextNumber);
    if (EOF_Check != EOF)
    {
        if (EOF_Check == 0)
        {
            scanf("%c", &mode);
            return mode;
        }
    }
    else
    {
        // if EOF reached we return R
        return 'R';
    }
    return 'R';
}

int T_Dijkstra_func(node **p_head, int srcNodeNum, int destNodeNum)
{
    pnode_pointer QH = makeQueue(p_head);
    node_pointer **p_QH = &QH;
    pnode temp_head = (*p_head);

    pnode srcNode = findNode(temp_head, srcNodeNum);
    srcNode->distance = 0;  // initializing the srcNode to have d[s]=0
    while ((*p_QH) != NULL) // going through all the nodes in the queue
    {

        pnode u = ExtractMin(p_QH);
        pedge temp_edge = u->edges;
        if (temp_edge == NULL)
        {
            break;
        }
        while (temp_edge->next != NULL)
        {
            // relax-start
            if (temp_edge->endpoint->distance > (u->distance + temp_edge->weight))
            {
                temp_edge->endpoint->distance = (u->distance + temp_edge->weight);
            }
            // relax-end
            temp_edge = temp_edge->next;
        }
        // relax-start
        if (temp_edge->endpoint->distance > (u->distance + temp_edge->weight))
        {
            temp_edge->endpoint->distance = (u->distance + temp_edge->weight);
        }
        // relax-end
    }

    // cleaning heap memory
    pnode_pointer temp = QH, freeNode;
    while (temp != NULL)
    {
        freeNode = temp;
        temp = temp->next;
        free(freeNode);
    }
    free(temp);

    pnode destNode = findNode(temp_head, destNodeNum);
    if (destNode->distance < INT_MAX)
    {
        return destNode->distance;
    }
    else
    {
        return -1;
    }
}
