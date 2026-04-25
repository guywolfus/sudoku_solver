#include "Cell.h"

namespace sudoku_solver {

Cell::Cell(const Digit& aDigit)
    : mName(UNTITLED_CELL)
    , mDigit(&aDigit)
    , mPossibleDigits({})
{
}

Cell::Cell(const std::string& aName, const Digit& aDigit)
    : mName(aName)
    , mDigit(&aDigit)
{
}

Cell::Cell(const Digits& aDigits)
    : mName(UNTITLED_CELL)
    , mPossibleDigits(aDigits)
{
}

Cell::Cell(const std::string& aName, const Digits& aDigits)
    : mName(aName)
    , mPossibleDigits(aDigits)
{
}

bool
Cell::isEmpty() const { return !mDigit.has_value(); }

const std::optional<const Digit*>&
Cell::digit() const { return mDigit; }

void
Cell::setDigit(const Digit* aDigit) { mDigit = aDigit; }

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
    for (const Digit* digit : aDigits)
    {
        mPossibleDigits.erase(digit);
    }
}

void
Cell::setPossibleDigits(const Digits& aDigits) { mPossibleDigits = aDigits; }

}
