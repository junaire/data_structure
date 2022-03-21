#include "graph.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Edge* jun_edge_create(int start, int end, int weight) {
  Edge* edge = malloc(sizeof(Edge));
  edge->start = start;
  edge->end = end;
  edge->weight = weight;

  return edge;
}

void jun_edge_destroy(Edge* edge) {
  free(edge);
  edge = NULL;
}

static BaseGraph* jun_base_graph_create_internal(int vertex_number,
                                                 GraphKind kind) {
  BaseGraph* base_graph = malloc(sizeof(BaseGraph));
  base_graph->vertex_number = vertex_number;
  base_graph->edge_number = 0;
  base_graph->kind = kind;

  base_graph->marks = malloc(sizeof(VisitFlag) * vertex_number);
  jun_graph_clear_visit_flag(base_graph);

  return base_graph;
}

static void jun_base_graph_destroy_internal(BaseGraph* base_graph) {
  free(base_graph->marks);
  free(base_graph);
  base_graph = NULL;
}

static Vertex* jun_vertex_create(int index, TYPE data) {
  Vertex* vertex = malloc(sizeof(Vertex));
  vertex->data = data;
  vertex->index = index;
  vertex->next = NULL;

  return vertex;
}

AdjGraph* jun_adj_graph_create(int vertex_number, GraphKind kind) {
  AdjGraph* graph = malloc(sizeof(AdjGraph));
  graph->base_graph = jun_base_graph_create_internal(vertex_number, kind);

  graph->matrix = malloc(sizeof(int*) * vertex_number);

  for (int i = 0; i < vertex_number; ++i) {
    graph->matrix[i] = malloc(sizeof(int) * vertex_number);
  }

  return graph;
}

void jun_adj_graph_destroy(AdjGraph* graph) {
  for (int i = 0; i < graph->base_graph->vertex_number; i++) {
    free(graph->matrix[i]);
  }
  free(graph->matrix);

  jun_base_graph_destroy_internal(graph->base_graph);
  free(graph);
  graph = NULL;
}

Edge* jun_adj_graph_first_edge(AdjGraph* adj_graph, int one_vertex) {
  for (int i = 0; i < adj_graph->base_graph->vertex_number; ++i) {
    if (adj_graph->matrix[one_vertex][i] != 0) {
      return jun_edge_create(one_vertex, i, adj_graph->matrix[one_vertex][i]);
    }
  }
  return NULL;
}

Edge* jun_adj_graph_next_edge(AdjGraph* adj_graph, Edge* edge) {
  for (int i = edge->end + 1; i < adj_graph->base_graph->vertex_number; ++i) {
    if (adj_graph->matrix[edge->start][i] != 0) {
      return jun_edge_create(edge->start, i, adj_graph->matrix[edge->start][i]);
    }
  }
  return NULL;
}

void jun_adj_graph_set_edge(AdjGraph* adj_graph, int start, int end,
                            int weight) {
  // if there's already an edge, add one.
  if (adj_graph->matrix[start][end] == 0) {
    adj_graph->base_graph->edge_number++;
  }

  adj_graph->matrix[start][end] = weight;

  // note we should add another if the type of graph is undirected.
  if (adj_graph->base_graph->kind == Undirected) {
    adj_graph->matrix[end][start] = weight;
  }
}

void jun_adj_graph_delete_edge(AdjGraph* adj_graph, int start, int end) {
  if (adj_graph->matrix[start][end] != 0) {
    adj_graph->base_graph->edge_number--;
  }
  adj_graph->matrix[start][end] = 0;

  if (adj_graph->base_graph->kind == Undirected) {
    adj_graph->matrix[end][start] = 0;
  }
}

void jun_adj_graph_print(AdjGraph* adj_graph) {
  for (int i = 0; i < adj_graph->base_graph->vertex_number; ++i) {
    for (int j = 0; j < adj_graph->base_graph->vertex_number; ++j) {
      printf("%d", adj_graph->matrix[i][j]);
    }
    printf("\n");
  }
}

ListGraph* jun_list_graph_create(int vertex_number, GraphKind kind) {
  ListGraph* list_graph = malloc(sizeof(ListGraph));
  list_graph->base_graph = jun_base_graph_create_internal(vertex_number, kind);
  list_graph->vertex_list = malloc(sizeof(Edge*) * vertex_number);

  return list_graph;
}

void jun_list_graph_destroy(ListGraph* list_graph) {
  for (int i = 0; i < list_graph->base_graph->vertex_number; ++i) {
    Vertex* iter = list_graph->vertex_list[i];
    while (iter != NULL) {
      Vertex* tmp = iter->next;
      free(iter);
      iter = tmp;
    }
  }

  jun_base_graph_destroy_internal(list_graph->base_graph);
}

