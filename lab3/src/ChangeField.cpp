#include "Life.h"

void ChangeField::calculateFieldByRules(Field &field) {
    BlockOfCells copyTree = BlockOfCells(field.getCellsList());
//    ChangeField::recursionCalcField(&field.getCellsList(), &copyTree);
field.drawField();
}

void ChangeField::recursionCalcField(BlockOfCells *original, BlockOfCells *copy) {
    if (copy->getLeftNode() != nullptr) {
        recursionCalcField(original->getLeftNode(), copy->getLeftNode());
    }
}
