#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "nodes.h"
#include "edges.h"
#include "algo.h"
#include "graph.h"

void delete_all_nodes(node **p_head)
{
    pnode temp = *p_head, freeNode = NULL;
    while (temp->next != NULL)
    {
        deleteAllEdges(temp);
        freeNode = temp;
        temp = temp->next;
        free(freeNode);
    }
    deleteAllEdges(temp);
    freeNode = temp;
    free(freeNode);
    *p_head = NULL;
}

void deleteNode(node **p_head, int nodeToDelete)
{
    pnode temp = *p_head, prev = NULL, freeNode = NULL;
    if (temp == NULL)
    {
        return;
    }
    while (temp->next != NULL)
    {
        if (temp == *p_head)
        {
            if (temp->node_num == nodeToDelete)
            {
                freeNode = temp;
                *p_head = temp->next;
                free(freeNode);
                return;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
        else
        {
            if (temp->node_num == nodeToDelete)
            {
                freeNode = temp;
                prev->next = temp->next;
                free(freeNode);
                return;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }
    if (temp->node_num == nodeToDelete)
    {
        if (prev == NULL)
        {
            *p_head = NULL;
        }
        else
        {
            prev->next = NULL;
        }
        free(temp);
        return;
    }
}

void printGraph(pnode head)
{
    pnode temp = head;
    pedge t_edge = NULL;
    if (temp == NULL)
    {
        printf("empty graph\n");
    }
    printf("\nPrinting graph\n");

    while (temp != NULL)
    {
        printf("currently in node %d\n", temp->node_num);
        if (temp->edges != NULL)
        {
            printf("current node edge list: \n");
            t_edge = temp->edges;
            while (t_edge->next != NULL)
            {
                printf("current edge dest:%d and weight:%d \n", t_edge->endpoint->node_num, t_edge->weight);
                t_edge = t_edge->next;
            }
            printf("current edge dest:%d and weight:%d \n", t_edge->endpoint->node_num, t_edge->weight);
        }
        temp = temp->next;
    }
}

void printNodes(pnode head)
{
    pnode temp = head;
    if (temp == NULL)
    {
        printf("empty graph\n");
    }
    while (temp->next != NULL)
    {
        printf("current node: %d\n", temp->node_num);
        if (temp->node_num == 0)
        {
            printf("first node's first edge: %d\n", temp->edges->endpoint->node_num);
        }

        temp = temp->next;
    }
    printf("current node: %d\n", temp->node_num);
    printf("last node's first edge: %d\n", temp->edges->endpoint->node_num);
}

pnode findNode(pnode headNode, int num)
{
    pnode temp = headNode;
    if (temp == NULL)
    {
        printf("null \n");
        return NULL;
    }

    while (temp->next != NULL)
    {
        if (temp->node_num == num)
        {
            return temp;
        }

        temp = temp->next;
    }
    if (temp->node_num == num)
    {
        return temp;
    }
    return NULL;
}

// making a new node and returning it's address in the memory
pnode makeNode()
{
    pnode newNode = (node *)calloc(1, sizeof(node));
    checkMemError(newNode);
    newNode->next = NULL;
    return newNode;
}

// filling the given node with the given data
void fillNode(pnode currNode, int node_num, pedge edges, struct GRAPH_NODE_ *next)
{
    currNode->node_num = node_num;
    currNode->next = next;
}

// creating a queue of node pointers
pnode_pointer makeQueue(node **head)
{
    // creating the head of the queue
    pnode_pointer QH = (node_pointer *)calloc(1, sizeof(node_pointer));
    checkMemError(QH);
    QH->node = (*head);

    if ((*head) == NULL)
    {
        QH = NULL;
        return QH;
    }

    pnode temp = (*head);
    pnode_pointer tempQueue = QH;
    while (temp->next != NULL)
    {
        // make a new node pointer in the queue
        tempQueue->next = (node_pointer *)calloc(1, sizeof(node_pointer));
        checkMemError(tempQueue->next);
        tempQueue->next->node = temp->next;
        temp->distance = INT_MAX;
        temp = temp->next;
        tempQueue = tempQueue->next;
    }
    // make the last node pointer in the queue
    temp->distance = INT_MAX;

    return QH;
}

void deleteNodePointer(node_pointer **p_QH, int nodeToDelete)
{
    pnode_pointer temp = *p_QH, prev = NULL, freeNode = NULL;
    if (temp == NULL)
    {
        return;
    }
    while (temp->next != NULL)
    {
        if (temp == *p_QH)
        {
            if (temp->node->node_num == nodeToDelete)
            {
                freeNode = temp;
                *p_QH = temp->next;
                free(freeNode);
                return;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
        else
        {
            if (temp->node->node_num == nodeToDelete)
            {
                freeNode = temp;
                prev->next = temp->next;
                free(freeNode);
                return;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }
    if (temp->node->node_num == nodeToDelete)
    {
        if (prev == NULL)
        {
            *p_QH = NULL;
        }
        else
        {
            prev->next = NULL;
        }
        free(temp);
        return;
    }
}

pnode ExtractMin(node_pointer **p_QH)
{
    if ((*p_QH) == NULL)
    {
        return NULL;
    }

    pnode_pointer tempQueue = (*p_QH);
    int minValue = tempQueue->node->distance;
    pnode tempNode = tempQueue->node;

    while (tempQueue->next != NULL)
    {
        if (tempQueue->node->distance < minValue)
        {
            minValue = tempQueue->node->distance;
            tempNode = tempQueue->node;
        }
        tempQueue = tempQueue->next;
    }
    if (tempQueue->node->distance < minValue)
    {
        minValue = tempQueue->node->distance;
        tempNode = tempQueue->node;
    }
    deleteNodePointer(p_QH, tempNode->node_num); // removes the node_pointer from the queue
    return tempNode;
}
