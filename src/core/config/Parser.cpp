#include <stdexcept>

#include "Parser.h"
#include "parsers/JsonParser.h"
#include "parsers/TomlParser.h"
#include "parsers/YamlParser.h"

namespace sudoku_solver {

std::unique_ptr<Parser>
createParser(const std::string& aFilepath)
{
    if (aFilepath.ends_with(".json"))
        return std::make_unique<JsonParser>();
    if (aFilepath.ends_with(".toml"))
        return std::make_unique<TomlParser>();
    if (aFilepath.ends_with(".yaml") || aFilepath.ends_with(".yml"))
        return std::make_unique<YamlParser>();

    throw std::runtime_error("Unsupported config file format: '" + aFilepath + "'");
}

}
