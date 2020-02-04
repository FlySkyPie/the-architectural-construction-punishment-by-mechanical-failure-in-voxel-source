#pragma once

class IElementStatus {
public:

  virtual ~IElementStatus() {
  }

  virtual float getGravitation() = 0;
  virtual float getCorrection() = 0;
  virtual float getCorrectedGravitation() = 0;
  virtual bool isSolid() = 0;
};

