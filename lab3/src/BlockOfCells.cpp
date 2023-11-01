#include "Life.h"
#define DIVIDER 2

BlockOfCells::BlockOfCells() {
    this->left = nullptr;
    this->right = nullptr;
    this->cellsList = nullptr;
}

BlockOfCells * BlockOfCells::constructorOfStruct(BlockOfCells *node, const size_t rows, const size_t columns, const size_t blockSize, const int mode) {
//    if (mode == 0) {
//        if (rows / DIVIDER >= blockSize) {
//            block->left = new BlockOfCells();
//            constructorOfStruct(block->left, rows / DIVIDER, columns, blockSize, 1);
//            block->right = new BlockOfCells();
//            constructorOfStruct(block->right, rows / DIVIDER, columns, blockSize, 1);
//        }
//    } else {
//        if (columns / DIVIDER >= blockSize) {
//            block->left = new BlockOfCells();
//            constructorOfStruct(block->left, rows, columns / DIVIDER, blockSize, 0);
//            block->right = new BlockOfCells();
//            constructorOfStruct(block->right, rows, columns / DIVIDER, blockSize, 0);
//        }
//    }
//    set<Cell> setObj;
//    this->cellsSet = &setObj;

    if (mode == 0) {
        if (rows / DIVIDER >= blockSize) {
            BlockOfCells *leftNode = new BlockOfCells();
            node->left = constructorOfStruct(leftNode, rows / DIVIDER, columns, blockSize, 1);
            BlockOfCells *rightNode = new BlockOfCells();
            node->right = constructorOfStruct(rightNode, rows / DIVIDER, columns, blockSize, 1);
        }
    } else {
        if (columns / DIVIDER >= blockSize) {
            BlockOfCells *leftNode = new BlockOfCells();
            node->left = constructorOfStruct(leftNode, rows, columns / DIVIDER, blockSize, 1);
            BlockOfCells *rightNode = new BlockOfCells();
            node->right = constructorOfStruct(rightNode, rows, columns / DIVIDER, blockSize, 1);
        }
    }

    if (node->left == nullptr && node->right == nullptr) {
        set<Cell> *cellListptr = new set<Cell>;
        node->cellsList = cellListptr;
    }
    return node;
}

BlockOfCells::~BlockOfCells() {
    if (left != nullptr) {
       ( *left).~BlockOfCells();
    }
    if (right != nullptr) {
        (*right).~BlockOfCells();
    }
}

void BlockOfCells::addCell(const Cell &cell, const size_t rows, const size_t columns, const int mode) {
    if (mode == 0) {
        if (cell.getX() <= rows / DIVIDER) {
            if (this->left != nullptr) {
                this->left->addCell(cell, rows / DIVIDER, columns, 1);
            }
        } else {
            if (this->right != nullptr) {
                this->right->addCell(cell, rows / DIVIDER, columns, 1);
            }
        }
    } else {
        if (cell.getY() <= columns / DIVIDER) {
            if (this->left != nullptr) {
                this->left->addCell(cell, rows, columns / DIVIDER, 0);
            }
        } else {
            if (this->right != nullptr) {
                this->right->addCell(cell, rows, columns / DIVIDER, 0);
            }
        }
    }
    if (this->left == nullptr && this->right == nullptr) {
        this->cellsList->insert(cell);
    }
}
