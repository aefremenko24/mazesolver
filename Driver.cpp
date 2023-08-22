#include <iostream>
#include <string>

#include "MazeModel.h"

using namespace std;

int main() {
  // Seed the random number generator
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  MazeWorld mazeWorld(10, 10);
  // Your game loop and interaction handling code here

  return 0;
}