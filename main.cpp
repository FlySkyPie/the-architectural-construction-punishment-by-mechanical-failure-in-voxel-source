#include <iostream>
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

int main() {
  ChunkMap map{};
  readFile(&map);
  
  //test

  LatticeChunk * latticeChunk = new LatticeChunk(map);

  return 0;
}