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
std::ofstream crashingFile("data5.txt");

void printData(LatticeChunk * latticeChunk) {
  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < 100; i++) {
      gravitationFile << latticeChunk->getGravitation(i, 0, j) << ",";
      correctionFile << latticeChunk->getCorrection(i, 0, j) << ",";
      correctionGravitationFile << latticeChunk->getCorrectedGravitation(i, 0, j) << ",";
      solidFile << latticeChunk->isSolid(i, 0, j) << ",";
      crashingFile << latticeChunk->isCrashing(i, 0, j) << ",";
    }
    //std::cout << "\n";
  }
  gravitationFile << "\n";
  correctionFile << "\n";
  correctionGravitationFile << "\n";
  solidFile << "\n";
  crashingFile << "\n";
}

int main() {
  //clear files
  /*std::ofstream ofs;
  ofs.open("data1.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  ofs.open("data2.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  ofs.open("data3.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  ofs.open("data4.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();*/

  //do job
  ChunkMap map{};
  readFile(&map);

  LatticeChunk * latticeChunk = new LatticeChunk(map);
  //for (int i = 0; i < 1000; i++) {
  for (int i = 0; i < 450; i++) {
    latticeChunk->tick();
    //if (i % 10 == 0) {
    if (i >= 350 && i < 450) {
      printData(latticeChunk);
    }
  }

  return 0;
}