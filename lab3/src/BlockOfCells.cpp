#include "Life.h"

BlockOfCells::BlockOfCells(const size_t rows, const size_t columns) {
    this->left = nullptr;
    this->right = nullptr;

}

void BlockOfCells::addCell(const Cell &cell) {
//    cout << cell.getX() << endl;
}