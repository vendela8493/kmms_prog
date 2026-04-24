#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using rva::DoublyLinkedList;

TEST(DoublyLinkedListTest, PushBack) {
	DoublyLinkedList<int> list;
	
	list.push_back(5);
	EXPECT_EQ(list.get_size(), 1);
	
	list.push_back(7);
	EXPECT_EQ(list.get_size(), 2);
}


TEST(DoublyLinkedListTest, HasItem) {
	DoublyLinkedList<int> list;
	
	list.push_back(5);
	list.push_back(7);
	
	EXPECT_TRUE(list.has_item(5));
	EXPECT_TRUE(list.has_item(7));
	EXPECT_FALSE(list.has_item(6));
}

TEST(DoublyLinkedListTest, RemoveFirst) {
	DoublyLinkedList<int> list;
	
	list.push_back(5);
	list.push_back(4);
	list.push_back(5);
	list.push_back(7);
	
	EXPECT_TRUE(list.remove_first(5));
	EXPECT_EQ(list.get_size(), 3);
	EXPECT_TRUE(list.has_item(5));
	
	EXPECT_TRUE(list.remove_first(4));
	EXPECT_EQ(list.get_size(), 2);
	EXPECT_FALSE(list.has_item(4));
	
	EXPECT_TRUE(list.has_item(5));
	EXPECT_TRUE(list.has_item(7));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}