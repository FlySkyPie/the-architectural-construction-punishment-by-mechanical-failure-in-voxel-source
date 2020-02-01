#pragma once

class IGravitationElement {
public:

  virtual ~IGravitationElement() {
  }
  virtual void addGravitation(float gravitation) = 0;
  virtual void addCorrection(float correction) = 0;
};
