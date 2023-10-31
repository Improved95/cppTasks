#include "Life.h"
#define TWO 2
BlockOfCells::BlockOfCells() {
    left = nullptr;
    right = nullptr;
}

BlockOfCells * BlockOfCells::constructorOfStruct(const size_t rows, const size_t columns, const size_t blockSize, const int mode) {
    if (mode == 0) {
        if (rows / TWO >= blockSize) {
            this->left = constructorOfStruct(rows / TWO, columns, blockSize, 1);
            this->right = constructorOfStruct(rows / TWO, columns, blockSize, 1);
        }
    } else {
        if (columns / TWO >= blockSize) {
            this->left = constructorOfStruct(rows, columns / TWO, blockSize, 0);
            this->right = constructorOfStruct(rows, columns / TWO, blockSize, 0);
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
