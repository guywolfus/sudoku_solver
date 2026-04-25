#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "Cell.h"
#include "Digit.h"

namespace sudoku_solver {

constexpr std::string_view UNTITLED_REGION = "Untitled Region";

// Represents a collection of cells that must contain unique digits in a valid Sudoku
// solution. Examples of standard regions are rows, columns, and boxes, but the idea
// is that Region is agnostic to the specific shape or arrangement of its cells.
class Region
{
public:
    Region(const Cells& aCells);
    Region(const std::string& aName, const Cells& aCells);

    Digits usedDigits() const;
    bool isComplete() const;
    void setName(const std::string& aName);

private:
    std::string mName;
    Cells mCells;
};

using Regions = std::vector<Region*>;

}