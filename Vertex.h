//
// Created by Arthur Efremenko on 8/22/23.
//

#ifndef MAZESOLVER_VERTEX_H
#define MAZESOLVER_VERTEX_H

#include "Posn.h"
#include "Edge.h"

// Represents a vertex
struct Vertex {
  Posn posn;
  std::vector<Edge*> edges;
  bool explored;
  bool path;

  Vertex(const Posn& posn) : posn(posn), explored(false), path(false) {}
};


#endif //MAZESOLVER_VERTEX_H
