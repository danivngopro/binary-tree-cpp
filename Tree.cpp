#include "Tree.hpp"
#include <iostream>

using namespace std;

struct node{
	int value;
	node *left;
	node *right;
	node *parent;
};

ariel::Tree::Tree(){//constructor
	Root = NULL;
	Size = 0;
}

ariel::Tree::~Tree(){
	destroy_Tree();
	Size = 0;
}
//private function that help to delet a tree with the root leaf
void ariel::Tree::destroy_Tree(node *leaf){
	if(leaf != NULL){
		destroy_Tree(leaf->left);
		destroy_Tree(leaf->right);
		delete leaf;
	}
}
//private function to insert int into tree with the root leaf
void ariel::Tree::insert(int key, node *leaf){
	//needed to insert on the left side of leaf 
	if(key < leaf->value){
		if(leaf->left != NULL){
			insert(key, leaf->left);
		}else{
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
			leaf->left->parent = leaf;
		}
	//needed to insert on the right side of leaf 
	}else if(key >= leaf->value){
		if(leaf->right != NULL){
			insert(key, leaf->right);
		}else{
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
			leaf->right->parent = leaf;
		}
	}

}
//insert int into the Root
void ariel::Tree::insert(int key){
		if (search(key)!=NULL)
			throw runtime_error("error");
		Size = Size +1;
		if(Root != NULL){
			insert(key, Root);
		}else{
			Root = new node;
			Root->value = key;
			Root->left = NULL;
			Root->right = NULL;
			Root->parent = NULL;
		}
}
//search int in the tree with the root leaf and return a pointer to it's node
node *ariel::Tree::search(int key, node *leaf){
	if(leaf != NULL){
		if(key == leaf->value){
			return leaf;
		}
		if(key < leaf->value){
			return search(key, leaf->left);
		}else{
			return search(key, leaf->right);
		}
	}else{
		return NULL;
	}
}
//search int in the Root and return a pointer to it's node
node *ariel::Tree::search(int key){
	return search(key, Root);
}
//private function that help to delet all the tree
void ariel::Tree::destroy_Tree(){
	destroy_Tree(Root);
}
//print all the tree by inorder scanning
void ariel::Tree::print(){
	print(Root);
	cout << "\n";
}
//private function that print the tree with the root leaf by inorder scan
void ariel::Tree::print(node *leaf){
	if(leaf != NULL){
		print(leaf->left);
		cout << leaf->value << " ";
		print(leaf->right);
	}
}

int ariel::Tree::size(){
	return Size;
}

int ariel::Tree::root(){
	if (Root==NULL) throw "error";
	return Root->value;
}
//return true if "key" is in the tree
bool ariel::Tree::contains(int key){
	if (search(key) == NULL)
		return false;
	else return true;
}
//return the parent of "key" if exists otherwise throw exception
int ariel::Tree::parent(int key){
	node* key_pointer = search(key);
	if (key_pointer == NULL) 
			throw "error no key";
	else if (key_pointer->parent==NULL)
			throw "error no parent";
 	else return key_pointer->parent ->value;
	
}
//return the left child of "key" if exists otherwise throw exception
int ariel::Tree::left(int key){
	node* key_pointer = search(key);
	if (key_pointer == NULL) 
			throw "error no key";
	else if (key_pointer->left==NULL)
			throw "error no left";
	else return key_pointer->left ->value;

}
//return the right child of "key" if exists otherwise throw exception
int ariel::Tree::right(int key){
	node* key_pointer = search(key);
	if (key_pointer == NULL) 
			throw "error no key";
	else if (key_pointer->right==NULL)
			throw "error no right";
	else return key_pointer->right ->value;

}
//remove number "key" by the rules of binary tree
void ariel::Tree::remove(int key){
	node* key_pointer = search(key);
	
	if (key_pointer==NULL)
		throw "error";
	Size--;
	remove(key_pointer);
}
//remove the node "key_pointer" by the rules of binary tree
void ariel::Tree::remove(node* key_pointer){
	// Case 1:  No child
	if(key_pointer->left == NULL && key_pointer->right == NULL) 
	{ 
		node *father = key_pointer->parent;
		if (father==NULL){
			Root = NULL;
		}else if (father->value <= key_pointer->value)
				father->right = NULL;
		else father->left = NULL;
		
		delete key_pointer;
	}	
	//Case 2: One child 
	else if(key_pointer->left == NULL) {
		node *father = key_pointer->parent;
		if (father==NULL){
			Root = key_pointer->right;
			Root->parent = NULL;
		}
		else if (father->value <= key_pointer->value){
				father->right = key_pointer->right;
				key_pointer->right->parent = father;
		}
		else {
			father->left = key_pointer->right;
			key_pointer->right->parent = father;
		}
		delete key_pointer;
	}
	else if(key_pointer->right == NULL) {
		node *father = key_pointer->parent;
		if (father==NULL){
			Root = key_pointer->left;
			Root->parent = NULL;
		}else if (father->value <= key_pointer->value){
			father->right = key_pointer->left;
			key_pointer->left->parent = father;
		}
		else {
			father->left = key_pointer->left;
			key_pointer->left->parent = father;
		}
		delete key_pointer;
	}
	// case 3: 2 children
	else { 
		node *temp = FindMin(key_pointer->right);
		int temp_val = temp->value;
		remove(temp);
		key_pointer->value = temp_val;
	}
}
//private function that find the max value in the tree with the root "curr"
node *ariel::Tree::FindMin(node *curr){
	if (curr==NULL) return NULL;
	while (curr->left != NULL){
		curr = 	curr->left;
	}
	return curr;
}

