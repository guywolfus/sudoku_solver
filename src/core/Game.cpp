#include "Game.h"

namespace sudoku_solver {

Game::Game(std::unique_ptr<Cell[]> aCells, std::vector<Region> aRegions)
    : mCells(std::move(aCells))
    , mRegions(std::move(aRegions))
{
}

}