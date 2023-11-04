#include "Life.h"
#define DIVIDER 2

BlockOfCells::BlockOfCells() {
    this->left = nullptr;
    this->right = nullptr;
    this->cellsList = nullptr;
}

BlockOfCells::~BlockOfCells() {
    if (left != nullptr) {
        left->~BlockOfCells();
    }
    if (right != nullptr) {
        right->~BlockOfCells();
    }
//    if (left == nullptr && right == nullptr) {
//        delete cellsList;
//        cellsList = nullptr;
//    }
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
        node->cellsList = cellListptr;
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
        this->cellsList->insert(cell);
    }
}

void BlockOfCells::copyConstructor(const BlockOfCells *example, BlockOfCells *node) {
    if (example->left != nullptr) {
        node->left = new BlockOfCells();
        copyConstructor(example->left, node->left);
    }
    if (example->right != nullptr) {
        node->right = new BlockOfCells();
        copyConstructor(example->right, node->right);
    }
    if (example->left == nullptr && example->right == nullptr) {
        node->cellsList = new set<Cell>;
        *(node->cellsList) = *(example->cellsList);
    }
}

BlockOfCells::BlockOfCells(const BlockOfCells &tree) {
    this->left = nullptr;
    this->right = nullptr;
    this->cellsList = nullptr;
    copyConstructor(&tree, this);
}

bool BlockOfCells::cellIsExist(const Cell &cell, const size_t rows, const size_t columns, const int mode) const {
    if (mode == 0) {
        if (cell.getX() <= rows / DIVIDER) {
            if (this->left != nullptr) {
                return this->left->cellIsExist(cell, rows / DIVIDER, columns, 1);
            }
        } else {
            if (this->right != nullptr) {
                return this->right->cellIsExist(cell, rows / DIVIDER, columns, 1);
            }
        }
    } else {
        if (cell.getY() <= columns / DIVIDER) {
            if (this->left != nullptr) {
                return this->left->cellIsExist(cell, rows, columns / DIVIDER, 0);
            }
        } else {
            if (this->right != nullptr) {
                return this->right->cellIsExist(cell, rows, columns / DIVIDER, 0);
            }
        }
    }
//    if (this->left == nullptr && this->right == nullptr) {
        return (this->cellsList->find(cell) != this->cellsList->end());
//    }
}

bool BlockOfCells::cellIsExistByCoordinate(const size_t posX, const size_t posY, const size_t rows, const size_t columns, const int mode) const {
    if (mode == 0) {
        if (posX <= rows / DIVIDER) {
            if (this->left != nullptr) {
                return this->left->cellIsExistByCoordinate(posX, posY, rows / DIVIDER, columns, 1);
            }
        } else {
            if (this->right != nullptr) {
                return this->right->cellIsExistByCoordinate(posX, posY, rows / DIVIDER, columns, 1);
            }
        }
    } else {
        if (posY <= columns / DIVIDER) {
            if (this->left != nullptr) {
                return this->left->cellIsExistByCoordinate(posX, posY, rows, columns / DIVIDER, 0);
            }
        } else {
            if (this->right != nullptr) {
                return this->right->cellIsExistByCoordinate(posX, posY, rows, columns / DIVIDER, 0);
            }
        }
    }

    return (std::find_if(this->cellsList->begin(), this->cellsList->end(), [posX, posY](const Cell &cell) {
        return (cell.getX() == posX && cell.getY() == posY);
    }) != this->cellsList->end());
}
