#include "StructureElement.h"

#include <cmath>
#include <cstdint>
#include <iostream>//edbug

StructureElement::StructureElement(float mass, bool boundary, bool solid) {
  this->mass = mass;
  this->boundary = boundary;
  this->solid = solid;

  this->gravitaionCapacitor.energy = 0;
  this->gravitaionCapacitor.energyBuffer = 0;
  this->gravitaionCapacitor.oldEnergy = 0;

  this->correctionCapacitor.energy = 0;
  this->correctionCapacitor.energyBuffer = 0;
  this->correctionCapacitor.oldEnergy = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      this->neighbors[i][j] = nullptr;
    }
  }
}

//IFlowElement 

void StructureElement::addGravitation(float gravitation) {
  this->gravitaionCapacitor.energyBuffer += gravitation;
}

void StructureElement::addCorrection(float correction) {
  this->correctionCapacitor.energyBuffer += correction;
}

//IFlowRegisted

void StructureElement::addNeighbor(uint16_t axis, bool direction, IFlowElement *element) {
  int16_t directionIndex = direction ? 1 : 0;

  if (axis >= 3) {
    throw "Must been 0~2.";
  }

  //std::cout << "Point A===\n";
  //std::cout << "axis: " << axis << ",direction: " << direction << ", element: " << element << "\n";

  this->neighbors[axis][directionIndex] = element;
}

bool StructureElement::isSolid() {
  return this->solid;
}


//IFlowControlled

void StructureElement::flowGravitation() {
  char allocation = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      if (this->neighbors[i][j]) {
        allocation += 1;
      }
    }
  }

  float value = this->gravitaionCapacitor.energy / allocation;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      if (this->neighbors[i][j]) {
        //std::cout << "Point A: \n";
        this->neighbors[i][j]->addGravitation(value);
      }
    }
  }

  //natural flow
  this->addGravitation(this->mass);
}

void StructureElement::updateGravitation() {
  if (this->boundary) {
    this->gravitaionCapacitor.energyBuffer = 0;
  }

  this->gravitaionCapacitor.oldEnergy = this->gravitaionCapacitor.energy;
  this->gravitaionCapacitor.energy = this->gravitaionCapacitor.energyBuffer;
  this->gravitaionCapacitor.energyBuffer = 0;
}

void StructureElement::flowCorrection() {
  char allocation = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (this->neighbors[i][j]) {
        allocation += 1;
      }
    }
  }

  float value = this->correctionCapacitor.energy / allocation;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (this->neighbors[i][j]) {
        this->neighbors[i][j]->addCorrection(value);
      }
    }
  }

  //natural flow
  this->addCorrection(this->getGravitaionDifference());
}

void StructureElement::updateCorrection() {
  this->correctionCapacitor.oldEnergy = this->correctionCapacitor.energy;
  this->correctionCapacitor.energy = this->correctionCapacitor.energyBuffer;
  this->correctionCapacitor.energyBuffer = 0;
}

//IFlowStatistic

float StructureElement::getGravitation() {
  return this->gravitaionCapacitor.energy;
}

float StructureElement::getCorrection() {
  return this->correctionCapacitor.energy;
}

float StructureElement::getCorrectedGravitation() {
  return (this->gravitaionCapacitor.energy - this->correctionCapacitor.energy);

}

//private stuff

float StructureElement::getGravitaionDifference() {
  return (this->gravitaionCapacitor.energy - this->gravitaionCapacitor.oldEnergy);

}