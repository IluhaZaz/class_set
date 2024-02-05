#pragma once
#include <algorithm> 

class Set {
private:
	int* _data;
	size_t _len;
public:
	Set() : _data(nullptr), _len(0) {};
	Set(const int& data, size_t len) {
		int* buf = new int[len];
		
	}
};