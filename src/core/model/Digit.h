#pragma once


namespace sudoku_solver {

// In Variant Sudoku, digits may sometimes have more logic attached to them than just
// their face value. For example, a digit's symbol (what's visually written in the
// cell) may differ from its value (the underlying number it represents).
struct Digit
{
    int symbol;
    int value;

    explicit Digit(int aInt)
        : symbol(aInt), value(aInt) {
    }

    explicit Digit(int aSymbol, int aValue)
        : symbol(aSymbol), value(aValue) {
    }

    // Two digits are equal if both their symbol and value match.
    bool operator==(const Digit& aOther) const
    {
        return symbol == aOther.symbol && value == aOther.value;
    }
};

}

namespace std {

// Dedicated hash for Digit so it can be used in unordered containers.
template <>
struct hash<sudoku_solver::Digit>
{
    size_t operator()(const sudoku_solver::Digit& aDigit) const
    {
        size_t h1 = std::hash<int>{}(aDigit.symbol);
        size_t h2 = std::hash<int>{}(aDigit.value);
        return h1 ^ (h2 << 1);
    }
};

}