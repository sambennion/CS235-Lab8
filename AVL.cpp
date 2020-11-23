	#include "AVL.h"
	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	Node * AVL::getRootNode() const{
        return rootNode;
    }

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool AVL::add(int data){

        return addHelper(data, rootNode);
    }
    bool AVL::addHelper(int data, Node*& parentNode){

        if(parentNode == NULL){
            parentNode = new Node(data);

            return true;
        }
        else if(parentNode->data > data){
            if(addHelper(data, parentNode->leftChild)){
 
                rebalance(parentNode);
                return true;
            }
            else{
                return false;
            } 
        }
        else if(parentNode->data < data){
            if(addHelper(data, parentNode->rightChild)){
                rebalance(parentNode);

                return true;
            }
            else{
                return false;
            }
        } 
        else{
            return false;
        }
        
    }
	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool AVL::remove(int data){
        if(removeHelper(rootNode, data)){
            rebalance(rootNode);
            return true;
        }
        return false;
        return removeHelper(rootNode, data);
    }
    bool AVL::removeHelper(Node*& local_root,int data){
        if(local_root == NULL){
            return false;
        }
        else{
            if (data < local_root->getData()){
                if(removeHelper(local_root->leftChild, data)){
                    rebalance(local_root);
                    return true;
                }
                //return removeHelper(local_root->leftChild, data);
            }
            else if(data > local_root->getData()){

                if(removeHelper(local_root->rightChild, data)){
                    rebalance(local_root);
                    return true;
                }
                //return removeHelper(local_root->rightChild, data);
            }
            else{
                Node* old_root = local_root;
                if(local_root->getLeftChild() == NULL){
                    local_root = local_root->getRightChild();
                    
                    delete old_root;
                    rebalance(local_root);
                }
                else if(local_root->getRightChild() == NULL){
                    local_root = local_root->getLeftChild();
                    //rebalance(local_root->leftChild);
                    delete old_root;
                    rebalance(local_root);
                }
                else{
                    //replace(old_root, local_root->leftChild);
                    Node *ptr = local_root->leftChild;
                    while (ptr->rightChild != NULL) {						
                        ptr = ptr->rightChild;		
                        //rebalance(ptr);			
                        }
                    rebalance(ptr);					
                    local_root->data = ptr->getData();					
                    removeHelper(local_root->leftChild, local_root->data);
                }
                //rebalance(rootNode);
                return true;
            }
        }
    }

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void AVL::clear(){
        clearHelper(this->rootNode);
        rootNode = NULL;
    }
    void AVL::clearHelper(Node *&node){
        if(node != NULL){
            clearHelper(node->leftChild);
            clearHelper(node->rightChild);
            delete node;
        }
    }

    void AVL::rebalance(Node*& node){
        if (node == NULL){
		return;
        }
	    if (node->getBalance() > 1){
		    rebalanceLeft(node);
        }
	    else if (node->getBalance() < -1){
		    rebalanceRight(node);
        }

		rebalance(node->leftChild);
		rebalance(node->rightChild);
        
    }
    void AVL::rotateRight(Node*& node){
        Node* temp = node->leftChild;
	    node->leftChild = temp->rightChild;
	    temp->rightChild = node;
	    node = temp;
        
    }
    void AVL::rotateLeft(Node*& node){
        Node* temp = node->rightChild;
	    node->rightChild = temp->leftChild;
	    temp->leftChild = node;
	    node = temp;
        
    }
    void AVL::rebalanceRight(Node*& n) //right-right and right-left
{
	if (n == NULL)
		return;

		//cout << "balanceRight" << endl;
		if (n->leftChild->getBalance() >= 1)
		{
			rotateLeft(n->leftChild);
		}
		rotateRight(n);
}

void AVL::rebalanceLeft(Node*& n) //left-left and left-right
{
	if (n == NULL)
		return;
	//cout << "balanceLeft" << endl;
		if (n->rightChild->getBalance() <= -1)
		{
			rotateRight(n->rightChild);
		}
		rotateLeft(n);
}