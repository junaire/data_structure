#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

/* Input
5 8 0
0 1 6
0 4 2
2 1 1
2 3 3
3 0 2
4 1 3
4 2 1
4 3 3
*/

int main() {
  int x, y, src;
  GraphKind kind;

  int beg, end, weight;

  scanf("%d %d %d", &x, &y, &src);

  AdjGraph* adj_graph = jun_adj_graph_create(x, Undirected);

  for (int i = 0; i < y; ++i) {
    scanf("%d %d %d", &beg, &end, &weight);
    jun_adj_graph_set_edge(adj_graph, beg, end, weight);
  }

  printf("Prim:\n");
  jun_adj_graph_prim(adj_graph);
  printf("Kruscal:\n");
  jun_adj_graph_kruscal(adj_graph);
  jun_adj_graph_destroy(adj_graph);
}
