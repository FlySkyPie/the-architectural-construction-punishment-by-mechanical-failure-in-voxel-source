#pragma once

#include <cstdint>
#include "IGravitationElement.h"

#include "NewTypDefinition.h"

class IElementStatus {
public:

  virtual ~IElementStatus() {
  }

  //virtual void setDistributary(bool* status) = 0;
  virtual void updateDistributary(int axis, int direction, bool status) = 0;

  virtual void setNeighbor(HexaheElement elements, HexaheDistributary distributary) = 0;

  virtual bool isSolid() = 0;
};
