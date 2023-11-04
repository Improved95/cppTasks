#include "Life.h"

size_t ChangeField::getRealCoord(long long coord, const size_t maxCoord) const {
    if (coord < 0) {
        coord = maxCoord + coord;
    }
    return coord % maxCoord;
}

size_t ChangeField::countNeighborsForCell(const Cell &cell, const BlockOfCells *copyRoot, const Field &field) const {
    size_t neighbors = 0;
    size_t posX = 0, posY = 0;
    // проверяю три клетки, которые сверху той, для которой считаем соседей
    for (size_t i = 0; i < 3; i++) {
        posX = getRealCoord(cell.getX() - 1 + i, field.rows);
        posY = getRealCoord(cell.getY() + 1, field.columns);
        if (copyRoot->cellIsExistByCoordinate(posX, posY, field.rows, field.columns, 0)) {
            neighbors++;
        }
    }

    // побоками
    posX = getRealCoord(cell.getX() - 1, field.rows);
    if (copyRoot->cellIsExistByCoordinate(posX, cell.getY(), field.rows, field.columns, 0)) {
        neighbors++;
    }
    posX = getRealCoord(cell.getX() - 1, field.rows);
    if (copyRoot->cellIsExistByCoordinate(posX, cell.getY(), field.rows, field.columns, 0)) {
        neighbors++;
    }

    // снизу
    for (size_t i = 0; i < 3; i++) {
        posX = getRealCoord(cell.getX() - 1 + i, field.rows);
        posY = getRealCoord(cell.getY() - 1, field.columns);
        if (copyRoot->cellIsExistByCoordinate(posX, posY, field.rows, field.columns, 0)) {
            neighbors++;
        }
    }

    return neighbors;
}

void ChangeField::bypassingExistCells(BlockOfCells *original, const BlockOfCells *copyRoot, const Field &field) {
    size_t neighbors;
    for (auto it = original->getCellsList()->begin(); it != original->getCellsList()->end(); it++) {
        neighbors = countNeighborsForCell(*it, copyRoot, field);
        if (field.survivalRule.find(std::to_string(neighbors)) == std::string::npos) {
            original->getCellsList()->erase(it);
        }

        // для каждой существующей клетки прове
    }
}

void ChangeField::recursionCalcField(BlockOfCells *original, const BlockOfCells *copy, const BlockOfCells *copyRoot, const Field &field) {
    if (copy->getLeftNode() != nullptr) {
        recursionCalcField(original->getLeftNode(), copy->getLeftNode(), copyRoot, field);
    }
    if (copy->getRightNode() != nullptr) {
        recursionCalcField(original->getRightNode(), copy->getRightNode(), copyRoot, field);
    }
    if (copy->getLeftNode() == nullptr && copy->getRightNode() == nullptr) {
        bypassingExistCells(original, copyRoot, field);
    }
}

void ChangeField::calculateFieldByRules(Field &field) {
    BlockOfCells copyTree = BlockOfCells(field.getCellsList());
    ChangeField::recursionCalcField(&field.getCellsList(), &copyTree, &copyTree, field);
}
