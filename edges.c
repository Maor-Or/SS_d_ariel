#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "nodes.h"
#include "edges.h"
#include "algo.h"
#include "graph.h"

// deletes all the edges of the given node
void deleteAllEdges(pnode p_node)
{
    if (p_node->edges == NULL)
    {
        return;
    }
    pedge t_edge1 = p_node->edges;
    pedge t_edge2 = t_edge1;
    while (t_edge1->next != NULL)
    {
        t_edge2 = t_edge1;
        t_edge1 = t_edge1->next;
        free(t_edge2);
    }
    free(t_edge1);
    p_node->edges = NULL;
}

int delete_all_edges_to_n(pnode currNode, int nodeToDelete)
{
    int counter = 0;
    pedge temp = currNode->edges, prev = NULL, freeEdge = NULL;

    // if there are no edges we are done
    if (temp == NULL)
    {
        return counter;
    }

    // while not the last node
    while (temp->next != NULL)
    {
        // if we still are at the start = "phase 1"
        if (currNode->edges == temp)
        {
            // if the node is bad
            if (temp->endpoint->node_num == nodeToDelete)
            {
                freeEdge = temp;
                currNode->edges = temp->next;
                temp = temp->next;
                free(freeEdge);
                counter++;
            }
            else
            { // we get to phase 2
                prev = temp;
                temp = temp->next;
            }
        }
        // phase 2 - not at the start
        else
        {
            // is the current node bad?
            if (temp->endpoint->node_num == nodeToDelete)
            {
                prev->next = temp->next;
                freeEdge = temp;
                free(freeEdge);
                counter++;
                temp = prev->next;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }

    // last node to check - no more nodes at next
    //(might be a single node at the begining)
    if (temp->endpoint->node_num == nodeToDelete)
    {
        if (prev == NULL)
        {
            currNode->edges = NULL;
        }
        else
        {
            prev->next = NULL;
        }
        freeEdge = temp;
        free(freeEdge);
        counter++;
    }

    return counter;
}

// making a new edge and returning it's address in the memory
pedge makeEdge()
{
    pedge newEdge = (edge *)calloc(1, sizeof(edge));
    checkMemError(newEdge);
    return newEdge;
}

// filling the given edge with the given data
void fillEdge(pedge currEdge, int weight, pnode endpoint)
{
    currEdge->weight = weight;
    currEdge->endpoint = endpoint;
    currEdge->next = NULL;
}

/*
when we add a new edge to the node's linkedList
we want to make sure it isn't already there'
if it is there - we update it's attributes
*/
void addToEdges(pnode currNode, int weight, pnode endpoint)
{
    pedge tempEdge = currNode->edges;
    if (tempEdge == NULL)
    {                                                    // if the node has no edges yet we make a new one
        pedge newEdge = (edge *)calloc(1, sizeof(edge)); // new edge
        checkMemError(newEdge);
        fillEdge(newEdge, weight, endpoint); // fill the new edge
        currNode->edges = newEdge;           // link it to the node
    }

    // else we need to reach the edge-list end and then add a new one
    else
    {
        while (tempEdge->next != NULL)
        { // get to the last edge in the linked-list
            tempEdge = tempEdge->next;
        }
        pedge newEdge = (edge *)calloc(1, sizeof(edge)); // new edge
        checkMemError(newEdge);
        fillEdge(newEdge, weight, endpoint); // fill the new edge
        tempEdge->next = newEdge;            // link it to the node
    }
}
