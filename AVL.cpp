#include "AVL.h"
using namespace std;

AVL::AVL() {};
AVL::~AVL() { clear(); };

Node* AVL::getRootNode() { return root; }

bool AVL::adder(Node* &current_node, int data) {
	//Empty spot in the right place is found.
	if (current_node == NULL) {
		//cout << "if0" << endl;
		current_node = new Node(data, NULL, NULL);
		//cout << "past add" << endl;

		if (has_changed_bool == 0) {
			has_changed_bool = 1;
			final_return = true;
		}
	}
	//Start trasversing tree.
	if (current_node->getData() < data) {
		//cout << "if1" << endl;
		adder(current_node->right_point, data);
		//Left heavy.
		if (lean(current_node) == -2) { rebalance_left(current_node); }
		//Right heavy.
		else if (lean(current_node) == 2) { rebalance_right(current_node); }
		//Balanced
		else {/*Do nothing.*/ }
		//After everything is done (recursed to root) we return our boolean.
		if (current_node == root) {
			return final_return;
		}
	}
	else if (current_node->getData() > data) {
		//cout << "if2" << endl;
		adder(current_node->left_point, data);
		//Left heavy.
		if (lean(current_node) == -2) { rebalance_left(current_node); }
		//Right heavy.
		else if (lean(current_node) == 2) { rebalance_right(current_node); }
		//Balanced
		else {/*Do nothing.*/ }
		if (current_node == root) {
			return final_return;
		}
	}
	//Data already there.
	else {
		//cout << "if3" << endl;
		//cout << "Exit with: " << data << endl;

		if (has_changed_bool == 0) {
			has_changed_bool = 1;
			final_return = false;
		}
	}
	return final_return;
}

bool AVL::add(int data) {
	//cout << "Adding: " << data << endl;
	final_return = false;
	has_changed_bool = 0;
	return adder(root, data);
}

bool AVL::remover(Node* &current_node, int data) {
	//cout << "REMOVING: " << data << endl;
	//Item is not found.
	if (current_node == NULL) {
		return false;
	}
	//Otherwise.
	if (current_node->getData() < data) {
		remover(current_node->right_point, data);
		//cout << "Lean for: " << current_node->getData() << " : ";
		//cout << lean(current_node) << endl;
		//Left heavy.
		if (lean(current_node) == -2) { rebalance_left(current_node); }
		//Right heavy.
		else if (lean(current_node) == 2) { rebalance_right(current_node); }
		//Balanced
		else {/*Do nothing.*/ }
	}
	else if (current_node->getData() > data) {
		remover(current_node->left_point, data);
		//cout << "Lean for: " << current_node->getData() << " : ";
		//cout << lean(current_node) << endl;
		//Left heavy.
		if (lean(current_node) == -2) { rebalance_left(current_node); }
		//Right heavy.
		else if (lean(current_node) == 2) { rebalance_right(current_node); }
		//Balanced
		else {/*Do nothing.*/ }
	}
	//Data found
	else {
		if (current_node->getRightChild() == NULL) {
			//cout << "if1" << endl;
			Node* temp = current_node;
			current_node = current_node->getLeftChild();
			delete temp;
			final_return = true;
		}
		else if (current_node->getLeftChild() == NULL) {
			//cout << "if2" << endl;
			Node* temp = current_node;
			current_node = current_node->getRightChild();
			delete temp;
			final_return = true;
		}
		//Two children.
		else {
			//cout << "if3" << endl;
			result = 0;
			current_node->set_data(iop_nater(current_node->left_point));
			//cout << "IS THIS 45?: " << current_node->getData() << endl;
			//Left heavy.
			if (lean(current_node) == -2) { rebalance_left(current_node); }
			//Right heavy.
			else if (lean(current_node) == 2) { rebalance_right(current_node); }
			//Balanced
			else {/*Do nothing.*/ }
			//cout << "Set data to: " << current_node->getData() << endl;
			final_return = true;
		}
	}
	return final_return;
}

