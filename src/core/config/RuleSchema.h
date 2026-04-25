#pragma once

#include <string_view>

namespace sudoku_solver::RuleSchema {

// Rule types
constexpr std::string_view UNIQUE = "unique";
constexpr std::string_view SUM = "sum";

// Shared parameter keys
namespace Params {
    constexpr std::string_view TARGET_SUM = "target_sum";
    constexpr std::string_view CELL_PARITY = "cell_parity";
}

}
