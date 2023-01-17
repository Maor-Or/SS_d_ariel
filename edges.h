#include "graph.h"

pedge makeEdge();
void fillEdge(pedge currEdge, int weight, pnode endpoint);
void addToEdges(pnode currNode, int weight, pnode endpoint);
void deleteAllEdges(pnode p_node);
int delete_all_edges_to_n(pnode currNode, int nodeToDelete);
