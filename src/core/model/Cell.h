#pragma once

#include <optional>
#include <unordered_set>

#include "Digit.h"

namespace sudoku_solver {

using Digits = std::unordered_set<Digit>;

// Represents a single square in the Sudoku grid. It may contain a digit if assigned,
// otherwise it is considered empty. Each cell also maintains a set of possible
// digits that could be assigned to it based on the current game state.
class Cell
{
public:
    bool isEmpty() const;

    const std::optional<Digit>& digit() const;
    void setDigit(Digit aDigit);

    const Digits& possibleDigits() const;
    void addPossibleDigits(const Digits& aDigits);
    void removePossibleDigits(const Digits& aDigits);
    void setPossibleDigits(const Digits& aDigits);

private:
    std::optional<Digit> mDigit;
    Digits mPossibleDigits;
};

}