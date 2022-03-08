#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef enum { Directed, Undirected } GraphKind;

typedef enum { Unvisited, Visited } VisitFlag;

typedef struct Edge {
  int start;
  int end;
  // FIXME: use generic data type
  int weight;
} Edge;

typedef struct {
  int vertex_number;
  int edge_number;
  VisitFlag* marks;
  GraphKind kind;

} BaseGraph;

typedef struct {
  BaseGraph* base_graph;
  int** matrix;
} AdjGraph;

static BaseGraph* jun_base_graph_create_internal(int vertex_number,
                                                 GraphKind kind);

static void jun_base_graph_destroy_internal(BaseGraph* base_graph);

static Edge* jun_edge_create(int start, int end, int weight);

static void jun_edge_destroy(Edge* edge);

AdjGraph* jun_adj_graph_create(int vertex_number, GraphKind kind);

void jun_adj_graph_destroy(AdjGraph* graph);

Edge* jun_adj_graph_first_edge(AdjGraph* adj_graph, int one_vertex);

Edge* jun_adj_graph_next_edge(AdjGraph* adj_graph, Edge* edge);

void jun_adj_graph_set_edge(AdjGraph* adj_graph, int start, int end,
                            int weight);

void jun_adj_graph_delete_edge(AdjGraph* adj_graph, int start, int end);
#endif
