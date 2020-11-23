//YOU MAY NOT MODIFY THIS DOCUMENT
/*
*/
#pragma once

#include "Node.h"
#include "AVLInterface.h"
using namespace std;

class AVL: public AVLInterface {
protected:
    Node *rootNode = NULL;
	//int heightCounter = 0;
public:
	AVL() {}
	~AVL() {
        clear();
    }

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	Node * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);
    bool addHelper(int data, Node*& parentNode);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);
    bool removeHelper(Node*& local_root,int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
    void clearHelper(Node*& node);
    //bool isBalanced(Node* node);
    void rebalance(Node*& node);
    void rotateRight(Node*& node);
    void rotateLeft(Node*& node);
	void rebalanceRight(Node*& n);
	void rebalanceLeft(Node*& n);
};
