//
// Created by Arthur Efremenko on 8/22/23.
//

#ifndef MAZESOLVER_EDGE_H
#define MAZESOLVER_EDGE_H


#include "Vertex.h"

// Represents an edge
struct Edge {
  Vertex* first;
  Vertex* second;
  int cost;

  Edge(Vertex* firstVertex, Vertex* secondVertex, int cost) :
      first(firstVertex), second(secondVertex), cost(cost) {}
};


#endif //MAZESOLVER_EDGE_H
