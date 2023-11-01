#include <db/Predicate.h>

using namespace db;

Predicate::Predicate(int field, Op op, const Field *operand) 
    : field(field), op(op), operand(operand) {}

int Predicate::getField() const {
    return field;
}

Op Predicate::getOp() const {
    return op;
}

const Field *Predicate::getOperand() const {
    return operand;
}

bool Predicate::filter(const Tuple &t) const {
    const Field *tupleField = &t.getField(field); // Get pointer to the field
    return tupleField->compare(op, operand); // Call compare with operand pointer
}


