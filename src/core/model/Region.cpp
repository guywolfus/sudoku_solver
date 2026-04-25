#include "Region.h"

namespace sudoku_solver {

Region::Region(const Cells& aCells)
    : mName(UNTITLED_REGION)
    , mCells(aCells)
{
}

Region::Region(const std::string& aName, const Cells& aCells)
    : mName(aName)
    , mCells(aCells)
{
}

void
Region::setName(const std::string& aName) { mName = aName; }

Digits
Region::usedDigits() const
{
    Digits digits;
    for (const Cell* cell : mCells)
    {
        if (!cell->isEmpty())
        {
            // .value() unpacks the optional, unrelated to Digit::value.
            // Inserts a pointer to the actual Digit object referenced in the cell.
            const Digit* digit = cell->digit().value();
            digits.insert(digit);
        }
    }
    return digits;
}

bool
Region::isComplete() const
{
    for (const Cell* cell : mCells)
    {
        if (cell->isEmpty())
        {
            return false;
        }
    }
    return true;
}

}