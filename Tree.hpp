#include <iostream>

using namespace std;

struct node;
namespace ariel{
class Tree{
public:
	Tree();
	~Tree();

	void insert(int key);
	bool contains(int key);
	void print();
	int size();
	int root();
	int parent(int key);
	int left(int key);
	int right(int key);
	void remove(int key);

private:
	void destroy_Tree();
	node *search(int key);
	void destroy_Tree(node *leaf);
	void insert(int key, node *leaf);
	node *search(int key, node *leaf);
	void print(node *leaf);
	void remove(node* key_pointer);
	node *FindMin(node *curr);


	node *Root;
	int Size;
};
}
