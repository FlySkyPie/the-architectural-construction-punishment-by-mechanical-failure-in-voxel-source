#include <iostream>
#include <fstream>
#include "LatticeChunk.h"
#include "NewTypDefinition.h"

void readFile(ChunkMap* map) {
  std::string lineText;

  std::ifstream readFile("chunk.txt");
  int index = 0;
  while (getline(readFile, lineText)) {
    for (int i = 0; i < lineText.length(); i++) {
      map->at(index) = lineText.at(i);
      index++;
    }
  }
  readFile.close();
}

void printData(LatticeChunk * latticeChunk) {
  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < 100; i++) {
      //std::cout << latticeChunk->getGravitation(i, 0, j) << ",";
      std::cout << latticeChunk->getCorrection(i, 0, j) << ",";
      //std::cout << latticeChunk->getCorrectedGravitation(i, 0, j) << ",";
    }
    //std::cout << "\n";
  }
  std::cout << "\n";
}

int main() {
  ChunkMap map{};
  readFile(&map);

  LatticeChunk * latticeChunk = new LatticeChunk(map);
  for (int i = 0; i < 1000; i++) {
    latticeChunk->tick();
    if (i % 10 == 0) {
      printData(latticeChunk);
    }
  }

  return 0;
}