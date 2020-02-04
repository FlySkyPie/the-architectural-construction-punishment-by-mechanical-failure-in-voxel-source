#pragma once

#include <cstdint>
#include "IElementBoundary.h"
#include "NewTypDefinition.h"

class IElementLink {
public:

  virtual ~IElementLink() {
  }

  virtual void setNeighbor(HexaheElement elements, HexaheDistributary distributary) = 0;
  
  //virtual void setDistributary(bool* status) = 0;
  //virtual bool isSolid() = 0;
};