//Balance is included in the iop_nater function not the remove function because this is where the node is actually removed.  Called when there are two children.
int AVL::iop_nater(Node* &iop_finder) {
	//cout << "RUNNING NATER" << endl;
	if (iop_finder->getRightChild() == NULL) {
		//cout << "RUNNING THIS IF" << endl;
		//When there is no right then it is the iop.
		result = iop_finder->getData();
		//cout << "IOP REMOVING THIS: " << iop_finder->node_data << endl;
		remover(iop_finder, iop_finder->node_data);
		if (iop_finder != NULL) {
			//cout << "CURRENT POSITION" << iop_finder->getData() << endl;
		}
	}
	//Otherwise continue moving right.
	else {
		iop_nater(iop_finder->right_point);
		//cout << "CHECK BALANCE OF: " << iop_finder->getData() << endl;
		//Left heavy.
		if (lean(iop_finder) == -2) { rebalance_left(iop_finder); }
		//Right heavy.
		else if (lean(iop_finder) == 2) { rebalance_right(iop_finder); }
		//Balanced
		else {/*Do nothing.*/}
	}
	return result;
}

bool AVL::remove(int data) {
	//cout << "================================Removing: " << data << endl;
	has_changed_bool = 0;
	final_return = false;
	return remover(root, data);
}

void AVL::clear() {
	//Removes root until root becomes NULL.
	while (root != NULL) { remove(root->node_data); }
}

void AVL::rebalance_left(Node*& local_root) {
	//cout << "REBALANCE LEFT: " << local_root->getData() << endl;
	// Cast local_root to an AVLNode pointer
	Node* AVL_local_root = local_root;
	// Obtain reference to the left child
	Node* left_child = local_root->left_point;
	// See whether left-right-heavy
	if (lean(left_child) > 0) {
		// Obtain a reference to the left-right child
		Node* left_right_child = left_child->right_point;
		rotate_left(local_root->left_point);
	}
	else { /*Left-Left case*/ }
	rotate_right(local_root);
}

void AVL::rebalance_right(Node*& local_root) {
	//cout << "REBALANCE RIGHT: " << local_root->getData() << endl;
	// Cast local_root to an AVLNode pointer
	Node* AVL_local_root = local_root;
	// Obtain reference to the right child
	Node* right_child = local_root->right_point;
	// See whether right-left-heavy
	if (lean(right_child) < 0) {
		// Obtain a reference to the right-left child
		Node* right_left_child = right_child->left_point;
		rotate_right(local_root->right_point);
	}
	else { /*Right-Right case*/ }
	rotate_left(local_root);
}

void AVL::rotate_right(Node *& current_node) {
	Node* temp = current_node->left_point;
	current_node->left_point = temp->right_point;
	temp->right_point = current_node;
	current_node = temp;
}

void AVL::rotate_left(Node *& current_node) {
	Node* temp = current_node->right_point;
	current_node->right_point = temp->left_point;
	temp->left_point = current_node;
	current_node = temp;
}

int AVL::lean(Node* local_root) {

	//Left heavy  = -2, Right heavy= +2.
	int left_weight;
	int right_weight;
	if (local_root->getLeftChild() == NULL) { left_weight = 0; }
	else { left_weight = local_root->getLeftChild()->getHeight() + 1; }
	if (local_root->getRightChild() == NULL) { right_weight = 0; }
	else { right_weight = local_root->getRightChild()->getHeight() + 1; }

	return right_weight - left_weight;
}

int AVL::dist_from_root(Node* leaf) {
	int count = 0;
	while (leaf->parent_point != NULL) {
		count++;
		leaf = leaf->parent_point;
	}
	return count;
}

void AVL::disp_heights() {
	disp_heights_inputs(root);
}

void AVL::disp_heights_inputs(Node* start) {
	if (start->left_point == NULL && start->right_point == NULL) {
		return;
	}
	else {
		if (start->left_point != NULL) {
			disp_heights_inputs(start->left_point);
		}
		if (start->right_point != NULL) {
			disp_heights_inputs(start->right_point);
		}
	}
}
