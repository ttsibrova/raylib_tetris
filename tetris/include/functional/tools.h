#pragma once
#include <array>
#include <concepts>
#include <iterator>

namespace Tools {

template <std::integral Type, size_t R, size_t C>
class multi_array {
public:

    using value_type = Type;

    multi_array (Type val) {
        m_arr.fill (val);
    }

    Type& Value (size_t row, size_t col) {
        return m_arr[row * C + col];
    }

    Type Value (size_t row, size_t col) const {
        return m_arr[row * C + col];
    }

    void Fill (Type val) { m_arr.fill (val); }

    struct sub_array {
        sub_array (Type* ptr):
            m_ptr (ptr)
        {}

        Type& operator[] (size_t col) {
            return *(m_ptr + col);
        }
        
        Type operator[] (size_t col) const {
            return *(m_ptr + col);
        }

    private:
        Type* m_ptr;
    };

    sub_array operator[] (size_t row) {
        return sub_array (&m_arr[row * C]);
    }

    const sub_array operator[] (size_t row) const {
        return sub_array (&m_arr[row * C]);
    }


public:

    //class iterator: public std::iterator <std::input_iterator_tag, Type, R * C>
    //{
    //public:

    //private:
    //    Type* 
    //};


private:
    std::array <Type, R * C> m_arr;
};
}
