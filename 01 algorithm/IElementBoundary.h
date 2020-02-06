#pragma once

class IElementBoundary {
public:

  virtual ~IElementBoundary() {
  }
  virtual void addGravitation(float gravitation) = 0;
  virtual void addCorrection(float correction) = 0;
  virtual void updateDistributary(int axis, int direction, bool status) = 0;
};
