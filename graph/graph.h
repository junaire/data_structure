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

Graph* Graph_create(GraphKind kind);

void Graph_destroy(Graph* graph);

VexNode Graph_getVex(Graph* graph, int v);

void Graph_putVex(Graph* graph, int v, VexValueType value);

ArcNode* Graph_getFirstArc(Graph* graph, int v);

void Graph_insertVex(Graph* graph, VexNode* vex);

void Graph_deleteVex(Graph* graph, int v);

void Graph_insertArc(Graph* graph, int v, int w);

void Graph_deleteArc(Graph* graph, int v, int w);

#endif