static void jun_list_graph_set_edge_internal(ListGraph* list_graph, int beg,
                                             int end, TYPE data) {
  Vertex* iter = list_graph->vertex_list[beg];
  if (iter->next == NULL) {
    iter->next = jun_vertex_create(end, data);
  } else {
    Vertex* tmp = iter->next;
    Vertex* edge = jun_vertex_create(end, data);
    iter->next = edge;
    edge->next = tmp;
  }
}

static void jun_list_graph_delete_edge_internal(ListGraph* list_graph, int beg,
                                                int end) {
  // TODO
}

void jun_list_graph_set_edge(ListGraph* list_graph, int beg, int end) {
  jun_list_graph_set_edge_internal(list_graph, beg, end,
                                   list_graph->vertex_list[end]->data);

  if (list_graph->base_graph->kind == Undirected) {
    jun_list_graph_set_edge_internal(list_graph, end, beg,
                                     list_graph->vertex_list[beg]->data);
  }
}

void jun_list_graph_delete_edge(ListGraph* list_graph, int beg, int end) {
  jun_list_graph_delete_edge_internal(list_graph, beg, end);
  if (list_graph->base_graph->kind == Undirected) {
    jun_list_graph_delete_edge_internal(list_graph, end, beg);
  }
}

void jun_list_graph_print(ListGraph* list_graph) {
  for (int i = 0; i < list_graph->base_graph->vertex_number; ++i) {
    Vertex* vertex = list_graph->vertex_list[i];

    while (vertex != NULL) {
      printf("%c", vertex->data);
      vertex = vertex->next;
    }
    printf("\n");
  }
}

void jun_list_graph_set_vertex(ListGraph* list_graph, TYPE* vertex_arr) {
  for (int i = 0; i < list_graph->base_graph->vertex_number; ++i) {
    list_graph->vertex_list[i] = jun_vertex_create(i, vertex_arr[i]);
  }
}

void jun_list_graph_bfs(ListGraph* list_graph,
                        void (*visitor)(Vertex* vertex)) {
  Vertex* iter = list_graph->vertex_list[0];
  Vertex* tmp = NULL;
  if (iter->next) {
    tmp = iter->next;
  }

  for (int i = 1; i < list_graph->base_graph->vertex_number; ++i) {
    if (iter->next) {
      tmp = iter->next;
    }
    while (iter != NULL) {
      if (list_graph->base_graph->marks[iter->index] == Unvisited) {
        visitor(iter);
        list_graph->base_graph->marks[iter->index] = Visited;
      }
      iter = iter->next;
    }

    iter = list_graph->vertex_list[tmp->index];
  }
}

void jun_list_graph_dfs(ListGraph* list_graph,
                        void (*visitor)(Vertex* vertex)) {
  int start = 0;

  for (int i = 0; i < list_graph->base_graph->vertex_number; ++i) {
    if (list_graph->base_graph->marks[start] == Unvisited) {
      visitor(list_graph->vertex_list[start]);
      list_graph->base_graph->marks[start] = Visited;

      Vertex* iter = list_graph->vertex_list[start]->next;
      while (iter != NULL) {
        if (list_graph->base_graph->marks[iter->index] == Unvisited) {
          start = iter->index;
          break;
        }
        iter = iter->next;
      }
    }
  }
}

void jun_graph_clear_visit_flag(BaseGraph* graph) {
  for (int i = 0; i < graph->vertex_number; ++i) {
    graph->marks[i] = Unvisited;
  }
}

