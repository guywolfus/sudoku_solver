#pragma once

#include <map>
#include <string>
#include <vector>

namespace sudoku_solver {

// Represents a rule applied to a region, describing how the cells in
// that region relate to each other.
struct RuleData {
    const std::string type;
    const std::map<std::string, int> params;
};

// Represents a named, ordered or unordered grouping of cells with one
// or more rules that constrain the digits assigned to those cells.
struct RegionData {
    const std::string name;
    const std::vector<int> cellIndices;
    const bool isOrdered;
    const std::vector<RuleData> rules;
};

// A fully validated, schema-resolved representation of a Sudoku puzzle
// template. Produced by the Parser and consumed by Game to construct
// all domain objects and their relationships.
struct GameData {
    const std::vector<int> digits;
    const int numCells;
    const std::vector<RegionData> regions;
};

}
