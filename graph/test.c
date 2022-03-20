#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void graph_visitor(Vertex* vertex) { printf("%c\t", vertex->data); }

/* Input
5 6
0
a
b
c
d
e
0 1
0 3
1 2
1 4
2 3
2 4
*/

int main() {
  char nodes[30] = {'\0'};

  int x, y, type;
  GraphKind kind;

  int beg, end;

  scanf("%d %d", &x, &y);
  scanf("%d", &type);

  if (type == 0) {
    kind = Undirected;
  } else {
    kind = Directed;
  }

  for (int i = 0; i < x; ++i) {
    scanf(" %c", &nodes[i]);
  }

  ListGraph* list_graph = jun_list_graph_create(x, kind);

  AdjGraph* adj_graph = jun_adj_graph_create(x, kind);

  jun_list_graph_set_vertex(list_graph, nodes);

  for (int i = 0; i < y; ++i) {
    scanf("%d %d", &beg, &end);
    jun_list_graph_set_edge(list_graph, beg, end);
    jun_adj_graph_set_edge(adj_graph, beg, end, 1);
  }

  printf("ListGraph implementation:\n");
  jun_list_graph_print(list_graph);
  printf("AdjGraph implementation:\n");
  jun_adj_graph_print(adj_graph);

  printf("BFS:\n");
  jun_list_graph_bfs(list_graph, graph_visitor);
  printf("\n");

  // don't forget to clear the visit flags.
  jun_graph_clear_visit_flag(list_graph->base_graph);

  printf("DFS:\n");
  jun_list_graph_dfs(list_graph, graph_visitor);
  printf("\n");

  printf("Prim:\n");
  jun_adj_graph_prim(adj_graph);

  printf("Kruscal:\n");
  jun_adj_graph_kruscal(adj_graph);

  jun_adj_graph_destroy(adj_graph);

  jun_list_graph_destroy(list_graph);
}
