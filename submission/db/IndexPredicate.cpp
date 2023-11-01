#include <db/IndexPredicate.h>

using namespace db;

IndexPredicate::IndexPredicate(Op op, const Field *fvalue) : op(op), fvalue(fvalue) {}

// Get the field from the predicate
const Field *IndexPredicate::getField() const {
    return fvalue;
}

// Get the operator from the predicate
Op IndexPredicate::getOp() const {
    return op;
}

// Check if two predicates are equal
bool IndexPredicate::operator==(const IndexPredicate &other) const {
    return (op == other.op) && (fvalue->compare(Op::EQUALS, other.fvalue));
}

std::size_t std::hash<IndexPredicate>::operator()(const IndexPredicate &ipd) const {
    // Compute the hash for the operation
    std::size_t opHash = std::hash<int>{}(static_cast<int>(ipd.getOp()));

    // Compute the hash for the Field's address (pointer)
    std::size_t fieldHash = std::hash<const Field*>{}(ipd.getField());

    // Combine the two hashes
    return opHash * fieldHash;
}

