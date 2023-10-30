#include "Life.h"

BlockOfCells::BlockOfCells(const size_t rows, const size_t columns, const size_t quantCellsInOneRowsInBlock) {
    left = nullptr;
    right = nullptr;

    const size_t binary = 2;
    const size_t quantBlocksInRow = (rows / binary) + (rows % binary);
    const size_t quantBlocksInColums = (columns / binary) + (columns % binary);


}

BlockOfCells::~BlockOfCells() {
    if (left != nullptr) {
       ( *left).~BlockOfCells();
    }
    if (right != nullptr) {
        (*right).~BlockOfCells();
    }
}

void BlockOfCells::addCell(const Cell &cell) {
//    cout << cell.getX() << endl;
}
