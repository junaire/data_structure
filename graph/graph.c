#include "graph.h"

#include <stdlib.h>
#include <string.h>

Graph* Graph_create(GraphKind kind) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->kind = kind;
  graph->vexNum = graph->arcNum = 0;
  return graph;
}

void Graph_destroy(Graph* graph) { free(graph); }

VexNode Graph_getVex(Graph* graph, int v) { return graph->vertices[v]; }

void Graph_putVex(Graph* graph, int v, VexValueType value) {
  graph->vertices[v].value = value;
}

ArcNode* Graph_getFirstArc(Graph* graph, int v) {
  return graph->vertices[v].firstArc;
}

void Graph_insertVex(Graph* graph, VexNode* vex) {
  graph->vertices[graph->vexNum] = *vex;
  graph->vexNum++;
}

void Graph_deleteVex(Graph* graph, int v) {
  ArcNode* arc = graph->vertices[v].firstArc;
  ArcNode* next = arc->nextArc;
  while (next != NULL) {
    free(arc);
    arc = next;
    next = next->nextArc;
  }
  memmove(graph->vertices + v, graph->vertices + v + 1,
          sizeof(VexNode) * (MAX_VERTEX_NUM - v - 1));

  graph->vexNum--;
}

void Graph_insertArc(Graph* graph, int v, int w) {
  ArcNode* iter = graph->vertices[v].firstArc;
  while (iter->nextArc != NULL) {
    iter = iter->nextArc;
  }
  ArcNode* last = (ArcNode*)malloc(sizeof(ArcNode));
  last->nextArc = NULL;
  last->adjVex = w;
  last->weight = 0;

  iter->nextArc = last;

  if (graph->kind == Undirected) {
    ArcNode* iter = graph->vertices[w].firstArc;
    while (iter->nextArc != NULL) {
      iter = iter->nextArc;
    }
    ArcNode* last = (ArcNode*)malloc(sizeof(ArcNode));
    last->nextArc = NULL;
    last->adjVex = v;
    last->weight = 0;

    iter->nextArc = last;
  }
}

void Graph_deleteArc(Graph* graph, int v, int w) {
  ArcNode* iter = graph->vertices[v].firstArc;
  ArcNode* tmp = iter;
  while (iter->nextArc != NULL) {
    if (iter->adjVex == w) {
      tmp->nextArc = iter->nextArc;
      free(iter);
    }
    tmp = iter;
    iter = iter->nextArc;
  }

  if (graph->kind == Undirected) {
    ArcNode* iter = graph->vertices[w].firstArc;
    while (iter->nextArc != NULL) {
      if (iter->adjVex == v) {
        tmp->nextArc = iter->nextArc;
        free(iter);
      }
      tmp = iter;
      iter = iter->nextArc;
    }
  }
}
