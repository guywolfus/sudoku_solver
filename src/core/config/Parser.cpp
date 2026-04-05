#include <fstream>
#include <stdexcept>

#include "nlohmann/json.hpp"

#include "core/config/Parser.h"
#include "core/config/PuzzleSchema.h"

using json = nlohmann::json;


namespace {

// Validates the file at the given path and returns the parsed JSON object.
// Throws a runtime_error if the file cannot be opened or if the JSON is invalid.
json
validateJsonFile(const std::string& aJsonFilepath)
{
    std::ifstream file(aJsonFilepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open puzzle file: '" + aJsonFilepath + "'");
    }

    try
    {
        return json::parse(file);
    }
    catch (const json::parse_error& e)
    {
        throw std::runtime_error("Invalid JSON in puzzle file: " + std::string(e.what()));
    }
}

// Retrieves a base template JSON object by file path or template name.
// Throws a runtime_error if the template cannot be found or loaded.
json
getBaseTemplate(const std::string& aBaseName)
{
    const std::string baseFilepath = aBaseName.ends_with(".json")
        ? aBaseName
        : "templates/" + aBaseName + ".json";

    try
    {
        return validateJsonFile(baseFilepath);
    }
    catch (const std::runtime_error&)
    {
        throw std::runtime_error("Failed to load base template: '" + baseFilepath + "'");
    }
}

// Recursively resolves and merges any base templates into the given JSON object.
void
resolveBasesRecursive(json& aPuzzleData)
{
    if (aPuzzleData.contains(sudoku_solver::PuzzleSchema::BASE))
    {
        json baseData = getBaseTemplate(
            aPuzzleData[sudoku_solver::PuzzleSchema::BASE]
        );
        resolveBasesRecursive(baseData);

        // Remove base field before merging
        aPuzzleData.erase(sudoku_solver::PuzzleSchema::BASE);

        // Merge base data into puzzle data, without overwriting existing keys
        for (auto& [key, value] : baseData.items())
        {
            if (!aPuzzleData.contains(key))
            {
                aPuzzleData[key] = value;
            }
        }
    }
}

// Validates the parsed JSON data against the expected schema for a Sudoku puzzle.
// Throws a runtime_error if the data does not conform to the schema.
void
validateGameData(const json& aPuzzleData)
{
    auto requireField = [&](std::string_view aFieldName)
    {
        if (!aPuzzleData.contains(aFieldName))
        {
            throw std::runtime_error(
                "Puzzle data is missing required field: '" + std::string(aFieldName) + "'"
            );
        }
    };

    requireField(sudoku_solver::PuzzleSchema::DIGITS);
    requireField(sudoku_solver::PuzzleSchema::CELLS);
    requireField(sudoku_solver::PuzzleSchema::REGIONS);
}

}


namespace sudoku_solver {

void parsePuzzle(const std::string& aJsonFilepath)
{
    json puzzleData = validateJsonFile(aJsonFilepath);
    resolveBasesRecursive(puzzleData);
    validateGameData(puzzleData);

    // TODO: convert puzzleData into Game representation.
}

}