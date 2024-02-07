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