#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "Digit.h"

namespace sudoku_solver {

constexpr std::string_view UNTITLED_CELL = "Untitled Cell";

// Represents a single square in the Sudoku grid. It may contain a digit if assigned,
// otherwise it is considered empty. Each cell also maintains a set of possible
// digits that could be assigned to it based on the current game state.
class Cell
{
public:
    explicit Cell(const Digit& aDigit);
    explicit Cell(const std::string& aName, const Digit& aDigit);
    Cell(const Digits& aDigits);
    Cell(const std::string& aName, const Digits& aDigits);

    bool isEmpty() const;

    const std::optional<const Digit*>& digit() const;
    void setDigit(const Digit* aDigit);

    const Digits& possibleDigits() const;
    void addPossibleDigits(const Digits& aDigits);
    void removePossibleDigits(const Digits& aDigits);
    void setPossibleDigits(const Digits& aDigits);

private:
    std::string mName;
    std::optional<const Digit*> mDigit;
    Digits mPossibleDigits;
};

using Cells = std::vector<Cell*>;

}
