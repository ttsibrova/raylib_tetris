#pragma once
#include <array>
#include <concepts>
#include <iomanip>
#include <iostream>
#include <iterator>


#include <vector>
namespace Tools {
template <class Type, size_t D0, size_t D1, size_t ... Dims>
class multi_array {
private:

    template <size_t Level = 0>
    constexpr size_t compute_idx (size_t D, std::convertible_to <size_t> auto ... Ds) const {
        if constexpr (Level + 1 < sizeof... (Dims) + 2) {
            return D * mplD_from <Level + 1> () + compute_idx <Level + 1> (Ds...);
        } else {
            return D;
        }
    }

    template <size_t Idx>
    static constexpr size_t mplD_from () {
        if constexpr (Idx < sizeof... (Dims) + 2) {
            return get_Di <Idx, 0, D0, D1, Dims...> () * mplD_from<Idx + 1> ();
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
            static_assert (sizeof... (Ds) + 1 == sizeof... (Dims) + 2, "Num of params is not equal to m_array dimensions num.");
            return m_arr[compute_idx (D, Ds...)];
        } else {
            return m_arr[D];
        }
    }

    const Type& Value (size_t D, std::convertible_to <size_t> auto ... Ds) const {
        if constexpr (sizeof... (Ds) != 0) {
            static_assert (sizeof... (Ds) + 1 == sizeof... (Dims) + 2, "Num of params is not equal to m_array dimensions num.");
            return m_arr[compute_idx (D, Ds...)];
        } else {
            return m_arr[D];
        }
    }

    static constexpr size_t Size() {
        return mplD_from<0> ();
    }

    static constexpr size_t DimSize() {
        return sizeof... (Dims) + 2;
    }

    template <size_t Idx>
    static constexpr size_t Dim() {
        static_assert (Idx < sizeof... (Dims) + 2, "Invalid dimension index. Should be less then DimSize().");
        return get_Di <Idx, 0, D0, D1, Dims...> ();
    }

    void Fill (Type val) {
        m_arr.fill (val);
    }

    template <typename FuncBefore,
              typename FuncAfter,
              typename FuncValue,
              size_t Level = 0>
    void RecurseApply (FuncBefore& FB, FuncAfter& FA, FuncValue& FV, std::convertible_to <size_t> auto ... Is) const {
        if constexpr (Level == DimSize() - 1) {
            for (size_t i = 0; i < Dim<Level> (); i++) {
                FV (Value (Is..., i));
            }
        } else {
            for (size_t i = 0; i < Dim<Level> (); i++) {
                FB();
                RecurseApply<FuncBefore, FuncAfter, FuncValue, Level+1> (FB, FA, FV, Is..., i);
                FA();
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const multi_array& other) {

        unsigned int tabNum = 0;
        auto arrDimSize = other.DimSize();
        auto Before = [&os, &tabNum, &arrDimSize]() {
            os << std::string (tabNum++, ' ') << "{";
            if (tabNum < arrDimSize-1) {
                os << std::endl;
            }
        };
        auto After = [&os, &tabNum, &arrDimSize]() {
            if (tabNum < arrDimSize-1) {
                os << std::string (tabNum-1, ' ');
            }
            os << "}\n"; tabNum--;
        };
        auto FuncVal = [&os] (const Type& val) {
            os << ' ' << val << ' ';
        };

        other.RecurseApply (Before, After, FuncVal);

        return os;
    }


private:
    std::array <Type, Size()> m_arr;
};

}
