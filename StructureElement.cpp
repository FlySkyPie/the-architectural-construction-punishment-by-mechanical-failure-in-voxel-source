#include <cmath>
#include <cstdint>
#include <iostream>//debug
//#include <typeinfo>//debug
#include <stdexcept>
#include "StructureElement.h"

StructureElement::StructureElement(float mass, bool boundary, bool solid) {
  this->mass = mass;
  this->gravitationCrashPoint = 350; //for early test
  this->correctedCrashPoint = 120; //for early test
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
  //gravitation rain
  this->addGravitation(this->mass);

  //flow to neighbors.
  int allocation = this->getGravitationAllocation();
  if (allocation == 0) {
    this->addGravitation(this->getGravitation());
  } else {
    float distributedValue = this->getGravitation() / allocation;
    for (int i = 0; i < 5; i++) {
      if (this->distributary.at(i)) {
        this->neighbors.at(i)->addGravitation(distributedValue);
      }
    }
  }
}

void StructureElement::updateGravitation() {
  //if (!(this->solid^this->crashing)) {
  //  return;
  //}
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
  //Increment from gravitation changed.
  this->addCorrection(this->getGravitaionDifference());

  //flow to neighbors.
  int allocation = this->getCorrectionAllocation();
  if (allocation == 0) {
    this->addCorrection(this->getCorrection());
  } else {
    float distributedValue = this->correctionCapacitor.energy / allocation;
    for (int i = 0; i < 4; i++) {
      if (this->distributary.at(i)) {
        this->neighbors.at(i)->addCorrection(distributedValue);
      }
    }
  }
}

void StructureElement::updateCorrection() {
  //if (!(this->solid^this->crashing)) {
  //  return;
  //}
  this->correctionCapacitor.oldEnergy = this->correctionCapacitor.energy;
  this->correctionCapacitor.energy = this->correctionCapacitor.energyBuffer;
  this->correctionCapacitor.energyBuffer = 0;
}

bool StructureElement::updateYield() {
  if (!this->solid) {
    return 0;
  }

  bool yieldCondition =
          (this->getCorrectedGravitation() > this->correctedCrashPoint ||
          this->getGravitation() > this->gravitationCrashPoint);

  if (yieldCondition) {
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

bool StructureElement::isIsolated() {
  if (!this->solid) {
    return 0;
  }
  int allocation = 0;

  for (int i = 0; i < 6; i++) {
    if (this->distributary.at(i)) {
      allocation += 1;
    }
  }
  return (allocation == 0) ? true : false;
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
  //remove 1 way boundary.
  for (int i = 0; i < 6; i++) {
    if (this->neighbors.at(i)) {
      this->neighbors.at(i)->updateDistributary(i / 2, !(i % 2), 0);
      this->updateDistributary(i / 2, (i % 2), 0);
    }
  }

  //setting to crashing status.
  this->initCapacitor();
  this->solid = false;
}

int StructureElement::getCorrectionAllocation() {
  int allocation = 0;

  for (int i = 0; i < 4; i++) {
    if (this->distributary.at(i)) {
      allocation += 1;
    }
  }
  return allocation;
}

int StructureElement::getGravitationAllocation() {
  int allocation = 0;

  for (int i = 0; i < 5; i++) {
    if (this->distributary.at(i)) {
      allocation += 1;
    }
  }
  return allocation;
}

void StructureElement::initCapacitor() {
  this->gravitaionCapacitor.energy = 0;
  this->gravitaionCapacitor.energyBuffer = 0;
  this->gravitaionCapacitor.oldEnergy = 0;

  this->correctionCapacitor.energy = 0;
  this->correctionCapacitor.energyBuffer = 0;
  this->correctionCapacitor.oldEnergy = 0;
}