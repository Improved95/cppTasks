#include "Life.h"
#define DIVIDER 2
BlockOfCells::BlockOfCells() {
    left = nullptr;
    right = nullptr;
}

void BlockOfCells::constructorOfStruct(BlockOfCells *block, const size_t rows, const size_t columns, const size_t blockSize, const int mode) {
    if (mode == 0) {
        if (rows / DIVIDER >= blockSize) {
            block->left = new BlockOfCells();
            constructorOfStruct(block->left, rows / DIVIDER, columns, blockSize, 1);
            block->right = new BlockOfCells();
            constructorOfStruct(block->right, rows / DIVIDER, columns, blockSize, 1);
        }
    } else {
        if (columns / DIVIDER >= blockSize) {
            block->left = new BlockOfCells();
            constructorOfStruct(block->left, rows, columns / DIVIDER, blockSize, 0);
            block->right = new BlockOfCells();
            constructorOfStruct(block->right, rows, columns / DIVIDER, blockSize, 0);
        }
    }
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

}
