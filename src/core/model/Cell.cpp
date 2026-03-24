#include "Cell.h"

namespace sudoku_solver {

bool
Cell::isEmpty() const { return !mDigit.has_value(); }

const std::optional<Digit>&
Cell::digit() const { return mDigit; }

void
Cell::setDigit(Digit aDigit) { mDigit = aDigit; }

const Digits&
Cell::possibleDigits() const { return mPossibleDigits; }

void
Cell::addPossibleDigits(const Digits& aDigits)
{
    mPossibleDigits.insert(aDigits.begin(), aDigits.end());
}

void
Cell::removePossibleDigits(const Digits& aDigits)
{
    for (const Digit& digit : aDigits)
    {
        mPossibleDigits.erase(digit);
    }
}

void
Cell::setPossibleDigits(const Digits& aDigits) { mPossibleDigits = aDigits; }

}