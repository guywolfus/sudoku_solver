#pragma once

#include <memory>
#include <string>

#include "core/GameData.h"

namespace sudoku_solver {

// Abstract base class for all config file parsers. Defines the interface
// any format-specific parser must implement to produce a GameData object.
class Parser
{
public:
    virtual ~Parser() = default;

    // Parses the config file at the given path into a validated GameData
    // ready for Game construction.
    virtual GameData parse(const std::string& aFilepath) const = 0;
};

// Creates and returns the appropriate parser for the given file path
// based on its extension.
std::unique_ptr<Parser> createParser(const std::string& aFilepath);

}
