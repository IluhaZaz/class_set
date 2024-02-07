#pragma once
#include <algorithm> 
#include <iostream>
#define max(a,b) (((a) > (b)) ? (a) : (b))

struct Node {
	int _val;
	Node* _left;
	Node* _right;

	Node(int val) :_val(val), _left(nullptr), _right(nullptr) {};
	Node(int val, Node* left, Node* right) :_val(val), _left(left), _right(right) {};
};

int compare(const void* x1, const void* x2)
{
	return (*(int*)x1 - *(int*)x2);             
}

size_t remove_duplicates(int* data, size_t len) {
	int j = 1;
	for (int i = 1; i < len; i++) {
		if (data[i] != data[i - 1]) {
			data[j] = data[i];
			j++;
		}
	}
	return j;
}

size_t get_middle(size_t len) {
	if (len == 1)
		return 1;
	return (int)(len / 2) ;
}

void right_branch(Node* root, int* data, size_t len);

void left_branch(Node* root, int* data, size_t len) {
	if (len == 1) {
		root->_left = new Node(data[0]);
	}
	else if (len == 2) {
		root->_left = new Node(data[1]);
		root->_left->_left = new Node(data[0]);
	}
	else {
		size_t mid_ind = get_middle(len);
		Node* new_root = new Node(data[mid_ind]);
		root->_left = new_root;
		left_branch(new_root, data, mid_ind);
		right_branch(new_root, data + mid_ind + 1, len - mid_ind - 1);
	}

}

void right_branch(Node* root, int* data, size_t len) {
	if (len == 1) {
		root->_right = new Node(data[0]);
	}
	else if (len == 2) {
		root->_right = new Node(data[0]);
		root->_right->_right = new Node(data[1]);
	}
	else {
		size_t mid_ind = get_middle(len);
		Node* new_root = new Node(data[mid_ind]);
		root->_right = new_root;
		left_branch(new_root, data, mid_ind);
		right_branch(new_root, data + mid_ind + 1, len - mid_ind - 1);
	}
}

void get_data(const Node* root, int*& buf) {
	if (root == nullptr) {
		return;
	}
	*buf = root->_val;
	buf++;
	get_data(root->_left, buf);
	get_data(root->_right, buf);
}

void remove_nodes(Node* root) {
	if (root == nullptr) {
		return;
	}
	remove_nodes(root->_left);
	remove_nodes(root->_right);
	delete root;
}


int help_print(Node* root, int raw, int curr) {

	if (root == nullptr) {
		return 0;
	}
	if (curr > raw) {
		return 0;
	}
	if (curr + 1 == raw) {
		if (root->_left)
		{
			std::cout << root->_left->_val << " ";
		}
		else
		{
			std::cout << "x ";
		}
		if (root->_right)
		{
			std::cout << root->_right->_val << " ";
		}
		else
		{
			std::cout << "x ";
		}
		return 1;
	}
	return help_print(root->_left, raw, curr + 1) + help_print(root->_right, raw, curr + 1);
}

class Set {
private:
	Node* _root;
public:
	size_t _len;
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
		
		size_t mid_ind = get_middle(len);

		Node* root = new Node(set[mid_ind]);
		left_branch(root, set, mid_ind);
		right_branch(root, set + mid_ind + 1, len - mid_ind - 1);

		_len = len;
		_root = root;
	}

	Set(const Set& s) {
		size_t len = s._len;
		int* buf = new int[len];
		get_data(s._root, buf);
		buf -= len;

		qsort(buf, len, sizeof(int), compare);

		size_t mid_ind = get_middle(len);

		Node* root = new Node(buf[mid_ind]);
		left_branch(root, buf, mid_ind);
		right_branch(root, buf + mid_ind + 1, len - mid_ind - 1);

		_len = len;
		_root = root;
		
	}

	~Set() {
		remove_nodes(_root);
	}

	int* get_array() {
		int* buf = new int[_len];
		get_data(_root, buf);
		buf -= _len;
		qsort(buf, _len, sizeof(int), compare);
		return buf;
	}

	int help_get_height(Node* root, int lvl) {
		if (root == nullptr) {
			return lvl - 1;
		}
		return max(help_get_height(root->_left, lvl + 1), help_get_height(root->_right, lvl + 1));

	}

	int get_height() {
		return help_get_height(_root, 1);
	}

	void print() {
		int printed = 0;
		int n = 2;
		int height = this->get_height();
		for (int i = 1; i < height; i++) {
			std::cout << " ";
		}
		std::cout << _root->_val << " " << std::endl;
		do {
			for (int i = n; i < height; i++) {
				std::cout << " ";
			}
			n++;
		} while (help_print(_root, n - 1, 1) && std::cout << std::endl);
	}

};



