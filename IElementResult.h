#pragma once

class IElementResult {
public:

  virtual ~IElementResult() {
  }

  virtual float getGravitation() = 0;
  virtual float getCorrection() = 0;
  virtual float getCorrectedGravitation() = 0;
};

