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

std::ofstream gravitationFile("data1.txt");
std::ofstream correctionFile("data2.txt");
std::ofstream correctionGravitationFile("data3.txt");
std::ofstream solidFile("data4.txt");
std::ofstream debugLogFile("debug.log");

void printData(LatticeChunk * latticeChunk, int time) {
  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < 100; i++) {
      gravitationFile << latticeChunk->getGravitation(i, 0, j) << ",";
      correctionFile << latticeChunk->getCorrection(i, 0, j) << ",";
      correctionGravitationFile << latticeChunk->getCorrectedGravitation(i, 0, j) << ",";
      solidFile << latticeChunk->isSolid(i, 0, j) << ",";
      if (latticeChunk->isIsolated(i, 0, j)) {
        debugLogFile << time << ", (" <<  i << ", 0, " << j << "), " 
                << latticeChunk->getGravitation(i, 0, j) << ", "
                << latticeChunk->getCorrection(i, 0, j) << ", "
                << latticeChunk->getCorrectedGravitation(i, 0, j) << ", "
                << latticeChunk->isSolid(i, 0, j) << "\n";
      }
    }
    //std::cout << "\n";
  }
  gravitationFile << "\n";
  correctionFile << "\n";
  correctionGravitationFile << "\n";
  solidFile << "\n";
}

int main() {
  ChunkMap map{};
  readFile(&map);

  LatticeChunk * latticeChunk = new LatticeChunk(map);
  for (int i = 0; i < 1000; i++) {
    //for (int i = 0; i < 100; i++) {
    //for (int i = 0; i < 450; i++) {
    latticeChunk->tick();
    if (i % 10 == 0) {
      //if (i >= 350 && i < 550 && i % 2 == 0) {
      printData(latticeChunk, i);
    }
  }

  return 0;
}