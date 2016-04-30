#pragma once
#include "Node.h"
#include "AVLInterface.h"
#include <iostream>

class AVL : public AVLInterface {
public:
	AVL();
	~AVL();
	Node* getRootNode();
	bool add(int data);
	bool remove(int data);
	bool adder(Node* &current_node, int data);
	bool remover(Node* &current_node, int data);
	void clear();
	int iop_nater(Node* &iop_finder);

	void rebalance_left(Node*& local_root);
	void rebalance_right(Node*& local_root);
	void rotate_right(Node* &current_node);
	void rotate_left(Node* &current_node);
	int lean(Node* local_root);

	//Debug.
	int dist_from_root(Node* leaf);
	void disp_heights();
	void disp_heights_inputs(Node* start);

private:
	Node* root = NULL;
	bool final_return = false;
	int has_changed_bool = 0;
	int result = 0;
	//This node pointer keeps track of the position when trasversing tree.
};