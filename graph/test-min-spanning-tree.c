#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

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
