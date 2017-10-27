#pragma once

#include <gtest/gtest.h>
#include <Generic/Serializers.h>

namespace Generic {

TEST(Serializer, Numeric)
{
    const char c = 'c';
    auto ba = toByteArray(c);
    char new_c;
    fromByteArray(ba.data(), new_c);
    EXPECT_EQ(c, new_c);

    const int i = 12345678;
    ba = toByteArray(i);
    int new_i;
    fromByteArray(ba.data(), new_i);
    EXPECT_EQ(i, new_i);
}

TEST(Serializers, Container)
{
    const std::vector<int> i_vec = { 1, 2, 3, 4, 5 };
    auto ba = toByteArray(i_vec);
    std::vector<int> new_vec;
    fromByteArray(ba.data(), new_vec);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(i_vec[i], new_vec[i]);
    }

    const std::set<char> c_set = { 'a', 'b', 'c' };
    ba = toByteArray(c_set);
    std::set<char> new_set;
    fromByteArray(ba.data(), new_set);
    EXPECT_EQ(c_set, new_set);
}

} // namespace Generic

