#pragma once

#include <span>
#include <unordered_set>

#include "Cell.h"
#include "Digit.h"

namespace sudoku_solver {

// Represents a collection of cells that must contain unique digits in a valid Sudoku
// solution. Examples of standard regions are rows, columns, and boxes, but the idea
// is that Region is agnostic to the specific shape or arrangement of its cells.
class Region
{
public:
    explicit Region(const std::span<Cell*> aCells);

    std::unordered_set<const Digit*> usedDigits() const;
    bool isComplete() const;

private:
    std::span<Cell*> mCells;
};

}