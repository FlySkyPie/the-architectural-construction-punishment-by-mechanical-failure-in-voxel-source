#pragma once
#include <array>

class StructureElement;
typedef std::array< StructureElement *, 6> HexaheElement;
typedef std::array< bool, 6 > HexaheDistributary;
typedef std::array<char, 1000000> ChunkMap;
typedef std::array<StructureElement*, 1000000> ChunkElements;