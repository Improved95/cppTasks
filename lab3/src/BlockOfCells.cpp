#include "Life.h"
#define DIVIDER 2

BlockOfCells::BlockOfCells() {
    this->left = nullptr;
    this->right = nullptr;
    this->cellsTree = nullptr;
}

BlockOfCells::~BlockOfCells() {
    if (left != nullptr) {
        left->~BlockOfCells();
    }
    if (right != nullptr) {
        right->~BlockOfCells();
    }
    // я не понимаю, удаляется ли то, что лежит по указателю cellsTree
}

BlockOfCells * BlockOfCells::constructorOfStruct(BlockOfCells *node, const size_t rows, const size_t columns, const size_t blockSize, const int mode) {
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
        node->cellsTree = cellListptr;
    }
    return node;
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
        this->cellsTree->insert(cell);
    }
}

bool BlockOfCells::cellIsExist() {
    return false;
}
