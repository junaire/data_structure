#ifndef _GRAPH_H_
#define _GRAPH_H_

#define MAX_VERTEX_NUM 20

#define VexValueType int

typedef enum { Directed, Undirected } GraphKind;

typedef struct ArcNode_ {
  int adjVex;
  int weight;
  struct ArcNode_* nextArc;
} ArcNode;

typedef struct {
  VexValueType value;
  ArcNode* firstArc;
} VexNode;

typedef struct {
  VexNode vertices[MAX_VERTEX_NUM];
  int vexNum;
  int arcNum;
  GraphKind kind;

} Graph;

Graph* graph_create(GraphKind kind);

void graph_destroy(Graph* graph);

VexNode graph_getvex(Graph* graph, int v);

void graph_putvex(Graph* graph, int v, VexValueType value);

ArcNode* graph_get_first_arc(Graph* graph, int v);

void graph_insertvex(Graph* graph, VexNode* vex);

void graph_deletevex(Graph* graph, int v);

void graph_insertarc(Graph* graph, int v, int w);

void graph_deletearc(Graph* graph, int v, int w);

#endif
