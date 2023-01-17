#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;
;

typedef struct edge_
{
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_
{
    int node_num;
    int distance; // for dijkstra's algo ( d[v])
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

// for making a queue that holds pointers to the nodes in the graph
typedef struct node_pointer
{
    struct GRAPH_NODE_ *node;
    struct node_pointer *next;
} node_pointer, *pnode_pointer;

#endif
