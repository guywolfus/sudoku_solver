#include <vector>
#include <iostream>

#include "core/model/Cell.h"
#include "core/model/Digit.h"
#include "core/model/Region.h"

int main()
{
	using namespace sudoku_solver;
    std::cout << std::boolalpha;

    // Create a flat array of cells, as Game would at runtime
    std::vector<Cell> cells;
    cells.reserve(6);

    // Assign digits to some cells
    cells[0].setDigit(Digit(9));
    cells[2].setDigit(Digit(7));

    // Build a pointer array for a non-contiguous region (cells 0, 2, 4)
    std::array<Cell*, 3> regionPtrs = {
        &cells[0],
        &cells[2],
        &cells[4]
    };

    // Create a region from the non-contiguous pointer array
    Region region(regionPtrs);

    // Region should not be complete since cell[4] is empty
    std::cout << "region isComplete: " << region.isComplete() << "\n"; // expected: false

    // Verify usedDigits only sees the two assigned digits within the region
    std::cout << "usedDigits count: " << region.usedDigits().size() << "\n"; // expected: 2

    // Complete the region and verify
    cells[4].setDigit(Digit(3));
    std::cout << "region isComplete after filling: " << region.isComplete() << "\n"; // expected: true

    // Verify cells outside the region are unaffected
    std::cout << "cell[1] isEmpty: " << cells[1].isEmpty() << "\n"; // expected: true
    std::cout << "cell[3] isEmpty: " << cells[3].isEmpty() << "\n"; // expected: true
    std::cout << "cell[5] isEmpty: " << cells[5].isEmpty() << "\n"; // expected: true

    /*
    // Expected solution for nyt_260319_easy, top-to-bottom left-to-right
    const std::array<int, 81> expectedSolution = {
        5, 9, 2, 7, 3, 4, 1, 6, 8,
        3, 8, 4, 1, 9, 6, 2, 7, 5,
        1, 6, 7, 8, 5, 2, 4, 9, 3,
        9, 4, 1, 6, 8, 5, 3, 2, 7,
        8, 7, 5, 3, 2, 9, 6, 1, 4,
        2, 3, 6, 4, 7, 1, 8, 5, 9,
        6, 1, 8, 5, 4, 7, 9, 3, 2,
        4, 5, 9, 2, 1, 3, 7, 8, 6,
        7, 2, 3, 9, 6, 8, 5, 4, 1
    };
    */

    std::cin.get();
}