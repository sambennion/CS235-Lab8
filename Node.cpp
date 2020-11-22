#include "Node.h"
#include <algorithm>

	int Node::getData() const{
        return this->data;
    }

	
	Node * Node::getLeftChild() const{
        return this->leftChild;
    }

	
	Node * Node::getRightChild() const{
        return this->rightChild;
    }

    int Node::getHeight()
	{
		int leftHeight = 0;
		int rightHeight = 0;

		if (leftChild != NULL)
		{
			leftHeight = leftChild->getHeight();
		}
		if (rightChild != NULL)
		{
			rightHeight = rightChild->getHeight();
		}
		return max(leftHeight, rightHeight) + 1;
	}
    int Node::getBalance()
	{
		int right;
		int left;

		if (rightChild != NULL)
		{
			right = rightChild->getHeight();
		}
		else{
		right = 0;

        }

		if (leftChild != NULL)
		{
			left = leftChild->getHeight();
		}
		else{
		    left = 0;
        }

        cout << "Right: " << right << " - Left: " << left << " = " << right-left << endl;
		return right - left;
	}