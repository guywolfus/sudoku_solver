#pragma once
#include <string_view>

namespace sudoku_solver::PuzzleSchema {

    // Required fields
    constexpr std::string_view DIGITS = "digits";
    constexpr std::string_view CELLS = "cells";
    constexpr std::string_view REGIONS = "regions";

    // Optional fields
    constexpr std::string_view BASE = "base";
    constexpr std::string_view GIVEN = "given";
    constexpr std::string_view RULES = "rules";

}