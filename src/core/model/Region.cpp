#include "Region.h"

namespace sudoku_solver {

Region::Region(const std::span<Cell*> aCells) : mCells(aCells) {}

std::unordered_set<const Digit*>
Region::usedDigits() const
{
    std::unordered_set<const Digit*> digits;
    for (const Cell* cell : mCells)
    {
        if (!cell->isEmpty())
        {
            // .value() unpacks the optional, unrelated to Digit::value.
            // Inserts a pointer to the actual Digit object stored in the cell.
            const Digit& digit = cell->digit().value();
            digits.insert(&digit);
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