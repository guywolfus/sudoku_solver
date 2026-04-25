#include <utility>

#include "Game.h"

namespace sudoku_solver {

Game::Game(std::vector<Cell> aCells, std::vector<Region> aRegions)
    : mCells(std::move(aCells))
    , mRegions(std::move(aRegions))
{
}

}