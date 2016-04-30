#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(int data_in, Node* left_in, Node* right_in) {
	node_data = data_in;
	left_point = left_in;
	right_point = right_in;
}

Node::~Node() {}

int Node::getData() {
	return node_data;
}

Node* Node::getLeftChild() {
	return left_point;
}

Node* Node::getRightChild() {
	return right_point;
}

Node* Node::getParent() {
	return parent_point;
}

//Extra functions to access data members.
void Node::set_data(int data_in) {
	node_data = data_in;
}

void Node::set_left(Node* left_in) {
	left_point = left_in;
}

void Node::set_right(Node* right_in) {
	right_point = right_in;
}

////////////////////////////////////////////////////////

int Node::getHeight() {
	return getHeightInput(this);
}

int Node::getHeightInput(Node* current) {
	
	//If passed in node is NULL.
	if (current == NULL) { return -1; }
	int left_height = getHeightInput(current->getLeftChild());
	int right_height = getHeightInput(current->getRightChild());
	int max_of = (left_height < right_height) ? right_height : left_height;
	return max_of + 1;
}