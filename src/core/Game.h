#pragma once
#include <vector>

#include "core/model/Cell.h"
#include "core/model/Region.h"

namespace sudoku_solver {

// Represents the full state of a Sudoku puzzle at any given moment. Owns all
// cells, regions and rules that make up the puzzle, and exposes methods for
// manipulating and validating the puzzle state.
class Game
{
public:
    // Constructs a fully initialized Game from the given cells and regions.
    // Models are expected to be fully constructed and valid before being passed in.
    explicit Game(std::vector<Cell> aCells, std::vector<Region> aRegions);

private:
    std::vector<Cell> mCells;
    std::vector<Region> mRegions;
};

}