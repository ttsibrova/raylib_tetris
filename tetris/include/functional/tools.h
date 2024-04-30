#pragma once
#include <array>
#include <concepts>
#include <iterator>


#include <vector>
namespace Tools {
template <class Type, size_t D0, size_t D1, size_t ... Dim>
class multi_array {
private:

    template <size_t Level = 0>
    constexpr size_t compute_idx (size_t D, std::convertible_to <size_t> auto ... Ds) {
        if constexpr (sizeof... (Ds) > Level + 1) {
            return D * mplD_from <Level + 1> () + compute_idx <Level + 1> (Ds...);
        } else {
            return 1;
        }
    }

    template <size_t Idx>
    static constexpr size_t mplD_from () {
        if constexpr (Idx < sizeof... (Dim) + 2) {
            return get_Di <Idx, 0, D0, D1, Dim...> ()* mplD_from<Idx + 1> ();
        } else {
            return 1;
        }
    }

    template <size_t Target, size_t Level, size_t D, size_t... Ds>
    static constexpr size_t get_Di () {
        if constexpr (Level == Target) {
            return D;
        } else {
            return get_Di <Target, Level + 1, Ds...> ();
        }
    }

public:

    multi_array (Type val) {
        m_arr.fill (val);
    }

    Type& Value (size_t D, std::convertible_to <size_t> auto ... Ds) {
        if constexpr (sizeof... (Ds) != 0) {
            static_assert (sizeof... (Ds) + 1 == sizeof... (Dim) + 2, "Num of params is not equal to m_array dimensions num.");
            return m_arr[compute_idx (D, Ds...)];
        } else {
            return m_arr[D];
        }
    }
    
    const Type& Value (size_t D, std::convertible_to <size_t> auto ... Ds) const {
        if constexpr (sizeof... (Ds) != 0) {
            static_assert (sizeof... (Ds) + 1 == sizeof... (Dim) + 2, "Num of params is not equal to m_array dimensions num.");
            return m_arr[compute_idx (D, Ds...)];
        } else {
            return m_arr[D];
        }
    }

    static constexpr size_t Size() {
        return mplD_from<0> ();
    }


private:
    std::array <Type, Size()> m_arr;
};

}
