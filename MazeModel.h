#ifndef MAZESOLVER_MAZEMODEL_H
#define MAZESOLVER_MAZEMODEL_H


#include "Player.h"
#include "Vertex.h"
#include "Edge.h"

// Represents the maze world class
class MazeWorld {
public:
  int sizeX;
  int sizeY;
  std::vector<std::vector<Vertex>> board;
  std::unordered_map<Vertex*, Vertex*> vertices;
  std::vector<Edge*> edgesInTree;
  std::vector<Edge*> worklist;
  std::vector<Vertex*> explored;
  std::vector<Vertex*> path;
  Player player;
  int count;
  std::vector<Vertex*> traveled;
  bool showPath;

  // MazeWorld constructor
  MazeWorld(int sizeX, int sizeY)
      : sizeX(sizeX), sizeY(sizeY), board(sizeX, std::vector<Vertex>(sizeY)),
        player(Posn(0, 0)), count(-1), showPath(true) {
    this->initBoard();
    this->kruskal(this->sortEdges(this->possibleEdges()), this->board);
    this->assignEdges();
    this->explorePath();
    this->traveled.push_back(&this->board[0][0]);
  }

  // Initializes the board
  void initBoard() {
    for (int x = 0; x < this->sizeX; x++) {
      for (int y = 0; y < this->sizeY; y++) {
        this->board[x][y] = Vertex(Posn(x, y));
      }
    }
  }

  // Returns all possible edges for a vertex
  std::vector<Edge*> possibleEdges() {
    std::vector<Edge*> result;
    for (int x = 0; x < this->sizeX; x++) {
      for (int y = 0; y < this->sizeY; y++) {
        if (x < this->sizeX - 1) {
          Vertex* vertex = &this->board[x][y];
          Vertex* right = &this->board[x + 1][y];
          Edge* edge2 = new Edge(vertex, right, std::rand());
          result.push_back(edge2);
        }
        if (y < this->sizeY - 1) {
          Vertex* vertex = &this->board[x][y];
          Vertex* down = &this->board[x][y + 1];
          Edge* edge1 = new Edge(vertex, down, std::rand());
          result.push_back(edge1);
        }
      }
    }
    return result;
  }

  // Sorts a list of edges by cost
  std::vector<Edge*> sortEdges(const std::vector<Edge*>& edges) {
    std::vector<Edge*> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](Edge* a, Edge* b) {
      return a->cost < b->cost;
    });
    return sortedEdges;
  }

  // Performs Kruskal's algorithm to build the board with connected vertices
  void kruskal(const std::vector<Edge*>& worklist, std::vector<std::vector<Vertex>>& board) {
    std::unordered_map<Vertex*, Vertex*> result;
    for (auto& vertexY : board) {
      for (auto& vertexX : vertexY) {
        result[&vertexX] = &vertexX;
      }
    }
    for (Edge* currentEdge : worklist) {
      if (this->edgesInTree.size() >= result.size() - 1) {
        break;
      }
      Vertex* firstRep = find(result, currentEdge->first);
      Vertex* secondRep = find(result, currentEdge->second);
      if (firstRep != secondRep) {
        this->edgesInTree.push_back(currentEdge);
        result[secondRep] = firstRep;
      }
    }
    this->worklist.erase(std::remove_if(this->worklist.begin(), this->worklist.end(),
                                        [this](Edge* edge) {
                                          return std::find(this->edgesInTree.begin(), this->edgesInTree.end(), edge) !=
                                                 this->edgesInTree.end();
                                        }),
                         this->worklist.end());
    this->vertices = result;
  }

  // Finds the representative vertex in the given map
  Vertex* find(std::unordered_map<Vertex*, Vertex*>& map, Vertex* v) {
    if (map[v] == v) {
      return map[v];
    }
    return find(map, map[v]);
  }

  // Adds edges to vertices
  void assignEdges() {
    for (Edge* edge : this->edgesInTree) {
      edge->first->edges.push_back(edge);
      edge->second->edges.push_back(edge);
    }
  }

  // Draws the maze (implementation not provided here)
  void makeScene() {
    // Your drawing code here
  }

  // Explores the path and sets explored and path vertices
  void explorePath() {
    std::unordered_map<Vertex*, Vertex*> cameFromEdge;
    std::vector<Vertex*> worklist;
    worklist.push_back(&this->board[0][0]);
    this->explored.clear();

    while (!worklist.empty()) {
      Vertex* next = worklist.front();
      worklist.erase(worklist.begin());
      Vertex* finalNode = &this->board[this->sizeX - 1][this->sizeY - 1];
      if (next == finalNode) {
        this->reconstruct(cameFromEdge, next);
        return;
      }
      for (Edge* edge : next->edges) {
        Vertex* neighbor = edge->first == next ? edge->second : edge->first;
        if (!std::count(this->explored.begin(), this->explored.end(), neighbor)) {
          worklist.push_back(neighbor);
          this->explored.push_back(next);
          cameFromEdge[neighbor] = next;
        }
      }
    }
  }

  // Reconstructs the shortest path
  void reconstruct(const std::unordered_map<Vertex*, Vertex*>& cameFromEdge, Vertex* nextVertex) {
    this->path.push_back(&this->board[this->sizeX - 1][this->sizeY - 1]);
    Vertex* start = &this->board[0][0];
    while (start != nextVertex) {
      this->path.push_back(cameFromEdge.at(nextVertex));
      nextVertex = cameFromEdge.at(nextVertex);
    }
  }
};


#endif //MAZESOLVER_MAZEMODEL_H
