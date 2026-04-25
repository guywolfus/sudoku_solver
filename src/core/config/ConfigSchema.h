#pragma once

#include <string_view>

namespace sudoku_solver::ConfigSchema {

// Required fields
constexpr std::string_view DIGITS = "digits";
constexpr std::string_view CELLS = "cells";
constexpr std::string_view REGIONS = "regions";

// Optional fields: generic definitions
constexpr std::string_view BASE = "base";
constexpr std::string_view GIVEN = "given";
constexpr std::string_view RULES = "rules";
constexpr std::string_view NAME = "name";

// Optional fields: region & rule definitions
constexpr std::string_view ORDERED = "ordered";
constexpr std::string_view TYPE = "type";
constexpr std::string_view PARAMS = "params";

}
