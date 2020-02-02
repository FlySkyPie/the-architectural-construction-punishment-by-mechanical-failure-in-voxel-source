#include <cmath>
#include <cstdint>
#include <iostream>//debug
#include <typeinfo>//debug
#include "StructureElement.h"

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

  for (int i = 0; i < 6; i++) {
    this->neighbors.at(i) = nullptr;
  }
}

StructureElement::~StructureElement() {
}

/***********************************************
 * Interfaces from IGravitationElement.
 ************************************************/

void StructureElement::addGravitation(float gravitation) {
  this->gravitaionCapacitor.energyBuffer += gravitation;
}

void StructureElement::addCorrection(float correction) {
  this->correctionCapacitor.energyBuffer += correction;
}

/***********************************************
 * Interfaces from IElementStatus.
 ************************************************/

void StructureElement::updateDistributary(int axis, int direction, bool status) {
  this->distributary.at(axis * 2 + direction) = status;
}

void StructureElement::setNeighbor(HexaheElement elements, HexaheDistributary distributary) {
  for (int i = 0; i < 6; i++) {
    this->neighbors.at(i) = elements.at(i);
    this->distributary.at(i) = distributary.at(i);
  }
}

bool StructureElement::isSolid() {
  return this->solid;
}

/***********************************************
 * Interfaces from IComputableElement.
 ************************************************/

/*
 * Flow gravitation to neighbor elements, excepted the element above it.
 */
void StructureElement::flowGravitation() {
  if (!this->solid) {
    return;
  }
  char allocation = 0;

  for (int i = 0; i < 5; i++) {
    if (this->distributary.at(i)) {
      allocation += 1;
    }
  }

  float value = this->gravitaionCapacitor.energy / allocation;

  for (int i = 0; i < 5; i++) {
    if (this->distributary.at(i)) {
      this->neighbors.at(i)->addGravitation(value);
    }
  }

  //gravitation rain
  this->addGravitation(this->mass);
}

void StructureElement::updateGravitation() {
  if (!this->solid) {
    return;
  }
  if (this->boundary) {
    this->gravitaionCapacitor.energyBuffer = 0;
  }

  this->gravitaionCapacitor.oldEnergy = this->gravitaionCapacitor.energy;
  this->gravitaionCapacitor.energy = this->gravitaionCapacitor.energyBuffer;
  this->gravitaionCapacitor.energyBuffer = 0;
}

void StructureElement::flowCorrection() {
  if (!this->solid) {
    return;
  }
  char allocation = 0;

  for (int i = 0; i < 4; i++) {
    if (this->distributary.at(i)) {
      allocation += 1;
    }
  }

  float value = this->correctionCapacitor.energy / allocation;

  for (int i = 0; i < 4; i++) {
    if (this->distributary.at(i)) {
      this->neighbors.at(i)->addCorrection(value);
    }
  }

  //Increment from gravitation changed.
  this->addCorrection(this->getGravitaionDifference());
}

void StructureElement::updateCorrection() {
  if (!this->solid) {
    return;
  }
  this->correctionCapacitor.oldEnergy = this->correctionCapacitor.energy;
  this->correctionCapacitor.energy = this->correctionCapacitor.energyBuffer;
  this->correctionCapacitor.energyBuffer = 0;
}

/***********************************************
 * Interfaces from IElementResult.
 ************************************************/

float StructureElement::getGravitation() {
  return this->gravitaionCapacitor.energy;
}

float StructureElement::getCorrection() {
  return this->correctionCapacitor.energy;
}

float StructureElement::getCorrectedGravitation() {
  return (this->gravitaionCapacitor.energy - this->correctionCapacitor.energy);

}

/***********************************************
 * Private Stuff
 ************************************************/

float StructureElement::getGravitaionDifference() {
  return (this->gravitaionCapacitor.energy - this->gravitaionCapacitor.oldEnergy);

}