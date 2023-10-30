#include "Life.h"

BlockOfCells::BlockOfCells(const size_t rows, const size_t columns) {
    this->left = nullptr;
    this->right = nullptr;
}

BlockOfCells::~BlockOfCells() {
    if (this->left != nullptr) {
        (*(this->left)).~BlockOfCells();
    }
    if (this->right != nullptr) {
        (*(this->right)).~BlockOfCells();
    }
}

void BlockOfCells::addCell(const Cell &cell) {
//    cout << cell.getX() << endl;
}
