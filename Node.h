#pragma once
#include "NodeInterface.h"

using namespace std;

class Node : public NodeInterface {
public:
	Node(int data_in, Node* left_in, Node* right_in);
	~Node();
	int getData();
	Node* getLeftChild();
	Node* getRightChild();
	Node* getParent();

	void set_data(int data_in);
	void set_left(Node* left);
	void set_right(Node* right);

	Node* left_point = NULL;
	Node* right_point = NULL;
	Node* parent_point = NULL;
	int node_data;

	////////////////////////////////
	int getHeight();
	int getHeightInput(Node* current_node);
};