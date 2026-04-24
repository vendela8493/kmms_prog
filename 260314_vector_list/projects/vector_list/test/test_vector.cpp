#include <gtest/gtest.h>

#include "vector.hpp"

using rva::Vector;

TEST(VectorTest, PushBack) {
    Vector<int> v;

    v.push_back(5);
    EXPECT_EQ(v.get_size(), 1);

    v.push_back(7);
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, HasItem) {
    Vector<int> v;

    v.push_back(5);
    v.push_back(5);
    v.push_back(7);

    EXPECT_TRUE(v.has_item(5));
    EXPECT_TRUE(v.has_item(7));
    EXPECT_FALSE(v.has_item(6));
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(5);
    v.push_back(7);

    EXPECT_TRUE(v.insert(0, 6));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(5));
    EXPECT_TRUE(v.has_item(7));
    EXPECT_TRUE(v.has_item(6));
}

TEST(VectorTest, RemoveFirst) {
    Vector<int> v;

    v.push_back(5);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);

    EXPECT_TRUE(v.remove_first(5));
    EXPECT_EQ(v.get_size(), 4);
    EXPECT_TRUE(v.has_item(5));

    EXPECT_TRUE(v.remove_first(7));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_FALSE(v.has_item(7));

    EXPECT_TRUE(v.has_item(6));
    EXPECT_TRUE(v.has_item(8));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}