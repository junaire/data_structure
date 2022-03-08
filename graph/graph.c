#include "graph.h"

#include <stdlib.h>
#include <string.h>

static Edge* jun_edge_create(int start, int end, int weight) {
  Edge* edge = malloc(sizeof(Edge));
  edge->start = start;
  edge->end = end;
  edge->weight = weight;

  return edge;
}

static void jun_edge_destroy(Edge* edge) {
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
  for (int i = 0; i < vertex_number; ++i) {
    base_graph->marks[i] = Unvisited;
  }

  return base_graph;
}

static void jun_base_graph_destroy_internal(BaseGraph* base_graph) {
  free(base_graph->marks);
  free(base_graph);
  base_graph = NULL;
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
  if (adj_graph->matrix[start][end] == 0) {
    adj_graph->base_graph->edge_number++;
  }

  adj_graph->matrix[start][end] = weight;

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
