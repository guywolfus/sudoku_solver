#pragma once

#include <stdexcept>

#include "../Parser.h"

namespace sudoku_solver {

// Parses TOML config files into a validated GameData object.
class TomlParser : public Parser
{
public:
    GameData parse(const std::string& aFilepath) const override
    {
        throw std::runtime_error("Not yet implemented");
    };
};

}
