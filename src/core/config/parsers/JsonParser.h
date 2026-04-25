#pragma once

#include "../Parser.h"

namespace sudoku_solver {

// Parses JSON config files into a validated GameData object.
class JsonParser : public Parser
{
public:
    GameData parse(const std::string& aFilepath) const override;
};

}
