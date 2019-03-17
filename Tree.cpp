#include "Tree.hpp"
#include <iostream>

using namespace std;

struct node{
	int value;
	node *left;
	node *right;
	node *parent;
};

ariel::Tree::Tree(){
	Root = NULL;
	Size = 0;
}

ariel::Tree::~Tree(){
	destroy_Tree();
	Size = 0;
}

void ariel::Tree::destroy_Tree(node *leaf){
	if(leaf != NULL){
		destroy_Tree(leaf->left);
		destroy_Tree(leaf->right);
		delete leaf;
	}
}

void ariel::Tree::insert(int key, node *leaf){

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

node *ariel::Tree::search(int key){
	return search(key, Root);
}

void ariel::Tree::destroy_Tree(){
	destroy_Tree(Root);
}

void ariel::Tree::print(){
	print(Root);
	cout << "\n";
}

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
	return Root->value;
}

bool ariel::Tree::contains(int key){
	if (search(key) == NULL)
		return false;
	else return true;
}
int ariel::Tree::parent(int key){
	node* key_pointer = search(key);
	if (key_pointer == NULL) 
			throw "error no key";
	else if (key_pointer->parent==NULL)
			throw "error no parent";
 	else return key_pointer->parent ->value;
	
}
int ariel::Tree::left(int key){
	node* key_pointer = search(key);
	if (key_pointer == NULL) 
			throw "error no key";
	else if (key_pointer->left==NULL)
			throw "error no left";
	else return key_pointer->left ->value;

}
int ariel::Tree::right(int key){
	node* key_pointer = search(key);
	if (key_pointer == NULL) 
			throw "error no key";
	else if (key_pointer->right==NULL)
			throw "error no right";
	else return key_pointer->right ->value;

}

void ariel::Tree::remove(int key){
	node* key_pointer = search(key);
	
	if (key_pointer==NULL)
		throw "error";
	Size--;
	remove(key_pointer);
}
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
		node *temp = FindMax(key_pointer->left);
		int temp_val = temp->value;
		remove(temp);
		key_pointer->value = temp_val;
	}
}
node *ariel::Tree::FindMax(node *curr){
	if (curr==NULL) return NULL;
	while (curr->right != NULL){
		curr = 	curr->right;
	}
	return curr;
}

