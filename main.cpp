#include <iostream>
#include "LatticeChunk.h"
#include "NewTypDefinition.h"

int main() {
  ChunkMap map{};
  LatticeChunk * latticeChunk = new LatticeChunk(map);
  
  return 0;
}