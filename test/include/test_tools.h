#pragma once

#include <random>
#include <gtest/gtest.h>
#include "functional/tools.h"

GTEST_TEST (multiarray, access_value) {

    Tools::multi_array <int, 3, 15> arr (0);
    EXPECT_EQ (arr.Value (2,7), 0);

    std::cout << arr;

    Tools::multi_array <int, 2, 3, 1> arr1 (0);
    for (int i = 0; i < arr1.Size (); i++) {
        arr1.Value (i) = i + 1;
    }
    for (size_t i = 0; i < arr1.Dim<0> (); i++) {
        for (size_t j = 0; j < arr1.Dim<1> (); j++) {
            for (size_t k = 0; k < arr1.Dim<2> (); k++) {
                arr1.Value (i,j,k);
            }
        }
    }
    EXPECT_EQ (arr1.Value(1,1,0), 5);
}

GTEST_TEST (multiarray, iteration) {
    Tools::multi_array <int, 4, 6, 7, 9> arr (0);

    std::random_device r;
    std::uniform_int_distribution <int> val_dist (-100, 100);
    std::mt19937 e (254089);

    size_t idx = 0;
    for (size_t i = 0; i < arr.Dim<0>(); i++) {
        for (size_t j = 0; j < arr.Dim<1>(); j++) {
            for (size_t k = 0; k < arr.Dim<2>(); k++ ) {
                for (size_t l = 0; l < arr.Dim<3>(); l++) {
                    arr.Value (i,j,k,l) = val_dist(e);
                    EXPECT_EQ (arr.Value (idx++), arr.Value (i, j, k, l));
                }
            }
        }
    }

    std::cout << arr;
}
