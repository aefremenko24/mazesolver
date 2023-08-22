//
// Created by Arthur Efremenko on 8/22/23.
//

#ifndef MAZESOLVER_VERTEX_H
#define MAZESOLVER_VERTEX_H

class Edge;

// Represents a vertex
struct Vertex {
public:
  Posn posn;
  std::vector<Edge*> edges;
  bool explored;
  bool path;

  Vertex(const Posn& posn) : posn(posn), explored(false), path(false) {}

  Vertex() : posn(0, 0), explored(false), path(false) {}
};


#endif //MAZESOLVER_VERTEX_H
