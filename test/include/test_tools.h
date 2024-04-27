#pragma once

#include <gtest/gtest.h>
#include "functional/tools.h"

GTEST_TEST (multiarray, access_value) {

    Tools::multi_array <int, 3, 15> arr (0);
    EXPECT_EQ (arr[2][7], 0);
    arr.Fill (4);
    EXPECT_EQ (arr[1][4], 4);
    arr[1][4] = 5;
    EXPECT_EQ (arr.Value (1,4), arr[1][4]);
}
