#include "graph.h"


void printGraph(pnode head);
void printNodes(pnode head);
pnode findNode(pnode headNode, int num);
pnode makeNode();
void fillNode(pnode currNode, int node_num, pedge edges, struct GRAPH_NODE_ *next);
void deleteNode(node **p_head, int nodeToDelete);
void deleteNodePointer(node_pointer **p_QH, int nodeToDelete);
void delete_all_nodes(node **p_head);
pnode_pointer makeQueue(node **head);
pnode ExtractMin(node_pointer **p_QH);