void jun_adj_graph_prim(AdjGraph* adj_graph) {
  int cost = 0;
  int selected[adj_graph->base_graph->vertex_number];  // a helper array to
                                                       // store selected edges
  memset(selected, 0, sizeof(selected));

  selected[0] = 1;  // the first edge is always in the set

  int x = 0;
  int y = 0;

  for (int no_edge = 0; no_edge < adj_graph->base_graph->vertex_number - 1;
       no_edge++) {
    int min = INT_MAX;

    for (int i = 0; i < adj_graph->base_graph->vertex_number; i++) {
      // if the edge is in the selected set
      if (selected[i]) {
        // if the choosen edge is not in the selected set and is a vaild one
        for (int j = 0; j < adj_graph->base_graph->vertex_number; j++) {
          if (!selected[j] && adj_graph->matrix[i][j]) {
            // find the minimal edge
            if (min > adj_graph->matrix[i][j]) {
              min = adj_graph->matrix[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    printf("%d %d %d\n", x, y, adj_graph->matrix[x][y]);
    cost += adj_graph->matrix[x][y];
    selected[y] = 1;
  }
  printf("%d\n", cost);
}

void jun_adj_graph_kruscal(AdjGraph* adj_graph) {
  int start, end;
  int edge_list_n = 0;
  int span_list_n = 0;
  int cost = 0;

  int vertex_number = adj_graph->base_graph->vertex_number;
  int belongs[vertex_number];
  memset(belongs, 0, vertex_number);

  Edge** edge_list = malloc(sizeof(Edge*) * 1024);
  Edge** span_list = malloc(sizeof(Edge*) * 1024);

  // store all edges in a list
  for (int i = 1; i < vertex_number; i++) {
    for (int j = 0; j < i; j++) {
      // if it is a valid edge
      if (adj_graph->matrix[i][j] != 0) {
        edge_list[edge_list_n] = jun_edge_create(i, j, adj_graph->matrix[i][j]);
        edge_list_n++;
      }
    }
  }

  // sort the edge list by their weight
  Edge* tmp = NULL;
  for (int i = 1; i < edge_list_n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (edge_list[j]->weight > edge_list[j + 1]->weight) {
        tmp = edge_list[j];
        edge_list[j] = edge_list[j + 1];
        edge_list[j + 1] = tmp;
      }
    }
  }

  for (int i = 0; i < vertex_number; i++) belongs[i] = i;

  for (int i = 0; i < edge_list_n; i++) {
    // always choose the shortest path from the ordered edge list.
    start = belongs[edge_list[i]->start];
    end = belongs[edge_list[i]->end];

    // it is not a circle
    if (start != end) {
      span_list[span_list_n] = edge_list[i];
      span_list_n++;

      // TODO: What does this mean?
      for (int j = 1; j < vertex_number; j++)
        if (belongs[j] == end) belongs[j] = start;
    }
  }

  for (int i = 0; i < span_list_n; i++) {
    printf("%d %d %d\n", span_list[i]->start, span_list[i]->end,
           span_list[i]->weight);
    cost = cost + span_list[i]->weight;
  }
  printf("%d\n", cost);
}

void jun_adj_graph_dijkstra(AdjGraph* adj_graph, int start_vertex) {
  int distance[1024];
  int path[1024];
  int s[1024];
  int apath[1024];
  int min;

  int MAX = 9999;  // can't use INT_MAX or will overflow.

  int vertex_number = adj_graph->base_graph->vertex_number;

  // initialize the graph for Dijkstra algorithm.
  for (int i = 0; i < vertex_number; ++i) {
    for (int j = 0; j < vertex_number; ++j) {
      // we don't allow circles here.
      if (i == j) {
        adj_graph->matrix[i][j] = 0;
      } else {
        // mark it as unreachable
        if (adj_graph->matrix[i][j] == 0) {
          adj_graph->matrix[i][j] = MAX;
        }
      }
    }
  }

  for (int i = 0; i < vertex_number; ++i) {
    distance[i] = adj_graph->matrix[start_vertex][i];
    if (distance[i] != MAX) {
      path[i] = start_vertex;
    } else {
      path[i] = -1;
    }
  }

  for (int i = 0; i < vertex_number; ++i) {
    s[i] = 0;
  }

  s[start_vertex] = 1;

  for (int i = 1; i < vertex_number; ++i) {
    // find the shortest path
    int Min = MAX;
    for (int j = 0; j < vertex_number; j++) {
      if ((s[j] == 0) && distance[j] < Min) {
        Min = distance[j];
        min = j;
      }
    }

    s[min] = 1;

    for (int k = 0; k < vertex_number; ++k) {
      if ((s[k] == 0) &&
          (distance[k] > distance[min] + adj_graph->matrix[min][k])) {
        distance[k] = distance[min] + adj_graph->matrix[min][k];
        path[k] = min;
      }
    }
  }

  // print out
  for (int i = 0; i < vertex_number; ++i) {
    if (s[i] == 1 && i != start_vertex) {
      if (distance[i] == MAX) {
        continue;
      }
      // the cost
      printf("%d ", distance[i]);

      int d = 0;
      apath[d] = i;
      int k = path[i];

      // if there's way to get there, print it, or we just discard it.
      if (k != -1) {
        while (k != start_vertex) {
          d++;
          apath[d] = k;
          k = path[k];
        }
        d++;
        apath[d] = start_vertex;
        printf("%d", apath[d]);
        for (int j = d - 1; j >= 0; j--) {
          printf(" %d", apath[j]);
        }
        printf("\n");
      }
    }
  }
}
