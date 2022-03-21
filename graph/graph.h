#ifndef _GRAPH_H_
#define _GRAPH_H_

#define TYPE char

typedef enum { Directed, Undirected } GraphKind;

typedef enum { Unvisited, Visited } VisitFlag;

// used in adj_graph implementation
typedef struct {
  int start;
  int end;
  int weight;
} Edge;

// used in list_graph implementation
typedef struct Vertex {
  struct Vertex* next;
  int index;
  TYPE data;
} Vertex;

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

typedef struct {
  BaseGraph* base_graph;

  // a list of linked list
  //
  // |0|-> |5|-> |6|-> NULL
  // |----
  // |1|-> |7|-> |1|-> NULL
  // |----
  // |2|-> |2|-> |8|-> NULL
  // |----
  // |3|-> |4|-> |9|-> NULL
  //
  Vertex** vertex_list;
} ListGraph;

static BaseGraph* jun_base_graph_create_internal(int vertex_number,
                                                 GraphKind kind);

static void jun_base_graph_destroy_internal(BaseGraph* base_graph);

static Edge* jun_edge_create(int start, int end, int weight);

void jun_edge_destroy(Edge* edge);

static Vertex* jun_vertex_create(int index, TYPE data);

AdjGraph* jun_adj_graph_create(int vertex_number, GraphKind kind);

void jun_adj_graph_destroy(AdjGraph* graph);

Edge* jun_adj_graph_first_edge(AdjGraph* adj_graph, int one_vertex);

Edge* jun_adj_graph_next_edge(AdjGraph* adj_graph, Edge* edge);

void jun_adj_graph_set_edge(AdjGraph* adj_graph, int start, int end,
                            int weight);

void jun_adj_graph_delete_edge(AdjGraph* adj_graph, int start, int end);

void jun_adj_graph_print(AdjGraph* adj_graph);

ListGraph* jun_list_graph_create(int vertex_number, GraphKind kind);

void jun_list_graph_destroy(ListGraph* list_graph);

Edge* jun_list_edge_first_edge(ListGraph* list_graph, int one_vertex);

Edge* jun_list_graph_next_edge(ListGraph* list_graph, Edge* edge);

void jun_list_graph_set_edge(ListGraph* list_graph, int beg, int end);

void jun_list_graph_delete_edge(ListGraph* list_graph, int start, int end);

void jun_list_graph_set_vertex(ListGraph* list_graph, TYPE* vertex_arr);

void jun_list_graph_print(ListGraph* list_graph);

static void jun_list_graph_set_edge_internal(ListGraph* list_graph, int beg,
                                             int end, TYPE data);

static void jun_list_graph_delete_edge_internal(ListGraph* list_graph, int beg,
                                                int end);

void jun_list_graph_bfs(ListGraph* list_graph, void (*visitor)(Vertex* vertex));

void jun_list_graph_dfs(ListGraph* list_graph, void (*visitor)(Vertex* vertex));

void jun_graph_clear_visit_flag(BaseGraph* base_graph);

void jun_adj_graph_prim(AdjGraph* adj_graph);

void jun_adj_graph_kruscal(AdjGraph* adj_graph);

void jun_adj_graph_dijkstra(AdjGraph* adj_graph, int start_vertex);

#endif
