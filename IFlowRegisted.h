#pragma once

#include <cstdint>
#include "IFlowElement.h"

class IFlowRegisted {
public:

  virtual ~IFlowRegisted() {
  }
  virtual void addNeighbor(uint16_t axis, bool direction, IFlowElement* element) = 0;
  virtual bool isSolid() = 0;
};
