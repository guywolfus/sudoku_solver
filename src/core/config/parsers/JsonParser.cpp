#include <fstream>
#include <stdexcept>

#include "nlohmann/json.hpp"

#include "JsonParser.h"
#include "../ConfigSchema.h"
#include "../RuleSchema.h"

using json = nlohmann::json;

namespace {

json
validateJsonFile(const std::string& aFilepath)
{
    std::ifstream file(aFilepath);
    if (!file.is_open())
        throw std::runtime_error("Failed to open config file: '" + aFilepath + "'");

    try
    {
        return json::parse(file);
    }
    catch (const json::parse_error& e)
    {
        throw std::runtime_error("Invalid JSON in config file: " + std::string(e.what()));
    }
}

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

void
resolveBasesRecursive(json& aConfigData)
{
    if (aConfigData.contains(sudoku_solver::ConfigSchema::BASE))
    {
        json baseData = getBaseTemplate(
            aConfigData[sudoku_solver::ConfigSchema::BASE]
        );
        resolveBasesRecursive(baseData);

        aConfigData.erase(sudoku_solver::ConfigSchema::BASE);

        for (auto& [key, value] : baseData.items())
        {
            if (!aConfigData.contains(key))
                aConfigData[key] = value;
        }
    }
}

void
validateConfigData(const json& aConfigData)
{
    auto requireField = [&](std::string_view aFieldName)
    {
        if (!aConfigData.contains(aFieldName))
            throw std::runtime_error(
                "Config data is missing required field: '" + std::string(aFieldName) + "'"
            );
    };

    requireField(sudoku_solver::ConfigSchema::DIGITS);
    requireField(sudoku_solver::ConfigSchema::CELLS);
    requireField(sudoku_solver::ConfigSchema::REGIONS);
}

sudoku_solver::RuleData
buildRule(const json& aRuleData)
{
    return sudoku_solver::RuleData{
        .type = aRuleData[sudoku_solver::ConfigSchema::TYPE].get<std::string>(),
        .params = aRuleData.value(
            sudoku_solver::ConfigSchema::PARAMS,
            std::map<std::string, int>{}
        )
    };
}

sudoku_solver::RegionData
buildRegion(const json& aRegionData)
{
    std::vector<sudoku_solver::RuleData> rules;
    if (aRegionData.contains(sudoku_solver::ConfigSchema::RULES))
    {
        rules.reserve(aRegionData[sudoku_solver::ConfigSchema::RULES].size());
        for (const auto& ruleData : aRegionData[sudoku_solver::ConfigSchema::RULES])
            rules.push_back(buildRule(ruleData));
    }

    return sudoku_solver::RegionData{
        .name = aRegionData[sudoku_solver::ConfigSchema::NAME].get<std::string>(),
        .cellIndices = aRegionData[sudoku_solver::ConfigSchema::CELLS].get<std::vector<int>>(),
        .isOrdered = aRegionData.value(sudoku_solver::ConfigSchema::ORDERED, false),
        .rules = std::move(rules)
    };
}

}

namespace sudoku_solver {

GameData
JsonParser::parse(const std::string& aFilepath) const
{
    json configData = validateJsonFile(aFilepath);
    resolveBasesRecursive(configData);
    validateConfigData(configData);

    std::vector<RegionData> regions;
    regions.reserve(configData[ConfigSchema::REGIONS].size());

    for (const auto& regionData : configData[ConfigSchema::REGIONS])
        regions.push_back(buildRegion(regionData));

    return GameData{
        .digits = configData[ConfigSchema::DIGITS].get<std::vector<int>>(),
        .numCells = configData[ConfigSchema::CELLS],
        .regions = std::move(regions)
    };
}

}
