#include "BasicTree.h"
#include <queue>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class val_not_found{};

BasicTree::BasicTree() : root{nullptr} {}
BasicTree::BasicTree(int i) : root{new Node(i)} {}

void BasicTree::insert(int val)
{
    // 1. Check whether the tree is empty or not;
	// 2a. if the tree is empty set root equal to a new node with the passed value and return.
	if(root == nullptr) {
		root = new Node(val);
	}
    // 2b. Otherwise, find the proper location to tag on a new node storing the passed value on to the tree; be sure to set this node's Node* parent to the node preceding it in the tree.
	else{
		Node *curr = root;
		Node *parent = nullptr;
		while(curr != nullptr){
			parent = curr;
			if(val < curr->data)
				curr = curr->left;
			else{
				curr = curr->right;
			}
		}
		if(val < parent->data){
			parent->left = new Node(val); 
			curr = parent->left;
			curr->parent = parent;
		}
		else{
			parent->right = new Node(val);
			curr = parent->right;
			curr->parent = parent;
		}
	}
}

ostream& BasicTree::in_order(Node *n, ostream &os)
{
    // 1. Traverse the left subtree by visiting node to the left of the current node.
	if(n == nullptr)
		return os;
    // 2. Visit the current node; insert its value to the stream.
	in_order(n->left, os);
	os << n->data << " ";
    // 3. Traverse the right subtree by visiting node to the right of the current node.
	in_order(n->right, os);
    // 4. Return the stream
    return os;
}

ostream& BasicTree::post_order(Node *n, ostream &os)
{
    // 1. Traverse the left subtree by visiting node to the left of the current node.
	if(n == nullptr)
		return os;
    // 2. Traverse the right subtree by visiting the node to the right of the current node.
	post_order(n->left, os);
	post_order(n->right, os);
    // 3. Visit the current node; insert its value to the stream
	os << n->data << " ";
    // 4. Return the stream
    return os;
}

ostream& BasicTree::pre_order(Node *n, ostream &os)
{
	if(n == nullptr)
		return os;
    // 1. Visit the current node; insert its value to the stream.
	os << n->data << " ";
    // 2. Traverse the left subtree by visiting node to the left of the current node.
	pre_order(n->left, os);
    // 3. Traverse the right subtree by visiting the node to the right of the current node.
	pre_order(n->right, os);
    // 4. Return the stream
    return os;
}

int const& BasicTree::find(int val){
	Node* curr = root;
	Node *parent = nullptr;
	// Check to see if the tree is empty
	if(root == nullptr)
		throw val_not_found{};
	else{
		// 1. Search the tree for node containing val ...
		// 2a. If such node is found, return a constant reference to the int object contained in that node (to do this, simply return curr->val);
		// 2b. Otherwise, if such a node is not found, throw val_not_found{};
		while(curr != nullptr){
			parent = curr;
			
			if(val == curr->data)
				return curr->data;
			if(val < curr->data)
				curr = curr->left;
			else
				curr = curr->right;
		}
		/* if(val < parent->data){
			curr = parent->left;
			curr->parent = parent;
		}
		else{
			curr = parent->right;
			curr->parent = parent;
		}
		if(val == curr->data)
			return curr->data;
		else */
			throw val_not_found{};	
	
	}
}

///////////////////////////////////////////////////////////////////////////////
// operator<< support
///////////////////////////////////////////////////////////////////////////////
stringstream& BasicTree::to_sstream(Node *n, int depth, string s, stringstream& os) const
{
    if (n==nullptr) {
        os << "Empty" << endl;
        return os;
    }
    os << "("<<n->data<<") Address: " << n << " Parent: " << n->parent << "\n";
    os << s << " `--[L]";
    s += " |  ";
    if (n->left)
        to_sstream(n->left, depth + 1, s, os);
    else
        os <<"nullptr\n";
    s.erase(s.end() - 4, s.end());

    os << s << " `--[R]";
    s += "    ";
    if (n->right)
        to_sstream(n->right, depth + 1, s, os);
    else 
        os <<"nullptr\n";
    s.erase(s.end() - 4, s.end());
    return os;
}

ostream& operator<<(ostream& os, BasicTree const& bt)
{
    os << bt.to_str();
    return os;
} 
