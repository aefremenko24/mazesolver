//
// Created by Arthur Efremenko on 8/22/23.
//

#ifndef MAZESOLVER_PLAYER_H
#define MAZESOLVER_PLAYER_H


#include "Posn.h"

// Represents the player
struct Player {
  Posn posn;

  Player(const Posn& posn) : posn(posn) {}

  // Draws the player (implementation not provided here)
  void drawPlayer() {
    // Your drawing code here
  }

  // Checks if the player reached the finish cell
  bool wonHuh(int x, int y) {
    return (this->posn.x >= x - 1 && this->posn.y >= y - 1);
  }
};

#endif //MAZESOLVER_PLAYER_H
