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
  int no_edge = 0;
  int selected[adj_graph->base_graph->vertex_number];
  memset(selected, 0, sizeof(selected));

  selected[0] = 1;

  int x;  //  row number
  int y;  //  col number

  while (no_edge < adj_graph->base_graph->vertex_number - 1) {
    // For every vertex in the set S, find the all adjacent vertices
    // , calculate the distance from the vertex selected at step 1.
    // if the vertex is already in the set S, discard it otherwise
    // choose another vertex nearest to selected vertex  at step 1.

    int min = INT_MAX;
    x = 0;
    y = 0;

    for (int i = 0; i < adj_graph->base_graph->vertex_number; i++) {
      if (selected[i]) {
        for (int j = 0; j < adj_graph->base_graph->vertex_number; j++) {
          if (!selected[j] &&
              adj_graph
                  ->matrix[i][j]) {  // not in selected and there is an edge
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
    no_edge++;
  }
  printf("%d\n", cost);
}

void jun_adj_graph_kruscal(AdjGraph* adj_graph) {
  int belongs[1024];
  int i, j, cno1, cno2;

  int edge_list_n = 0;
  int span_list_n = 0;
  int cost = 0;

  int vertex_number = adj_graph->base_graph->vertex_number;

  Edge** edge_list = malloc(sizeof(Edge*) * 1024);
  Edge** span_list = malloc(sizeof(Edge*) * 1024);

  for (i = 1; i < vertex_number; i++) {
    for (j = 0; j < i; j++) {
      if (adj_graph->matrix[i][j] != 0) {
        edge_list[edge_list_n] = jun_edge_create(i, j, adj_graph->matrix[i][j]);
        edge_list_n++;
      }
    }
  }

  // Sort the edge list
  Edge* tmp;

  for (int i = 1; i < edge_list_n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (edge_list[j]->weight > edge_list[j + 1]->weight) {
        tmp = edge_list[j];
        edge_list[j] = edge_list[j + 1];
        edge_list[j + 1] = tmp;
      }
    }
  }

  for (i = 0; i < vertex_number; i++) belongs[i] = i;

  for (i = 0; i < edge_list_n; i++) {
    cno1 = belongs[edge_list[i]->start];
    cno2 = belongs[edge_list[i]->end];

    if (cno1 != cno2) {
      span_list[span_list_n] = edge_list[i];
      span_list_n++;

      for (i = 1; i < vertex_number; i++)
        if (belongs[i] == cno2) belongs[i] = cno1;
    }
  }

  for (i = 0; i < span_list_n; i++) {
    printf("%d %d %d\n", span_list[i]->start, span_list[i]->end,
           span_list[i]->weight);
    cost = cost + span_list[i]->weight;
  }
  printf("%d\n", cost);
}
