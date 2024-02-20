#include "set.cpp"
#include <gtest/gtest.h>


TEST(SetTests, ConstructorCheck) {
	int* array = new int[12] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 12);
	int* data = s.get_array();
	for (int i = 0; i < s._len; i++) {
		EXPECT_EQ(array[i], data[i]);
	}	
}

TEST(SetTests, ConstructorCheck2) {
	int* array = new int[10] {2,2,1,3,4,5,4,6,7,7};
	int* unique_array = new int[7] {1, 2, 3, 4, 5, 6, 7};
	Set s(array, 10);
	int* data = s.get_array();
	for (int i = 0; i < s._len; i++) {
		EXPECT_EQ(unique_array[i], data[i]);
	}
}

TEST(SetTests, CopyConstructorCheck) {
	int* array = new int[12] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 12);
	Set s2(s);
	int* data2 = s2.get_array();
	for (int i = 0; i < s._len; i++) {
		EXPECT_EQ(array[i], data2[i]);
	}
}

TEST(SetTests, PrintCheck) {
	int* array = new int[12] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 12);
	s.print();
}

TEST(SetTests, ContainsCheck) {
	int* array = new int[12] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 12);
	EXPECT_TRUE(s.contains(1));
	EXPECT_TRUE(s.contains(12));
	EXPECT_TRUE(s.contains(7));
	EXPECT_FALSE(s.contains(0));
	EXPECT_FALSE(s.contains(13));
}

TEST(SetTests, OperatorCheck) {
	int* array = new int[12] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 12);
	Set s2 = s;
	int* data = s2.get_array();
	for (int i = 0; i < s._len; i++) {
		EXPECT_EQ(array[i], data[i]);
	}
}

TEST(SetTests, InsertCheck) {
	int* array = new int[11] {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 11);
	s.print();
	EXPECT_TRUE(s.insert(4));
	s.print();
}

TEST(SetTests, InsertCheck2) {
	int* array = new int[7] {2, 3 ,4, 9, 12, 3, -4};
	Set s(array, 7);
	s.print();
	EXPECT_TRUE(s.insert(1));
	s.print();
}

TEST(SetTests, InsertCheck3) {
	int* array = new int[7] {2, 3, 4, 9, 12, 3, -4};
	Set s(array, 7);
	s.print();
	EXPECT_FALSE(s.insert(-4));
	EXPECT_FALSE(s.insert(9));
	s.print();
}

TEST(SetTests, EraseCheck) {
	int* array = new int[5] {2, 3, 4, 5};
	Set s(array, 4);
	s.print();
	EXPECT_TRUE(s.erase(2));
	s.print();
}

TEST(SetTests, EraseCheck2) {
	int* array = new int[6] {2, 3, 4, 5, 6, 7};
	Set s(array, 6);
	s.print();
	EXPECT_TRUE(s.erase(6));
	s.print();
}

TEST(SetTests, EraseCheck3) {
	int* array = new int[12] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Set s(array, 12);
	s.print();
	EXPECT_TRUE(s.erase(2));
	s.print();
}

TEST(SetTests, GetCopiesCheck) {
	std::vector<int>a = std::vector<int>();
	int* array = new int[6] {1, 2, 3, 3, 4, 1};
	for (int i = 0; i < 6; i++)
		a.push_back(array[i]);
	std::vector<int> b = get_copies(a);
	for (int i = 0; i < b.size(); i++)
		std::cout << b[i] << " ";
}