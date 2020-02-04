#include <cmath>
#include <cstdint>
#include <iostream>//debug
#include <typeinfo>//debug
#include "StructureElement.h"

StructureElement::StructureElement(float mass, bool boundary, bool solid) {
  this->mass = mass;
  this->yieldPoint = 120.0; //for early test
  this->boundary = boundary;
  this->solid = solid;

  this->initCapacitor();

  for (int i = 0; i < 6; i++) {
    this->neighbors.at(i) = nullptr;
  }
}

StructureElement::~StructureElement() {
}

/***********************************************
 * Interfaces from IElementBoundary.
 ************************************************/

void StructureElement::addGravitation(float gravitation) {
  this->gravitaionCapacitor.energyBuffer += gravitation;
}

void StructureElement::addCorrection(float correction) {
  this->correctionCapacitor.energyBuffer += correction;
}

void StructureElement::updateDistributary(int axis, int direction, bool status) {
  this->distributary.at(axis * 2 + direction) = status;
}

/***********************************************
 * Interfaces from IElementLink.
 ************************************************/

void StructureElement::setNeighbor(HexaheElement elements, HexaheDistributary distributary) {
  for (int i = 0; i < 6; i++) {
    this->neighbors.at(i) = elements.at(i);
    this->distributary.at(i) = distributary.at(i);
  }
}

/***********************************************
 * Interfaces from IElementComputable.
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

bool StructureElement::updateYield() {
  if (!this->solid) {
    return 0;
  }
  if (this->getCorrectedGravitation()>this->yieldPoint) {
    this->yield();
    return 1;
  }
  return 0;
}

/***********************************************
 * Interfaces from IElementStatus.
 ************************************************/

float StructureElement::getGravitation() {
  return this->gravitaionCapacitor.energy;
}

float StructureElement::getCorrection() {
  return this->correctionCapacitor.energy;
}

float StructureElement::getCorrectedGravitation() {
  return std::abs(this->gravitaionCapacitor.energy - this->correctionCapacitor.energy);
}

bool StructureElement::isSolid() {
  return this->solid;
}

/***********************************************
 * Private Stuff
 ************************************************/

float StructureElement::getGravitaionDifference() {
  return (this->gravitaionCapacitor.energy - this->gravitaionCapacitor.oldEnergy);
}

/*
 * The block has broken by gravitation.
 * should remove boundary and exceeded and correction from neighbors.
 */

void StructureElement::yield() {
  //remove exceeded correction
  float exceedeCorrection = this->correctionCapacitor.energy - this->gravitaionCapacitor.energy;
  char allocation = 0;

  for (int i = 0; i < 4; i++) {
    if (this->distributary.at(i)) {
      allocation += 1;
    }
  }

  float value = exceedeCorrection / allocation;

  for (int i = 0; i < 4; i++) {
    if (this->distributary.at(i)) {
      this->neighbors.at(i)->addCorrection(value);
    }
  }
  //remove boundary.
  for (int i = 0; i < 3; i++) {
    for (int direction = 0; direction <= 1; direction++) {
      if (this->neighbors.at(i * 2 + direction)) {
        this->neighbors.at(i * 2 + direction)->updateDistributary(i, !direction, 0);
        this->updateDistributary(i, direction, 0);
      }
    }
  }

  //initial this element to air
  this->solid = false;
  this->initCapacitor();
}

void StructureElement::initCapacitor() {
  this->gravitaionCapacitor.energy = 0;
  this->gravitaionCapacitor.energyBuffer = 0;
  this->gravitaionCapacitor.oldEnergy = 0;

  this->correctionCapacitor.energy = 0;
  this->correctionCapacitor.energyBuffer = 0;
  this->correctionCapacitor.oldEnergy = 0;
}