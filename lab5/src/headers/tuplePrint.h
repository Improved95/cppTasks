#ifndef TUPLE_PRINT
#define TUPLE_PRINT

#include <iostream>
#include <ostream>
#include <tuple>

template <typename TupleT, size_t... Is>
std::ostream& printTupleImp(std::ostream& os, const TupleT& tp, std::index_sequence<Is...>) {
    size_t index = 0;
    auto printElem = [&index, &os](const auto& x) {
        if (index++ > 0) { os << " "; }
        os << x;
    };

    (printElem(std::get<Is>(tp)), ...);
    return os;
}

template <typename TupleT, size_t TupSize = std::tuple_size<TupleT>::value>
std::ostream& operator <<(std::ostream& os, const TupleT& tp) {
    return printTupleImp(os, tp, std::make_index_sequence<TupSize>{});
}

#endif
