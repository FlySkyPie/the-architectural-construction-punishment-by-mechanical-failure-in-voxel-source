#include <array>
#include <cmath>
#include "LatticeChunk.h"
#include "StructureElement.h"

#include <iostream>

LatticeChunk::LatticeChunk(ChunkMap chunkConfig) {
  this->createElements(chunkConfig);
  this->updateElementConnections();
}

LatticeChunk::~LatticeChunk() {
  for (int i = 0; i < 1000000; i++) {
    delete this->elements[i];
  }
}

void LatticeChunk::tick() {
  for (int i = 0; i < 1000000; i++) {
    this->elements[i]->flowGravitation();
  }

  for (int i = 0; i < 1000000; i++) {
    this->elements[i]->updateGravitation();
  }

  for (int i = 0; i < 1000000; i++) {
    this->elements[i]->flowCorrection();
  }

  for (int i = 0; i < 1000000; i++) {
    this->elements[i]->updateCorrection();
  }

  for (int i = 0; i < 1000000; i++) {
    this->elements[i]->updateYield();
  }
}

float LatticeChunk::getGravitation(int x, int y, int z) {
  return this->getElement(x, y, z)->getGravitation();
}

float LatticeChunk::getCorrection(int x, int y, int z) {
  return this->getElement(x, y, z)->getCorrection();
}

float LatticeChunk::getCorrectedGravitation(int x, int y, int z) {
  return this->getElement(x, y, z)->getCorrectedGravitation();
}

void LatticeChunk::createElements(ChunkMap chunkConfig) {
  for (int i = 0; i < 1000000; i++) {
    float mass = 0;
    bool boundary = false;
    bool solid = false;

    if (chunkConfig[i] == 'X') {
      boundary = true;
      solid = true;
    } else if (chunkConfig[i] == '1') {
      mass = 1;
      solid = true;
    }

    this->elements[i] = new StructureElement(mass, boundary, solid);
  }
}

void LatticeChunk::updateElementConnections() {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      for (int k = 0; k < 100; k++) {
        /*
        //should used in two way linking.
        if ((i + j + k) % 2 == 1) {
          continue;
        }
         */
        this->updateElementConnection(i, j, k);
      }
    }
  }
}

//updateElementConnection

void LatticeChunk::updateElementConnection(int x, int y, int z) {
  HexaheElement neighbors = this->getElementNeighbors(x, y, z);
  HexaheDistributary distributary = this->getElementDistributary(neighbors);

  this->getElement(x, y, z)->setNeighbor(neighbors, distributary);
}

HexaheDistributary LatticeChunk::getElementDistributary(HexaheElement neighbors) {
  HexaheDistributary distributary;
  for (int i = 0; i < 6; i++) {
    if (!neighbors.at(i)) {
      distributary.at(i) = false;
      continue;
    }
    if (neighbors.at(i)->isSolid()) {
      distributary.at(i) = true;
    } else {
      distributary.at(i) = false;
    }
  }
  return distributary;
}

HexaheElement LatticeChunk::getElementNeighbors(int x, int y, int z) {
  HexaheElement neighbors;

  if (x == 0) {
    neighbors[0] = nullptr;
  } else {
    neighbors[0] = this->getElement(x - 1, y, z);
  }

  if (x == 99) {
    neighbors[1] = nullptr;
  } else {
    neighbors[1] = this->getElement(x + 1, y, z);
  }

  if (y == 0) {
    neighbors[2] = nullptr;
  } else {
    neighbors[2] = this->getElement(x, y - 1, z);
  }

  if (y == 99) {
    neighbors[3] = nullptr;
  } else {
    neighbors[3] = this->getElement(x, y + 1, z);
  }

  if (z == 0) {
    neighbors[4] = nullptr;
  } else {
    neighbors[4] = this->getElement(x, y, z - 1);
  }

  if (z == 99) {
    neighbors[5] = nullptr;
  } else {
    neighbors[5] = this->getElement(x, y, z + 1);
  }
  return neighbors;
}

/*
 * Get element by 3d racord(?).
 */
StructureElement* LatticeChunk::getElement(int x, int y, int z) {
  int index = x + 100 * y + 10000 * z;
  return this->elements[index];
}