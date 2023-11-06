#include "Life.h"

size_t ChangeField::getRealCoord(long long coord, const size_t maxCoord) const {
    if (coord < 0) {
        coord = maxCoord + coord;
    }
    return coord % maxCoord;
}

size_t ChangeField:: countNeighborsForCellByCoordinate(const size_t posX, const size_t posY, const BlockOfCells *copyRoot, const Field &field) const {
    size_t neighbors = 0;
    size_t newPosX = 0, newPosY = 0;
    // проверяю три клетки, которые сверху той, для которой считаем соседей
    for (size_t i = 0; i < 3; i++) {
        newPosX = getRealCoord(posX - 1 + i, field.rows);
        newPosY = getRealCoord(posY + 1, field.columns);
        if (copyRoot->cellIsExistByCoordinate(newPosX, newPosY, field.rows, field.columns, 0)) {
            neighbors++;
        }
    }

    // побоками
    newPosX = getRealCoord(posX - 1, field.rows);
    if (copyRoot->cellIsExistByCoordinate(newPosX, posY, field.rows, field.columns, 0)) {
        neighbors++;
    }
    newPosX = getRealCoord(posX + 1, field.rows);
    if (copyRoot->cellIsExistByCoordinate(newPosX, posY, field.rows, field.columns, 0)) {
        neighbors++;
    }

    // снизу
    for (size_t i = 0; i < 3; i++) {
        newPosX = getRealCoord(posX - 1 + i, field.rows);
        newPosY = getRealCoord(posY - 1, field.columns);
        if (copyRoot->cellIsExistByCoordinate(newPosX, newPosY, field.rows, field.columns, 0)) {
            neighbors++;
        }
    }

    return neighbors;
}

void ChangeField::bypassingNoExistCells(Cell &cell, BlockOfCells *originalRoot, const BlockOfCells *copyRoot, const Field &field) {
    size_t neighbors = 0;
    size_t posX = 0, posY = 0;
    // проверяю три клетки, которые сверху той, возле которой обрабатываем пустые
    for (size_t i = 0; i < 3; i++) {
        posX = getRealCoord(cell.getX() - 1 + i, field.rows);
        posY = getRealCoord(cell.getY() + 1, field.columns);
        neighbors = countNeighborsForCellByCoordinate(posX, posY, copyRoot, field);
        if (field.birthRule.find(std::to_string(neighbors)) != std::string::npos && !copyRoot->cellIsExistByCoordinate(posX, posY, field.rows, field.columns, 0)) {
            originalRoot->addCell(Cell(posX, posY), field.rows, field.columns, 0);
        }
    }

    // побоками
    posX = getRealCoord(cell.getX() - 1, field.rows);
    posY = cell.getY();
    neighbors = countNeighborsForCellByCoordinate(posX, posY, copyRoot, field);
    if (field.birthRule.find(std::to_string(neighbors)) != std::string::npos && !copyRoot->cellIsExistByCoordinate(posX, posY, field.rows, field.columns, 0)) {
        originalRoot->addCell(Cell(posX, posY), field.rows, field.columns, 0);
    }
    posX = getRealCoord(cell.getX() + 1, field.rows);
    posY = cell.getY();
    neighbors = countNeighborsForCellByCoordinate(posX, posY, copyRoot, field);
    if (field.birthRule.find(std::to_string(neighbors)) != std::string::npos  && !copyRoot->cellIsExistByCoordinate(posX, posY, field.rows, field.columns, 0)) {
        originalRoot->addCell(Cell(posX, posY), field.rows, field.columns, 0);
    }

    // снизу
    for (size_t i = 0; i < 3; i++) {
        posX = getRealCoord(cell.getX() - 1 + i, field.rows);
        posY = getRealCoord(cell.getY() - 1, field.columns);
        neighbors = countNeighborsForCellByCoordinate(posX, posY, copyRoot, field);
        if (field.birthRule.find(std::to_string(neighbors)) != std::string::npos  && !copyRoot->cellIsExistByCoordinate(posX, posY, field.rows, field.columns, 0)) {
            originalRoot->addCell(Cell(posX, posY), field.rows, field.columns, 0);
        }
    }
}

void ChangeField::bypassingExistCells(BlockOfCells *original, const BlockOfCells *copy, BlockOfCells *originalRoot, const BlockOfCells *copyRoot, const Field &field) {
    size_t neighbors = 0;
    set<Cell> *originalList = original->getCellsList();
    set<Cell> *copyList = copy->getCellsList();

    for (auto cell : *copyList) {
        neighbors = countNeighborsForCellByCoordinate(cell.getX(), cell.getY(), copyRoot, field);
        if (field.survivalRule.find(std::to_string(neighbors)) == std::string::npos) {
            originalList->erase(cell);
        }
        bypassingNoExistCells(cell, originalRoot, copyRoot, field);
    }
}

void ChangeField::recursionCalcField(BlockOfCells *original, const BlockOfCells *copy, BlockOfCells *originalRoot, const BlockOfCells *copyRoot, const Field &field) {
    if (copy->getLeftNode() != nullptr) {
        recursionCalcField(original->getLeftNode(), copy->getLeftNode(), originalRoot, copyRoot, field);
    }
    if (copy->getRightNode() != nullptr) {
        recursionCalcField(original->getRightNode(), copy->getRightNode(), originalRoot, copyRoot, field);
    }
    if (copy->getLeftNode() == nullptr && copy->getRightNode() == nullptr) {
        bypassingExistCells(original, copy, originalRoot, copyRoot, field);
    }
}

void ChangeField::calculateFieldByRules(Field &field) {
    BlockOfCells copyTree = BlockOfCells(field.getCellsList());
    ChangeField::recursionCalcField(&field.getCellsList(), &copyTree, &field.getCellsList(), &copyTree, field);
}
