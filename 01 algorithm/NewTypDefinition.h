#pragma once
#include <array>

#define FlowGravitationMission 1
#define UpdateGravitationMission 2
#define FlowCorrectionMission 3
#define UpdateCorrectionMission 4
#define UpdateYieldMission 5

class StructureElement;
typedef std::array< StructureElement *, 6> HexaheElement;
typedef std::array< bool, 6 > HexaheDistributary;
typedef std::array<char, 1000000> ChunkMap;
typedef std::array<StructureElement*, 1000000> ChunkElements;