#pragma once
#include <algorithm> 
#include <iostream>
#include <vector>
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

Node* find_node_to_ins(Node* root, int key) {
	if (key < root->_val) {
		if(root->_left == nullptr)
			return root;
		return find_node_to_ins(root->_left, key);
	}
	if (key > root->_val) {
		if(root->_right == nullptr)
			return root;
		return find_node_to_ins(root->_right, key);
	}
}

Node* copy_root(Node* root, int len) {
	int* buf = new int[len];
	get_data(root, buf);
	buf -= len;

	qsort(buf, len, sizeof(int), compare);

	Node* c_root = nullptr;

	if (len == 1) {
		c_root = new Node(buf[0]);
	}
	else if (len == 2) {
		c_root = new Node(buf[0]);
		if (buf[1] < buf[0]) {
			c_root->_left = new Node(buf[1]);
		}
		else {
			c_root->_right = new Node(buf[1]);
		}
	}
	else {
		size_t mid_ind = get_middle(len);

		c_root = new Node(buf[mid_ind]);
		left_branch(c_root, buf, mid_ind);
		right_branch(c_root, buf + mid_ind + 1, len - mid_ind - 1);

	}
	return c_root;
}

Node* find_node_parent(Node* root, int key) {
	if (root->_val == key) {
		return nullptr;
	}
	if (root->_left && key < root->_val) {
		if(root->_left->_val == key)
			return root;
		if (key < root->_left->_val)
			find_node_parent(root->_left, key);
		else if (root->_left) {
			if (key > root->_right->_val) {
				find_node_parent(root->_right, key);
			}
		}
	}
	else if (root->_right && key > root->_val) {
		if (root->_right->_val == key)
			return root;
		if (key > root->_right->_val)
			find_node_parent(root->_right, key);
	}
}

Node* find_node_and_parent(Node* root, int key, Node*& parent) {
	if (root == nullptr) {
		return nullptr;
	}
	if (root->_val == key) {
		return root;
	}
	parent = root;
	if (key < root->_val) {
		find_node_and_parent(root->_left, key, parent);
	}
	else {
		find_node_and_parent(root->_right, key, parent);
	}
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

		if (len == 1) {
			_root = new Node(set[0]);
			_len = 1;
		}
		else if (len == 2) {
			_root = new Node(set[0]);
			if (set[1] < set[0]) {
				_root->_left = new Node(set[1]);
			}
			else {
				_root->_right = new Node(set[1]);
			}
			_len = 2;
		}
		else {
			size_t mid_ind = get_middle(len);

			Node* root = new Node(set[mid_ind]);
			left_branch(root, set, mid_ind);
			right_branch(root, set + mid_ind + 1, len - mid_ind - 1);

			_len = len;
			_root = root;
		}
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

	int get_num_of_nodes(Node* root, int*& num) {
		if (root == nullptr) {
			return 0;
		}
		*num += 1;
		get_num_of_nodes(root->_left, num);
		get_num_of_nodes(root->_right, num);
	}

	Set(Node* root) {
		int* nums = new int(0);
		get_num_of_nodes(root, nums);
		_len = *nums;
		_root = copy_root(root, _len);
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
		if (_root == nullptr)
			std::cout << "";
		else {
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
	}

	bool contains(int key) {
		int* data = this->get_array();
		for (int i = 0; i < _len; i++) {
			if (key == data[i])
				return true;
		}
		return false;
	}

	void operator=(const Set& s) {
		this->_len = s._len;
		Node* root = copy_root(s._root, _len);
		this->_root = s._root;
	}

	bool insert(int key) {

		if (this->contains(key)) {
			return false;
		}

		Node* ins = find_node_to_ins(this->_root, key);
		Node* new_node = new Node(key);
		
		if (key < ins->_val) {
			ins->_left = new_node;
		}
		else {
			ins->_right = new_node;
		}

		return true;
	}

	bool erase(int key) {
		if (!this->contains(key)) {
			return false;
		}
		
		Node* parent = nullptr;
		

		Node* del = find_node_and_parent(_root, key, parent);

		if (parent == nullptr) {
			if (del->_left && del->_right) {
				del->_left->_right = del->_right;
				_root = del->_left;
			}
			else if (del->_left) {
				_root = del->_left;
			}
			else if(del->_right){
				_root = del->_right;
			}
			else {
				_root = nullptr;
			}
		}

		else if (del->_left && del->_right) {

			int* left_num = new int(0);
			int* left_data = new int[get_num_of_nodes(del->_left, left_num)];
			get_data(del->_left, left_data);
			left_data -= *left_num;
			

			int* right_num = new int(0);
			int* right_data = new int[get_num_of_nodes(del->_left, right_num) + *left_num];
			get_data(del->_right, right_data);
			right_data -= *right_num;

			for (int i = 0; i < *left_num; i++) {
				right_data[*right_num + i] = left_data[i];
			}
			int new_len = *left_num + *right_num;

			Set s(right_data, new_len);
			Node* new_root = copy_root(s._root, s._len);

			if (parent->_left == del) {
				parent->_left = new_root;
			}
			else {
				parent->_right = new_root;
			}

			remove_nodes(del);
		}

		else if (del->_left || del->_right) 
		{
			if (parent->_left)
			{
				if (parent->_left->_val == key)
				{
					if (del->_left)
					{
						parent->_left = del->_left;
					}
					else
					{
						parent->_left = del->_right;
					}
				}
				else
				{

					if (del->_left)
					{
						parent->_right = del->_left;
					}
					else
					{
						parent->_right = del->_right;
					}
				}
			}
			else {
				if (del->_left)
				{
					parent->_right = del->_left;
				}
				else
				{
					parent->_right = del->_right;
				}
			}
		}

		else if (!(del->_left && del->_right)) {
			if (parent->_left == del)
			{
				delete parent->_left;
				parent->_left = nullptr;
			}
			else
			{
				delete parent->_right;
				parent->_right = nullptr;
			}
		}
		_len -= 1;
		return true;
	}

};

std::vector<int> get_copies(std::vector<int> data) {
	size_t len = data.size();
	Set s(data.data(), len);
	int* copies = new int[len - s._len];
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (s.contains(data[i])) {
			s.erase(data[i]);
		}
		else {
			copies[j] = data[i];
			j++;
		}
	}
	std::vector<int>ans;
	for (int i = 0; i < j; i++)
		ans.push_back(copies[i]);
	return ans;
}

