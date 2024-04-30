#pragma once

#include <gtest/gtest.h>
#include "functional/tools.h"

GTEST_TEST (multiarray, access_value) {

    Tools::multi_array <int, 3, 15> arr (0);
    EXPECT_EQ (arr.Value (2,7), 0);

    Tools::multi_array <int, 2, 3, 1> arr1 (0);
    for (int i = 0; i < arr1.Size (); i++) {
        arr1.Value (i) = i + 1;
    }
    EXPECT_EQ (arr1.Value(1,2,1), 5);

}
