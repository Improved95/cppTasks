#include "Life.h"

BlockOfCells::

BlockOfCells::BlockOfCells() {
    left = nullptr;
    right = nullptr;
}

BlockOfCells * BlockOfCells::constructorOfStruct(const size_t rows, const size_t columns, const size_t blockSize, const int mode) {
//    const size_t binary = 2;
//    const size_t quantBlocksInRow = (rows / binary) + (rows % binary);
//    const size_t quantBlocksInColums = (columns / binary) + (columns % binary);

    if (mode == 0) {
        if (rows / 2 >= blockSize) {
            this->left = constructorOfStruct(rows / 2, columns, blockSize, 1);
            this->right = constructorOfStruct(rows / 2, columns, blockSize, 1);
        }
    } else {
        if (columns / 2 >= blockSize) {
            this->left = constructorOfStruct(rows, columns / 2, blockSize, 0);
            this->right = constructorOfStruct(rows, columns / 2, blockSize, 0);
        }
    }
    BlockOfCells *ptrBlock = new BlockOfCells();
    return ptrBlock;
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
