#pragma once

class IFlowElement {
public:

  virtual ~IFlowElement() {
  }
  virtual void addGravitation(float gravitation) = 0;
  virtual void addCorrection(float correction) = 0;
};
