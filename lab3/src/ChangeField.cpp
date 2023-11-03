#include "Life.h"

void ChangeField::calculateFieldByRules(Field &field) {
    BlockOfCells copyTree = BlockOfCells(field.getCellsList());
    field.drawField();
    ChangeField::recursionCalcField(&field.getCellsList(), &copyTree, &copyTree, field);
}

void ChangeField::bypassingExistCells(BlockOfCells *original, const BlockOfCells *copy, const BlockOfCells *copyRoot, const Field &field) {
    size_t neighbors = 0;
    for(auto cell : *(copy->getCellsTree())) {
        for (size_t i = 0; i < 8; i++) {
            if (copyRoot->cellIsExist(cell, field.rows, field.columns, 0)) {
                neighbors++;
            }
        }
        if (!field.survivalRule.find(std::to_string(neighbors))) {
            original->getCellsTree()->erase(cell);
        }
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
        bypassingExistCells(original, copy, copyRoot, field);
    }
}


