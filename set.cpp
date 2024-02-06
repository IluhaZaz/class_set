#pragma once
#include <algorithm> 
#include <iostream>

struct Node {
	int _val;
	Node* _left;
	Node* _right;

	Node(int val) :_val(val) {};
	Node(int val, Node* left, Node* right) :_val(val), _left(left), _right(right) {};
};

int compare(const void* x1, const void* x2)
{
	return (*(int*)x1 - *(int*)x2);             
}

size_t remove_duplicates(int* data, size_t len) {
	for (int i = 0; i < len; i++) {
		int j = i;
		while (data[i] == data[j + 1]) {
			j++;
		}
		for (int k = i + 1; k < len; k++) {
			data[k] = data[k + (j - i)];
		}
		len -= (j - i);
	}
	return len;
}

class Set {
private:
	Node* _root;
	size_t _len;
public:
	Set() : _root(nullptr), _len(0) {};
	Set(const int* data, size_t len) {
		int* buf = new int[len];
		for (int i = 0; i < len; i++) {
			buf[i] = data[i];
		}
		qsort(buf, len, sizeof(int), compare);
		
		len = remove_duplicates(buf, len);
		

		int* set = new int[len];
		for (int i = 0; i < len; i++) {
			set[i] = buf[i];
		}

		delete[] buf;
		
	}
};

