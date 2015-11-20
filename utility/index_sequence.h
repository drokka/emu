//
// Thanks to Piotr Skotnicki - Stack Overflow
//

#ifndef FUNCTION_UTILITIES_INDEX_SEQUENCE_H
#define FUNCTION_UTILITIES_INDEX_SEQUENCE_H

#include <utility>

namespace doc {
    namespace  utility {

        template<std::size_t... Is>
        struct index_sequence {
        };

        template<std::size_t N, std::size_t... Is>
        struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {
        };

        template<std::size_t... Is>
        struct make_index_sequence_h<0, Is...> {
            using type = index_sequence<Is...>;
        };

        template<std::size_t N>
        using make_index_sequence = typename make_index_sequence_h<N>::type;

    }}
#endif //FUNCTION_UTILITIES_INDEX_SEQUENCE_H
