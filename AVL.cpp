	#include "AVL.h"
    //Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

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
            //rebalance(rootNode);
            //heightCounter = 0;
            return true;
        }
        else if(parentNode->data > data){
            if(addHelper(data, parentNode->leftChild)){
                //parentNode->balance--;
                //if (!isBalanced(parentNode)){
                //    parentNode->height++;
                //}
                //if(parentNode->balance < -1){
                //    rebalance(parentNode);
                //}
                rebalance(parentNode);
                //heightCounter++;
                return true;
            }
            else{
                return false;
            } 
        }
        else if(parentNode->data < data){
            if(addHelper(data, parentNode->rightChild)){
                //parentNode->balance++;
                rebalance(parentNode);
                //if(parentNode->balance > 1){
                //    rebalance(parentNode);
                //}
                //heightCounter++;
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
                }
                else if(local_root->getRightChild() == NULL){
                    local_root = local_root->getLeftChild();
                    delete old_root;
                }
                else{
                    //replace(old_root, local_root->leftChild);
                    Node *ptr = local_root->leftChild;
                    while (ptr->rightChild != NULL) {						
                        ptr = ptr->rightChild;					
                        }					
                    local_root->data = ptr->getData();					
                    removeHelper(local_root->leftChild, local_root->data);
                }
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
    //bool AVL::isBalanced(Node* node){
    //    return node->balance == 0;
    //}

    void AVL::rebalance(Node*& node){
        int left_balance;
        int right_balance;
        int root_balance = node->getBalance();
        if(node->leftChild != NULL){
            left_balance = node->leftChild->getBalance();
        }
        if(node->rightChild != NULL){
            right_balance = node->rightChild->getBalance();
        }
        //Left-Left
        if(root_balance == -2 && left_balance == -1){
            rotateRight(node);
        }
        //Left-Right
        else if(root_balance == -2 && left_balance == 1){
            rotateLeft(node->leftChild);
            rotateRight(node);
        }
        //Right-Right
        else if(root_balance == 2 && right_balance == 1){
            rotateLeft(node);
        }
        //Right-Left
        else if(root_balance == 2 && right_balance == -1){
            rotateRight(node->rightChild);
            rotateLeft(node);
        }
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