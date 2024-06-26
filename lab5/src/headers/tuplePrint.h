#ifndef TUPLE_PRINT
#define TUPLE_PRINT

#include <iostream>
#include <ostream>
#include <tuple>
#include <iomanip>

template <typename TupleT, std::size_t... Is>
std::ostream& printTupleImp(std::ostream &os, const TupleT &tp, std::index_sequence<Is...>) {
    auto printElem = [&os](const auto& x, const size_t index) {
        if (index > 0) { os << std::setw(15); }
        os << x;
    };

    (printElem(std::get<Is>(tp), Is), ...);
    return os;
}

template <typename TupleT, size_t tupleSize = std::tuple_size<TupleT>::value>
std::ostream& operator <<(std::ostream &os, const TupleT &tp) {
    return printTupleImp(os, tp, std::make_index_sequence<tupleSize>{});
}

#endif
